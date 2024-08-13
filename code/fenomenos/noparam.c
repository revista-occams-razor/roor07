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

int margarita (int a, int b, int c) {
  int _a, _b, _c, _d;

  _a = a;
  _b = _b;
  _c = _c;
  _d = _d + _a;

  return _d;
}

int azucena (int a, int b, int c) {
  int _a, _b, _c, _d;

  _a = _a;
  _b = b;
  _c = _c;
  _d = _d + b;
}

int hortensia (int a, int b, int c) {
  int _a, _b, _c, _d;

  _a = _a;
  _b = _b;
  _c = _c;
  _d = _d;
}

int despiste (int a, int b, int c) {
  int _a, _b, _c, _d, _e;

  _a = _a - 10;
  _b = _b + 5;
  _c = _c*2;
  _d = _d + 1;
  
  _e = (a *2 -b*b)/c;
  
  _d--;
  _a +=10;
  _b -=5;
  _c *=2;
  return _d;
}

int casper (int a, int b, int c) {
  int _a, _b, _c, _d;

  _d = _d + 2 * (_a +  _b + _c);

  return _d;
}


int main () {
  int (*f)(void) = (int (*)())(casper);
  int v1;
  v1 = margarita (4, 20, 30);
  v1 = azucena   (10, 7, 30);
  v1 = hortensia (10, 20, 5);
  v1 = despiste  (1,2,3);
  int v2 = f ();

  printf ("v2 : %d\n", v2);

}
