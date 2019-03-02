#ifndef CAMERAVIEW_H
#define CAMERAVIEW_H

#include <QAbstractVideoSurface>
#include <QLabel>
#include <QDebug>
#include <QPainter>

class VideoSurface : public QAbstractVideoSurface
{
public:
    VideoSurface(QLabel* &view);
    QList<QVideoFrame::PixelFormat> supportedPixelFormats(
            QAbstractVideoBuffer::HandleType type = QAbstractVideoBuffer::NoHandle) const;
    bool present(const QVideoFrame &frame);
private:
    QLabel *view;
};

#endif // CAMERAVIEW_H
