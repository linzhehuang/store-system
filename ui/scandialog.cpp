#include "scandialog.h"
#include "ui_scandialog.h"

ScanDialog::ScanDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ScanDialog)
{
    ui->setupUi(this);
    barcodeUtil = new BarcodeUtil();
    videoSurface = new VideoSurface(ui->scanView);
    // Congfigure the scan view.
    ui->scanView->setScaledContents(true);
    // Prepare the camera util.
    cameraUtil = new CameraUtil(videoSurface);
    cameraUtil->setCamera("Droidcam (v4l2loopback)");
    connect(cameraUtil, &CameraUtil::imageCaptured,
            this, &ScanDialog::handle_imageCaptured);
    // Start timer.
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout,
            this, &ScanDialog::handle_timeout);
    timer->start(1000);
}

ScanDialog::~ScanDialog()
{
    delete ui;
}

void ScanDialog::handle_imageCaptured(QImage image)
{
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

    QImage barcodeImg = image.copy(rect);
    Mat mat = Mat(barcodeImg.height(), barcodeImg.width(), CV_8UC4,
                  (void*)barcodeImg.constBits(), barcodeImg.bytesPerLine());
    string result = barcodeUtil->getEAN13Code(mat);
    if(result.empty()) return;

    Good* good = GoodRepo::findByGoodID(result);
    if(good == NULL) {
        ui->tips->setText("No '" +
                          to_qstring(result) + "' in database!");
    }
    else {
        emit goodPicked_signal(good);
        this->close();
    }
}

void ScanDialog::handle_timeout()
{
    cameraUtil->captureImage();
}
