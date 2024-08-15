#ifndef STOCK_H
#define STOCK_H

#include <string>
#include <functional> // For std::hash

using namespace std;

class Stock {
public:
    // Constructor
    Stock(const string& name, double price, int volatility, int mean);
    
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

    // Method to update stock price
    void update_price(double price); 

    // Overloaded equality operator
    bool operator==(const Stock& other) const {
        return m_name == other.m_name &&
               m_price == other.m_price &&
               m_volatility == other.m_volatility &&
               m_mean == other.m_mean;
    }

private:
    string m_name;
    double m_price;
    int m_volatility;
    int m_mean;
};

// Hash function for Stock
namespace std {
    template <>
    struct hash<Stock> {
        size_t operator()(const Stock& stock) const {
            size_t name_hash = hash<string>()(stock.get_name());
            size_t price_hash = hash<double>()(stock.get_price());
            size_t volatility_hash = hash<int>()(stock.get_volatility());
            size_t mean_hash = hash<int>()(stock.get_mean());
            return name_hash ^ (price_hash << 1) ^ (volatility_hash << 2) ^ (mean_hash << 3);
        }
    };
}

#endif // STOCK_H
