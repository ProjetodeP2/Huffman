#include "../lib/bitmask.h"

int is_bit_i_set(unsigned char c, int i)
{
    unsigned char mask = 1 << i;
    if(mask & c)return 1;
    else return 0;
}

unsigned char set_bit (unsigned char c, int i)
{
    unsigned char mask = 1 << i;
    return mask | c;
}
