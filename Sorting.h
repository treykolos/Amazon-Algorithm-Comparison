#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <unordered_map>
#include <string>
#include <chrono>
#include "Listing.h"
#include "CSV.h"





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
        //std::cout << "1" << std::endl;

        bool compare;


        if (sortBy == "price") {
            compare = (*itLeft).second.getPrice() < (*itRight).second.getPrice();
        }
        else if (sortBy == "rating") {
            compare = (*itLeft).second.getRating() < (*itRight).second.getRating();
        }
        else if (sortBy == "number_ratings") {
            compare = (*itLeft).second.getNumRatings() < (*itRight).second.getNumRatings();
        }
        else if (sortBy == "name") {
            compare = (*itLeft).second.getName() < (*itRight).second.getName();
        }
        else if (sortBy == "category") {
            compare = (*itLeft).second.getCategory() < (*itRight).second.getCategory();
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
        //std::cout << "2" << std::endl;
        itMerged->second = itLeft->second;
        itLeft++;
        itMerged++;
    }

    while (itRight != rightMap.end()) {
        //std::cout << "3" << std::endl;

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
        else if (sortBy == "rating") {
            compare = it->second.getRating() < pivot->second.getRating();
        }
        else if (sortBy == "number_ratings") {
            compare = it->second.getNumRatings() < pivot->second.getNumRatings();
        }
        else if (sortBy == "name") {
            compare = it->second.getName() < pivot->second.getName();
        }
        else if (sortBy == "category") {
            compare = it->second.getCategory() < pivot->second.getCategory();
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
