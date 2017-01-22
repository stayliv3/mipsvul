#include <stdio.h>

// Function callception!
// This is to analyze what happens when a function calls a function.
// by b1ack0wl

int call_one(); // declaration
int call_two(); // declaration

void main(){
int a = 0;
int b = 1;
call_one(a,b);
}

int call_one(int a, int b){
call_two();
return (a+b);
}

int call_two(){
return 1;
}

