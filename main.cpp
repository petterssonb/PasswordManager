#include "passwordManager.h"

int main(){
    
    std::string filePath = "100kMostUsedPasswords.txt";
    PasswordManager passwordmanager;
    passwordmanager.modifyPasswords(filePath);
    passwordmanager.menu();



    return 0;
}