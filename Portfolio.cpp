#include "Portfolio.h"
#include <iostream> // For outputting error messages

// Constructor
Portfolio::Portfolio(double starting_balance) {
    m_cash = starting_balance; 
    m_bank_balance = 0.0; 
}

// Get cash 
double Portfolio::get_cash() {
    return m_cash; 
}

// Set Cash
void Portfolio::set_cash(double amount) {
    m_cash = amount; 
}

// Get for bank balance
double Portfolio::get_bank_balance() {
    return m_bank_balance;
}

// Desposit money into bank account
void Portfolio::deposit_in_bank(double amount) {
    if (amount <= 0){
        cerr << "Error: Invalid amount" << endl;
        return; 
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
        return; 
    }

    if (m_bank_balance - amount >= 0){
        m_bank_balance -= amount; 
        m_cash += amount;
    }
    else {
        cerr << "Error: Insufficient funds" << endl;
    }
}

// Method to get the value of a specific stock
double Portfolio::get_stock_value(const Stock& stock) {
    if (m_stocks.find(stock) != m_stocks.end()) {
        return stock.get_price() * get_number_of_shares(stock); 
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

// Method to invest in a stock
void Portfolio::invest_in_stock(const Stock& stock, int shares) {
    if (m_cash - stock.get_price() * shares >= 0) {
        m_cash = m_cash - stock.get_price() * shares; 
        m_stocks[stock] += shares;
    }
}

// Sell your stocks
void Portfolio::sell_stock(const Stock& stock, double shares){
    if (shares <= 0){
        return; 
    }

    if (m_stocks[stock] - shares >= 0){
        m_stocks[stock] = m_stocks[stock] - shares; 
        m_cash += shares * stock.get_price();
    }
}
    