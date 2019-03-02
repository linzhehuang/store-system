#include "videosurface.h"

VideoSurface::VideoSurface(QLabel *&view)
{
    this->view = view;
}

bool VideoSurface::present(const QVideoFrame &frame)
{
    QVideoFrame img(frame);
    if(!img.map(QAbstractVideoBuffer::ReadOnly)) return false;
    QImage image(img.bits(),
                 img.width(),
                 img.height(),
                 img.bytesPerLine(),
                 QImage::Format_RGB888);
    int imgWidth = image.width(), imgHeight = image.height();
    int frameWidth = 0, frameHeight = 0;
    if(imgWidth > imgHeight) {
        frameHeight = imgHeight*0.5;
        frameWidth = frameHeight*1.3;
    }
    else {
        frameWidth = imgWidth*0.5;
        frameHeight = frameWidth*1.3;
    }
    int frameLeft = (imgWidth - frameWidth)/2 ,
        frameTop = (imgHeight - frameHeight)/2;
    QRect rect(frameLeft, frameTop, frameWidth, frameHeight);
    QPainter painter(&image);
    painter.setPen(QPen(Qt::SolidLine));
    painter.setPen(QColor(255,0,0));
    painter.drawRect(rect);

    view->setPixmap(QPixmap::fromImage(image));
    img.unmap();
    view->update();
    return true;
}

QList<QVideoFrame::PixelFormat> VideoSurface::supportedPixelFormats(
        QAbstractVideoBuffer::HandleType type) const
{
    if(type == QAbstractVideoBuffer::NoHandle) {
        return QList<QVideoFrame::PixelFormat>()
                << QVideoFrame::Format_RGB24;
    }
    return QList<QVideoFrame::PixelFormat>();
}
