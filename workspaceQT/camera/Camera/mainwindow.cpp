#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGridLayout>
#include <QtMultimedia>
#include <QMessageBox>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <capturethread.h>
#include <zbar.h>
#include <opencv2/core.hpp>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , fileMenu(nullptr)
    , capturer(nullptr)
{
    initUI();
    data_lock = new QMutex;
}

MainWindow::~MainWindow()
{
}

void MainWindow::initUI()
{
    this -> resize(1000,800);

    //setup menu bar:

    fileMenu = menuBar() -> addMenu("&File");

    QGridLayout *main_layout = new QGridLayout();


    imageScene = new QGraphicsScene(this);
    imageView = new QGraphicsView(imageScene);
    //add widget( row 0, collumn 0, span 12 row, span 1 collumn)
    main_layout ->addWidget(imageView, 0, 0, 12, 1);



    QGridLayout *toolLayout = new QGridLayout();
    main_layout ->addLayout(toolLayout, 12,  0 , 1, 1);

    monitorCheckBox = new QCheckBox(this);
    monitorCheckBox ->setText("Monitor On/Off");
    toolLayout -> addWidget(monitorCheckBox, 0, 0);

    recordPushButton = new QPushButton(this);
    recordPushButton -> setText("Record");
    toolLayout -> addWidget(recordPushButton, 0, 1, Qt::AlignHCenter);
    toolLayout -> addWidget(new QLabel(this), 0, 2);




    dataBrowser = new QTextBrowser(this);
    main_layout -> addWidget(dataBrowser, 13, 0 , 4, 1);

    // create the new widget to use main_layout, set this new widget in the mainwindows w func setCentralWidget();
    QWidget *widget = new QWidget();
    widget -> setLayout(main_layout);
    setCentralWidget(widget);


    mainStatusBar = statusBar();
    mainStatusLabel = new QLabel(mainStatusBar);
    mainStatusBar -> addPermanentWidget(mainStatusLabel);
    mainStatusLabel -> setText("Application is ready");

    createActions();


}

void MainWindow::createActions()
{
    cameraInfoAction = new QAction("Camera &Information", this);
    fileMenu -> addAction(cameraInfoAction);
    openCameraAction = new QAction("&Open Camera", this);
    fileMenu->addAction(openCameraAction);
    calcFPSAction = new QAction("&Calculate FPS", this);
    fileMenu->addAction(calcFPSAction);
    exitAction = new QAction("E&xit", this);
    fileMenu->addAction(exitAction);

    connect(exitAction, SIGNAL(triggered(bool)), QApplication::instance(), SLOT(quit()));
    connect(cameraInfoAction, SIGNAL(triggered(bool)), this, SLOT(showCameraInfo()));
    connect(openCameraAction, SIGNAL(triggered(bool)), this, SLOT(openCamera()));
    connect(calcFPSAction, SIGNAL(triggered(bool)), this, SLOT(calculateFPS()));

}

void MainWindow::showCameraInfo()
{
 const QList<QCameraDevice> cameras =  QMediaDevices::videoInputs();
 QString info = QString("Available Cameras: \n");

 foreach (const QCameraDevice &cameraInfo, cameras)
 {
     info += "id camera: " + cameraInfo.id();
     info += cameraInfo.description() + "\n" ;
 }
 QMessageBox::information(this, "Cameras", info);
}

void MainWindow::openCamera()
{
    if(capturer != nullptr) {
        // if a thread is already running, stop it
        capturer->setRunning(false);
        disconnect(capturer, &CaptureThread::frameCapture, this, &MainWindow::updateFrame);
        connect(capturer, &CaptureThread::finished, capturer, &CaptureThread::deleteLater);
    }


    int camID = 0;
    capturer = new CaptureThread(camID, data_lock);
    //when the CaptureThread::frameCaptured signal is emitted,
    //the MainWindow::updateFrame slot (method) will be called with the same argument
    //that's used when the signal is emitted.
    connect(capturer, &CaptureThread::frameCapture, this, &MainWindow::updateFrame);
    capturer -> start(); //start the thread
    mainStatusLabel -> setText(QString("Capturing Camera %1").arg(camID));
}

void MainWindow::updateFrame(cv::Mat *mat)
{
    //using QMutex to protect the pointer "frame", 1 moment, 1 thread can access that pointer
    data_lock->lock();
    currentFrame = *mat;
    data_lock->unlock();
    zbar::ImageScanner scanner;
    cv:: Mat  grey;
    cvtColor(currentFrame,grey, cv::COLOR_BGR2GRAY);
    int width = currentFrame.cols;
    int height = currentFrame.rows;
    uchar *raw = (uchar *)grey.data;
    zbar:: Image image(width, height, "Y800", raw, width * height);
    int n =scanner.scan(image);
    for(zbar::Image::SymbolIterator symbol = image.symbol_begin();symbol != image.symbol_end();++symbol)
    {
        std::vector<cv::Point> vp;
        QString text = QString::fromStdString(symbol ->get_data());
        dataBrowser ->insertPlainText(text + "\n");
        int n = symbol->get_location_size();
        for(int i=0;i<n;i++)
            {
            vp.push_back(cv::Point(symbol->get_location_x(i),symbol->get_location_y(i)));
            }
        cv::RotatedRect r = minAreaRect(vp);
        cv::Point2f pts[4];
        r.points(pts);
        for(int i=0;i<4;i++)
            {
            line(currentFrame,pts[i],pts[(i+1)%4],cv::Scalar(255,0,0),3);
            }
    }


    QImage frame(
        currentFrame.data,
        currentFrame.cols,
        currentFrame.rows,
        currentFrame.step,
        QImage::Format_RGB888);
    QPixmap image1 = QPixmap::fromImage(frame);

    imageScene->clear();
    imageScene->addPixmap(image1);
    imageScene->update();
    imageView->setSceneRect(image1.rect());

}

void MainWindow::calculateFPS()
{

}

void MainWindow::updateFPS(float)
{

}

void MainWindow::recordingStartStop()
{

}

void MainWindow::appendSavedVideo(QString name)
{

}

void MainWindow::updateMonitorStatus(int status)
{

}

