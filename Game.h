#ifndef GAME_H
#define GAME_H

#include <vector>
#include <iostream>
#include "Stock.h"
#include "Portfolio.h"

using namespace std;

const string RESET = "\033[0m";
const string RED = "\033[31m";
const string GREEN = "\033[32m";
const string YELLOW = "\033[33m";
const string BLUE = "\033[34m";
const string MAGENTA = "\033[35m";
const string CYAN = "\033[36m";
const string WHITE = "\033[37m";

class Game {
public:
    // Constructor
    Game();

    // Getter and Setter for year
    int get_year() const { return m_year; }
    void set_year(int year) { m_year = year; }

    // Getter and Setter for index fund value
    double get_index_fund_value() const { return m_index_fund_value; }
    void set_index_fund_value(double value) { m_index_fund_value = value; }

    // Getter and Setter for portfolio
    const Portfolio& get_portfolio() const { return m_portfolio; }
    void set_portfolio(const Portfolio& portfolio) { m_portfolio = portfolio; }

    // Function declarations
    void start();
    void load();
    void menu();
    void display();
    void update();
    void read_news();
    void next_year();

    // Helper functions
    Sector string_to_sector(const string& sector) {
        if (sector == "TECH") return Sector::TECH;
        if (sector == "HEALTH") return Sector::HEALTH;
        if (sector == "FINANCE") return Sector::FINANCE;
        if (sector == "ENERGY") return Sector::ENERGY;
        if (sector == "CONSUMER") return Sector::CONSUMER;
        if (sector == "INDUSTRIALS") return Sector::INDUSTRIALS;
        if (sector == "UTILITIES") return Sector::UTILITIES;
        if (sector == "REAL_ESTATE") return Sector::REAL_ESTATE;
        if (sector == "COMMUNICATION") return Sector::COMMUNICATION;
        return Sector::UNKNOWN; 
    }

private:
    int m_year;
    double m_index_fund_value;

    Portfolio m_portfolio;

    vector<string> m_news; 
    vector<Sector> m_sector; 
    vector<double> m_impact;

    vector<Stock> m_stocks;  
};

#endif // GAME_H
