#pragma once
// This file will contain the custom class object for Amazon Listings
// An Amazon listing object contains the various properties of a listing such as price, rating, etc
// These properties will be called for each object in order to sort the amazon listing objects by the various properties
// Listing will have Name (object name), category, number of ratings, star rating, price

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <string>

class Listing {
private:
    std::string category;
    int numRatings;
    float rating;
    float price;

public:
    // Default constructor (should not be needed)
    Listing() : category(""), numRatings(0), rating(0.0f), price(0.0f) {}

    // Parameterized constructor
    Listing(std::string cat, int numRat, float rat, float pri)
        : category(cat), numRatings(numRat), rating(rat), price(pri) {}

    // Getters
    std::string getCategory() const { return category; }
    int getNumRatings() const { return numRatings; }
    float getRating() const { return rating; }
    float getPrice() const { return price; }
};