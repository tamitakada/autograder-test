#include <stdlib.h>
#include <stdio.h>
#include "frequencies.h"

void print_frequencies(Frequencies freq)
{
  for (int i = 0; i < 256; i++)
  {
    if (freq[i] > 0)
    {
      printf("'%c' (%d): %llu\n", i, i, freq[i]);
    }
  }
}

int main(int argc, char *argv[])
{
  Frequencies freqs = {0};
  const char *error = NULL;
  calc_frequencies(freqs, "ex.txt", &error);
  print_frequencies(freqs);
  return EXIT_SUCCESS;
}