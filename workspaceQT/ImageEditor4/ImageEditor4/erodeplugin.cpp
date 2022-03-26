#include "erodeplugin.h"

ErodePlugin::ErodePlugin(QObject *parent)
    : QObject{parent}
{

}

QString ErodePlugin::name()
{
    return "Erode";
}

void ErodePlugin::edit(const cv::Mat &input, cv::Mat &output)
{
    erode(input, output, cv::Mat());
}
