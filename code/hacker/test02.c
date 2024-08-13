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

  /* Read standard input*/
  while (!feof (stdin)) {
    if ((n = read (0, buf + offset, 1024)) <=0) break;
    offset +=n;
  }
  printf ("+ %ld bytes leidos\n", offset);

  cs_open (CS_ARCH_X86, CS_MODE_64, &h);
  cs_option(h, CS_OPT_DETAIL, CS_OPT_ON); 
  count = cs_disasm(h, buf, offset, 0x0, 0, &ins);
  
  if (count > 0) {
    for (j = 0; j < count; j++) {

      printf("0x%lx:\t%s\t\t%s", ins[j].address, ins[j].mnemonic,
	     ins[j].op_str);
      // Imprime detalles
      cs_detail *d = ins[j].detail;
      if (d->x86.operands[1].type == X86_OP_MEM &&
	  d->x86.operands[1].mem.base == X86_REG_RIP) {
	long ptr1 = ins[j].address + d->x86.operands[1].mem.disp + ins[j].size;
	long ptr2 = ((long)buf + ptr1 ); // Create a label for this
	printf ("; 0x%lx ", ptr1);
	printf (" -> '%s'", (char*)ptr2);
	}
      if (d->x86.operands[0].type == X86_OP_IMM) {
	  char *tmp = (char *)&d->x86.operands[0].imm;
	  printf (" ; %s\n", tmp);
      } else printf ("%s", "\n");
    }
  } else
    printf("ERROR: Failed to disassemble given code!\n");
  long data = (long)ins[j-1].address + ins[j-1].size;
  if (data < offset)
    printf ("0x%lx %s\n", data, (char*)buf + data);
  cs_close (&h);
}
