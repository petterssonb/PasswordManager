#include "passwordManager.h"

void PasswordManager::createUser(){
     int hashChoice;

    while(true){
        std::cout << "Choose hash function: " << std::endl;
        std::cout << "1. MD5" << std::endl;
        std::cout << "2. SHA-256" << std::endl;
        std::cout << "3. Back to main menu" << std::endl;
        std::cin >> hashChoice;

        switch(hashChoice){
            case 1:
                std::cout << "Unsafe hash function selected (beware of bad choice)" << std::endl;
                break;
            case 2:
                std::cout << "Safe and sound hash function selected (beware of good choice)" << std::endl;
                break;
            case 3:
                std::cout << "Returned to main menu" << std::endl;
                return;
            default:
                std::cerr << "Invalid choice." << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
        }
    while(true){
        std::cout << "Enter username: " << std::endl;
        std::cin >> username;

        if(isValidName(username) && !existsInFile(username)){
            break;
        } else{
            std::cout << "Invalid email address or the user exsists" << std::endl;
            continue;
        }
    }


    while(true){
        std::cout << "Enter password: "  << std::endl;
        std::cin >> password;

        if(isValidPassword(password)){
            std::string salt = generateSalt();
            std::string saltedPassword = salt + password;

            if(hashChoice == 1){
            std::string hashedPassword = salt + hashPasswordMD5(saltedPassword);
            saveToFile(username, hashedPassword, salt);
            } else if(hashChoice == 2){
                std::string hashedPassword = salt + hashPasswordSHA256(saltedPassword);
                saveToFile(username, hashedPassword, salt);
            }
            break;

        } else{
            std::cout << "Invalid password." << std::endl;
            continue;
        }
    }
    break;
    }


}

bool PasswordManager::isValidName(const std::string& username){
    std::regex pattern(R"([a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,})");

    return std::regex_match(username, pattern);
}

bool PasswordManager::isValidPassword(const std::string& password){
    std::regex pattern("^(?=.*[a-z]|.*[A-Z])(?=.*\\d)(?=.*[@#%^&+=!]).{8,}$");

    return std::regex_match(password, pattern);
}

std::string PasswordManager::hashPasswordMD5(const std::string& inputPassword){
    MD5_CTX hashedPassword;
    MD5_Init(&hashedPassword);
    MD5_Update(&hashedPassword, inputPassword.c_str(), inputPassword.length());

    unsigned char hash[MD5_DIGEST_LENGTH];
    MD5_Final(hash, &hashedPassword);

    char hashedStr[MD5_DIGEST_LENGTH * 2 + 1];
    for(int i = 0; i < MD5_DIGEST_LENGTH; ++i){
        sprintf(&hashedStr[i * 2], "%02x", hash[i]);
    }

    return hashedStr;
}

std::string PasswordManager::hashPasswordSHA256(const std::string& inputPassword){
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, inputPassword.c_str(), inputPassword.length());

    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_Final(hash, &sha256);

    char hashedStr[SHA256_DIGEST_LENGTH * 2 + 1];
    for(int i = 0; i < SHA256_DIGEST_LENGTH; ++i){
        sprintf(&hashedStr[i * 2], "%02x", hash[i]);
    }

    return hashedStr;
}

void PasswordManager::saveToFile(std::string username, std::string hashedPassword, std::string salt){
    std::ofstream usersFile("users.txt", std::ios::app);

    if(!usersFile.is_open()){
        std::cerr << "Error opening file." << std::endl;
        return;
    }

    if(existsInFile(username)){
        std::cout << "Error: User already exists." << std::endl;
        return;
    }

    salt = generateSalt();
    std::string saltedPassword = salt + password;

    hashedPassword = hashPasswordMD5(saltedPassword);

    usersFile << username << ":" << salt << ":" << hashedPassword << std::endl;
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


        std::ifstream inFile("users.txt");
        std::string line;

        while(std::getline(inFile, line)){
            size_t pos = line.find(':');
            if(pos != std::string::npos){
                std::string user = line.substr(0, pos);
                std::string storedPasswordWithSalt = line.substr(pos + 1);

                if(user == username){
                    size_t saltPos = storedPasswordWithSalt.find(':');
                    std::string storedSalt = storedPasswordWithSalt.substr(0, saltPos);
                    std::string storedPassword = storedPasswordWithSalt.substr(saltPos + 1);

                    std::string saltedInputPassword = storedSalt + password;
                    std::string hashedInputPassword = hashPasswordMD5(saltedInputPassword);


                    if(storedPassword == hashedInputPassword){
                        std::cout << "OK Login successful! Welcome, " << username << "!" << std::endl;
                        inFile.close();
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

    const std::string charactersInSalt = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*_+";
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
                            break;
                        default:
                            std::cerr << "Invalid choice." << std::endl;
                            std::cin.clear();
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                            break;
                        
                    }
                    if(choice == 3){
                        break;
                    }
        }
    }


