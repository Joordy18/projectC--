#include <opencv2/opencv.hpp>
#include <opencv2/objdetect.hpp>
#include <iostream>

using namespace cv;
using namespace std;

string readQRCode(const string& imagePath) {
    Mat img = imread(imagePath);
    if (img.empty()) {
        cerr << "Error: Could not open or find the image at " << imagePath << endl;
        return "";
    }
    QRCodeDetector qrDecoder;
    string data = qrDecoder.detectAndDecode(img);
    return data;
}

