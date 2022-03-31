#ifndef CAPTURETHREAD_H
#define CAPTURETHREAD_H

#include <QObject>
#include <QString>
#include <QThread>
#include <QMutex>
#include <zbar.h>
#include "opencv2/opencv.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/video/background_segm.hpp"


class CaptureThread : public QThread
{
    Q_OBJECT
public:
    CaptureThread(int camera, QMutex *lock);
    CaptureThread(QString videoPath, QMutex *lock);
    ~CaptureThread();




    void setRunning(bool run)
    {
        running = run;
    }



protected:
    void run() override;


signals:
    void frameCapture(cv::Mat *data);


private:
    bool running;
    int cameraID;
    QString videoPath;
    QMutex *data_lock;
    cv::Mat  frame;
};

#endif // CAPTURETHREAD_H
