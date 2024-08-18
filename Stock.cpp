// Stock.cpp
#include "Stock.h"

// Constructor
Stock::Stock(const string& name, double price, int volatility, int mean, Sector sector) {
    m_name = name; 
    m_price = price; 
    m_volatility = volatility; 
    m_mean = mean; 
    m_sector = sector; 
}

// Getters
string Stock::get_name() const {
    return m_name;
}

double Stock::get_price() const {
    return m_price;
}

double Stock::get_volatility() const {
    return m_volatility;
}

double Stock::get_mean() const {
    return m_mean;
}

Sector Stock::get_sector() const {
    return m_sector; 
}

// Setters
void Stock::set_name(const string& name) {
    m_name = name;
}

void Stock::set_price(double price) {
    if (price <= 0) {
        m_price = 0.01; 
        return;
    }
    m_price = price;
}

void Stock::set_volatility(double volatility) {
    m_volatility = volatility;
}

void Stock::set_mean(double mean) {
    m_mean = mean;
}

void Stock::set_sector(Sector sector){
    m_sector = sector; 
}

// Update stock price
void Stock::update_price(double price) {
    m_price = price;
}
