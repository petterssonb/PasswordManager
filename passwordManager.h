#ifndef _PASSWORDMANAGER_H_
#define _PASSWORDMANAGER_H_

#include <iostream>
#include <regex>
#include <openssl/md5.h>
#include <openssl/sha.h>
#include <fstream>
#include <set>
#include <string>

class PasswordManager{
public:
    std::string username;
    std::string password;
    std::string hashedPassword;

    void createUser();
    bool isValidName(const std::string& username);
    bool isValidPassword(const std::string& password);
    std::string hashPasswordMD5(const std::string& inputPassword);
    std::string hashPasswordSHA256(const std::string& inputPassword);
    void saveToFile(std::string username, std::string hashedPassword, std::string salt);
    bool existsInFile(const std::string& username);
    void testLogin();
    std::string generateSalt();
    void menu();

};



#endif // _PASSWORDMANAGER_H_

