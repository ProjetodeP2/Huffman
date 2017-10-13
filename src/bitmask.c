#include "../lib/bitmask.h"
int is_bit_i_set(unsigned char c, int i)
{
    unsigned char mask = 1 << i;
    return mask & c;
}

unsigned char set_bit (unsigned char c, int i)
{
    unsigned char mask = 1 << i;
    return mask | c;
}
