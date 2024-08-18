#ifndef GAME_H
#define GAME_H

#include <vector>
#include "Stock.h"
#include <fstream>
#include <sstream>
#include <cstdlib>  
#include <ctime>   
#include <conio.h>  // For _getch()
#include <iomanip>
#include <thread> // For sleep_for
#include <chrono> // For chrono literals

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
const string BOLD = "\033[1m";
const string ORANGE = "\033[38;5;208m";
const string PURPLE = "\033[38;5;129m"; 
const string BLACK = "\033[38;5;235m"; 

const string BG_WHITE = "\033[47m";   
const string BG_YELLOW = "\033[48;5;237m"; 

const int NUM_NEWS = 3; 

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
    void display_stocks();
    void update();
    void read_news();
    void next_year();
    void draw_clock();
    void bank(); 

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

    string sector_to_string(const Sector sector){
        if (sector == TECH) return "Technology";
        else if (sector == HEALTH) return "Healthcare";
        else if (sector == FINANCE) return "Finance";
        else if (sector == ENERGY) return "Energy";
        else if (sector == CONSUMER) return "Consumer";
        else if (sector == INDUSTRIALS) return "Industrials";
        else if (sector == UTILITIES) return "Utilities";
        else if (sector == REAL_ESTATE) return "Real Estate";
        else if (sector == COMMUNICATION) return "Communication";
        else return "Unknown";
    }

    void display_header() {
        // Display header
        cout << MAGENTA << string(136, '-') << endl;
        cout << RED << "[Year: >> " << RESET << m_year << RED << " <<]" << RESET << string (9, ' ');
        cout << YELLOW << "[Your Portfolio Value: " << RESET << "$" << fixed << setprecision(2) << m_portfolio.get_total_value() + m_portfolio.get_bank_balance() + m_portfolio.get_cash() << YELLOW << "]";
        cout << GREEN << "[CASH~" << RESET << "$" << fixed << setprecision(2) << m_portfolio.get_cash() << GREEN << "]";
        cout << ORANGE << "[STOCKS~" << RESET << "$" << fixed << setprecision(2) << m_portfolio.get_total_value() << ORANGE << "]"; 
        cout << BLUE << "[BANK~" << RESET  << "$" << fixed << setprecision(2) << m_portfolio.get_bank_balance() << BLUE << "]"; 
        cout << CYAN << string (9, ' ');
        cout << CYAN << "[Index Fund Value: " << RESET << "$" << m_index_fund_value << CYAN << "]" << RESET << endl;
        cout << MAGENTA << string(136, '-') << endl;
    }

    void display_return(){
        // Print top border
        cout << CYAN << string(40, ' ') << "+" << string(53, '-') << "+" << RESET << endl;

        // Print the prompt with side borders
        cout << CYAN << string(40, ' ') << "|" << RESET 
            << string(8, ' ') << CYAN 
            << BOLD << "Press " << GREEN << "\'ENTER\'" << CYAN << BOLD << "to return to the menu ..." << RESET 
            << string(7, ' ') << CYAN << "|" << RESET << endl;

        // Print bottom border
        cout << CYAN << string(40, ' ') << "+" << string (53, '-') << "+" << RESET << endl;
    }

    void update_news(){
        while(m_curr_news.size() < 3) {
            int random_index = rand() % m_news.size(); 
            
            if(find(m_curr_news.begin(), m_curr_news.end(), random_index) == m_curr_news.end()){
                m_curr_news.push_back(random_index);
            }
        }
    }
private:
    int m_year;
    double m_index_fund_value;

    Portfolio m_portfolio;

    vector<string> m_news; 
    vector<Sector> m_sector; 
    vector<double> m_impact;

    vector<int> m_curr_news; 
    vector<Stock> m_stocks;  
};

#endif // GAME_H
