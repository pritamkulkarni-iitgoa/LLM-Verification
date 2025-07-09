/* Copyright (c) 2008, Jacob Burnim (jburnim@cs.berkeley.edu)
 *
 * This file is part of CREST, which is distributed under the revised
 * BSD license.  A copy of this license can be found in the file LICENSE.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See LICENSE
 * for details.
 */

#include <stdio.h>
#include <stdlib.h>

void f(int);
void g(int);
void h(int);
void i(int);


void f(int a) {
  if (a > 13) {
    printf("\ngreater than 13\n");
  } else {
    printf("\nnot greater than 13\n");
  }
}

void g(int a) {
  h(a);

  if (a == 7) {
    printf("\n7\n");
  } else {
    printf("\nnot 7\n");
  }

  i(a);
}

void h(int a) {
  if (a == -4) {
    printf("\n-4\n");
  } else {
    printf("\nnot -4\n");
  }
}

void i(int a) {
  if (a == 100) {
    printf("\n100\n");
  } else {
    printf("\nnot 100\n");
  }
}

int main(int argc, int* argv[]) {
  int a;
  a=atoi(argv[1]);

  if (a <= 19) {
    printf("\n19\n");
  } else {
    printf("\nnot 19\n");
  }
 
  if (a> 5){
	printf("\nThe value of is greater than 5");
	printf("\nThe value of a is %d", a);
  	f(a);
	}
   if (a< 5){
	printf("\nThe value of is less than 5");
	printf("\nThe value of a is %d", a);
  	g(a);
	}
    if (a==5){
        printf("\nThe value of is equal to 5");
	printf("\nThe value of a is %d", a);
	f(a);
  	g(a);
	}
  f(a);
  g(a);

  if (a != 1) {
    printf("\nnot 1\n");
  } else {
    printf("\n1\n");
  }

  return 0;
}
