//
// Created by unriv on 9/11/2019.
//

#ifndef BIOINFORMATICSHW1_PARTIALDIGESTER_H
#define BIOINFORMATICSHW1_PARTIALDIGESTER_H

#include <vector>
#include "iostream"
#include "algorithm"

class PartialDigester {
private:
    std::vector<int> deltaX;
    std::vector<int> X;

public:
    PartialDigester() = default;
    PartialDigester(std::vector<int> deltaX) {
        this->deltaX = deltaX;
        digest();
    }

    // Generates a set = X - y for each x in X
    std::vector<int> getMultiSet(int y, std::vector<int> &X){
        std::vector<int> subset;

        // Generate subset
        for(const auto &x: X) {
            subset.push_back(abs(x-y));
        }

        return subset;
    }

    void digest() {
        this->X.push_back(0);
        this->X.push_back(this->deltaX.at(this->deltaX.size() - 1));
        removeSubsetFromParentSet(this->X, this->deltaX);

        int deltaXSize = this->deltaX.size();

        for(int i = 0; i < deltaXSize; i++) {
            int y = this->deltaX.at(i);
            std::vector<int> subset = getMultiSet(this->deltaX.at(i), this->X);
            if(isSubset(subset, this->deltaX)) {
                removeSubsetFromParentSet(subset, this->deltaX);
                this->X.push_back(y);
            }

        }

    }

    bool isSubset(std::vector<int> subset, std::vector<int> parentSet) {
        for(const auto &s: subset) {
            if(std::find(parentSet.begin(), parentSet.end(), s) == parentSet.end())
                return false;
        }
        return true;
    }

    void removeSubsetFromParentSet(std::vector<int> subset, std::vector<int> &parentSet) {
        // if X.at(i) == deltaX.at(j)
        for(const auto &s: subset) {
            parentSet.erase(std::remove(parentSet.begin(), parentSet.end(), s), parentSet.end());
        }
    }

    void printX() {
        for(const auto &x: this->X) {
            std::cout << x << " ";
        }
    }


};


#endif //BIOINFORMATICSHW1_PARTIALDIGESTER_H
