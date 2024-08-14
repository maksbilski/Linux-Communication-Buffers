#ifndef BITMAP_H
#define BITMAP_H

#include <stdio.h>
#include <string.h>
#include "virtual_disk.h"

void set_bit(unsigned char *bitmap, int n);
int get_bit(unsigned char *bitmap, int n);
int find_free_bit(unsigned char *bitmap);
void clear_bit(unsigned char *bitmap, int n);
int hasEnoughFreeBits(int required_bits);
void printFreeBitsCount();

#endif // BITMAP_H