gcc emu.c chip8.c graphics.c -Wall -Wextra -g -I include/ -L lib/ -lraylib -lopengl32 -lgdi32 -lwinmm -o chip8.exe