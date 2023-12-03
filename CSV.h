#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <unordered_map>
#include <string>
#include <algorithm>
#include <stdexcept>
#include "Listing.h"

// This file contains the function to extract data from a CSV file and its helpers 
// readCSVOriginal and readCSVBackup are obsolete, the datasets scraped from the internet were incomplete
// and hard to work with, so I generated my own CSV file using an online tool: "https://extendsclass.com/csv-generator.html"

// Function to parse a CSV field, considering quoted fields and leading empty spaces
std::string parseCSVField(std::stringstream& ss) {
    std::string field;

    if (ss.eof()) {
        return "";  // Return empty string if end of file is reached
    }

    // Skip leading spaces
    while (ss.peek() == ' ') {
        ss.get();
    }

    char nextChar = ss.peek();

    // Check if the field starts with a quote
    if (nextChar == '"') {
        // Consume the opening quote
        ss.get();
        std::ostringstream fieldStream;

        while (true) {
            if (ss.peek() == '"') {
                ss.get(); // Consume one quote
                if (ss.peek() == '"') {
                    // This is an escaped quote (double quote)
                    fieldStream << static_cast<char>(ss.get()); // Add one quote to the field
                }
                else {
                    // This is the closing quote
                    break;
                }
            }
            else {
                fieldStream << static_cast<char>(ss.get()); // Add the character to the field
            }
        }

        field = fieldStream.str();

        // If the stream is still good, discard the next character if it's a comma
        if (ss.good() && ss.peek() == ',') {
            ss.get();
        }
    }
    else {
        // Read up to the next comma
        std::getline(ss, field, ',');
    }

    return field;
}

// Reads CSV file and creates a map with the name as key and value as the Listing object (call before sorting)
// line format: name,category,number_of_reviews,rating,price
std::map<std::string, Listing> readCSVGenerated(const std::string& filename) {
    std::map<std::string, Listing> listings;
    std::ifstream file(filename);
    std::string line, name, category;
    int numRatings = 0;
    float rating = 0, price = 0;

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

        // Parse number of reviews
        std::string numRatingsStr = parseCSVField(ss);
        numRatings = std::stoi(numRatingsStr);

        // Parse ratings
        std::string ratingStr = parseCSVField(ss);
        rating = std::stof(ratingStr);

        // Parse actual price
        std::string priceStr = parseCSVField(ss);
        price = std::stof(priceStr);

        // Create Listing object out of parsed values
        listings[name] = Listing(name, category, numRatings, rating, price);
    }

    return listings;
}

// Function to read and then display CSV file (call for testing CSV extraction)
void readDisplayListings(std::string filename) {
    auto listings = readCSVGenerated(filename);
    int index = 1;
    for (auto& pair : listings) {
        std::cout << index << ". " << "Name: " << pair.second.getName()
            << ", Category: " << pair.second.getCategory()
            << ", Num Ratings: " << pair.second.getNumRatings()
            << ", Rating: " << pair.second.getRating()
            << ", Price: $" << pair.second.getPrice() << std::endl;
        index++;
    }
}

// Function to display the map of Listings (call after sorting)
void readListings(std::map<std::string, Listing> listings) {
    int index = 1;
    for (auto& pair : listings) {
        std::cout << index << ". " << "Name: " << pair.second.getName()
            << ", Category: " << pair.second.getCategory()
            << ", Num Ratings: " << pair.second.getNumRatings()
            << ", Rating: " << pair.second.getRating()
            << ", Price: $" << pair.second.getPrice() << std::endl;
        index++;
    }
}

// (obsolete)
// Helper function to remove commas and currency symbols
std::string cleanNumericString(std::string str) {
    str.erase(std::remove_if(str.begin(), str.end(), [](char c) {
        // Value is casted to unsigned char to prevent assertion error from negative numbers (found in URL which are skipped)
        return !isdigit(static_cast<unsigned char>(c)) && c != '.';
        }), str.end());
    return str;
}

// (obsolete)
// line format: name,main_category,sub_category,image,link,ratings,no_of_ratings,discount_price,actual_price
std::map<std::string, Listing> readCSVBackup(const std::string& filename) {
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

        // Parse ratings, if the string is empty assign 0
        std::string ratingStr = parseCSVField(ss);
        try {
            rating = ratingStr.empty() ? 0.0f : std::stof(ratingStr);
        }
        catch (const std::invalid_argument&) {
            rating = 0.0f;  // Assign default value if conversion fails
        }

        // Parse number of ratings, if the string is empty assign 0
        std::string numRatingsStr = cleanNumericString(parseCSVField(ss));
        try {
            numRatings = numRatingsStr.empty() ? 0 : std::stoi(numRatingsStr);
        }
        catch (const std::invalid_argument&) {
            numRatings = 0;  // Assign default value if conversion fails
        }

        // Skip discount price
        parseCSVField(ss);

        // Parse actual price, if the string is empty assign 0
        std::string priceStr = cleanNumericString(parseCSVField(ss));
        try {
            price = priceStr.empty() ? 0.0f : std::stof(priceStr);
        }
        catch (const std::invalid_argument&) {
            price = 0.0f;  // Assign default value if conversion fails
        }

        // Create Listing object out of parsed values
        listings[name] = Listing(name, category, numRatings, rating, price);
    }

    return listings;
}

// (obsolete)
// line format: Product Description,Price(Dollar),Number of  reviews,Real price(Dollar),Free days,Shipment,Delivery Date
std::map<std::string, Listing> readCSVOriginal(const std::string& filename) {
    std::map<std::string, Listing> listings;
    std::ifstream file(filename);
    std::string line, name, category;
    int numRatings;
    float rating = 0, price;

    // Skip the header line
    if (file.good()) {
        getline(file, line);
    }

    while (getline(file, line)) {
        std::stringstream ss(line);

        // Parse name
        name = parseCSVField(ss);

        // Parse price, if the string is empty assign 0
        std::string priceStr = cleanNumericString(parseCSVField(ss));
        price = priceStr.empty() ? 0.0f : std::stof(priceStr);

        // Parse number of ratings
        std::string numRatingsStr = cleanNumericString(parseCSVField(ss));
        numRatings = std::stoi(numRatingsStr);

        // Skip real price
        parseCSVField(ss);

        // Skip Free days
        parseCSVField(ss);

        // Skip shipment
        parseCSVField(ss);

        // Skip delivery date
        parseCSVField(ss);      

        // Create Listing object out of parsed values
        listings[name] = Listing(name, category, numRatings, rating, price);
    }

    return listings;
}

