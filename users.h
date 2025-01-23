#ifndef USERS_H
#define USERS_H

#include <string>
#include <unordered_map>

void displayUsers();
bool validateUser(const std::unordered_map<std::string, std::string>& users, const std::string& username, const std::string& password);
bool compareQRCodeWithUser();

#endif // USERS_H