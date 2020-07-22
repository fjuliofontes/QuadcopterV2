
#include "util.h"
#include <string.h>

uint32_t myAtoi(char *str){
    uint32_t res = 0;
    uint16_t i;
    for (i = 0; str[i] != '\0'; ++i)
        res = res*10 + str[i] - '0';
    return res;
}

char *myITOA(uint32_t num, uint8_t base, uint8_t decimal_points){
    static char Representation[]= "0123456789ABCDEF";
    static char buffer[50];
    char *ptr;
    uint8_t i = 0;

    ptr = &buffer[49];
    *ptr = '\0';

    do
    {
        i++;
        *--ptr = Representation[num%base];
        num /= base;
    }while(num != 0);

    // padding with left zeros if needed
    while (i < decimal_points){
        i++;
        *--ptr = '0';
    }

    return(ptr);
}
