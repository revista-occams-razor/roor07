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

int main () {
  char clave[1024];
  
  puts ("Servicio Super Secreto");
  puts ("(c) Yvil Yenius para IbolCorp, 2024\n");
  printf ("Contraseña ?  ");
  fflush (stdin);
  fgets (clave, 1024, stdin);
  if (strncmp (clave, "YvilRulez!", 10) != 0) {
    puts ("Acceso Denegado!");
    return 1;
  }
  puts ("Bienvenido secuaz! ");
  // Aquí empieza el servicio super secreto
  return 0;
}
