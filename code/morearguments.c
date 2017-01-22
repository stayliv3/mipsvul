#include <stdio.h>

// Function that calls another function with some arguments.
// Passing more than 4 arguments to see what happens
// by b1ack0wl

void main(){

int a = 0;
int b = 1;
int c = 2;
int d = 3;
int e = 4;
int f = 5;
int g = 6;
int h = 7;
int i = 8;
int j = 9;

pass_args_to_me(a,b,c,d,e,f,g,h,i,j);
}


int pass_args_to_me(int a, int b, int c ,int d, int e, int f, int g ,int h, int i, int j){

return (a+b+c+d+e+f+g+h+i+j);
}