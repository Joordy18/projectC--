#include <opencv2/opencv.hpp>
#include <opencv2/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <bcrypt.h>

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
    QRCodeDetector qrCode;
    Mat img;
    VideoCapture cap(0);
    if (!cap.isOpened()) {
        cerr << "Error: Could not open the webcam" << endl;
        return false;
    }

    unordered_map<string, string> users;
    ifstream file("../users.txt");
    if (!file.is_open()) {
        cerr << "Error: Could not open the file 'users.txt'" << endl;
        return false;
    }

    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        string username, password;
        if (iss >> username >> password) {
            users[username] = password;
        }
    }
    file.close();

    string inputUsername, inputPassword;
    cout << "Enter username: ";
    cin >> inputUsername;
    cout << "Enter password: ";
    cin >> inputPassword;

    while (true) {
        cap >> img;
        if (img.empty()) {
            cerr << "Error: Could not capture frame from webcam" << endl;
            return false;
        }

        Mat pts, result;
        string qrData = qrCode.detectAndDecode(img, pts, result);
        if (!qrData.empty()) {
            cout << "QR Code Data: " << qrData << endl;

            istringstream iss(qrData);
            string qrUsername, qrPassword;
            if (iss >> qrUsername >> qrPassword) {
                if (qrUsername == inputUsername && qrPassword == inputPassword) {
                    if (users.count(qrUsername) && users[qrUsername] == qrPassword) {
                        cout << "User validated successfully" << endl;
                        return true;
                    } else {
                        cout << "Invalid user credentials in file" << endl;
                        return false;
                    }
                } else {
                    cout << "QR code data does not match input credentials" << endl;
                    return false;
                }
            }
        }

        imshow("Webcam", img);
        if (waitKey(30) >= 0) {
            break; // Exit if any key is pressed
        }
    }

    cap.release();
    destroyAllWindows();
    return false;
}