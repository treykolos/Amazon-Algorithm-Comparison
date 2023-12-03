#pragma once
// This file contains the custom class object for Amazon Listings
// map is sorted by name with leading spaces, then capitals, then lowercase alphabetically by default
// we need it sorted alphabetically by category and name (can keep leading spaces or delete) 
// and numerically (by rating, number of reviews, price)
// can also store listings in an unordered map (probably necessary)

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <unordered_map>
#include <string>

/*
class AmazonCatalogue {
private:
    // Unordered map for storing listings
    std::unordered_map<std::string, Listing> listings; 

public:
    // Methods to add, remove, update listings

    void displayListings() const {
        int index = 1;
        for (const auto& pair : listings) {
            std::cout << index << ". " << "Name: " << pair.second.getName()
                << ", Category: " << pair.second.getCategory()
                << ", Num Ratings: " << pair.second.getNumRatings()
                << ", Rating: " << pair.second.getRating()
                << ", Price: $" << pair.second.getPrice() << std::endl;
            index++;
        }
    }
    
    void readCSVGenerated(const std::string& filename) {
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

            // Assume parseCSVField is a function that correctly parses a CSV field
            name = parseCSVField(ss);
            category = parseCSVField(ss);
            numRatings = std::stoi(parseCSVField(ss));
            rating = std::stof(parseCSVField(ss));
            price = std::stof(parseCSVField(ss));

            // Add the Listing object to the class's unordered map
            listings[name] = Listing(name, category, numRatings, rating, price);
        }
    }
};
*/

class Listing {
private:
    std::string name;
    std::string category;
    int numRatings;
    float rating;
    float price;

public:
    // Default constructor (should not be needed)
    Listing() : name(""), category(""), numRatings(0), rating(0.0f), price(0.0f) {}

    // Parameterized constructor
    Listing(std::string name, std::string cat, int numRat, float rat, float pri)
        : name(name), category(cat), numRatings(numRat), rating(rat), price(pri) {}

    // Getters
    std::string getName() const { return name; }
    std::string getCategory() const { return category; }
    int getNumRatings() const { return numRatings; }
    float getRating() const { return rating; }
    float getPrice() const { return price; }
};

