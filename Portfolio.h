// Portfolio.h
#ifndef PORTFOLIO_H
#define PORTFOLIO_H

#include <unordered_map>
#include <utility> 
#include "Stock.h"

class Portfolio {
public:
    // Constructor
    Portfolio();

    // Methods for managing investments and bank account
    void invest_in_stock(const Stock& stock, int shares);

    // Methods to get portfolio values
    double get_stock_value(const Stock& stock);
    double get_total_value();
    int get_number_of_shares(const Stock& stock);

private:
    std::unordered_map <Stock, int> m_stocks; // Stock and number of shares
};

#endif // PORTFOLIO_H
