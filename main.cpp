#include <iostream>
#include <algorithm>
#include <fstream>

void start();

void ping(std::string& input){

    std::cout << "Pinging " << input << "...\n";
    std::string cmd("ping " + input + " -c 1");

    if(!std::system(cmd.c_str())) {
        std::system("clear");
        std::cout << "Website is up and running! ::\n";
    }

    else{
        std::system("clear");
        std::cout << "This webpage / server seems to be DOWN ::\n";
    }

}

void testPage(){
    std::system("clear");
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
    file.open("saved.txt", std::ios::in);
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

bool inFile(std::fstream &file, std::string &needle) {
    std::string line;
    file.open("saved.txt", std::ios::in);
    if(file.is_open()) {
        //std::cout << "File is open ::\n";
        while (getline(file, line)) {
            //std::cout << line << "\n";
            if (line == needle) {
                std::cout << "Connection is already saved ::\n\n";
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
    std::system("clear");
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
    std::fstream my_file;

    std::system("clear");
    char choice;

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
