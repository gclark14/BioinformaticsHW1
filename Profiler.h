//
// Created by unriv on 9/11/2019.
//

#ifndef BIOINFORMATICSHW1_PROFILER_H
#define BIOINFORMATICSHW1_PROFILER_H

#include <vector>
#include "iostream"
#include "fstream"

enum DNA { A,C,G,T };

#define FILEHANDLE "input1.txt"

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

        int consensusValues[COL];

        for(int j = 0; j < COL; j++) {
            int largest = 0;
            for(int i = A; i < T; i++) {
                if (profileMatrix.at(A).at(j) > largest) {
                    largest = A;
                } else if(profileMatrix.at(C).at(j) > largest) {
                    largest = C;
                } else if(profileMatrix.at(G).at(j) > largest) {
                    largest = G;
                } else {
                    largest = T;
                }
            }
            if (largest == A) {
                consensusValues[j] = A;
            } else if (largest == C) {
                consensusValues[j] = C;
            } if (largest == G) {
                consensusValues[j] = G;
            } else {
                consensusValues[j] = T;
            }
        }

        for(int i = 0; i < COL; i++) {
            std::cout << consensusValues[i] << " " ;
        }

        std::cout << std::endl;

    }

public:
    Profiler(){
        setStrings();
        initializeProfileMatrix();
        generateProfileMatrix();
        generateConsensus();
    }


    void printStrings() {
        for(const std::string s: dnaStrings)
            std::cout << s << '\n';
    }




    void printProfileMatrix() {
        for(const std::vector<int> profiles: profileMatrix) {
            for(const int i: profiles) {
                std::cout << i << " ";
            }
            std::cout << std::endl;
        }

    }




};





#endif //BIOINFORMATICSHW1_PROFILER_H
