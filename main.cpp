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
    std::string filename = "Files/test.csv";
    auto listings = readCSV(filename);

    for (const auto& pair : listings) {
        std::cout << "Name: " << pair.first
            << ", Category: " << pair.second.getCategory()
            << ", Num Ratings: " << pair.second.getNumRatings()
            << ", Rating: " << pair.second.getRating()
            << ", Price: $" << pair.second.getPrice() << std::endl;
    }

    return 0;
}