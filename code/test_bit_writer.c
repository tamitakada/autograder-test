#include "bit_tools.h"
#include <stdlib.h>

int main(int argc, char *argv[])
{
  BitWriter writer = open_bit_writer("new_file.bits");
  write_bits(&writer, 0x05, 3); // 0x05 ↔ 00000101₂ ⋯ writes just 101₂
  write_bits(&writer, 0xf3, 3); // 0xf3 ↔ 11110011₂ ⋯ writes just 011₂
  write_bits(&writer, 0x01, 2); // 0x01 ↔ 00000001₂ ⋯ writes just 01₂
  write_bits(&writer, 0x20, 6); // 0x20 ↔ 00100000₂ ⋯ writes just 100000₂
  write_bits(&writer, 0x13, 5); // 0x13 ↔ 00010011₂ ⋯ writes just 10011₂
  close_bit_writer(&writer);
  return EXIT_SUCCESS;
}