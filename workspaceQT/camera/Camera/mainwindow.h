#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenuBar>
#include <QAction>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QCheckBox>
#include <QPushButton>
#include <QTextBrowser>

#include <QListView>
#include <QStandardItemModel>
#include <QStatusBar>
#include <QLabel>
#include <QMutex>
#include <opencv2/core.hpp>
#include <zbar.h>
#include <capturethread.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#ifdef CAMERA_USE_QT_CAMERA
#include <QCameraViewfinder>
#include <QCamera>
#endif




#include "opencv2/opencv.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    typedef struct
    {
        std:: string type;
        std:: string data;
        std:: vector<cv::Point> location;
    }decodedObject;

private:
    void initUI();
    void createActions();
    void populateSavedList();

private slots:
    void showCameraInfo();
    void openCamera();
    void updateFrame(cv::Mat *mat);
    void calculateFPS();
    void updateFPS(float);
    void recordingStartStop();
    void appendSavedVideo(QString name);
    void updateMonitorStatus(int status);


private:
    QMenu *fileMenu;

    QAction *cameraInfoAction;
    QAction *openCameraAction;
    QAction *calcFPSAction;
    QAction *exitAction;

    QGraphicsScene *imageScene;
    QGraphicsView *imageView;



    QCheckBox *monitorCheckBox;
    QPushButton *recordPushButton;


    QStatusBar *mainStatusBar;
    QLabel *mainStatusLabel;
    QTextBrowser *dataBrowser;

    QMutex *data_lock;
    CaptureThread *capturer;
    cv::Mat currentFrame;



private:

};
#endif // MAINWINDOW_H
