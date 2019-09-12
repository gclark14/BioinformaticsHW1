//
// Created by unriv on 9/11/2019.
//

#ifndef BIOINFORMATICSHW1_PROFILER_H
#define BIOINFORMATICSHW1_PROFILER_H

#include <vector>
#include "iostream"
#include "fstream"

enum DNA { A,C,G,T };

#define FILEHANDLE "input2.txt"

class Profiler{
private:
    std::vector<std::string> dnaStrings;
    std::vector<std::vector<int>> profileMatrix; //4xn matrix
    std::string consensus;

    void initializeProfileMatrix(){
        profileMatrix.resize(4);
        for(int i = 0; i < 4; i++) {
            profileMatrix.at(i).resize(dnaStrings.at(0).size());
        }
    }

    void setStrings() {
        std::ifstream fin;
        std::string s;
        fin.open(FILEHANDLE);
        while(getline(fin,s)){
            dnaStrings.push_back(s);
        }
    }

    void generateProfileMatrix() {
        const int ROW = dnaStrings.size();
        const int COL = dnaStrings.at(0).size();

        for(int i = 0; i < ROW; i++) {
            for(int j = 0; j < COL; j++) {
                if(dnaStrings.at(i).at(j) == 'A') {
                    profileMatrix.at(A).at(j)++;
                }
                else if(dnaStrings.at(i).at(j) == 'C'){
                    profileMatrix.at(C).at(j)++;
                }
                else if(dnaStrings.at(i).at(j) == 'G'){
                    profileMatrix.at(G).at(j)++;
                } else {
                    profileMatrix.at(T).at(j)++;
                }
            }
        }
    }

    void generateConsensus() {
        const int COL = profileMatrix.at(0).size();

        char consensusValues[COL];
        int scores[COL];

        for(int j = 0; j < COL; j++) {
            int largest = 0;
            int largestNucleotide = 0;
            if (profileMatrix.at(A).at(j) > largest) {
                largest = profileMatrix.at(A).at(j);
                largestNucleotide = A;
            }
            if (profileMatrix.at(C).at(j) > largest) {
                largest = profileMatrix.at(C).at(j);
                largestNucleotide = C;
            }
            if (profileMatrix.at(G).at(j) > largest) {
                largest = profileMatrix.at(G).at(j);
                largestNucleotide = G;
            }
            if (profileMatrix.at(T).at(j) > largest) {
                largest = profileMatrix.at(T).at(j);
                largestNucleotide = T;
            }
            scores[j] = largest;
            if (largestNucleotide == A) {
                consensusValues[j] = 'A';
            } else if (largestNucleotide == C) {
                consensusValues[j] = 'C';
            }
            else if (largestNucleotide == G) {
                consensusValues[j] = 'G';
            } else {
                consensusValues[j] = 'T';
            }
        }

        std::cout << "Consensus\n";
        std::cout << "  ";
        int score = 0;
        for(int i = 0; i < COL; i++) {
            std::cout << scores[i] << " " ;
            score += scores[i];
        }

        std::cout << "\n  ";
        for(int i = 0; i < COL; i++) {
            std::cout << consensusValues[i] << " " ;
            consensus += (consensusValues[i]);
        }
        std::cout << std::endl;

    }

public:
    Profiler(){
        setStrings();
        initializeProfileMatrix();
        generateProfileMatrix();
        generateConsensus();
        std::cout << getHammingDistances() << std::endl;
    }

    void printStrings() {
        for(const std::string s: dnaStrings){
            std::cout << "  ";
            int length = s.length();
            for(int i = 0; i < length; i++) {
                std::cout << s.at(i) << " ";
            }
            std::cout << std::endl;
        }
    }

    void printProfileMatrix() {
        int j = 0;
        for(const std::vector<int> profiles: profileMatrix) {
            if(j == 0) {
                std::cout << "A ";
            } else if(j == 1) {
                std::cout << "C ";
            } else if(j == 2) {
                std::cout << "G ";
            } else {
                std::cout << "T ";
            }
            for(const int i: profiles) {
                std::cout << i << " ";
            }
            std::cout << std::endl;
            j++;
        }

    }

    // This function calculates the hamming distance between each
    // 8-mer and the consensus.
    int getHammingDistances() {
        int distance = 0;
        for(const std::string s: dnaStrings) {
            int size = s.length();
            for(int i = 0; i < size; i++) {
                if(consensus.at(i) != s.at(i)) {
                    distance++;
                }
            }
        }
        return distance;
    }

};

#endif //BIOINFORMATICSHW1_PROFILER_H
