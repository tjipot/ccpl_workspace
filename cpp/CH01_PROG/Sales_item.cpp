/* @UNIVESRE.COM_20161220_HYE
 * Sales_item.cpp */

#include <iostream>
#include "Sales_item.h"

int main(){

    //Declare variables to hold running sum and data for next record;
    Sales_item total, trans;
    //Is there data to process?
    if (std::cin >> total) {
        //If so, read transaction record;
        while (std::cin >> trans) {
            if (total.same_isbn(trans)) {
                //Match: update the running total;
                total += trans;
            }else{
                //No match: print & assign to total;
                std::cout << total << std::endl;
                total = trans;
            }
        }
        //Remember to print last record;
        std::cout << total << std::endl;
    }else{
        //No input!, warn the user;d
        std::cout << "No data?!" << std::endl;
        return -1;  //Indicate failure;
    }

    return 0;
}