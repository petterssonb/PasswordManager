#include "passwordManager.h"

void PasswordManager::createUser(){
    while(true){
        std::cout << "Enter username: " << std::endl;
        std::cin >> username;

        if(isValidName(username)){
            std::cout << "Valid email address." << std::endl;
            break;
        } else{
            std::cout << "Invalid email address." << std::endl;
            continue;
        }

        std::cout << "Enter password: "  << std::endl;
        std::cin >> password;

        if(isValidPassword(password)){
            std::cout << "Valid password." << std::endl;
            break;
        } else{
            std::cout << "Invalid password." << std::endl;
            continue;
        }
    }


}

bool PasswordManager::isValidName(const std::string& username){
    std::regex pattern(R"([a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,})");

    return std::regex_match(username, pattern);
}

bool PasswordManager::isValidPassword(const std::string& password){
    std::regex pattern("(?=.*[a-z])(?=.*[A-Z])(?=.*\\d)(?=.*[@#$%^&+=]).{8,}");

    return std::regex_match(password, pattern);
}

void hashPassword(){
    

}

void PasswordManager::menu(){

    while(true){
    std::cout << "1. Create User" << std::endl;
    std::cout << "2. Login" << std::endl;
    std::cout << "3. Exit program" << std::endl;
    int choice;
    std::cin >> choice;

        switch(choice){
            case 1:
                createUser();
                break;
            case 2:
                testLogin();
                break;
            case 3:
                std::cout << "Shutting down program." << std::endl;
                return;
            default:
                std::cerr << "Invalid choice." << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                break;
            
        }
    }
}
