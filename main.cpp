#include <iostream>
#include <fstream>
#include <vector>
#include "File.h"

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

    if(!std::system(cmd.c_str()))
        return true;
    else
        return false;

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
    if(success.empty() and fail.empty())
        return;
    clear();
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

void launch(File& file){
    if(file.checkFileExists()){
        runSaved(file.file);
    }
}

void start(File& file){
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
                file.addPages();
                clear();
                break;

            case '2':
                file.readFile();
                clear();
                break;

            case '3':
                testPage();
                clear();
                break;

            case '4':
                runSaved(file.file);
                clear();
                break;

            case '5':
                file.clearFile();
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

void run(File& file){
    launch(file);
    start(file);
}

int main() {
    File saved("saved.txt");

    run(saved);
    return 0;
}
