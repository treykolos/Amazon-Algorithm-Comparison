#pragma once
//This file will contain the function to extract data from a CSV file (used to get data from amazon excel)
// When reading the amazon file, the listing's properties will be stored into a custom object meant to hold info about listings
// Extract CSV data, if the file has too much info, skip some of the lines until the next comma that is relevant

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <string>
#include <algorithm>
#include <cctype>
#include <locale>
#include "Listing.h"

// Helper function to remove commas and currency symbols
std::string cleanNumericString(std::string str) {
    str.erase(std::remove_if(str.begin(), str.end(), [](char c) {
        // Value is casted to unsigned char to prevent assertion error from negative numbers (found in URL which are skipped)
        return !isdigit(static_cast<unsigned char>(c)) && c != '.';
        }), str.end());
    return str;
}

// Function to parse a CSV field, considering quoted fields
std::string parseCSVField(std::stringstream& ss) {
    std::string field;

    if (ss.eof()) {
        return "";  // Return empty string if end of file is reached
    }

    char nextChar = ss.peek();

    // Check if the field starts with a quote
    if (nextChar == '"') {
        // Consume the opening quote
        ss.get();

        // Read characters until the closing quote
        std::getline(ss, field, '"');

        // If the stream is still good, discard the next character if it's a comma
        if (ss.good() && ss.peek() == ',') {
            ss.get();
        }
    }
    else {
        // Read the field up to the next comma
        std::getline(ss, field, ',');
    }

    return field;
}


std::map<std::string, Listing> readCSV(const std::string& filename) {
    std::map<std::string, Listing> listings;
    std::ifstream file(filename);
    std::string line, name, category;
    int numRatings;
    float rating, price;

    // Skip the header line
    if (file.good()) {
        getline(file, line);
    }

    while (getline(file, line)) {
        std::stringstream ss(line);

        // Parse name
        name = parseCSVField(ss);

        // Parse main category
        category = parseCSVField(ss);

        // Skip sub_category, image, and link
        for (int i = 0; i < 3; ++i) parseCSVField(ss);

        // Parse ratings
        rating = std::stof(parseCSVField(ss));

        // Parse number of ratings
        std::string numRatingsStr = cleanNumericString(parseCSVField(ss));
        numRatings = std::stoi(numRatingsStr);

        // Skip discount price
        parseCSVField(ss);

        // Parse actual price
        std::string priceStr = cleanNumericString(parseCSVField(ss));
        price = std::stof(priceStr);

        // Create Listing object out of parsed values
        listings[name] = Listing(category, numRatings, rating, price);
    }

    return listings;
}