//
// Created by unriv on 9/11/2019.
//

#ifndef BIOINFORMATICSHW1_SUBSTRING_H
#define BIOINFORMATICSHW1_SUBSTRING_H

#include <string>

class Substring {
private:
    std::string bigString;
    std::string subString;

public:
    Substring(std::string bigString, std::string subString){
        this->bigString = bigString;
        this->subString = subString;
    }

    int indexOfFirstSubstring(){
        return bigString.find(subString);
    }

};

#endif //BIOINFORMATICSHW1_SUBSTRING_H
