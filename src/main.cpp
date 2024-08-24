#include "passwordManager.h"

int main(){
    
    std::string filePath = "commonpasswords/100kMostUsedPasswords.txt";
    PasswordManager passwordmanager;
    passwordmanager.modifyPasswords(filePath);
    passwordmanager.menu();



    return 0;
}