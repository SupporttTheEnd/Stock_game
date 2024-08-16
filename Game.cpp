#include "Game.h"
#include <fstream>
#include <sstream>
#include <iomanip>

// Constructor
Game::Game() {
    // Initialize member variables
    m_year = 0;
    m_index_fund_value = 1000;
}

// Method to start the game
void Game::start() {
    cout << "Welcome to Stock Game Player" << endl;
    load(); 
    menu(); 
}

void Game::load() {
    ifstream file("news.txt");
    if (!file.is_open()){
        cerr << "Failed to open news.txt" << std::endl;
        return;
    }

    string headline, sector, impact; 

    while(getline(file, headline, '|') && getline(file, sector, '|') && getline(file, impact)){
        m_news.push_back(headline);
        m_sector.push_back(string_to_sector(sector));
        m_impact.push_back(stoi(impact));
    }

    m_stocks.push_back(Stock("Apple Inc.", 175.0, 20, Sector::TECH));
    m_stocks.push_back(Stock("Pfizer Inc.", 43.0, 15, Sector::HEALTH));
    m_stocks.push_back(Stock("JPMorgan Chase & Co.", 155.0, 18, Sector::FINANCE));
    m_stocks.push_back(Stock("Exxon Mobil Corporation", 110.0, 22, Sector::ENERGY));
    m_stocks.push_back(Stock("Procter & Gamble Co.", 145.0, 10, Sector::CONSUMER));
    m_stocks.push_back(Stock("Caterpillar Inc.", 290.0, 25, Sector::INDUSTRIALS));
    m_stocks.push_back(Stock("Duke Energy Corporation", 97.0, 12, Sector::UTILITIES));
    m_stocks.push_back(Stock("Simon Property Group", 120.0, 17, Sector::REAL_ESTATE));
    m_stocks.push_back(Stock("Verizon Communications Inc.", 38.0, 19, Sector::COMMUNICATION));
}

void Game::menu() {
    display();
}

void Game::display() {
    // Display header
    cout << RED << "[Year: >> " << RESET << m_year << RED << " <<]" << RESET << string (30, ' ');
    cout << CYAN << "[Index Fund Value: " << RESET << "$" << m_index_fund_value << CYAN << "]" << RESET << endl;

    // Display stocks in a table format
    cout << GREEN << string(40, '=') << "[ Stocks ]" << string(40, '=') << RESET << endl;

    // Header row
    string name_header = "Name";
    string price_header = "Price";
    string mean_growth_header = "Mean Growth";
    string shares_header = "Your Shares";
    string sector_header = "Sector";

    cout << GREEN << "|$| " << RESET; 
    cout << YELLOW << name_header << RESET << string(30 - name_header.length(), ' ') << "| "
         << YELLOW << price_header << RESET << string(13 - price_header.length(), ' ') << "| "
         << YELLOW << mean_growth_header << RESET << string(16 - mean_growth_header.length(), ' ') << "| "
         << YELLOW << shares_header << RESET << string(16 - shares_header.length(), ' ') << "| "
         << YELLOW << sector_header << RESET << string(16 - sector_header.length(), ' ') 
         << RESET; 

    cout << GREEN << " |$|" << RESET << endl; 

    cout << GREEN << "|$| " << RESET; 
    cout << string(81, '-'); 
    cout << GREEN << " |$|" << RESET << endl; 

    for (const auto& stock : m_stocks) {
        // Data rows
        string name = stock.get_name();
        string mean_growth = "";
        string sector;

        // Determine the sector name
        switch (stock.get_sector()) {
            case TECH: sector = "Technology"; break;
            case HEALTH: sector = "Healthcare"; break;
            case FINANCE: sector = "Finance"; break;
            case ENERGY: sector = "Energy"; break;
            case CONSUMER: sector = "Consumer"; break;
            case INDUSTRIALS: sector = "Industrials"; break;
            case UTILITIES: sector = "Utilities"; break;
            case REAL_ESTATE: sector = "Real Estate"; break;
            case COMMUNICATION: sector = "Communication"; break;
            default: sector = "Unknown"; break;
        }

        // Determine color based on mean growth
        string growth_color;
        if (stock.get_mean() < 0) {
            mean_growth = "-" + mean_growth; 
            growth_color = RED;
        } else {
            mean_growth = "+" + mean_growth; 
            growth_color = GREEN;
        }

        cout << GREEN << "|$| " << RESET; 

        cout << left 
             << name << string(30 - name.length(), ' ') << "| "
             << "$" << fixed << setprecision(2) << stock.get_price() << string(16 - to_string(stock.get_price()).length(), ' ') << "| "
             << growth_color << mean_growth
             << fixed << setprecision(2) << stock.get_mean() << " (" 
             << fixed << setprecision(2) << stock.get_mean() / stock.get_price() - stock.get_mean() << "%)"<< RESET 
             << string(16 - mean_growth.length() - to_string(stock.get_mean()).length() - to_string(stock.get_mean() / stock.get_price() - stock.get_mean()).length(), ' ') << "| " 
             << RED << "SHARES: " << RESET << m_portfolio.get_number_of_shares(stock) << RED << "    VALUE: " << RESET << m_portfolio.get_stock_value(stock) << RESET
             << string(16 - to_string(m_portfolio.get_number_of_shares(stock)).length() - to_string(m_portfolio.get_stock_value(stock)).length(), ' ') << "| "
             << sector << RESET << string(16 - sector.length(), ' ');  

        cout << GREEN << " |$|" << RESET << endl; 
    }

    // Display footer
    cout << GREEN << string(90, '=') << RESET << endl;
}

void Game::update() {
    
}

