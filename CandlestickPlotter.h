//used my teachers assisstance in this code
#ifndef CANDLESTICK_PLOTTER_H
#define CANDLESTICK_PLOTTER_H

#include <vector>
#include <string>

//the CandlestickPlotter class provides functionality to visually plot candlestick graph
class CandlestickPlotter {
public:
    //plots the OHLC data as a candlestick graph
    void plotCandlesticks(const std::vector<std::vector<std::string>>& ohlcData);
};

#endif
//used my teachers assisstance in this code