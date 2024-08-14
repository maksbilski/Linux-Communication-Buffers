#include "../include/bitmap.h"

static int earliest_free_bit = 0;
static int free_bits_count = NUM_BLOCKS;

void
set_bit(unsigned char *bitmap, int n) {
  if (!get_bit(bitmap, n)) {
      free_bits_count--;
  }
  bitmap[n / 8] |= (1 << (n % 8));
  if (n == earliest_free_bit) {
      earliest_free_bit = find_free_bit(bitmap);
  }
}

int
get_bit(unsigned char *bitmap, int n) {
  return (bitmap[n / 8] >> (n % 8)) & 1;
}

int
find_free_bit(unsigned char *bitmap) {
  int i;
  for (i = earliest_free_bit; i < NUM_BLOCKS; i++) {
      if (!get_bit(bitmap, i)) {
          earliest_free_bit = i;
          return i;
      }
  }
  earliest_free_bit = NUM_BLOCKS;
  return -1;
}

void
clear_bit(unsigned char *bitmap, int n) {
  if (get_bit(bitmap, n)) {
      free_bits_count++;
  }
  bitmap[n / 8] &= ~(1 << (n % 8));
  if (n < earliest_free_bit) {
      earliest_free_bit = n;
  }
}

int hasEnoughFreeBits(int required_bits) {
  return free_bits_count >= required_bits;
}

void printFreeBitsCount() {
  printf("Liczba wolnych bitów: %d\n", free_bits_count);
}