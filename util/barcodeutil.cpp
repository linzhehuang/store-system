#include "barcodeutil.h"
#include <QDebug>

string BarcodeUtil::zbarDecoder(Mat &img)
{
    string result;
    ImageScanner scanner;
    const void *raw = (&img)->data;
    // Configure the reader.
    scanner.set_config(ZBAR_EAN13, ZBAR_CFG_ENABLE, 1);
    // Wrap image data.
    Image image(img.cols, img.rows, "Y800", raw, img.cols * img.rows);
    // Scan the image for barcodes.
    int n = scanner.scan(image);
    // Extract results.
    result = image.symbol_begin()->get_data();
    image.set_data(NULL, 0);
    return result;
}

string BarcodeUtil::decodeBarcodeImg(Mat &img)
{
  string result = zbarDecoder(img);
  if(result.empty())
  {
      Mat openImg;
      Mat element = getStructuringElement(MORPH_RECT, Size(3, 3));
      morphologyEx(img, openImg, MORPH_OPEN, element);
      result = zbarDecoder(openImg);
  }
  return result;
}

string BarcodeUtil::getEAN13Code(Mat &barcodeImg)
{
  string result;
  Mat binImg;
  cvtColor(barcodeImg, barcodeImg, CV_RGB2GRAY);
  int tValue = threshold(barcodeImg, binImg, 0, 255, THRESH_OTSU);
  while(result.empty() && tValue<255) {
      threshold(barcodeImg, binImg, tValue, 255, THRESH_BINARY);
      result = decodeBarcodeImg(binImg);
      // Increase the threshold value.
      // The bigger the value,the faster,but reducing recognition rate.
      tValue += 20;
  }
  return result;
}
