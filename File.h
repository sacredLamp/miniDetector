#pragma once
#include <string>
#include <fstream>

struct File{
    std::fstream file;
    std::string name;

    explicit File(std::string name);

    ~File(){
        // TODO: Create Deconstructor
    }

    bool checkFileExists();

    bool inFile(std::string& needle);

    void addPages();

    void clearFile();

    void readFile();




};
