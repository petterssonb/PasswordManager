#ifndef _PASSWORDMANAGER_H_
#define _PASSWORDMANAGER_H_

#include <iostream>
#include <regex>
#include <openssl/md5.h> // fråga stefan på fredag varför includen blir röd permanent
#include <fstream>
#include <set>
#include <string>

class PasswordManager{
public:
    std::string username;
    std::string password;

    void createUser();
    bool isValidName(const std::string& username);
    bool isValidPassword(const std::string& password);
    void hashPassword();
    void saveToFile();
    bool existsInFile(const std::string& username);
    void testLogin();
    void menu();

};



#endif // _PASSWORDMANAGER_H_

