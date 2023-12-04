#pragma once
// This file will contain the function for Quick Sort algorithm 
// sorts must be able to be done alphabetically and also numerically (including int and float, check if errors)
// can use 2 seperate functions to be called or include some way to recognize the variable to be sorted
// can create a function to run through a single step of the sorting algorithm at a time and then print to test i
// This file contains the function for Merge Sort algorithm 
// sorts must be able to be done alphabetically and also numerically (including int and float, check if errors)
// can use 2 seperate functions to be called or include some way to recognize the variable to be sorted
// can create a function to run through a single step of the sorting algorithm at a time and then print to test it

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <unordered_map>
#include <string>
#include "Listing.h"
#include "CSV.h"
#include <chrono>

/*
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

        bool compare = false;


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
        bool compare = false;

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
*/