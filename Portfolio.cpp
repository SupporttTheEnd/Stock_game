#include "Portfolio.h"
#include <iostream> // For outputting error messages

// Constructor
Portfolio::Portfolio(double starting_balance = 0.0) {
    m_cash = starting_balance; 
    m_bank_balance = 0.0; 
}

// Get for bank balance
double Portfolio::get_bank_balance() {
    return m_bank_balance;
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
        return stock.get_price(); 
    } 
    else {
        return 0.0; 
    }
}

// Method to get the total value of all stocks in the portfolio
double Portfolio::get_total_value() {
    double total = 0.0; 

    for(const auto& pair : m_stocks){
        total += pair.second * pair.first.get_price();
    }

    return total; 
}

// Method to get the number of shares of a specific stock
int Portfolio::get_number_of_shares(const Stock& stock) {
    if (m_stocks.find(stock) != m_stocks.end()) {
        return m_stocks[stock]; 
    } 
    else {
        return 0.0; 
    }
}

// Desposit money into bank account
void Portfolio::deposit_in_bank(double amount) {
    if (amount <= 0){
        cerr << "Error: Invalid amount" << endl;
    }

    if (m_cash - amount >= 0){
        m_cash -= amount; 
        m_bank_balance += amount;
    }
    else {
        cerr << "Error: Insufficient funds" << endl;
    }
}

// Withdraw
void Portfolio::withdraw_from_bank(double amount){
    if (amount <= 0){
        cerr << "Error: Invalid amount" << endl;
    }

    if (m_bank_balance - amount >= 0){
        m_bank_balance -= amount; 
        m_cash += amount;
    }
    else {
        cerr << "Error: Insufficient funds" << endl;
    }
}

// Sell your stocks
void Portfolio::sell_stock(const Stock& stock, double shares){
    if (shares <= 0){
        cerr << "Error: Invalid amount" << endl;
    }

    if (m_stocks.find(stock) == m_stocks.end()) {
        cerr << "Error: Stock does not exist"; 
    } 

    if (m_stocks[stock] - shares >= 0){
        m_stocks[stock] -= shares; 
        m_cash += shares * stock.get_price();
    }
}
    