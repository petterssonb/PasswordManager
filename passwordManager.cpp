#include "passwordManager.h"
#include <limits>
#include <iomanip>

void PasswordManager::createUser(){


    while(true){
        std::cout << "Choose hash function: " << std::endl;
        std::cout << "1. Unsafe mode." << std::endl;
        std::cout << "2. Safe mode." << std::endl;
        std::cout << "3. Back to main menu" << std::endl;
        std::cin >> hashChoice;

        switch(hashChoice){
            case 1:
                std::cout << "Using MD5 hashing function." << std::endl;
                hashChoice = 1;
                break;
            case 2:
                std::cout << "Using SHA256 hashing function." << std::endl;
                hashChoice = 2;
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
    std::regex pattern("^(?=.*[a-z])(?=.*[A-Z])(?=.*\\d)(?=.*[@#%^&+=!\\?]).{8,}$");

    return std::regex_match(password, pattern);
}

std::string PasswordManager::hashPasswordMD5(const std::string& inputPassword){
    MD5_CTX hashedPassword;
    MD5_Init(&hashedPassword);
    MD5_Update(&hashedPassword, inputPassword.data(), inputPassword.size());

    unsigned char hash[MD5_DIGEST_LENGTH];
    MD5_Final(hash, &hashedPassword);


    std::stringstream hashedStr;
    for(int i = 0; i < MD5_DIGEST_LENGTH; ++i){
        hashedStr << std::hex << std::setw(2) << std::setfill('0') << static_cast<unsigned>(hash[i]);
    }

    return hashedStr.str();
}

std::string PasswordManager::hashPasswordSHA256(const std::string& inputPassword){
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, inputPassword.data(), inputPassword.size());

    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_Final(hash, &sha256);


    std::stringstream hashedStr;
    for(int i = 0; i < SHA256_DIGEST_LENGTH; ++i){
        hashedStr << std::hex << std::setw(2) << std::setfill('0') << static_cast<unsigned>(hash[i]);
    }

    return hashedStr.str();
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

void PasswordManager::testLogin(int &hashChoice){
    std::cout << "Did you create the account using safe mode or none safe mode?" << std::endl;
    std::cout << "1. Unsafe mode." << std::endl;
    std::cout << "2. Safe mode." << std::endl;
    std::cin >> hashChoice;

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

                    std::string hashedInputPassword;

                    

                    if(hashChoice == 1){
                        hashedInputPassword = hashPasswordMD5(saltedInputPassword);
                        hashChoice = 1;
                    } else if(hashChoice == 2){
                        hashedInputPassword = hashPasswordSHA256(saltedInputPassword);
                        hashChoice = 2;
                    }


                    if(storedPassword == hashedInputPassword){
                        std::cout << "Ok Login successful! Welcome, " << username << "!" << std::endl;
                        inFile.close();
                        return;
                    } else{
                        std::cerr << "Login failed, incorrect password or wrong mode selected." << std::endl;
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
                std::cout << "4. Crack Passwords" << std::endl;
                std::cout << "5. Crack a single password" << std::endl;
                int choice;
                std::cin >> choice;
                    switch(choice){
                        case 1:
                            createUser();
                            break;
                        case 2:
                            testLogin(hashChoice);
                            break;
                        case 3:
                            std::cout << "Shutting down program." << std::endl;
                            break;
                        case 4:
                            compareHashes(hashFilePath, commonPasswordsFilePath);
                            break;
                        case 5:
                            checkSinglePassword(crackPassword);
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

    std::cout << "Enter name of the file you want to crack: ";
    std::cin >> hashFilePath;

    std::cout << "Enter name of the common password file: ";
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

void PasswordManager::checkSinglePassword(std::string& crackPassword){
    std::cout << "Enter the password to check: ";
    std::cin >> crackPassword;


    std::string hashMD5 = hashPasswordMD5(crackPassword);
    std::string hashSHA256 = hashPasswordSHA256(crackPassword);

    std::ifstream hashFile("hashes.txt");
    if(!hashFile.is_open()){
        std::cerr << "Error opening hash file" << std::endl;
        return;
    }

    std::unordered_map<std::string, std::string> passwordHashes;

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

    bool foundMatch = false;

    for(const auto& entry : passwordHashes){
        if(entry.second == hashMD5 || entry.second == hashSHA256){
            std::cout << "Match found for user: " << entry.first << " Password: " << crackPassword << std::endl;
            foundMatch = true;
        }
    }

    if(!foundMatch){
        std::cout << "No matches found for the given password." << std::endl;
    }
}

void PasswordManager::modifyPasswords(const std::string& filePath){
    std::ifstream inFile(filePath);
    if(!inFile.is_open()){
        std::cerr << "Error opening file." << std::endl;
        return;
    }

    std::ofstream outFile("temp.txt");
    if(!outFile.is_open()){
        std::cerr << "Error opening temp file." << std::endl;
        inFile.close();
        return;
    }

    std::string line;
    while(std::getline(inFile, line)){

        bool contains123 = (line.find("123") != std::string::npos);
        bool contains2024 = (line.find("2024") != std::string::npos);

        if(!contains123 && !contains2024){
            std::string randomString = (rand() % 2 == 0) ? "123" : "2024";
            line += randomString;

        }

        if(!ispunct(line.back())){
            char specialChar = (rand() % 2 == 0) ? '!' : '?';
            line += specialChar;
        }

        outFile << line << std::endl;
    }

    inFile.close();
    outFile.close();

    if(std::rename("temp.txt", filePath.c_str()) != 0){
        std::cerr << "Error renaming file." << std::endl;
    } else{}

}



