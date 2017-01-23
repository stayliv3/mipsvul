#include <stdio.h>

// What if....
// This is to analyze how basic branching works on MIPS
// by b1ack0wl

int main(int argc, char **argv[]){
if (argc < 2 ){
    printf("Usage: %s number", argv[0]);
    return 1;
}

int a = atoi(argv[1]); // cast argv[1] as an integer
if (a < 5) {
    printf("%i is less than 5", a);
}
else{
    printf("%i is greater than 5", a);
}
return 0;
}

<script src="https://gist.github.com/gitpraetorianlabs/280297927d746b20e7f860b0f7a8d0af.js"></script>