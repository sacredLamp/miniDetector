#include <iostream>
#include <algorithm>

void start();

void testPage(){
    std::system("clear");
    std::string input;
    std::cout << "Enter website IP / URL ::\n";

    while(true){

        std::cin >> input;
        if(input == "q")
            break;

        std::string cmd("ping " + input + " -c 1");

        if(!std::system(cmd.c_str())) {
            std::system("clear");
            std::cout << "Website is up and running! ::\n";
        }
        else{
            std::system("clear");
            std::cout << "This webpage / server seems to be DOWN ::\n";
        }

        std::cout << "\nEnter 'q' to quit or enter another IP/URL ::\n\n";

    }
    start();
}


void start(){
    std::system("clear");
    char choice;

    std::cout << "Welcome!\nInput your desired choice. ::\n";
    std::cout << "1 -> Add Webpages ::\n";
    std::cout << "2 -> View Favorites ::\n";
    std::cout << "3 -> Test a Page ::\n";
    std::cout << "q -> Exit ::\n";

    while(choice != 'q') {
        std::cin >> choice;
        switch(choice){
            case '1':
                std::cout << "Add Webpages ::\n";
                break;

            case '2':
                std::cout << "View Favorites ::\n";
                break;

            case '3':
                testPage();
                break;
            case 'q':
                std::cout << "Exit ::\n";
                break;

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
