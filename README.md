# Temperature Viewer

A C++ command-line app that analyses hourly European temperature data (1980–2019) and shows it as yearly **OHLC** (Open, High, Low, Close) values. It draws **candlestick charts** right in the terminal and gives a simple **2020 prediction** for each country.

Built as the midterm project for an Object-Oriented Programming course.

## Features

- **Yearly OHLC table** for any of 28 European countries
  - **Open**: the previous year's average temperature
  - **High / Low**: the year's highest and lowest hourly temperature
  - **Close**: the year's average temperature
- **Terminal candlestick chart** over a year range you choose. Green candles mean the year was warmer than the year before; red candles mean it was colder.
- **2020 prediction**: averages the OHLC values across all years and shows them as a colour-coded bar graph.

## Dataset

`weather_data.csv` holds hourly temperatures (°C) from `1980-01-01` to `2019-12-31`, with one column per country:

`AT BE BG CH CZ DE DK EE ES FI FR GB GR HR HU IE IT LT LU LV NL NO PL PT RO SE SI SK`

## Project Structure

| File | Purpose |
|------|---------|
| `main.cpp` | Entry point: loads the data and runs the main menu loop |
| `Candlestick.h/.cpp` | `Candlestick` class: holds one year's date and OHLC values |
| `CountryTemperature.h/.cpp` | Loads the CSV and computes yearly candlesticks (1980–2019) |
| `Country2020.h/.cpp` | Loads the CSV and computes the predicted 2020 OHLC values |
| `CandlestickPlotter.h/.cpp` | Draws the ASCII candlestick chart with ANSI colours |
| `Menu.h/.cpp` | Menus for picking a country and viewing results |
| `Object Oriented Programming Report.pdf` | Project report |
| `CODE.pdf` | Printed source code |

### OOP concepts used

- **Encapsulation**: each class keeps its data private (`countryData`, `countryCodes`) and exposes it through const getters.
- **Abstraction**: `Menu` handles user interaction and leaves data processing to `CountryTemperature`/`Country2020` and drawing to `CandlestickPlotter`.
- **Composition**: `Menu` holds references to the data classes and owns a `CandlestickPlotter`.
- **Constructor overloading**: `Menu` has constructors for one or both data sources.

## Build & Run

You need a C++17 compiler (g++ or clang++).

### Quick start (one command)

Run this command in the terminal. It downloads the project from GitHub into a temporary folder, compiles it and starts the program:

```bash
D=$(mktemp -d) && gh repo clone Alizea2/Temperature-Viewer "$D" && cd "$D" && g++ -std=c++17 *.cpp -o TemperatureViewer && ./TemperatureViewer
```

> This needs the [GitHub CLI](https://cli.github.com/) (`gh`) signed in to an account that can access this repository.

### Manual build

From inside the project folder:

```bash
g++ -std=c++17 *.cpp -o TemperatureViewer
./TemperatureViewer
```

Run the program from the folder that contains `weather_data.csv`. Loading the data takes a few seconds.

## Usage

```
======================= Menu =======================
1. OCHL Values & Candlesticks
2. Predicting OCHL Values for 2020
0. Exit
```

1. Pick **1**, choose a country number, then enter a start and end year to draw the candlestick chart.
2. Pick **2** and choose a country to see its predicted 2020 values and bar graph.
3. Enter **0** to go back or exit.

> Tip: widen your terminal. The candlestick chart is 100 rows tall and each year adds a column.

## Author

[@Alizea2](https://github.com/Alizea2)
