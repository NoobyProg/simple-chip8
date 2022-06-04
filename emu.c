#include <stdio.h>
#include "include/chip8.h"

int main(int argc, char *argv[]){
    initialize();
    printf("%X %X %X", myChip8.pc, myChip8.I, myChip8.sp);
    return 0;
}