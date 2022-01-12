#include <stdio.h>
#include <stdlib.h>
#include "cpu.h"

void initialize(){
    pc = 0x200;
    I = 0;
    sp = 0;

    //Graphics not implemented yet.

    for(int i = 0; i < 16; i++){
        stack[i] = '\0';
        V[i] = '\0';
    }

    for(int i = 0; i < 4096; i++){
        memory[i] = '\0';
    }

    for(int i = (int)0x50; i < (int)0x9F; i++){
        memory[i] = fontset[i];
    }

    sound_timer = 0, delay_timer = 0;
}

int loadrom(const char *rom){
    FILE *fp;
    int file_size = 0;

    fp = fopen(rom, "rb");
    if(fp == NULL){
        printf("Failed to open \"%s\"\n", rom);
        return -1;
    }
    if(fseek(fp, 0, SEEK_END) != 0){
        printf("\"%s\" could not be read.\n", rom);
        return -1;
    }
    file_size = ftell(fp);
    if(fseek(fp, 0, SEEK_SET) != 0){
        printf("\"%s\" could not be read.\n", rom);
        return -1;
    }
    fread(memory[0x200], 1, file_size, fp);
}