#ifndef _PASSWORDMANAGER_H_
#define _PASSWORDMANAGER_H_

#include <iostream>
#include <regex>

class PasswordManager{
public:
    std::string username;
    std::string password;

    void createUser();
    bool isValidName(const std::string& username);
    bool isValidPassword(const std::string& password);
    void hashPassword();
    void testLogin();
    void saveToFile();
    bool existsInFile(const std::string& username);
    void menu();

};



#endif // _PASSWORDMANAGER_H_

