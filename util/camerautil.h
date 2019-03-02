#ifndef CAMERAUTIL_H
#define CAMERAUTIL_H


#include <QCamera>
#include <QCameraInfo>
#include <QCameraImageCapture>
#include <QDebug>
#include <QString>
#include "videosurface.h"

class CameraUtil : public QObject
{
    Q_OBJECT
public:
    CameraUtil(VideoSurface *&videoSurface);
    ~CameraUtil();
    QList<QString> getAvailableCameras();
    void setCamera(QString description);
    void captureImage();

private:
    QCamera *camera;
    QCameraImageCapture *cameraImageCapture;
    VideoSurface *videoSurface;
    void configureCamera();

signals:
    void imageCaptured(QImage image);

private slots:
    void handle_imageCaptured(int id, QImage frame);

};

#endif // CAMERAUTIL_H
