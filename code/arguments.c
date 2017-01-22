#include <stdio.h>

// Function that calls another function with some arguments.
// This will be below the max amount of a(x) registers.
// by b1ack0wl

void main(){

int a = 0;
int b = 0x41;

pass_args_to_me(a,b);
}

int pass_args_to_me(int a, int b){

return (a+b);
}

