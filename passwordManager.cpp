#include "passwordManager.h"


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
