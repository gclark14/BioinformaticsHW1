//
// Created by Gabriel on 9/12/2019.
//

#ifndef BIOINFORMATICSHW1_PDP_H
#define BIOINFORMATICSHW1_PDP_H

#include <string>
#include <vector>
#include <algorithm>

class PDP {
private:
    std::vector<int> deltaX;
    std::vector<int> X;
    std::vector<int> S; // Solution set
    int placeCall = 1;

public:
    PDP(const std::vector<int> &deltaX) {
        this->deltaX = deltaX;
        BBd(this->deltaX);
    }

    // This remove function removes the last occurence of y in a sorted
    // vector by traversing the list backwords, deleting the first
    // occurence of y.
    void remove(int y, std::vector<int> &v) {
        int size = v.size();
        for(int i = size-1; i >= 0; i--){
            if(v.at(i) == y) {
                v.erase(v.begin()+i);
            }
        }
    }

    std::vector<int> getStartingIndices(const std::vector<int> &s, const std::vector<int> &v) {
        int pSize = v.size();
        int sSize = s.size();
        std::vector<int> indices;
        int j = 0;
        for(int i = 0; i < sSize; i++) {
            for(int k = 0; k < pSize; k++) {
                if(v.at(k) == s.at(i)){
                    indices.push_back(k);
                    break;
                }
            }
        }

        return indices;
    }

    bool isSubset(std::vector<int> &subset, const std::vector<int> &parentSet) {
        for(const auto &s: subset) {
            if(std::find(parentSet.begin(), parentSet.end(), s) == parentSet.end())
                return false;
        }
        return true;
    }

    // Only remove one occurrence of the subset from the parent set.
    void removeSubsetFromParentSet(std::vector<int> &subset, std::vector<int> &parentSet) {
        std::sort(subset.begin(), subset.end());
        std::vector<int> indices = getStartingIndices(subset, parentSet);

        // Delete backwards because the vector is going to be resizing
        int iSize = indices.size();
        for(int i = iSize - 1; i >= 0; i--) {
            parentSet.erase(parentSet.begin() + indices.at(i));
        }
    }

    void BBd(std::vector<int> multiSet) {
        int width = deltaX.back();
        deltaX.pop_back();

        X.push_back(0);
        X.push_back(width);

        Place(width, deltaX, X);
    }

    // arg D is deltaX
    // arg X is the set that makes D = deltaX
    void Place(const int width, std::vector<int> &deltaX, std::vector<int> &X) {
        // If deltaX is empty
        // 1
        if(deltaX.size() == 0) {
            // and if X is a subset of S
            // 2
            if(!isSubset(X, S)) {
                // add X to S
                // 3
                printX();
                merge(X,S);
                std::cout << '\n';
                // sort for clarity
                return;
            }
        }

        // Max aka final element in deltaX
        // 5
        int y = deltaX.back();

        // 6
        std::vector<int> deltaYX = getDeltas(y,X);
        sort(deltaYX);

        // 6
        if(isSubset(deltaYX, deltaX)) {
            // 7
            X.push_back(y);
            sort(X);

            // Remove the elements deltaYX from deltaX
            // 8
            removeSubsetFromParentSet(deltaYX, deltaX);

            // 7
            placeCall++;
            Place(width, deltaX, X);

            // Added this, might not be needed
            // 8
            remove(y,X);

            // Add deltaYX to deltaX
            // 9
            merge(deltaYX, deltaX);
        }

        // 11
        std::vector<int> widthYX = getDeltas(width-y, X);
        // 11
        if(isSubset(widthYX, deltaX)) {
            // 12
            X.push_back(width-y);
            sort(X);

            // 12
            removeSubsetFromParentSet(widthYX, deltaX);

            // 13
            placeCall++;
            Place(width, deltaX, X);

            // 14
            remove(width-y, X);
            // 14
            merge(deltaYX,deltaX);
        }

    }

    void sort(std::vector<int> &v) {
        std::sort(v.begin(), v.end());
    }

    void merge(const std::vector<int> &addFromVector, std::vector<int> &addToVector) {
        for(const int i: addFromVector) {
            addToVector.push_back(i);
            std::sort(addToVector.begin(), addToVector.end());
        }
    }

    // Generates the set X - y for all x in X
    std::vector<int> getDeltas(int y, const std::vector<int> &X){
        std::vector<int> deltas;
        for(int x: X) {
            deltas.push_back(std::abs(x-y));
        }
        return deltas;
    }

    void printX(){
        for(const int x: X) {
            std::cout << x << ' ';
        }
    }



};


#endif //BIOINFORMATICSHW1_PDP_H
