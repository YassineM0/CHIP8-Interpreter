#include <iostream>
#include <stdio.h>

#include "chip8.h"

Chip8::Chip8()
{
    pc = PROGRAM_START_ADRESS;
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