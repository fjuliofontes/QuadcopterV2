#ifndef UTIL_H
#define UTIL_H

#include <stdint.h>

uint32_t myAtoi(char *str);
char *myITOA(uint32_t num, uint8_t base, uint8_t decimal_points);
char *myFTOA(float float_part, uint8_t decimal_points , uint8_t base);

#endif