//my code
#include <iostream>
#include "CountryTemperature.h"
#include "Country2020.h"
#include "Menu.h"

int main() {
    //specifying the path to the weather data file
    std::string filepath = "weather_data.csv";

    //loading temperature data and initializing the menu system
    CountryTemperature tempData(filepath);
    Country2020 tempoData(filepath);
    Menu menu(tempData, tempoData);

    //main application loop
    while (true) {
        //displaying the menu options
        std::cout << "======================= Menu =======================" << std::endl;
        std::cout << "1. OCHL Values & Candlesticks" << std::endl;
        std::cout << "2. Predicting OCHL Values for 2020 " << std::endl;
        std::cout << "0. Exit" << std::endl;
        std::cout << "Select one option: ";

        int choice;
        std::cin >> choice;

        //handles user input
        switch (choice) {
            case 1:
                //shows OHCL table and candlestick data
                menu.show(); 
                break;
            case 2:
                //shows predicted 2020 OHCL values
                menu.showed(); 
                break;
            case 0:
                //exit the program
                std::cout << " Goodbye :( " << std::endl;  
                return 0;
            default:
                //handles invalid input
                std::cout << "Invalid choice. Please try again." << std::endl; 
        }
    }
}
//my code