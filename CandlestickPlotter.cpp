//used my teachers assisstance in this code
#include "CandlestickPlotter.h"
#include <iostream>
#include <iomanip>
#include <cmath>
#include <tuple>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

//using ANSI escape codes for colors
#define RED "\033[31m"  
#define GREEN "\033[32m" 
#define RESET "\033[0m"  

//normalizing a value for plotting and mapping the given value to a scale for graphical representation
int normalize(double value, double min, double max, int scale) {
    double normalizedValue = (value - min) / (max - min) * scale;
    //ensures values fit within the range
    int result = std::round(normalizedValue); 
    return result;
}

//filtering data based on the users selected year range and also ensuring only relevant years are included for processing
std::vector<std::vector<std::string>> filterDataByYearRange(
    const std::vector<std::vector<std::string>>& data, int startYear, int endYear) {
    std::vector<std::vector<std::string>> filteredData;

    for (const auto& row : data) {
        //extractig the year from date
        std::string yearString = row[0].substr(0, 4); 
        int year = std::stoi(yearString);
        if (year >= startYear && year <= endYear) {
            //adding rows that fit the year range
            filteredData.push_back(row); 
        }
    }

    return filteredData;
}

//getting the minimum and maximum years from the dataset that are usefull for determining available data bounderies
std::pair<int, int> getYearRange(const std::vector<std::vector<std::string>>& data) {
    int minYear = std::numeric_limits<int>::max();
    int maxYear = std::numeric_limits<int>::min();

    for (const auto& row : data) {
        //extracting year from date
        std::string yearString = row[0].substr(0, 4); 
        int year = std::stoi(yearString);
        //trackiing earliest and latest years
        minYear = std::min(minYear, year); 
        maxYear = std::max(maxYear, year); 
    }

    return {minYear, maxYear};
}

//ploting candlestick data for a given dataset
void CandlestickPlotter::plotCandlesticks(const std::vector<std::vector<std::string>>& ohlcData) {
    const int plotHeight = 100; 
    const int candlestickWidth = 10; 
    const double bufferFactor = 0.2; 

    if (ohlcData.empty()) {
        //informing the user about empty dataset
        std::cerr << "No data to plot!\n"; 
        return;
    }

    //getting the available year range from the dataset
    int minYear = std::numeric_limits<int>::max();
    int maxYear = std::numeric_limits<int>::min();
    for (const auto& row : ohlcData) {
        //extracting year from the date
        int year = std::stoi(row[0].substr(0, 4)); 
        minYear = std::min(minYear, year);
        maxYear = std::max(maxYear, year);
    }

    std::cout << "Available years: " << minYear << " to " << maxYear << "\n";

    //asking user for year range input
    int startYear, endYear;
    std::cout << "Enter the starting year: ";
    std::cin >> startYear;
    std::cout << "Enter the ending year: ";
    std::cin >> endYear;

    //validating the input year range given by user
    if (startYear < minYear || endYear > maxYear || startYear > endYear) {
        std::cerr << "Invalid year range. Please select between " << minYear << " and " << maxYear << ".\n";
        return;
    }

    //filterring data by the selected year range
    std::vector<std::vector<std::string>> filteredData;
    for (const auto& row : ohlcData) {
        //extractting year from the date
        int year = std::stoi(row[0].substr(0, 4)); 
        if (year >= startYear && year <= endYear) {
            filteredData.push_back(row); 
        }
    }

    if (filteredData.empty()) {
        std::cerr << "No data available for the selected year range!\n";
        return;
    }

    // Display the OHLC table for the user selected years 
    std::cout << "\n================= OHLC Values of Candlesticks =================\n";
    std::cout << std::setw(12) << "Date" << std::setw(12) << "Open"
              << std::setw(12) << "High" << std::setw(12) << "Low"
              << std::setw(12) << "Close\n";
    for (const auto& row : filteredData) {
        std::cout << std::setw(12) << row[0]
                  << std::setw(12) << std::fixed << std::setprecision(3) << row[1]
                  << std::setw(12) << row[2]
                  << std::setw(12) << row[3]
                  << std::setw(12) << row[4] << "\n";
    }
    std::cout << "================================================================\n";

    double globalHigh = -std::numeric_limits<double>::infinity();
    double globalLow = std::numeric_limits<double>::infinity();

    //finding global min and max for normalization
    for (const auto& row : filteredData) {
        double high = std::stod(row[2]);
        double low = std::stod(row[3]);
        globalHigh = std::max(globalHigh, high);
        globalLow = std::min(globalLow, low);
    }

    //bufferingcthe Y-axis range
    double range = globalHigh - globalLow;
    globalHigh += range * bufferFactor;
    globalLow -= range * bufferFactor;

    //precomputing the normalized positions for all candlesticks
    std::vector<std::tuple<int, int, int, int>> normalizedCandlesticks;
    for (const auto& row : filteredData) {
        double open = std::stod(row[1]);
        double high = std::stod(row[2]);
        double low = std::stod(row[3]);
        double close = std::stod(row[4]);

        int highPos = normalize(high, globalLow, globalHigh, plotHeight);
        int lowPos = normalize(low, globalLow, globalHigh, plotHeight);
        int openPos = normalize(open, globalLow, globalHigh, plotHeight);
        int closePos = normalize(close, globalLow, globalHigh, plotHeight);

        normalizedCandlesticks.emplace_back(highPos, lowPos, openPos, closePos);
    }

    //generating the candlesticks text based graph
    std::cout << "\n=============== Candlestick Graph ===============\n";
    for (int i = plotHeight; i >= 0; --i) {
        double labelValue = globalLow + (globalHigh - globalLow) * i / plotHeight;
        std::cout << std::setw(6) << std::fixed << std::setprecision(1) << labelValue << " |";

        for (size_t j = 0; j < filteredData.size(); ++j) {
            auto [highPos, lowPos, openPos, closePos] = normalizedCandlesticks[j];
            bool isUpward = closePos > openPos; // True if green candlestick

            std::string color = isUpward ? GREEN : RED;

            if (i <= highPos && i > std::max(openPos, closePos)) {
                std::cout << color << "   |    " << RESET;
            } else if (i == openPos) {
                std::cout << color << "  ---   " << RESET;
            } else if (i == closePos) {
                std::cout << color << "  ---   " << RESET;
            } else if (i < std::min(openPos, closePos) && i >= lowPos) {
                std::cout << color << "   |    " << RESET;
            } else {
                std::cout << "        ";
            }
        }
        std::cout << "\n";
    }

    //drawing x-axis
    std::cout << "       +";
    for (size_t j = 0; j < filteredData.size(); ++j) {
        std::cout << std::string(candlestickWidth, '-');
    }
    std::cout << "\n";

    //drawing x-axis dates
    std::cout << "       ";
    for (const auto& row : filteredData) {
        std::cout << std::setw(candlestickWidth) << row[0].substr(2, 5);
    }
    std::cout << "\n";
}
//used my teachers assisstance in this code