//my code
#ifndef COUNTRY_2020_H
#define COUNTRY_2020_H

#include <string>
#include <vector>
#include <map>
#include "Candlestick.h"

//this Country2020 class handles temperature data for various countries allowing for predicting 2020 OHCL values
class Country2020 {
private:
    //stores the temperature data for each country using country code.
    std::map<std::string, std::vector<double>> countryData;
    //list of country codes
    std::vector<std::string> countryCodes;
    //loads temperature data from a CSV file 
    void loadData(const std::string& filepath);

public:
    //constructor that initializes the class by loading data from the provided file
    Country2020(const std::string& filepath);
    //gets the temperature data for a specific country code
    const std::vector<double>& getTemperatureData(const std::string& country) const;
    //returns a list of all available country codes
    const std::vector<std::string>& getCountryCodes() const;
    //computes candlestick data a countrys
    std::vector<Candlestick> computeCandlestick(const std::string& country) const;
    //computes 2020 OHCL values for any selected country
    std::tuple<double, double, double, double> compute2020Values(const std::string& countryCode) const;

};

#endif
//my code
