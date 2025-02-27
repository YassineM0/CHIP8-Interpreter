#include <iostream>
#include <stdio.h>

#include "chip8.h"

//16 character sprite * 5 bytes for each character
const unsigned int fontSet_size = 80;

uint8_t fontSet[fontSet_size] = 
{
    0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
	0x20, 0x60, 0x20, 0x20, 0x70, // 1
	0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
	0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
	0x90, 0x90, 0xF0, 0x10, 0x10, // 4
	0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
	0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
	0xF0, 0x10, 0x20, 0x40, 0x40, // 7
	0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
	0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
	0xF0, 0x90, 0xF0, 0x90, 0x90, // A
	0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
	0xF0, 0x80, 0x80, 0x80, 0xF0, // C
	0xE0, 0x90, 0x90, 0x90, 0xE0, // D
	0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
	0xF0, 0x80, 0xF0, 0x80, 0x80  // F
};


Chip8::Chip8()
{
    // initialize program counter at 0x200
    pc = PROGRAM_START_ADRESS;
    
    //load font starting from 0x50
    for(unsigned int i = 0;i < fontSet_size;i++)
    {
        MEMORY[FONTSET_START_ADDRESS + i] = fontSet[i];
    }
}

int Chip8::loadRom(const char* filename)
{
    FILE* file = fopen(filename, "rb");

    if(file == NULL)
    {
        std::cerr << "failed to open ROM file:" << filename << std::endl;
        return 0;
    }

    fseek(file, 0, SEEK_END);
    unsigned long fileSize = ftell(file);
    rewind(file);

    if(fileSize > MEMORY_CAPACITY - PROGRAM_START_ADRESS)
    {
        std::cerr << "ROM file too large: " << filename << std::endl;
        fclose(file);
        return 0;
    }

    size_t bytes_read = fread(&MEMORY[PROGRAM_START_ADRESS], 1, fileSize, file);

    //handling reading errors
    if(bytes_read != fileSize)
    {
        std::cerr << "error loading ROM file: "<< filename << std::endl;
        fclose(file);
        return 0;
    }

    printf("ROM file loaded succesfully: %s (%ld bytes)",
        filename,
        fileSize
    );
    fclose(file);
    return 1;
}

int main()
{
    Chip8 chip8;

    const char* path = "../roms/demo/1dcell.ch8";

    int result = chip8.loadRom(path);

    std::cout << result;
}