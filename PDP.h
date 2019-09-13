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

public:
    PDP(std::vector<int> deltaX) {
        this->deltaX = deltaX;
        BBd(this->deltaX);
    }

    void BBd(std::vector<int> multiSet) {
        int width = deltaX.back();
        deltaX.pop_back();

        X.push_back(0);
        X.push_back(width);

        Place(width, deltaX, X);
    }

    bool isSubset(const std::vector<int> &subset, const std::vector<int> &parentSet) {
        for(const auto &s: subset) {
            if(std::find(parentSet.begin(), parentSet.end(), s) == parentSet.end())
                return false;
        }
        return true;
    }

    void removeSubsetFromParentSet(const std::vector<int> subset, std::vector<int> &parentSet) {
        // if X.at(i) == deltaX.at(j)
        for(const auto &s: subset) {
            parentSet.erase(std::remove(parentSet.begin(), parentSet.end(), s), parentSet.end());
        }
    }

    void remove(int y, std::vector<int> &v) {
        int size = v.size();
        for(int i = 0; i < size; i++) {
            if(v.at(i) == y) {
                v.erase(v.begin()+i);
            }
        }
    }

    // arg D is deltaX
    // arg X is the set that makes D = deltaX
    void Place(const int width, std::vector<int> &D, std::vector<int> &X) {
        // If deltaX is empty
        if(D.size() == 0) {
            // and if X is a subset of S
            if(isSubset(X,S)) {
                // add X to S
                for(const int i: D){
                    S.push_back(i);
                }
                // sort for clarity
                std::sort(S.begin(), S.end());
                return;
            }
        }

        // Max or final element in D
        int y = D.back();

        std::vector<int> deltaYX = getDeltas(y,X);

        if(isSubset(deltaYX, D)) {
            X.push_back(y);
            // Remove the elements deltaYX from D
            removeSubsetFromParentSet(deltaYX, D);
            Place(width, D, X);
            // Add deltaYX to D
            for(const int deltas: deltaYX){
                D.push_back(deltas);
            }
        }


        std::vector<int> widthYX = getDeltas(width-y, X);
        if(isSubset(widthYX, D)) {
            X.push_back(width-y);
            removeSubsetFromParentSet(widthYX, D);
            Place(width, D, X);
            remove(width-y, X);
            for(const int deltas: widthYX){
                D.push_back(deltas);
            }
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
