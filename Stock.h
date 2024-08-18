#ifndef STOCK_H
#define STOCK_H

#include <string>
#include <iostream>
#include <functional> // For std::hash

using namespace std;

enum Sector {
    TECH,
    HEALTH,
    FINANCE,
    ENERGY,
    CONSUMER,
    INDUSTRIALS,
    UTILITIES,
    REAL_ESTATE,
    COMMUNICATION, 
    UNKNOWN
};

class Stock {
public:
    // Constructor
    Stock(const string& name, double price, int volatility, int mean, Sector sector);
    
    // Getter and Setter for stock name
    string get_name() const;
    void set_name(const string& name);

    // Getter and Setter for stock price
    double get_price() const;
    void set_price(double price);

    // Getter and Setter for volatility
    int get_volatility() const;
    void set_volatility(int volatility);

    // Getter and Setter for mean
    int get_mean() const;
    void set_mean(int mean); 

    // Getter and Setter for sector
    Sector get_sector() const;
    void set_sector(Sector sector);

    // Method to update stock price
    void update_price(double price); 

    // Overloaded equality operator
    bool operator==(const Stock& other) const {
        return m_name == other.m_name && m_sector == other.m_sector;
    }

private:
    string m_name;
    double m_price;
    int m_volatility;
    int m_mean;
    Sector m_sector;
};

// Hash function for Stock
namespace std {
    template <>
    struct hash<Stock> {
        size_t operator()(const Stock& stock) const {
            size_t name_hash = hash<string>()(stock.get_name());
            size_t sector_hash = hash<int>()(static_cast<int>(stock.get_sector()));
            return name_hash ^ (sector_hash << 1);
        }
    };
}

#endif // STOCK_H
