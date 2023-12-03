// This file will contain the main menu and will contain the headers for each individual algorithm as well as the CSV extraction tool
// Complexity comes in how the various sorting methods work with different categories of items
// The main function should also be able to accept input on which items to sort by, ex. "fishing rod" only will sort fishing rod items.

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <string>
#include "Listing.h"
#include "CSV.h"

int main() {
    int option = 0;

    std::cout << "What would you lke to do?\n" << "Test data extraction = 1\n" << "Test sorting algorithms = 2\n" << 
        "Go to Menu = 3\n";
    std::cin >> option;

    // Test CSV extraction functions
    if(option == 1){
        int function = 0;
        std::cout << "What function would you like to run?\n" << "Test Generated = 1\n" << "Test Backup = 2\n" << "Test Original = 3\n";
        std::cin >> function;

        if (function == 1) {
            std::string filename = "Files/test.csv";
            auto listings = readCSVGenerated(filename);
            int index = 1;

            for (const auto& pair : listings) {
                std::cout << index << ". " << "Name: " << pair.first
                    << ", Category: " << pair.second.getCategory()
                    << ", Num Ratings: " << pair.second.getNumRatings()
                    << ", Rating: " << pair.second.getRating()
                    << ", Price: $" << pair.second.getPrice() << std::endl;
                index++;
            }
        }

        if (function == 2) {
            std::string filename = "Files/test.csv";
            auto listings = readCSVBackup(filename);
            int index = 1;

            for (const auto& pair : listings) {
                std::cout << index << ". " << "Name: " << pair.first
                    << ", Category: " << pair.second.getCategory()
                    << ", Num Ratings: " << pair.second.getNumRatings()
                    << ", Rating: " << pair.second.getRating()
                    << ", Price: $" << pair.second.getPrice() << std::endl;
                index++;
            }
        }

        if (function == 3) {
            std::string filename = "Files/test.csv";
            auto listings = readCSVOriginal(filename);
            int index = 1;

            for (const auto& pair : listings) {
                std::cout << index << ". " << "Name: " << pair.first
                    << ", Category: " << pair.second.getCategory()
                    << ", Num Ratings: " << pair.second.getNumRatings()
                    << ", Rating: " << pair.second.getRating()
                    << ", Price: $" << pair.second.getPrice() << std::endl;
                index++;
            }
        }

    }
    
    // Test sorting algorithms
    if (option == 1) { return 0; }

    // User menu / functionality
    if (option == 1) { return 0; }

    return 0;
}