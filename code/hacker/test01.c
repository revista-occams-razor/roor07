/*
* This program is part of Occam's Razor Number 7
* Copyright (C) 2024 Occam's Razor
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <stdio.h>
#include <unistd.h>

#include <capstone/capstone.h>

int
main (int argc, char *argv[]) {
  csh           h;
  cs_insn       *ins;
  unsigned char buf[1024*16]; // 16Kb
  int           n;
  size_t        offset, count;
  size_t        j;

  cs_open (CS_ARCH_X86, CS_MODE_64, &h);
  
  /* Read standard input*/
  while (!feof (stdin)) {
    if ((n = read (0, buf + offset, 1024)) <=0) break;
    offset +=n;
  }
  printf ("+ %ld bytes leidos\n", offset);
  
  count = cs_disasm(h, buf, offset, 0x0, 0, &ins);
  
  if (count > 0) {
    for (j = 0; j < count; j++) {
      printf("0x%lx:\t%s\t\t%s\n", ins[j].address, ins[j].mnemonic,
	     ins[j].op_str);
    }
  } else
    printf("ERROR: Failed to disassemble given code!\n");
  
  cs_close (&h);
}
