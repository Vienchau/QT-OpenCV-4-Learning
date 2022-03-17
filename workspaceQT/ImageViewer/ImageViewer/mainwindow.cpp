#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QApplication>
#include <QFileDialog>
#include <QMessageBox>
#include <QPixmap>
#include <QKeyEvent>
#include <QDebug>
#include <QGraphicsScene>
#include <QGraphicsView>
#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , fileMenu(nullptr)
    , viewMenu(nullptr)
    , currentImage(nullptr)
{

    initUI();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initUI()
{
    this -> resize(800, 600);

    //setup menubar
    fileMenu = menuBar() -> addMenu("&File");
    viewMenu = menuBar() -> addMenu("&View");

    //setup toolbar
    fileToolBar = addToolBar("File");
    viewToolBar = addToolBar("View");

    //image display
    imageScene = new QGraphicsScene(this);
    imageView = new QGraphicsView(imageScene);
    setCentralWidget(imageView);

    //status bar
    //statusBar() is func in QStatusBar class, this func return the status bar for the main wd.
    mainStatusbar = statusBar();
    mainStatusLabel = new QLabel(mainStatusbar);
    //addPermanentWidget() is func in QStatusBar class, add widget to the status bar.
    mainStatusbar -> addPermanentWidget(mainStatusLabel);
    mainStatusLabel -> setText("Image Information will be here!");

    createActions();


}

void MainWindow::createActions()
{
    openAction = new QAction("&Open", this);
    fileMenu -> addAction(openAction);
    saveAsAction = new QAction("&Save as", this);
    fileMenu -> addAction(saveAsAction);
    exitAction = new QAction("&Exit", this);
    fileMenu -> addAction(exitAction);


    zoomInAction = new QAction("&Zoom in", this);
    viewMenu -> addAction(zoomInAction);
    zoomOutAction = new QAction("Zoom out", this);
    viewMenu -> addAction(zoomOutAction);
    prevAction = new QAction("&Previous Image", this);
    viewMenu -> addAction(prevAction);
    nextAction = new QAction("&Next Image", this);
    viewMenu -> addAction(nextAction);

    fileToolBar -> addAction(openAction);
    viewToolBar->addAction(zoomInAction);
    viewToolBar->addAction(zoomOutAction);
    viewToolBar->addAction(prevAction);
    viewToolBar->addAction(nextAction);


    connect(exitAction, SIGNAL(triggered(bool)), QApplication::instance(), SLOT(quit()));
    connect(openAction, SIGNAL(triggered(bool)), this, SLOT(openImage()));
    /*connect(saveAsAction, SIGNAL(triggered(bool)), this, SLOT(saveAs()));
    connect(zoomInAction, SIGNAL(triggered(bool)), this, SLOT(zoomIn()));
    connect(zoomOutAction, SIGNAL(triggered(bool)), this, SLOT(zoomOut()));
    connect(prevAction, SIGNAL(triggered(bool)), this, SLOT(prevImage()));
    connect(nextAction, SIGNAL(triggered(bool)), this, SLOT(nextImage()));*/

    setupShortcuts();
}

void MainWindow::showImage(QString path)
{
    imageScene->clear();
    QPixmap image(path);
    currentImage = imageScene->addPixmap(image);
    imageScene->update();
    imageView->setSceneRect(image.rect());
    QString status = QString("%1, %2x%3, %4 Bytes").arg(path).arg(image.width()).arg(image.height()).arg(QFile(path).size());
    mainStatusLabel->setText(status);
    currentImagePath = path;
}

void MainWindow::setupShortcuts()
{
    QList<QKeySequence> shortcuts;
       shortcuts << Qt::Key_Plus << Qt::Key_Equal;
       zoomInAction->setShortcuts(shortcuts);

       shortcuts.clear();
       shortcuts << Qt::Key_Minus << Qt::Key_Underscore;
       zoomOutAction->setShortcuts(shortcuts);

       shortcuts.clear();
       shortcuts << Qt::Key_Up << Qt::Key_Left;
       prevAction->setShortcuts(shortcuts);

       shortcuts.clear();
       shortcuts << Qt::Key_Down << Qt::Key_Right;
       nextAction->setShortcuts(shortcuts);
}

void MainWindow::openImage()
{
    QFileDialog dialog(this);
    dialog.setWindowTitle("Open Image");
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setNameFilter(tr("Images (*.png *.bmp *.jpg)"));
    QStringList filePaths;
    if (dialog.exec()) {
        filePaths = dialog.selectedFiles();
        showImage(filePaths.at(0));
    }
}

void MainWindow::zoomIn()
{

}

void MainWindow::zoomOut()
{

}

void MainWindow::prevImage()
{

}

void MainWindow::nextImage()
{

}

void MainWindow::saveAs()
{

}

