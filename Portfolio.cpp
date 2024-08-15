#include "Portfolio.h"
#include <iostream> // For outputting error messages

// Constructor
Portfolio::Portfolio() {
    // Default constructor implementation, if needed
}

// Method to invest in a stock
void Portfolio::invest_in_stock(const Stock& stock, int shares) {
    if (shares <= 0) {
        cerr << "Error: Number of shares must be positive." << endl;
        return;
    }
    m_stocks[stock] += shares;
}

// Method to get the value of a specific stock
double Portfolio::get_stock_value(const Stock& stock) {
    if (m_stocks.find(stock) != m_stocks.end()) {
        return m_stocks[stock] * stock.get_price(); 
    } 
    else {
        return 0.0; 
    }
}

// Method to get the total value of all stocks in the portfolio
double Portfolio::get_total_value() {
    if ()
}

// Method to get the number of shares of a specific stock
int Portfolio::get_number_of_shares(const Stock& stock) {
  
}
