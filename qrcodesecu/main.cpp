#include <iostream>
#include <fstream>

#include "qrcode.h"
#include "users.h"
#include "camera.h"


using namespace std;


int main() {
    string imagePath = "../Rickrolling_QR_Code.png";
    string qrData = readQRCode(imagePath);
    if (!qrData.empty()) {
        cout << "QR Code Data: " << qrData << endl;
    } else {
        cout << "No QR Code detected or the image is invalid." << endl;
    } // next compare to camera

    //displayUsers();
    //camera();
    compareQRCodeWithUser();
}
