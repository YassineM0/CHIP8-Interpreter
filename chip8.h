#ifndef chip8.h
#define chip8.h

#include <cstdint>

#define V_NUM 16
#define MEMORY_CAPACITY 4096
#define STACK_SIZE 16

#define HEIGHT 32
#define WIDTH 64



class ship8
{
private:
    uint8_t MEMORY[MEMORY_CAPACITY]{};

    uint8_t V[V_NUM]{}; // registers (V0 - VF)
    uint16_t index; // register's index
    uint16_t pc; // program counter
    
    uint16_t stack[STACK_SIZE]; // 16 levels stack

    uint32_t display[HEIGHT][WIDTH]; // 64*32 screen size

    uint8_t delay_timer;
    uint8_t sound_timer;

};

#endif