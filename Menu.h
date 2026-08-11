//my code
#ifndef MENU_H
#define MENU_H

#include "CountryTemperature.h"
#include "Country2020.h"
#include "CandlestickPlotter.h" 

//this Menu class provides a user interface for interacting with temperature data allowing users to view OHLC values and generate candlestick graph
class Menu {
private:
    CountryTemperature& tempData; 
    Country2020& tempoData; 

    //dummy objects for initialization
    static CountryTemperature dummyCountryTemperature;
    static Country2020 dummyCountry2020;

    //instance of CandlestickPlotter for visualizing data
    CandlestickPlotter plotter;   

    //displaying a list of countries for user selection
    void displayCountryList();
    //displaying OHLC values and candlestick data for a specific country
    void showCountryTemperature(const std::string& countryCode);
    //displaying predicted 2020 OHCL values for a specific country
    void showCountry2020(const std::string& countryCode);

public:
   //constructor for CountryTemperature
    Menu(CountryTemperature& data) : tempData(data), tempoData(dummyCountry2020) {}
    //constructor for Country2020
    Menu(Country2020& data) : tempData(dummyCountryTemperature), tempoData(data) {}
    //new constructor for both CountryTemperature and Country2020
    Menu(CountryTemperature& data, Country2020& data2020) : tempData(data), tempoData(data2020) {}

    //declarations
    void show();
    void showed(); 
    void plotBarGraph(double open, double high, double low, double close);

};

#endif
//my code