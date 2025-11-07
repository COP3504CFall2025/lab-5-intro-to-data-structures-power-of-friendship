#ifdef MAIN

#include "ABDQ.hpp"
#include "ABQ.hpp"
#include "ABS.hpp"
#include "Interfaces.hpp"
#include "LinkedList.hpp"
#include "LLDQ.hpp"
#include "LLQ.hpp"
#include "LLS.hpp"
#include <iostream>

/*
    - LEAVE THE IFDEF GUARDS TO KEEP YOUR MAIN WITHOUT CONFLICTING WITH GRADESCOPE!
    - Test your code in this main and run locally with the RunMain configuration in CLion, or
    through your own command line compilation. Make sure to add flag "-DMAIN" to your compilation so this
    main function can compile.

*/

int main() {

    ABDQ<int> x;
    x.pushFront((1));
    x.pushFront((4));
    x.pushFront(3);
    x.pushFront(68);
    x.pushFront(56);
    int* temp = x.get_data_();
    for (int i = 0; i<x.getSize();i++) {
        std::cout<<temp[i]<<std::endl;
    }
    return 0;
}


#endif