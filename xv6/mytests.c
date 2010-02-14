#include "types.h"
#include "user.h"
#include "printf.h"





int 
main() 
{

    int x = 0;
    while (x < 9) { 
        unsigned int j = rand();
        unsigned int k = gettic();

   
        printf(1,"Random Number: %d\n", j%100);
        printf(1, "NumTicks: %d\n", k);
        x++;
        sleep(5);
    }
    


    exit();


}