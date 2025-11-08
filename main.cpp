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

    LLDQ<int> x =  LLDQ<int>();
    x.pushBack(1);
    x.pushBack(2);
    x.pushFront(3);
    x.pushFront(4);
    x.pushFront(5);
    x.pushBack(0);

    x.getList().printForward();
    std::cout<<"\n";

    int y = x.popBack();
    int z = x.popBack();
    int fj = x.popFront();
    int lj = x.popBack();

    x.getList().printForward();

    std::cout<<"\n"<<y<< "\t"<< z << "\t" << fj<< "\t"<< lj<<std::endl;





    return 0;
}


#endif