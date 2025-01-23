#include <opencv2/opencv.hpp>
#include <opencv2/objdetect.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <bcrypt.h>
#include <iomanip>
#include "camera.h"

using namespace std;
using namespace cv;

void displayUsers() {
    vector<string> usernames;
    vector<string> passwords;
    vector<string> HashedPasswords;
    ifstream file("../users.txt");
    if (!file.is_open()) {
        cerr << "Error: Could not open the file 'users.txt'" << endl;
        return;
    }
    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        string username, password;
        if (iss >> username >> password) {
            usernames.push_back(username);
            passwords.push_back(password);
        }
    }
    file.close();

    ofstream hashedFile("../hashedUsers.txt");
    if (!hashedFile.is_open()) {
        cerr << "Error: Could not open the file 'hashedUsers.txt'" << endl;
        return;
    }

    for (size_t i = 0; i < usernames.size(); ++i) {
        string hashedPassword = bcrypt::generateHash(passwords[i]);
        HashedPasswords.push_back(hashedPassword);
        hashedFile << usernames[i] << " " << hashedPassword << endl;
    }

    hashedFile.close();

    cout << "Usernames:" << endl;
    for (const string& username : usernames) {
        cout << username << endl;
    }

    cout << "\nPasswords:" << endl;
    for (const string& password : passwords) {
        cout << password << endl;
    }

    cout << "\nHashed Passwords:" << endl;
    for (const string& hashedPassword : HashedPasswords) {
        cout << hashedPassword << endl;
    }
}

bool validateUser(const unordered_map<string, string>& users, const string& username, const string& password) {
    return users.count(username) && users.at(username) == password;
}

bool compareQRCodeWithUser() {
    camera();

    QRCodeDetector qrDecoder;
    Mat bbox, rectifiedImage;
    img = imread(pathtoqrcode);
    string qrData = qrDecoder.detectAndDecode(img, bbox, rectifiedImage);

    cap.release();

    if (qrData.empty()) {
        cerr << "No QR Code detected or the image is invalid." << endl;
        return false;
    }

    ifstream file("../users.txt");
    if (!file.is_open()) {
        cerr << "Error: Could not open the file 'users.txt'" << endl;
        return false;
    }

    unordered_map<string, string> users;
    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        string username, password;
        if (iss >> username >> password) {
            users[username] = password;
        }
    }
    file.close();

    for (const auto& user : users) {
        if (qrData == user.first + " " + user.second) {
            return true;
        }
    }
    return false;
}