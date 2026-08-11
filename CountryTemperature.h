//my code
#ifndef COUNTRY_TEMPERATURE_H
#define COUNTRY_TEMPERATURE_H

#include <string>
#include <vector>
#include <map>
#include "Candlestick.h"

//this CountryTemperature class handles temperature data for various countries allowing for retrieval and candlestick style analysis
class CountryTemperature {
private:
    //stores the temperature data for each country 
    std::map<std::string, std::vector<double>> countryData;
    //list of country codes
    std::vector<std::string> countryCodes;
    //loads temperature data from a CSV file 
    void loadData(const std::string& filepath);

public:
    //constructor that initializes the class by loading data from the provided file
    CountryTemperature(const std::string& filepath);
    //gets the temperature data for a specific country code
    const std::vector<double>& getTemperatureData(const std::string& country) const;
    //returns a list of all available country codes
    const std::vector<std::string>& getCountryCodes() const;
    //computes candlestick data a countrys
    std::vector<Candlestick> computeCandlestick(const std::string& country) const;

};

#endif
//my code