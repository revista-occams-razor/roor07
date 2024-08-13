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
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <termios.h>

#define MAX_PASS  32
int main(int argc, char *argv[])
{
  puts ("Servicio Super Secreto");
  puts ("(c) Yvil Yenius para IbolCorp, 2024\n");
  
  printf("Contraseña? ");
  fflush (stdout);
  
  /* Get terminal*/
  struct termios orig_term;
  struct termios new_term;
  tcgetattr(fileno(stdin), &orig_term);
  memcpy (&new_term, &orig_term, sizeof(struct termios));
  
  /* Haz lo siguiente :
   *   + Desabilita Echo
   *   + Activaba modo canonico
   *   + Configura lectura 1 caracter sin timeout */
  new_term.c_lflag &= ~(ICANON | ECHO);
  new_term.c_cc[VTIME] = 0;
  new_term.c_cc[VMIN] = 1;
  tcsetattr(fileno(stdin), 0, &new_term);
  
  char pass[MAX_PASS];
  /* Leemos password caracter a caracter */
  char c, n, indx=0;
  srand (time(NULL));
  do {
    read (0, &c, 1);
    if (c == '\n') break;
    // Descomentar para filtrar caracteres de control (BS)
    //if (c < 32) continue; // Ignora caracteres de control
    pass[indx++] = c;
    n = rand () % 3 + 1;
    for (int i = 0; i < n; i++, write (1, "*", 1));
    if (indx > MAX_PASS) break;
    
  } while (1);
  
  tcsetattr(fileno(stdin), 0, &orig_term);
 
  if (!strncmp (pass, "YvilEsGenial!", 13)) 
    puts ("\nBienvenido estimado acólito");
  else puts ("\nContraseña incorrecta...");
}
