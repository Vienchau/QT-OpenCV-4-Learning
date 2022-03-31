

#include "capturethread.h"


CaptureThread::CaptureThread(int camera, QMutex *lock):
     running(false), cameraID(camera), videoPath(""), data_lock(lock)
{
}

CaptureThread::CaptureThread(QString videoPath, QMutex *lock):
    running(false), cameraID(-1), videoPath(videoPath), data_lock(lock)
{
}

CaptureThread::~CaptureThread()
{
}



void CaptureThread::run()
{
    running = true;

    //videocapture using camera index
    cv::VideoCapture cap(cameraID);
    //instance mat to save the capture frame
    cv::Mat tmp_frame;
    cv::Mat tmp_frame2;

    while(running)
    {
        cap >> tmp_frame;
        if(tmp_frame.empty())
        {
            break;
        }
        cvtColor(tmp_frame, tmp_frame2, cv::COLOR_BGR2RGB);
        data_lock->lock();
        frame = tmp_frame2;
        data_lock->unlock();

        emit frameCapture(&frame);
    }

    cap.release(); //close video file or capture device
    running = false;

}

