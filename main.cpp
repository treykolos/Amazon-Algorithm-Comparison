// Complexity comes in how the various sorting methods work with different categories of items
// The main function should also be able to accept input on which items to sort by, ex. "fishing rod" 
// only will sort fishing rod items. (will create a sub-map of only those items) (can be implemented with fixed categories)

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <unordered_map>
#include <string>
#include <chrono>
#include "Listing.h"
#include "Sorting.h"
#include "CSV.h"



int main() {
    int option = 0;
    int function = 0;
    std::string filename = "Files/test100.csv";
    // Initializes on 100 items test

    auto listings = readCSVGenerated(filename);

    std::cout << "What would you like to do?\n" << " 1. Test data extraction\n"
        << " 2. Test sorting algorithms\n" << " 3. Go to Menu\n";
    std::cin >> option;

    // Test CSV extraction functions
    if (option == 1) {
        std::cout << "What function would you like to run?\n" << " 1. Test Generated\n" <<
            " 2. Test Generated 100\n" << " 3. Test Backup\n" << " 4. Test Original\n";
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

            // Display the listings
            displayListings(listings);

            std::cout << "MergeSort Elapsed Time (in milliseconds): " << duration << std::endl;
        }

        // Run Quicksort test 100 (choose attribute to sort by)
        if (function == 2) {
            auto listings = readCSVGenerated(filename);

            // Mergesort the listings
            auto timeStart = std::chrono::high_resolution_clock::now();

            quickSort("price", listings, listings.begin(), listings.end());

            auto timeEnd = std::chrono::high_resolution_clock::now();
            double duration = std::chrono::duration_cast<std::chrono::milliseconds>(timeEnd - timeStart).count();

            // Display the listings
            displayListings(listings);

            std::cout << "Quicksort Elapsed Time (in milliseconds): " << duration << std::endl;
        }
    }


    // User menu / functionality
    if (option == 3) {
        bool continueLoop = true;
        std::cout << "Welcome to the Amazon Catalogue sorting tool!\n";


        while (continueLoop) {

            std::cout << "Current CSV File: " << filename << "\nWhat would you like to do? \n 1.Load a file"
                << "\n 2.Display the data \n 3.Sort the data \n 4.Exit\n";

            std::cin >> function;


            // Select the file to be sorted (displays load time of file)
            if (function == 1) {
                int fileSelection = 0;
                std::cout << "Select the file to load:\n 1. Input file name\n 2. Test 100000 items"
                    << "\n 3. Test 100 items\n";
                std::cin >> fileSelection;
                if (fileSelection == 1) {
                    std::cout << "Enter file name: ";
                    std::cin >> filename;

                    auto timeStart = std::chrono::high_resolution_clock::now();

                    listings = readCSVGenerated(filename);

                    auto timeEnd = std::chrono::high_resolution_clock::now();
                    auto loadTime = std::chrono::duration_cast<std::chrono::milliseconds>(timeEnd - timeStart).count();

                    std::cout << "Load time: " << loadTime << "ms\n\n";
                }
                else if (fileSelection == 2) {
                    filename = "Files/test.csv";

                    auto timeStart = std::chrono::high_resolution_clock::now();

                    listings = readCSVGenerated(filename);

                    auto timeEnd = std::chrono::high_resolution_clock::now();
                    auto loadTime = std::chrono::duration_cast<std::chrono::milliseconds>(timeEnd - timeStart).count();

                    std::cout << "Load time: " << loadTime << "ms\n\n";

                }
                else if (fileSelection == 3) {
                    filename = "Files/test100.csv";

                    auto timeStart = std::chrono::high_resolution_clock::now();

                    listings = readCSVGenerated(filename);

                    auto timeEnd = std::chrono::high_resolution_clock::now();
                    auto loadTime = std::chrono::duration_cast<std::chrono::milliseconds>(timeEnd - timeStart).count();

                    std::cout << "Load time: " << loadTime << "ms\n\n";
                }
            }

            // Display data
            else if (function == 2) {

                auto timeStart = std::chrono::high_resolution_clock::now();

                displayListings(listings);

                auto timeEnd = std::chrono::high_resolution_clock::now();
                auto displayTime = std::chrono::duration_cast<std::chrono::milliseconds>(timeEnd - timeStart).count();

                std::cout << "Time to display: " << displayTime << "ms\n\n";
            }

            // Sort the file data
            else if (function == 3) {
                // Select classification to sort by
                int classification = 0;
                std::cout << "What classification would you like to sort by?\n 1. Item name\n 2. Item category\n "
                    << "3. Number of reviews\n 4. Rating (out of 5)\n 5. Price (dollars)\n";
                std::cin >> classification;
                std::string sortBy;

                if (classification == 1) {
                    // sort for listing name
                    sortBy = "name";
                }

                else if (classification == 2) {
                    // sort for listing category
                    sortBy = "category";
                }

                else if (classification == 3) {
                    // sort for number of ratings
                    sortBy = "number_ratings";
                }

                else if (classification == 4) {
                    // sort for listing rating
                    sortBy = "rating";
                }

                else if (classification == 5) {
                    // sort for listing price
                    sortBy = "price";
                }


                // Mergesort the listings
                auto timeStartQuickSort = std::chrono::high_resolution_clock::now();

                std::cout << "Running QuickSort..." << std::endl;

                quickSort(sortBy, listings, listings.begin(), listings.end());
                std::cout << "Finished QuickSort!" << std::endl;

                auto timeEndQuickSort = std::chrono::high_resolution_clock::now();
                double durationQuickSort = std::chrono::duration_cast<std::chrono::milliseconds>(timeEndQuickSort - timeStartQuickSort).count();


                std::map<std::string, Listing> listings = readCSVGenerated(filename);


                auto timeStartMergeSort = std::chrono::high_resolution_clock::now();
                std::cout << "Running MergeSort..." << std::endl;

                mergeSort(sortBy, listings, 0, listings.size() - 1);
                std::cout << "Finished MergeSort!" << std::endl;

                auto timeEndMergeSort = std::chrono::high_resolution_clock::now();
                double durationMergeSort = std::chrono::duration_cast<std::chrono::milliseconds>(timeEndMergeSort - timeStartMergeSort).count();





                // Display the listings
                //displayListings(listings);

                std::cout << "QuickSort Elapsed Time (in milliseconds): " << durationQuickSort << std::endl;
                std::cout << "MergeSort Elapsed Time (in milliseconds): " << durationMergeSort << std::endl;



                // Sort by both merge sort and quick sort and display the time to sort for each.

            }

            // Exit the loop
            else if (function == 4) {
                continueLoop = false;
            }
        }
    }

    return 0;
}
