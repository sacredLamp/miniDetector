//
// Created by Henock Dinberu on 7/20/23.
//

#include "File.h"
#include <iostream>
#include <utility>
#include <vector>

// Constructor
File::File(std::string fileName) : name(std::move(fileName)) {}

bool File::checkFileExists(){
    this->file.open("saved.txt");
    if(!this->file) {
        std::cout << "File could not be created\n";
        return false;
    }
    else{
        this->file.close();
        return true;
    }

}

void File::readFile(){
#ifdef _WIN32
    std::system("cls");
#elif __APPLE__
    std::system("clear");
#endif
    std::string input;

    this->file.open("saved.txt", std::ios::in);
    std::string line;
    std::cout << "Saved File: \n";
    while (getline(this->file, line)) {
        std::cout << line << "\n";
    }
    this->file.close();
    std::cout << "Enter \'q\' to exit. ::\n";
    while(input != "q") {
        std::cin >> input;
    }
}

bool File::inFile(std::string &needle) {
    std::string line;

    file.open("saved.txt", std::fstream::in);
    if(file.is_open()) {
        while (getline(file, line)) {
            if (line.compare(needle) != 0) {
                std::cout << "Connection is already saved ::\n\n";
                file.close();
                return false;
            }
        }
        file.close();
        return true;
    }
    else{
        std::cout << "File is not open ::\n";
        return false;
    }

}

void File::addPages(){
#ifdef _WIN32
    std::system("cls");
#elif __APPLE__
    std::system("clear");
#endif
    std::string input;

    if (checkFileExists()) {
        while (input.compare("q") != 0) {
            std::cout << "Input connection to save ::\n";
            std::cin >> input;

            if (input == "q") {
                break;
            }
            if (inFile(input)) {
                file.open("saved.txt", std::ios::app);
                std::cout << "Adding to list...\n";
                file << input << "\n";
                std::cout << "Connection added! ::\n\n";
                file.close();
            }

        }
    }

}

void File::clearFile(){
#ifdef _WIN32
    std::system("cls");
#elif __APPLE__
    std::system("clear");
#endif
    if(checkFileExists()){
        this->file.open("saved.txt", std::ios::out | std::ios::trunc);
        file.close();
    }
}

