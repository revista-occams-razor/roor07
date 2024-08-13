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
#include <string.h>
#include <termios.h>

int main(int argc, char *argv[])
{
  char pass[32];
  puts ("Servicio Super Secreto");
  puts ("(c) Yvil Yenius para IbolCorp, 2024\n");

 
  printf("Contraseña? ");
  fgets (pass, sizeof(pass), stdin);
  if (!strncmp (pass, "YvilEsGenial!", 13)) 
    puts ("Bienvenido estimado acólito");
  else puts ("Contraseña incorrecta...");

}
