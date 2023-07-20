#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>

void start(std::fstream& file);

void clear(){
#ifdef _WIN32
    std::system("cls");
#elif __APPLE__
    std::system("clear");
#endif
}

bool ping(std::string& input){

    std::cout << "Pinging " << input << "...\n";
#ifdef _WIN32
    std::string cmd("ping " + input + " -n 1");
#elif __APPLE__
    std::string cmd("ping " + input + " -c 1");
#endif

    if(!std::system(cmd.c_str())) {
        //std::cout << "Website is up and running! ::\n";
        return true;
    }

    else{
        //std::cout << "This webpage / server seems to be DOWN ::\n";
        return false;
    }

}

void testPage(){
    clear();
    std::string input;
    std::cout << "Enter website IP / URL ::\n";

    while(true){

        std::cin >> input;
        if(input == "q")
            break;

        if(ping(input))
            std::cout << "Website is up and running! ::\n";
        else
            std::cout << "This webpage / server seems to be DOWN ::\n";

        std::cout << "\nEnter 'q' to quit or enter another IP/URL ::\n\n";

    }

}

bool checkFileExists(std::fstream &file){
    file.open("saved.txt");
    if(!file) {
        std::cout << "File could not be created\n";
        return false;
    }
    else{
        //std::cout << "File created successfully\n";
        file.close();
        return true;
    }

}

void readPages(std::fstream& file){
    clear();
    std::string input;

    file.open("saved.txt", std::ios::in);
    std::string line;
    std::cout << "File: \n";
    while (getline(file, line)) {
        std::cout << line << "\n";
    }
    file.close();
    std::cout << "Enter \'q\' to exit. ::\n";
    while(input != "q") {
        std::cin >> input;
    }
}

bool inFile(std::fstream &file, std::string &needle) {
    std::string line;

    //readPages(file);
        //std::cout << "File is open ::\n";
    file.open("saved.txt", std::fstream::in);
    if(file.is_open()) {
        while (getline(file, line)) {
            if (line == needle) {
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

void addPages(std::fstream& file){
    clear();
    std::string input;

    if (checkFileExists(file)) {
        while (input != "q") {
            std::cout << "Input connection to save ::\n";
            std::cin >> input;

            if (input == "q") {
                break;
            }
            if (inFile(file, input)) {
                file.open("saved.txt", std::ios::app);
                std::cout << "Adding to list...\n";
                file << input << "\n";
                std::cout << "Connection added! ::\n\n";
                file.close();
            }

        }
    }

}

void runSaved(std::fstream& file){
    std::string input;
    std::cout << "Running SAVED URLs...\n";
    std::string line;
    std::vector<std::string> success, fail;
    file.open("saved.txt", std::ios::in);
    if(file.is_open()){
        while(getline(file, line)) {
            if (!line.empty()) {
                if (ping(line))
                    success.push_back(line);
                else
                    fail.push_back(line);
            }
        }
    }
    file.close();
    clear();
    if(success.empty() and fail.empty())
        start(file);
    std::cout << "Completed! ::\n";
    std::cout << "Succeeded: " << success.size() << "\n";
    for(auto &l: success){
        std::cout << "\t" << l << "\n";
    }

    std::cout << "Failed: " << fail.size() << "\n";
    for(auto &l : fail){
        std::cout << "\t" << l << "\n";
    }

    std::cout << "Enter \'q\' to exit. ::\n";
    while(input != "q") {
        std::cin >> input;
    }

}

void launch(std::fstream& file){
    if(checkFileExists(file)){
        runSaved(file);
    }
}

void clearFile(std::fstream& file){
    if(checkFileExists(file)){
        file.open("saved.txt", std::ios::out | std::ios::trunc);
        file.close();
    }
}


void start(std::fstream& file){
    char choice = 0;

    while(choice != 'q') {
        clear();
        std::cout << "Welcome!\nInput your desired choice. ::\n";
        std::cout << "1 -> Add Webpages ::\n";
        std::cout << "2 -> View Saved ::\n";
        std::cout << "3 -> Test a Page ::\n";
        std::cout << "4 -> Run Saved Servers ::\n";
        std::cout << "5 -> Clear Saved ::\n";
        std::cout << "q -> Exit ::\n";
        std::cin >> choice;
        switch(choice){
            case '1':
                addPages(file);
                break;

            case '2':
                readPages(file);
                break;

            case '3':
                testPage();
                break;

            case '4':
                runSaved(file);
                break;

            case '5':
                clearFile(file);
                break;

            case 'q':
                std::cout << "Exit ::\n";
                exit(0);

            default:
                std::cout << "Not an option. ::\n";
                break;

        }
    }
}

void run(std::fstream& file){
    launch(file);
    start(file);
}

int main() {
    std::fstream file;
    run(file);
    return 0;
}
