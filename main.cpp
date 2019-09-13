#include <iostream>
#include "PartialDigester.h"
#include "Substring.h"
#include "Profiler.h"
#include "PDP.h"

int main() {
    std::vector<int> L = { 2, 2, 3, 3, 4, 5, 6, 7, 8, 10 };
    std::vector<int> L2 = { 1, 2, 2, 3, 5, 6, 7, 8, 8, 10 };

    PDP pdp(L2);
    //pdp.printX();

    //PartialDigester pd(L);
    //pd.printX();

    // Problem 5
    //Substring str("We think in generalities, but we live in details.", "live");
    //std::cout << str.indexOfFirstSubstring() << '\n';

    Profiler profiler;

    //profiler.printProfileMatrix();
    //profiler.printStrings();





    return 0;
}