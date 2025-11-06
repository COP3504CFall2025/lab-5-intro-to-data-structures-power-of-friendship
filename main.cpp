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

    ABDQ<size_t>* x = new ABDQ<size_t>((5));
    x->pushBack(1);
    x->pushBack(2);
    x->pushBack((3));
    x->pushBack(4);
    x->pushBack(5);
    x->pushFront(6);
    size_t* temp = x->get_data_();
    for (int i = 0; i<x->getSize();i++) {
        std::cout<<(temp[i])<<std::endl;
    }
    delete x;

    return 0;
}


#endif