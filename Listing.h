#pragma once
// This file contains the custom class object for Amazon Listings
// map is sorted by name with leading spaces, then capitals, then lowercase alphabetically by default

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <unordered_map>
#include <string>

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
