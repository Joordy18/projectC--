#include <opencv2\opencv.hpp>
using namespace cv;
using namespace std;

void camera() {
    Mat image;
    namedWindow("Display window");
    VideoCapture cap(0);
    if (!cap.isOpened()) {
        cout << "cannot open camera";
    }
    while (true) {
        cap >> image;
        imshow("Display window", image);
        if (waitKey(25) == 27) { //press escape
            cap.release();
            break;
        }
    }
}