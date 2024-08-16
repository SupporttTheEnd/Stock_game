// Portfolio.h
#ifndef PORTFOLIO_H
#define PORTFOLIO_H

#include <unordered_map>
#include <utility> 
#include "Stock.h"

class Portfolio {
public:
    // Constructor
    Portfolio(double starting_balance = 0.0);

    // Get and set for cash 
    double get_cash();
    void set_cash(double amount);

    // Methods for bank balance
    double get_bank_balance();
    void deposit_in_bank(double amount);
    void withdraw_from_bank(double amount); 

    // Methods to get portfolio values
    double get_stock_value(const Stock& stock);
    double get_total_value();
    int get_number_of_shares(const Stock& stock);

    // Methods for managing investments
    void invest_in_stock(const Stock& stock, int shares);
    void sell_stock(const Stock& stock, double shares);

private:
    int debt; 
    double m_cash; 
    double m_bank_balance; 
    unordered_map <Stock, int> m_stocks; // Stock and number of shares
};

#endif // PORTFOLIO_H
