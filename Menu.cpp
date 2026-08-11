//my code
#include "Menu.h"
#include <iostream>
#include <iomanip>

// Define the dummy objects
CountryTemperature Menu::dummyCountryTemperature("weather_data.csv");
Country2020 Menu::dummyCountry2020("weather_data.csv");


//displaying the list of countries for selection
void Menu::displayCountryList() {
    const auto& countries = tempData.getCountryCodes();
    std::cout << "=============== Countries ===============" << std::endl;
    for (size_t i = 0; i < countries.size(); i++) {
        //listing countries with numbering
        std::cout << i + 1 << ". " << countries[i] << std::endl; 
    }
    //option to return to the previous menu
    std::cout << "0. Back" << std::endl; 
}

//displaying OHLC data for the selected country and generatting a candlestick graph
void Menu::showCountryTemperature(const std::string& countryCode) {
    auto candlesticks = tempData.computeCandlestick(countryCode);

    //displaing yearly OHLC data in a table format
    std::cout << "\nYearly OHLC Data for " << countryCode << ":" << std::endl;
    std::cout << std::setw(10) << "Year" << " "
              << std::setw(10) << "Open" << " "
              << std::setw(10) << "High" << " "
              << std::setw(10) << "Low" << " "
              << std::setw(10) << "Close" << std::endl;

    for (const auto& candle : candlesticks) {
        std::cout << std::setw(10) << candle.date << " "
                  << std::setw(10) << candle.open << " "
                  << std::setw(10) << candle.high << " "
                  << std::setw(10) << candle.low << " "
                  //displaying each candlesticks data
                  << std::setw(10) << candle.close << std::endl; 
    }

    //prepareing data for the plotCandlesticks function
    std::vector<std::vector<std::string>> formattedCandlesticks;
    for (const auto& candle : candlesticks) {
        formattedCandlesticks.push_back({
            candle.date,
            std::to_string(candle.open),
            std::to_string(candle.high),
            std::to_string(candle.low),
            std::to_string(candle.close)
        });
    }

    //generating and displaying the candlestick graph
    std::cout << "\nCandlestick Graph:" << std::endl;
    plotter.plotCandlesticks(formattedCandlesticks);
}

//handlling the main menu interaction for selecting and displaying country data
void Menu::show() {
    while (true) {
        //showing the list of countries
        displayCountryList(); 
        std::cout << "Select a country by number : ";
        int choice;
        std::cin >> choice;

        //exits the menu
        if (choice == 0) { 
            break;
        }

        const auto& countries = tempData.getCountryCodes();
        if (choice > 0 && static_cast<size_t>(choice) <= countries.size()) {
            //displaying temperature data for the selected country
            showCountryTemperature(countries[choice - 1]);
        } else {
            //handle invalid input
            std::cerr << "Invalid choice! Please try again." << std::endl; 
        }
    }
}

void Menu::showCountry2020(const std::string& countryCode) {
    auto [avgOpen, avgHigh, avgLow, avgClose] = tempoData.compute2020Values(countryCode);
    std::cout << "\n2020 OHLC Values (Computed Averages):\n";
    std::cout << "Open: " << avgOpen << "\n";
    std::cout << "High: " << avgHigh << "\n";
    std::cout << "Low: " << avgLow << "\n";
    std::cout << "Close: " << avgClose << "\n";

    //plots the bar graph
    plotBarGraph(avgOpen, avgHigh, avgLow, avgClose);
}

void Menu::showed() {
    int choice;
    do {
        //displays the list of countries for users to select
        displayCountryList();
        std::cout << "Select a country by number : ";
        std::cin >> choice;

        //checking if the choice is valid and within the range of available countries
        if (choice > 0 && choice <= tempoData.getCountryCodes().size()) {
            std::string countryCode = tempoData.getCountryCodes()[choice - 1];
            //displaying the selcted countriies info
            showCountry2020(countryCode);
        }
    //exit    
    } while (choice != 0);
}

void Menu::plotBarGraph(double open, double high, double low, double close) {
    //height of the graph
    const int graphHeight = 10; 
    //width of each bar
    const int barWidth = 5;   

    //determining the range of values to normalize the graph
    double minValue = std::min({open, high, low, close});
    double maxValue = std::max({open, high, low, close});
    double range = maxValue - minValue;

    //normalizing the OHLC values
    int openHeight = static_cast<int>((open - minValue) / range * graphHeight);
    int highHeight = static_cast<int>((high - minValue) / range * graphHeight);
    int lowHeight = static_cast<int>((low - minValue) / range * graphHeight);
    int closeHeight = static_cast<int>((close - minValue) / range * graphHeight);

    //displaying the the OHLC values and prepare for graph visualization
    std::cout << "\nPredicted 2020 OHLC Values:\n";
    std::cout << "Open: " << open << ", High: " << high << ", Low: " << low << ", Close: " << close << "\n";
    std::cout << "Bar Graph:\n";

    //y axis labels
    std::cout << std::fixed << std::setprecision(2);
    for (int i = graphHeight; i >= 0; --i) {
        double yValue = minValue + (range * i / graphHeight);
        std::cout << std::setw(6) << yValue << " |";

        //renders a green color open bar
        std::cout << "\033[32m"; 
        std::cout << "|";
        for (int j = 0; j < barWidth; ++j) {
            if (i <= openHeight) {
                std::cout << "O"; 
            } else {
                std::cout << " ";
            }
        }
        //resets color
        std::cout << "\033[0m"; 
        std::cout << "|";

        //renders a red color high bar
        std::cout << "\033[31m"; 
        std::cout << "|";
        for (int j = 0; j < barWidth; ++j) {
            if (i <= highHeight) {
                std::cout << "H"; 
            } else {
                std::cout << " ";
            }
        }
        //resets color
        std::cout << "\033[0m"; 
        std::cout << "|";

        //renders a blue color low bar
        std::cout << "\033[34m"; 
        std::cout << "|";
        for (int j = 0; j < barWidth; ++j) {
            if (i <= lowHeight) {
                std::cout << "L"; 
            } else {
                std::cout << " ";
            }
        }
        //resets color
        std::cout << "\033[0m"; 
        std::cout << "|";

        //renders a yellow color close bar
        std::cout << "\033[33m"; 
        std::cout << "|";
        for (int j = 0; j < barWidth; ++j) {
            if (i <= closeHeight) {
                std::cout << "C"; 
            } else {
                std::cout << " ";
            }
        }
        //reseets color
        std::cout << "\033[0m"; 
        std::cout << "|\n";
    }

    //drawing the x axis
    std::cout << "       +";
    for (int i = 0; i < 4; ++i) {
        std::cout << std::string(barWidth + 2, '-');
    }
    std::cout << "+\n";

    //labeling the bars
    std::cout << "        Open    High    Low    Close\n";
}
//my code