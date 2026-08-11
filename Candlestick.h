//my code
#ifndef CANDLESTICK_H
#define CANDLESTICK_H

#include <string>
#include <iostream>

//candlestick class models OHLC data for a specific date
class Candlestick {
public:
    //attributes representing the date and OHLC values
    std::string date; 
    double open;      
    double high;     
    double low;       
    double close;     

    //constructor to initialize a candlestick with the given parameters
    Candlestick(const std::string& date, double open, double high, double low, double close)
        : date(date), open(open), high(high), low(low), close(close) {}

    //displaying the candlestick data in a simple format
    void display() const {
        //printing the OHCL values
        std::cout << date << " " 
                  << open << " "  
                  << high << " "  
                  << low << " "   
                  << close << std::endl; 
    }
};

#endif
//my code