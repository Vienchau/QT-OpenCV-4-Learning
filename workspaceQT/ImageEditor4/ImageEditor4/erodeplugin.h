#ifndef ERODEPLUGIN_H
#define ERODEPLUGIN_H

#include <QObject>
#include <QtPlugin>
#include "editor_plugin_interface.h"


class ErodePlugin : public QObject, public EditorPluginInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID EDIT_PLUGIN_INTERFACE_IID);
    Q_INTERFACES(EditorPluginInterface);
public:
    explicit ErodePlugin(QObject *parent = nullptr);
    QString name();
    void edit(const cv::Mat &input, cv::Mat &output);
};

#endif // ERODEPLUGIN_H
