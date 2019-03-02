#ifndef __BARCODEUTIL_H
#define __BARCODEUTIL_H

#include <vector>
#include <zbar.h>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;
using namespace zbar;

class BarcodeUtil
{
public:
  string getEAN13Code(Mat &barcodeImg);
private:
  string decodeBarcodeImg(Mat &img);
  string zbarDecoder(Mat &img);
};

#endif
