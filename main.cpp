#include <iostream>
#include <algorithm>
#include <fstream>

void start();

void clear(){
#ifdef _WIN32
    std::system("cls");
#elif __unix__
    std::system("clear");
#endif
}

void ping(std::string& input){

    std::cout << "Pinging " << input << "...\n";
#ifdef _WIN32
    std::string cmd("ping " + input + " -n 1");
#elif __APPLE__
    std::string cmd("ping " + input + " -c 1");
#endif

    if(!std::system(cmd.c_str())) {
        clear();
        std::cout << "Website is up and running! ::\n";
    }

    else{
        clear();
        std::cout << "This webpage / server seems to be DOWN ::\n";
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

        ping(input);

        std::cout << "\nEnter 'q' to quit or enter another IP/URL ::\n\n";

    }

    start();
}

bool checkFileExists(std::fstream &file){
    file.open("saved.txt", std::ios::out);
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
    std::string line;
    std::cout << "File: \n";
    while(getline(file, line)){
        std::cout << line << "\n";
    }
}

bool inFile(std::fstream &file, std::string &needle) {
    std::string line;
    file.open("saved.txt", std::ios::in);
    if(file.is_open()) {
        //std::cout << "File is open ::\n";
        readPages(file);
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

//return true;
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

            //file.open("saved.txt", std::ios::in | std::ios::out | std::ios::app);
            if (inFile(file, input)) {
                file.open("saved.txt", std::ios::app);
                std::cout << "Adding to list...\n";
                file << input << "\n";
                std::cout << "Connection added! ::\n\n";
                file.close();
            }

        }
    }

    start();
}


void start(){
    clear();

    std::fstream my_file;
    char choice = 0;

    std::cout << "Welcome!\nInput your desired choice. ::\n";
    std::cout << "1 -> Add Webpages ::\n";
    std::cout << "2 -> View Saved ::\n";
    std::cout << "3 -> Test a Page ::\n";
    std::cout << "q -> Exit ::\n";

    while(choice != 'q') {
        std::cin >> choice;
        switch(choice){
            case '1':
                std::cout << "Add Webpages ::\n";
                addPages(my_file);
                break;

            case '2':
                std::cout << "View Favorites ::\n";
                break;

            case '3':
                testPage();
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

void run(){
    start();
}

int main() {
    run();
    return 0;
}
