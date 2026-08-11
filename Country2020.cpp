//my code
#include "Country2020.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <numeric>
#include <map>
#include "Candlestick.h"


//constructor
Country2020::Country2020(const std::string& filepath) {
    loadData(filepath);
}

//loads data from file
void Country2020::loadData(const std::string& filepath) {
    std::ifstream file(filepath);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file!" << std::endl;
        return;
    }

    std::string line, header;
     //reads the header line
    getline(file, header);
    std::istringstream headerStream(header);
    std::string colName;

    //extracting the country codes from the header
    while (getline(headerStream, colName, ',')) {
        if (colName != "utc_timestamp") {
            countryCodes.push_back(colName.substr(0, 2));
            countryData[colName.substr(0, 2)] = std::vector<double>();
        }
    }

    //reading temperature data
    while (getline(file, line)) {
        std::istringstream lineStream(line);
        std::string value;
        int colIndex = 0;

        while (getline(lineStream, value, ',')) {
            if (colIndex > 0) { 
                //skips the timestamp column
                countryData[countryCodes[colIndex - 1]].push_back(std::stod(value));
            }
            colIndex++;
        }
    }
}

//gets the country codes
const std::vector<std::string>& Country2020::getCountryCodes() const {
    return countryCodes;
}


std::vector<Candlestick> Country2020::computeCandlestick(const std::string& country) const {
    //retrieves temperature data for the country
    const auto& temperatures = countryData.at(country);
    std::map<std::string, std::vector<double>> yearlyData;

    //grouping the data by year
    for (size_t i = 0; i < temperatures.size(); ++i) {
        std::string year = std::to_string(1980 + (i / (365 * 24)));  // Adjust year calculation
        yearlyData[year].push_back(temperatures[i]);
    }

    std::vector<Candlestick> candlesticks;
    double previousClose = 0.0;

    for (const auto& [year, temps] : yearlyData) {
        //finds highest temperature of the year
        double high = *std::max_element(temps.begin(), temps.end());
        //finds lowest temperature of the year
        double low = *std::min_element(temps.begin(), temps.end());
        //calculates average temperature
        double close = std::accumulate(temps.begin(), temps.end(), 0.0) / temps.size();
        //uses the previous years close as the current years open
        double open = previousClose;

        candlesticks.emplace_back(year, open, high, low, close);
        previousClose = close;
    }

    return candlesticks;
}

std::tuple<double, double, double, double> Country2020::compute2020Values(const std::string& countryCode) const {
    //generates candlestick data for a country
    const auto& candlesticks = this->computeCandlestick(countryCode);

    double sumOpen = 0.0, sumHigh = 0.0, sumLow = 0.0, sumClose = 0.0;
    //getting the number of candlesticks
    int count = candlesticks.size();

    for (const auto& candle : candlesticks) {
        //accumulates open
        sumOpen += candle.open;
        //accumulates high
        sumHigh += candle.high;
        //accumulates low
        sumLow += candle.low;
        //accumulates close
        sumClose += candle.close;
    }

    return {
        //average open
        sumOpen / count,
        //average high
        sumHigh / count,
        //average low
        sumLow / count,
        //average close
        sumClose / count
    };
}
//my code