#ifndef _PASSWORDMANAGER_H_
#define _PASSWORDMANAGER_H_

#include <iostream>
#include <regex>
#include <openssl/md5.h>
#include <openssl/sha.h>
#include <fstream>
#include <set>
#include <string>
#include <unordered_map>
#include <sstream>
#include <cctype>
#include <cstdlib>
#include <ctime>

class PasswordManager{
private:
    int hashChoice;
    std::string hashFilePath;
    std::string commonPasswordsFilePath;
    std::string crackableHash;
    std::string crackableHash256;
    std::string crackPassword;

public:
    std::string username;
    std::string password;
    std::string hashedPassword;

    void createUser();
    bool isValidName(const std::string& username);
    bool isValidPassword(const std::string& password);
    std::string hashPasswordMD5(const std::string& inputPassword);
    std::string hashPasswordSHA256(const std::string& inputPassword);
    void saveToFile(const std::string &username, const std::string &hashedPassword, const std::string &salt);
    void saveCrackableToFile(const std::string &username, const std::string &hashedPassword);
    bool existsInFile(const std::string& username);
    void testLogin(int &hashChoice);
    std::string generateSalt();
    void menu();
    void compareHashes(std::string& hashFilePath, std::string& commonPasswordsFilePath);
    void checkSinglePassword(std::string& crackPassword);
    void modifyPasswords(const std::string& filePath);

};



#endif // _PASSWORDMANAGER_H_

