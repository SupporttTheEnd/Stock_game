// Stock.cpp
#include "Stock.h"

// Constructor
Stock::Stock(const string& name, double price, int volatility, int mean) {
    m_name = name; 
    m_price = price; 
    m_volatility = volatility; 
    m_mean = mean; 
}

// Getters
string Stock::get_name() const {
    return m_name;
}

double Stock::get_price() const {
    return m_price;
}

int Stock::get_volatility() const {
    return m_volatility;
}

int Stock::get_mean() const {
    return m_mean;
}

// Setters
void Stock::set_name(const string& name) {
    m_name = name;
}

void Stock::set_price(double price) {
    m_price = price;
}

void Stock::set_volatility(int volatility) {
    m_volatility = volatility;
}

void Stock::set_mean(int mean) {
    m_mean = mean;
}

// Update stock price
void Stock::update_price(double price) {
    m_price = price;
}
