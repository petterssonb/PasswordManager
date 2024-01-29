#include "passwordManager.h"

void PasswordManager::createUser(){


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
            std::string hashedPassword = hashPasswordMD5(saltedPassword);
            crackableHash = hashPasswordMD5(password);
            saveToFile(username, hashedPassword, salt);
            saveCrackableToFile(username, crackableHash);
            } else if(hashChoice == 2){
                std::string hashedPassword = hashPasswordSHA256(saltedPassword);
                crackableHash256 = hashPasswordSHA256(password);
                saveToFile(username, hashedPassword, salt);
                saveCrackableToFile(username, crackableHash256);
            }
            return;

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



void PasswordManager::saveToFile(const std::string &username, const std::string &hashedPassword, const std::string &salt){

    

    if(existsInFile(username)){
        std::cout << "Error: User already exists." << std::endl;
        return;
    }

    std::ofstream usersFile("users.txt", std::ios::app);

    if(!usersFile.is_open()){
        std::cerr << "Error opening file." << std::endl;
        return;
    }

    

    usersFile << username << ":" << salt << ":" << hashedPassword << std::endl;
}

void PasswordManager::saveCrackableToFile(const std::string &username, const std::string &hashedPassword){
    


    std::ofstream hashFile("hashes.txt", std::ios::app);

    if(!hashFile.is_open()){
        std::cerr << "Error opening hashes file." << std::endl;
        return;
    }

    hashFile << username << ":" << hashedPassword << std::endl;

    hashFile.close();
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

                    if(hashChoice == 1){
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
                    } else if(hashChoice == 2){
                        std::string hashedInputPassword = hashPasswordSHA256(saltedInputPassword);

                            if(storedPassword == hashedInputPassword){
                                std::cout << "Ok Login successful! Welcome, " << username << "!" << std::endl;
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
                std::cout << "4. Crack Passwords" << std::endl;
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
                        case 4:
                            compareHashes(hashFilePath, commonPasswordsFilePath);
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

void PasswordManager::compareHashes(std::string& hashFilePath, std::string& commonPasswordsFilePath){

    std::cout << "Enter path to hash file: ";
    std::cin >> hashFilePath;

    std::cout << "Enter path to common passwords file: ";
    std::cin >> commonPasswordsFilePath;

    std::unordered_map<std::string, std::string> passwordHashes;

    std::ifstream hashFile(hashFilePath);
    if(!hashFile.is_open()){
        std::cerr << "Error opening hash file" << std::endl;
        return;
    }

    std::string line;
    while(std::getline(hashFile, line)){
        size_t pos = line.find(':');
        if(pos != std::string::npos){
            std::string user = line.substr(0, pos);
            std::string hash = line.substr(pos + 1);
            passwordHashes[user] = hash;
        }
    }
    hashFile.close();

    std::ifstream commonPasswordsFile(commonPasswordsFilePath);
    if(!commonPasswordsFile.is_open()){
        std::cerr << "Error opening common passwords file." << std::endl;
        return;
    }

    bool foundSome = false;

    while(std::getline(commonPasswordsFile, line)){
        std::string hashedPasswordMD5Local = hashPasswordMD5(line);
        std::string hashedPasswordSHA256Local = hashPasswordSHA256(line);

        for(const auto& entry : passwordHashes){
            if(entry.second == hashedPasswordMD5Local || entry.second == hashedPasswordSHA256Local){
                std::cout << "Match found for user: " << entry.first << " Password: " << line << std::endl;
                foundSome = true;
            }
        } 
    }
    commonPasswordsFile.close();

    if(!foundSome){
        std::cout << "No matches found inside the file." << std::endl;
    }
}


