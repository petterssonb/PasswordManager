#include "passwordManager.h"

void PasswordManager::createUser(){
    while(true){
        std::cout << "Enter username: " << std::endl;
        std::cin >> username;

        if(isValidName(username) && !existsInFile(username)){
            std::cout << "Valid email address." << std::endl;
            break;
        } else{
            std::cout << "Invalid email address or the user exsists" << std::endl;
            continue;
        }

        std::cout << "Enter password: "  << std::endl;
        std::cin >> password;

        if(isValidPassword(password)){
            std::cout << "Valid password." << std::endl;
            hashPassword();
            saveToFile();
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

void PasswordManager::hashPassword(){
    MD5_CTX hashedPassword;
    MD5_Init(&hashedPassword);
    MD5_Update(&hashedPassword, password.c_str(), password.length());

    unsigned char hash[MD5_DIGEST_LENGTH];
    MD5_Final(hash, &hashedPassword);

    char hashedStr[MD5_DIGEST_LENGTH * 2 + 1];
    for(int i = 0; i < MD5_DIGEST_LENGTH; ++i){
        sprintf(&hashedStr[i * 2], "%02x", hash[i]);
    }

    password = hashedStr;
}

void PasswordManager::saveToFile(){
    std::ofstream usersFile("users.txt", std::ios::app);

    if(!usersFile.is_open()){
        std::cerr << "Error opening file." << std::endl;
        return;
    }

    if(existsInFile(username)){
        std::cout << "Error: User already exists." << std::endl;
        return;
    }

    usersFile << username << ":" << password << std::endl;
}

bool PasswordManager::existsInFile(const std::string& username){
    std::ifstream inFile("users.txt");
    std::string line;

    while(std::getline(inFile, line)){
        size_t pos = line.find(':');
        if(pos != std::string::npos){
            std::string user = line.substr(0, pos);
            if(user == username){
                inFile.close();
                return true;
            }
        }
    }
    inFile.close();
    return false;
}

void PasswordManager::testLogin(){
    std::cout << "Enter username: ";
    std::cin >> username;

    if(existsInFile(username)){
        std::cout << "Enter password: ";
        std::cin >> password;

        hashPassword();

        std::ifstream inFile("users.txt");
        std::string line;

        while(std::getline(inFile, line)){
            size_t pos = line.find(':');
            if(pos != std::string::npos){
                std::string user = line.substr(0, pos);
                std::string storedPassword = line.substr(pos + 1);

                if(user == username){
                    if(storedPassword == password){
                        std::cout << "OK Login successful! Welcome, " << username << "!" << std::endl;
                        return;
                    } else{
                        std::cerr << "Login failed, incorrect password." << std::endl;
                        inFile.close();
                        return;
                    }
                }
            }
        }
        std::cerr << "User not found. Login failed" << std::endl;
        inFile.close();
    } else{
        std::cerr << "User not found. Login failed" << std::endl;
    }
}

std::string PasswordManager::generateSalt(){
    srand(static_cast<unsigned int>(time(nullptr)));

    const std::string charactersInSalt = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*()_+";
    const size_t saltLenght = 32;

    std::string salt;
    for(size_t i = 0; i < saltLenght; ++i){
        salt += charactersInSalt[rand() % charactersInSalt.length()];
    }

    return salt;
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
