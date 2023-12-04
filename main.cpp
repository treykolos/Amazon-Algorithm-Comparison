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
#include "Listing.h"
#include "CSV.h"
#include <chrono>


void merge(std::string sortBy, std::map<std::string, Listing>& listings, int const left, int const mid, int const right) {

    int const subMapOne = mid - left + 1;
    int const subMapTwo = right - mid;

    std::map<std::string, Listing> leftMap, rightMap;

    auto it = listings.begin();
    std::advance(it, left);
    leftMap.insert(it, std::next(it, subMapOne));

    it = listings.begin();
    std::advance(it, mid + 1);
    rightMap.insert(it, std::next(it, subMapTwo));

    auto itLeft = leftMap.begin();
    auto itRight = rightMap.begin();
    auto itMerged = listings.begin();

    std::advance(itMerged, left);

    while (itLeft != leftMap.end() && itRight != rightMap.end()) {

        bool compare;


        if (sortBy == "price") {
            compare = (*itLeft).second.getPrice() < (*itRight).second.getPrice();
        }
        else if (sortBy == "rating") {

        }

        if (compare) {
            itMerged->second = itLeft->second;
            itLeft++;
        }
        else {
            itMerged->second = itRight->second;
            itRight++;
        }
        itMerged++;
    }

    while (itLeft != leftMap.end()) {
        itMerged->second = itLeft->second;
        itLeft++;
        itMerged++;
    }

    while (itRight != rightMap.end()) {
        itMerged->second = itRight->second;
        itRight++;
        itMerged++;
    }

}

void mergeSort(std::string sortBy, std::map<std::string, Listing>& listings, const int begin, const int end) {

    if (begin >= end) {
        return;
    }

    int mid = begin + (end - begin) / 2;
    mergeSort(sortBy, listings, begin, mid);
    mergeSort(sortBy, listings, mid + 1, end);
    merge(sortBy, listings, begin, mid, end);

}

std::map<std::string, Listing>::iterator partition(const std::string& sortBy, std::map<std::string, Listing>& listings, std::map<std::string, Listing>::iterator start, std::map<std::string, Listing>::iterator end) {
    auto pivot = std::prev(end);
    auto pivotIndex = start;

    for (auto it = start; it != std::prev(end); ++it) {
        bool compare;

        if (sortBy == "price") {
            compare = it->second.getPrice() <= pivot->second.getPrice();
        }
        else {

        }

        if (compare) {
            std::swap(it->second, pivotIndex->second);
            ++pivotIndex;
        }
    }

    std::swap(pivot->second, pivotIndex->second);

    return pivotIndex;
}

void quickSort(const std::string& sortBy, std::map<std::string, Listing>& listings, std::map<std::string, Listing>::iterator start, std::map<std::string, Listing>::iterator end) {
    if (std::distance(start, end) <= 1) {
        return;
    }

    auto p = partition(sortBy, listings, start, end);

    quickSort(sortBy, listings, start, p);
    quickSort(sortBy, listings, std::next(p), end);
}


int main() {
    int option = 0;

    std::cout << "What would you like to do?\n" << "Test data extraction = 1\n"
        << "Test sorting algorithms = 2\n" << "Go to Menu = 3\n";
    std::cin >> option;

    // Test CSV extraction functions
    if (option == 1) {
        int function = 0;
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
        int function = 0;
        std::cout << "What function would you like to run?\n" << "Test Mergesort = 1\n"
            << "Test Quicksort = 2\n";
        std::cin >> function;

        // Run Mergesort test 100 (choose attribute to sort by)
        if (function == 1) {

            auto listings = readCSVGenerated(filename);

            // Mergesort the listings

            auto timeStart = std::chrono::high_resolution_clock::now();

            mergeSort("price", listings, 0, listings.size() - 1);

            auto timeEnd = std::chrono::high_resolution_clock::now();
            double duration = std::chrono::duration_cast<std::chrono::milliseconds>(timeEnd - timeStart).count();
            
            std::cout << "MergeSort Elapsed Time (in milliseconds): " << duration << std::endl;

            // Display the listings
            displayListings(listings);
        }

        // Run Quicksort test 100 (choose attribute to sort by)
        if (function == 2) {
            auto listings = readCSVGenerated(filename);

            // Mergesort the listings
            auto timeStart = std::chrono::high_resolution_clock::now();

            quickSort("price", listings, listings.begin(), listings.end());

            auto timeEnd = std::chrono::high_resolution_clock::now();
            double duration = std::chrono::duration_cast<std::chrono::milliseconds>(timeEnd - timeStart).count();

            std::cout << "Quicksort Elapsed Time (in milliseconds): " << duration << std::endl;

            // Display the listings
            displayListings(listings);
        }
    }

    // User menu / functionality (real practical use case with 100000 items)
    if (option == 3) { return 0; }

    return 0;
}
