#ifndef CHIP8_H
#define CHIP8_H

#include <cstdint>
#include <stdio.h>
#include <iostream>

#define V_NUM 16
#define MEMORY_CAPACITY 4096
#define STACK_SIZE 16

#define PROGRAM_START_ADDRESS 0x200
#define FONTSET_START_ADDRESS 0x50

#define HEIGHT 32
#define WIDTH 64



class Chip8
{
private:
    uint8_t MEMORY[MEMORY_CAPACITY]{};

    uint8_t V[V_NUM]{}; // registers (V0 - VF)
    uint16_t index; // register's index
    uint16_t pc; // program counter

    uint8_t sp; //stack pointer
    uint16_t stack[STACK_SIZE]; // 16 levels stack

    uint32_t display[HEIGHT][WIDTH]; // 64*32 screen size

    //timers
    uint8_t delay_timer;
    uint8_t sound_timer;

    uint16_t opcode;

public:
    Chip8();
    uint8_t getMemoryAt(uint16_t address) const;
    int loadRom(const char* filename);
    void emulateCycle();
};

#endif