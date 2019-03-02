#ifndef SCANDIALOG_H
#define SCANDIALOG_H

#include <QDialog>
#include <QTimer>
#include <QPainter>
#include "repository/goodrepo.h"
#include "util/camerautil.h"
#include "util/barcodeutil.h"
#include "util/videosurface.h"

namespace Ui {
class ScanDialog;
}

class ScanDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ScanDialog(QWidget *parent = 0);
    ~ScanDialog();

signals:
    void goodPicked_signal(Good*);

private slots:
    void handle_imageCaptured(QImage image);
    void handle_timeout();

private:
    Ui::ScanDialog *ui;
    CameraUtil *cameraUtil;
    BarcodeUtil *barcodeUtil;
    QTimer *timer;
    VideoSurface *videoSurface;
};

#endif // SCANDIALOG_H
