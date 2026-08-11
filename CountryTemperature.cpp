//my code
#include "CountryTemperature.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <numeric>
#include <map>

CountryTemperature::CountryTemperature(const std::string& filepath) {
    loadData(filepath);
}

//loading temperature data from the file and organizes it into country specific 
void CountryTemperature::loadData(const std::string& filepath) {
    std::ifstream file(filepath);
    if (!file.is_open()) {
        //file opening error
        std::cerr << "Error: Could not open file!" << std::endl; 
        return;
    }

    std::string line, header;
    //reading the header line
    getline(file, header); 
    std::istringstream headerStream(header);
    std::string colName;

    //extracting country codes from the header
    while (getline(headerStream, colName, ',')) {
        //skips the timestamp
        if (colName != "utc_timestamp") { 
            countryCodes.push_back(colName.substr(0, 2)); 
            countryData[colName.substr(0, 2)] = std::vector<double>(); 
        }
    }

    //reading the remaining lines containing temperature data
    while (getline(file, line)) {
        std::istringstream lineStream(line);
        std::string value;
        int colIndex = 0;

        //distributing data into country vectors
        while (getline(lineStream, value, ',')) {
            if (colIndex > 0) { 
                //skips the timestamp column
                countryData[countryCodes[colIndex - 1]].push_back(std::stod(value));
            }
            colIndex++;
        }
    }
}

//returns temperature data for a country
const std::vector<double>& CountryTemperature::getTemperatureData(const std::string& country) const {
    //accesses the data using the country code
    return countryData.at(country); 
}

//returns the list of available countrirs
const std::vector<std::string>& CountryTemperature::getCountryCodes() const {
    return countryCodes; // Provide a reference to the country codes vector
}

//computing candlestick data for a given country's yearly temperature data
std::vector<Candlestick> CountryTemperature::computeCandlestick(const std::string& country) const {
    const auto& temperatures = countryData.at(country);
    std::map<std::string, std::vector<double>> yearlyData;

    //grouping temperature data by years
    for (size_t i = 0; i < temperatures.size(); ++i) {
        //calculates year based on index
        std::string year = std::to_string(1980 + (i / (365 * 24))); 
        yearlyData[year].push_back(temperatures[i]);
    }

    std::vector<Candlestick> candlesticks;
    double previousClose = 0.0;

    //creates candlesticks for each year till 2019
    for (const auto& [year, temps] : yearlyData) {
        if (std::stoi(year) > 2019) {
            break; 
        }
        //finds the highest and lowest temperature         
        double high = *std::max_element(temps.begin(), temps.end()); 
        double low = *std::min_element(temps.begin(), temps.end()); 
        //calculates average
        double close = std::accumulate(temps.begin(), temps.end(), 0.0) / temps.size(); 
        //uses the previous years close as the current years open
        double open = previousClose; 

       //adds candlestick for the year
        candlesticks.emplace_back(year, open, high, low, close);
        //updates the previous close for the next iteration
        previousClose = close; 
    }

    return candlesticks;
}
//my code