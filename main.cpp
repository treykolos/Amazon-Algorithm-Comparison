// This file will contain the main menu and will contain the headers for 
// each individual algorithm as well as the CSV extraction tool 
// Complexity comes in how the various sorting methods work with different categories of items
// The main function should also be able to accept input on which items to sort by, ex. "fishing rod" 
// only will sort fishing rod items. (will create a sub-map of only those items) (can be implemented with fixed categories)

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <unordered_map>
#include <string>
#include <ctime>
#include "Listing.h"
#include "CSV.h"

int main() {
    int option = 0;
    int function = 0;

    std::cout << "What would you like to do?\n" << "Test data extraction = 1\n"
        << "Test sorting algorithms = 2\n" << "Go to Menu = 3\n";
    std::cin >> option;

    // Test CSV extraction functions
    if(option == 1){
        std::cout << "What function would you like to run?\n" << "Test Generated = 1\n" << "Test Generated 100 = 2\n" << "Test Backup = 3\n" << "Test Original = 4\n";
        std::cin >> function;

        if (function == 1) {
            std::string filename = "Files/test.csv";
            readDisplayListings(filename);
        }

        if (function == 2) {
            std::string filename = "Files/test100.csv";
            readDisplayListings(filename);
        }

        if (function == 3) {
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

        if (function == 4) {
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
    if (option == 2) {
        std::string filename = "Files/test100.csv";
        std::cout << "What function would you like to run?\n" << "Test Mergesort = 1\n" 
            << "Test Quicksort = 2\n";
        std::cin >> function;
        clock_t t;

        // Run Mergesort test 100 (choose attribute to sort by)
        if (function == 1) { 
            auto listings = readCSVGenerated(filename);

            // Mergesort the listings
            
            t = clock();
            std::cout << "Timer starts\n";
            auto mergesorted_listings = readCSVGenerated(filename);
            std::cout << "Timer ends \n";
            t = clock() - t;

            // Display the listings (always will be 100 items)
            displayListings(mergesorted_listings);
            std::cout << "items sorted: 100\n";
            std::cout << "sorting time: " << t << "\n";
        }

        // Run Quicksort test 100 (choose attribute to sort by)
        if (function == 2) { 
            auto listings = readCSVGenerated(filename);

            // Quicksort the listings

            t = clock();
            std::cout << "Timer starts\n";
            auto quicksorted_listings = readCSVGenerated(filename);
            std::cout << "Timer ends \n";
            t = clock() - t;

            // Display the listings
            displayListings(quicksorted_listings);
            std::cout << "items sorted: 100\n";
            std::cout << "sorting time: " << t << "\n";
        }
    }

    // User menu / functionality (real practical use case with 100000 items)
    if (option == 3) { return 0; }

    return 0;
}