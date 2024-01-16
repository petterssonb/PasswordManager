#ifndef _PASSWORDMANAGER_H_
#define _PASSWORDMANAGER_H_

#include <iostream>

class PasswordManager{
public:
    std::string username;
    std::string password;

    void createUser();
    void testLogin();
    void saveToFile();
    void hashPassword();
    bool existsInFile(const std::string& username);
    bool isValidName(const std::string& username);
    bool isValidPassword(const std::string& password);
    void menu();

};



#endif // _PASSWORDMANAGER_H_

