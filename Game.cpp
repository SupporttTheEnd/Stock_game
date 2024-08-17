#include "Game.h"

// Constructor
Game::Game() {
    // Initialize member variables
    m_year = 2000;
    m_index_fund_value = 1000;
}

// Method to start the game
void Game::start() {
    cout << "Welcome to Stock Game Player" << endl;
    load(); 
    update_news(); 
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

// Function to display the menu with highlighting
void Game::menu() {
    vector<string> options = {"View Stocks/Portfolio", "Read News", "Next Year", "Exit"};
    int selected_option = 0;
    char key;

    while (true) {
        system("cls"); // Clear screen

        display_header();

        // Print top border
        cout << string (20, ' ') << CYAN << "+" << string (86, '-') << "+" << RESET << endl;

        // Print instructions
        cout << string (20, ' ') << CYAN << "|" << RESET
            << string(4 , ' ') << CYAN
            << "Select an Option [Use " << GREEN << "'A'" << CYAN
            << " and " << GREEN << "'D'" << CYAN
            << " keys to navigate | Press " << GREEN << "'ENTER'" << CYAN
            << " to select]" << RESET
            << string(5 , ' ') << CYAN << "|" << RESET << endl;

        cout << string (20, ' ') << CYAN << "+" << string (86, '-') << "+" << RESET << endl;

        // Print menu options
        cout << string (20, ' ') << CYAN << "|" << string(10 , ' ') << RESET;
        for (int i = 0; i < options.size(); ++i) {
            if (i == selected_option) {
                cout << BOLD << GREEN << " > " << options[i] << RESET;
            } else {
                cout << "   " << options[i];
            }
            if (i < options.size() - 1) {
                cout << " | ";
            }
        }

        cout << string(12 , ' ') << CYAN << "|" << RESET << endl;

        cout << string (20, ' ') << CYAN << "+" << string (86, '-') << "+" << RESET << endl;

        key = _getch(); // Get the pressed key

        if (key == 'a' || key == 'A') { // Up arrow key
            selected_option = (selected_option - 1 + options.size()) % options.size();
        } else if (key == 'd' || key == 'D') { // Down arrow key
            selected_option = (selected_option + 1) % options.size();
        }

        // Pressing Enter should execute the selected option
        if (key == 13) { // Enter key
            system("cls");
            switch (selected_option) {
                case 0:
                    display_stocks();
                    break;
                case 1:
                    read_news();
                    break;
                case 2:
                    update();
                    break;
                case 3:
                    cout << "Exiting..." << endl;
                    return; // Exit the menu loop

            }
        }
    }
}

void Game::display_stocks() {
    // Initialize selected stock index
    int selected_index = 0;
    char key;
    string adjustment = string(10, ' ');
    bool buying_mode = true; // Start in buying mode

    while (true) {
        system("cls"); // Clear screen
        display_header();

        // Display stocks in a table format
        cout << adjustment << GREEN << string(50, '=') << "[";

        if(buying_mode) {
            cout << CYAN << "($Buying)" << RESET; 
        } else {
            cout << RED << "(Selling)" << RESET; 
        }   

        cout << GREEN << " Stocks]" << string(50, '=') << RESET << endl;

        // Header row
        string name_header = "Name";
        string price_header = "Price";
        string mean_growth_header = "Mean Growth";
        string shares_header = "Your Shares";
        string sector_header = "Sector";

        cout << adjustment << GREEN << "|$| " << RESET;
        cout << YELLOW << name_header << RESET << string(30 - name_header.length(), ' ') << "| "
             << YELLOW << price_header << RESET << string(13 - price_header.length(), ' ') << "| "
             << YELLOW << mean_growth_header << RESET << string(16 - mean_growth_header.length(), ' ') << "| "
             << YELLOW << shares_header << RESET << string(26 - shares_header.length(), ' ') << "| "
             << YELLOW << sector_header << RESET << string(16 - sector_header.length(), ' ')
             << RESET;

        cout << GREEN << " |$|" << RESET << endl;

        cout << adjustment << GREEN << "|$| " << RESET;
        cout << string(109, '-');
        cout << GREEN << " |$|" << RESET << endl;

        // Display each stock with highlighting for the selected stock
        for (int i = 0; i < m_stocks.size(); ++i) {
            const auto& stock = m_stocks[i];
            string name = stock.get_name();
            string mean_growth = "";
            string sector = sector_to_string(stock.get_sector());

            // Determine color based on mean growth
            string growth_color;
            if (stock.get_mean() < 0) {
                mean_growth = "-" + mean_growth;
                growth_color = RED;
            } else {
                mean_growth = "+" + mean_growth;
                growth_color = GREEN;
            }

            // Highlight the selected stock
            if (i == selected_index) {
                cout << adjustment << BOLD << BG_YELLOW << RED << ">>> " << WHITE;  // Highlight with background color
            } else {
                cout << adjustment << GREEN << "|$| " << RESET;
            }

            cout << left
                << name << string(30 - name.length(), ' ') << "| "
                << "$" << fixed << setprecision(2) << stock.get_price() << string(16 - to_string(stock.get_price()).length(), ' ') << "| "
                << growth_color << mean_growth
                << fixed << setprecision(2) << stock.get_mean() << " ("
                << fixed << setprecision(2) << stock.get_mean() / stock.get_price() - stock.get_mean() << "%)" << WHITE
                << string(16 - mean_growth.length() - to_string(stock.get_mean()).length() - to_string(stock.get_mean() / stock.get_price() - stock.get_mean()).length(), ' ') << "| "
                << RED << "NUM: " << WHITE << m_portfolio.get_number_of_shares(stock) << RED << " VAL: " << WHITE << m_portfolio.get_stock_value(stock) << WHITE
                << string(19 - to_string(m_portfolio.get_number_of_shares(stock)).length() - to_string(m_portfolio.get_stock_value(stock)).length(), ' ') << "| "
                << sector << WHITE << string(16 - sector.length(), ' ');

            if (i == selected_index) {
                cout << RED << " <<<" << RESET; // End highlight
            } else {
                cout << GREEN << " |$|" << RESET;
            }

            cout << endl;
        }

        // Display footer
        cout << adjustment << GREEN << string(117, '=') << RESET << endl;

        display_return();

        key = _getch(); // Get the pressed key

        if (key == 'w' || key == 'W') { // Move up
            selected_index = (selected_index - 1 + m_stocks.size()) % m_stocks.size();
        } else if (key == 's' || key == 'S') { // Move down
            selected_index = (selected_index + 1) % m_stocks.size();
        } else if (key == 'q' || key == 'Q') { // Toggle mode
            buying_mode = !buying_mode;
        } else if (key >= '0' && key <= '9') { // Handle number input for quantity
            int quantity = key - '0'; // Convert character to integer
            if (!buying_mode) {
                m_portfolio.sell_stock(m_stocks[selected_index], quantity);
            } else {
                m_portfolio.invest_in_stock(m_stocks[selected_index], quantity);
            }
        } else if (key == 13) { // ESC key to exit
            return;
        }
    }
}

void Game::update() {
    draw_clock();
    update_news(); 
}

void Game::read_news() {
    display_header();
    string adjustment = string(35, ' ');

    // Print ASCII art
    cout << adjustment << RED << " ___           _           _                _   _                   \n" << RESET;
    cout << adjustment << RED << "|_ _|_ __   __| |_   _ ___| |_ _ __ _   _  | \\ | | _____      _____ \n" << RESET;
    cout << adjustment << WHITE << " | || '_ \\ / _` | | | / __| __| '__| | | | |  \\| |/ _ \\ \\ /\\ / / __|\n" << RESET;
    cout << adjustment << WHITE << " | || | | | (_| | |_| \\__ \\ |_| |  | |_| | | |\\  |  __/\\ V  V /\\__ \\\n" << RESET;
    cout << adjustment << BLUE << "|___|_| |_|\\__,_|\\__,_|___/\\__|_|   \\__, | |_| \\_|\\___| \\_/\\_/ |___/\n" << RESET;
    cout << adjustment << BLUE << "                                    |___/                           \n" << RESET;

    // Print top border of the news box
    cout << CYAN << string(130, '-') << RESET << endl;

    // Print title
    cout << CYAN << "| " << BOLD << WHITE << "  Latest News  " << RESET << CYAN << " |" << string(110, ' ') << "|" << RESET << endl;
    cout << CYAN << string(130, '-') << RESET << endl;

    // Print news items inside the box
    for (int index : m_curr_news) {
        // Print news item with sector impact
        cout << CYAN << "| " << RESET
             << ORANGE << "- " << m_news[index] << RESET
             << string(90 - m_news[index].length(), ' ') << "| "
             << GREEN << "Sector Impacted: " << RESET 
             << sector_to_string(m_sector[index]) 
             << string(15 - sector_to_string(m_sector[index]).length(), ' ') 
             << CYAN << " |" << RESET << endl;
    }

    // Print bottom border of the box
    cout << CYAN << string(130, '-') << RESET << endl;

    // Print prompt to return
    display_return();

    // Wait for Enter key
    char key;
    do {
        key = getch();
    } while (key != 13);
}

void Game::draw_clock() {
    tm time_info = {};
    time_info.tm_hour = 23;
    time_info.tm_min = 59;
    time_info.tm_sec = 55;
    time_info.tm_mon = 11; // December
    time_info.tm_mday = 31;
    time_info.tm_year = m_year - 1900; // Year 2023

    while (true) {
        system("cls");
        cout << RED << " _    _                           _   _                __     __             \n";
        cout << ORANGE << "| |  | |                         | \\ | |               \\ \\   / /             \n";
        cout << YELLOW << "| |__| | __ _ _ __  _ __  _   _  |  \\| | _____      __  \\ \\_/ /__  __ _ _ __ \n";
        cout << GREEN << "|  __  |/ _` | '_ \\| '_ \\| | | | | . ` |/ _ \\ \\ /\\ / /   \\   / _ \\/ _` | '__|\n";
        cout << CYAN<< "| |  | | (_| | |_) | |_) | |_| | | |\\  |  __/\\ V  V /     | |  __/ (_| | |   \n";
        cout << BLUE << "|_|  |_|\\__,_| .__/| .__/ \\__, | |_| \\_|\\___| \\_/\\_/      |_|\\___|\\__,_|_|   \n";
        cout << MAGENTA << "             | |   | |     __/ |                                              \n";
        cout << WHITE << "             |_|   |_|    |___/                                              \n";
        cout << RESET; 
        // Update the tm structure to the current time
        time_info.tm_sec++;
        if (time_info.tm_sec >= 60) {
            time_info.tm_sec = 0;
            time_info.tm_min++;
        }
        if (time_info.tm_min >= 60) {
            time_info.tm_min = 0;
            time_info.tm_hour++;
        }
        if (time_info.tm_hour >= 24) {
            time_info.tm_hour = 0;
            time_info.tm_mday++;
        }
        if (time_info.tm_mday > 31) {
            time_info.tm_mday = 1;
            time_info.tm_mon++;
        }
        if (time_info.tm_mon > 11) {
            time_info.tm_mon = 0;
            time_info.tm_year++;
        }

        // Convert tm structure to time_t for formatted output
        time_t raw_time = mktime(&time_info);
        tm* local_time = localtime(&raw_time);

        // Exit if we have transitioned to the next year
        if (local_time->tm_year > m_year - 1900) {
            // Display the current date and time
            cout << "Calendar Animation" << endl;
            cout << "-------------------" << endl;
            cout << BOLD << YELLOW << "Date: " << put_time(local_time, "%Y-%m-%d") << endl;
            cout << "Time: " << put_time(local_time, "%H:%M:%S") << RESET << endl;

            this_thread::sleep_for(chrono::seconds(2));
            return; 
        } 

        // Display the current date and time
        cout << "Calendar Animation" << endl;
        cout << "-------------------" << endl;
        cout << "Date: " << put_time(local_time, "%Y-%m-%d") << endl;
        cout << "Time: " << put_time(local_time, "%H:%M:%S") << endl;
    
        // Wait for 1 second
        this_thread::sleep_for(chrono::seconds(1));
    }
}