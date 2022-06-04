#include <stdio.h>
#include <stdlib.h>
#include "include/chip8.h"
#include "include/graphics.h"

struct chip8 myChip8;

// Resets the pc, Index and Stack Pointer. Clears the memory, registers and stack and resets the timers
void initialize(){
    myChip8.pc = 0x200;
    myChip8.I = 0;
    myChip8.sp = 0;

    //Graphics not implemented yet.

    for(int i = 0; i < 16; i++){
        myChip8.stack[i] = '\0';
        myChip8.V[i] = '\0';
    }

    for(int i = 0; i < 4096; i++){
        myChip8.memory[i] = '\0';
    }

    for(int i = 0x50; i < 0x9F; i++){
        myChip8.memory[i] = fontset[i];
    }

    myChip8.sound_timer = 0, myChip8.delay_timer = 0;

    initScreen();
}

// Uses fopen() in binary mode and fread() to copy the contents of the rom to the memory array.
int loadrom(const char *rom){
    FILE *fp;
    int file_size = 0;

    fp = fopen(rom, "rb");

    // If file pointer doesn't exist
    if(fp == NULL){
        printf("Failed to open \"%s\"\n", rom);
        return -1;
    }

    if(fseek(fp, 0, SEEK_END) != 0){
        printf("The rom could not be read.\n");
        return -1;
    }

    file_size = ftell(fp);

    if(fseek(fp, 0, SEEK_SET) != 0){
        printf("The rom could not be read.\n");
        return -1;
    }

    fread(&myChip8.memory[0x200], 1, file_size, fp);
    fclose(fp);
    return file_size;
}


// Function to fetch the current opcode the pc is pointing at.
void fetch_opcode(){
    myChip8.opcode = myChip8.memory[myChip8.pc] << 8 | myChip8.memory[myChip8.pc + 1]; //Combines two bytes (two elements) from the memory array.
    myChip8.pc += 2;
}

void decode_and_execute(){
    char byte_f = (myChip8.opcode >> 8) & 0xFF; //The first (Higher) byte of the opcode
    char inst_nibble = (byte_f >> 4) & 0xFF;
    char nibble_X = byte_f & 0xF;

    char byte_s = (myChip8.opcode & 0xFF); //The second (Lower) byte of the opcode
    char nibble_Y = (byte_s >> 4) & 0xFF;
    char nibble_N = byte_s & 0xF;

    char NN = byte_s;
    unsigned short NNN = nibble_X << 8 | NN;

    // X, Y, N, NN, and NNN are named following conventional chip-8 conventions.

    switch (inst_nibble){
        case 0x1:
            myChip8.pc = NNN;
            break;

        case 0x6:
            myChip8.V[nibble_X] = NN;
            break;

        default:
            break;
    }
}