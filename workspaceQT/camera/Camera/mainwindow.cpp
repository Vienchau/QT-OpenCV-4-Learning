#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGridLayout>
#include <QtMultimedia>
#include <QMessageBox>

#include <capturethread.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , fileMenu(nullptr)
    , capturer(nullptr)
    //inherited class, parent kyword?
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



    saved_list = new QListView(this);
    main_layout -> addWidget(saved_list, 13, 0 , 4, 1);

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
    connect(capturer, &CaptureThread::frameCapture, this, &MainWindow::updateFrame);
    capturer -> start();
    mainStatusLabel -> setText(QString("Capturing Camera %1").arg(camID));
}

void MainWindow::updateFrame(cv::Mat *mat )
{
    data_lock->lock();
    currentFrame = *mat;
    data_lock->unlock();

    QImage frame(
        currentFrame.data,
        currentFrame.cols,
        currentFrame.rows,
        currentFrame.step,
        QImage::Format_RGB888);
    QPixmap image = QPixmap::fromImage(frame);

    imageScene->clear();
    imageScene->addPixmap(image);
    imageScene->update();
    imageView->setSceneRect(image.rect());

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

