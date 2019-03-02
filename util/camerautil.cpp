#include "camerautil.h"

CameraUtil::CameraUtil(VideoSurface *&videoSurface)
{
    camera = NULL;
    cameraImageCapture = NULL;
    this->videoSurface = videoSurface;
}

CameraUtil::~CameraUtil()
{
    delete camera;
}

QList<QString> CameraUtil::getAvailableCameras()
{
    QList<QCameraInfo> cameras = QCameraInfo::availableCameras();
    QList<QString> result;
    foreach (const QCameraInfo &cameraInfo, cameras) {
        result.push_back(cameraInfo.description());
    }
    return result;
}

void CameraUtil::setCamera(QString description)
{
    QList<QCameraInfo> cameras = QCameraInfo::availableCameras();
    foreach (const QCameraInfo &cameraInfo, cameras) {
        if(cameraInfo.description() == description) {
            if(camera != NULL) delete camera;
            if(cameraImageCapture != NULL) delete cameraImageCapture;

            camera = new QCamera(cameraInfo);
            if(camera != NULL) {
                configureCamera();
                camera->start();
            }
            else {
                // TODO: handle error here.
            }
        }
    }
}

void CameraUtil::captureImage()
{
    if(cameraImageCapture != NULL) {
        cameraImageCapture->capture();
    }
}

// Private domain.
void CameraUtil::configureCamera()
{
    cameraImageCapture = new QCameraImageCapture(camera);
    cameraImageCapture->setCaptureDestination(QCameraImageCapture::CaptureToBuffer);

    camera->setViewfinder(videoSurface);
    camera->setCaptureMode(QCamera::CaptureStillImage);
    connect(cameraImageCapture,
            &QCameraImageCapture::imageCaptured,
            this,
            &CameraUtil::handle_imageCaptured);
}

void CameraUtil::handle_imageCaptured(int id, QImage frame)
{
    id = id; // Avoid the unused warning.
    emit imageCaptured(frame);
}
