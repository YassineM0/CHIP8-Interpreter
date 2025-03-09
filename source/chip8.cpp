#include <iostream>
#include <stdio.h>

#include "chip8.h"

// 16 character sprite * 5 bytes for each character
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
    pc = PROGRAM_START_ADDRESS;

    // load font starting from 0x50
    for (unsigned int i = 0; i < fontSet_size; i++)
    {
        MEMORY[FONTSET_START_ADDRESS + i] = fontSet[i];
    }
}

uint8_t Chip8::getMemoryAt(uint16_t address) const
{
    return MEMORY[address];
}

int Chip8::loadRom(const char *filename)
{
    FILE *file = fopen(filename, "rb");

    if (file == NULL)
    {
        std::cerr << "failed to open ROM file:" << filename << std::endl;
        return 0;
    }

    fseek(file, 0, SEEK_END);
    unsigned long fileSize = ftell(file);
    rewind(file);

    if (fileSize > MEMORY_CAPACITY - PROGRAM_START_ADDRESS)
    {
        std::cerr << "ROM file too large: " << filename << std::endl;
        fclose(file);
        return 0;
    }

    size_t bytes_read = fread(&MEMORY[PROGRAM_START_ADDRESS], 1, fileSize, file);

    // handling reading errors
    if (bytes_read != fileSize)
    {
        std::cerr << "error loading ROM file: " << filename << std::endl;
        fclose(file);
        return 0;
    }

    printf("ROM file loaded succesfully: %s (%ld bytes)",
           filename,
           fileSize);
    fclose(file);
    return 1;
}
void Chip8::emulateCycle()
{
    opcode = (MEMORY[pc] << 8 | MEMORY[pc + 1]);

    pc += 2;

    switch (opcode & 0xF000)
    {
    case 0x0000:
        if (opcode == 0x00E0) // CLS
        {
            // Clear the display.
            memset(display, 0, sizeof(display));
        }

        else if (opcode == 0x00EE) // RET
        {
            // Return from a subroutine.
            pc = stack[--sp];
        }
        break;

    case 0x1000:
        // Jump to location nnn.
        pc = opcode & 0x0FFF;
        break;

    case 0x2000:
        // Call subroutine at nnn.
        stack[++sp] = pc;
        pc = opcode & 0x0FFF;
        break;

    case 0x3000:
        // Skip next instruction if Vx == kk.
        if (V[(opcode & 0x0F00) >> 8] == (opcode & 0x00FF))
            pc += 2;
        break;

    case 0x4000:
        // Skip next instruction if Vx != kk.
        if (V[(opcode & 0x0F00) >> 8] != (opcode & 0x00FF))
            pc += 2;
        break;

    case 0x5000:
        // Skip next instruction if Vx == Vy.
        if (V[(opcode & 0x0F00) >> 8] == V[(opcode & 0x00F0) >> 4])
            pc += 2;
        break;

    case 0x6000:
        // Set Vx = kk.
        V[(opcode & 0x0F00) >> 8] = (opcode & 0x00FF);
        break;

    case 0x7000:
        // Set Vx = Vx + kk.
        V[(opcode & 0x0F00) >> 8] += (opcode & 0x00FF);
        break;

    case 0x8000:
        switch (opcode & 0x000F)
        {
        case 0x0:
            // Set Vx = Vy.
            V[(opcode & 0x0F00) >> 8] = V[(opcode & 0x00F0) >> 4];
            break;

        case 0x1:
            // Set Vx = Vx OR Vy.
            V[(opcode & 0x0F00) >> 8] = V[(opcode & 0x0F00) >> 8] | V[(opcode & 0x00F0) >> 4];
            break;

        case 0x2:
            // Set Vx = Vx AND Vy.
            V[(opcode & 0x0F00) >> 8] = V[(opcode & 0x0F00) >> 8] & V[(opcode & 0x00F0) >> 4];
            break;

        case 0x3:
            // Set Vx = Vx XOR Vy.
            V[(opcode & 0x0F00) >> 8] = V[(opcode & 0x0F00) >> 8] ^ V[(opcode & 0x00F0) >> 4];
            break;

        case 0x4:
            // Set Vx = Vx + Vy, set VF = carry.
            uint8_t x = (opcode & 0x0F00) >> 8;
            uint8_t y = (opcode & 0x00F0) >> 4;

            uint16_t sum = V[x] + V[y];

            V[0xF] = (sum > 255) ? 1 : 0;
            V[x] = sum & 0xFF;

            break;

        case 0x5:
            // Set Vx = Vx - Vy, set VF = NOT borrow.
            uint8_t x = (opcode & 0x0F00) >> 8;
            uint8_t y = (opcode & 0x00F0) >> 4;

            V[0xF] = (V[x] > V[y]) ? 1 : 0;

            V[x] = V[x] - V[y];
            break;

        case 0x6:
            //Set Vx = Vx SHR 1.
            uint8_t x = (opcode & 0x0F00) >> 8; 
          
            V[0xF] = V[x] & 0x1; 

            V[x] = V[x] >> 1; 
            break;

        case 0x7:
            // Set Vx = Vy - Vx, set VF = NOT borrow.
            uint8_t x = (opcode & 0x0F00) >> 8;
            uint8_t y = (opcode & 0x00F0) >> 4; 

            V[0xF] = (V[y] > V[x]) ? 1 : 0; 

            V[x] = V[y] - V[x];
            break;

        case 0xE:
            // Set Vx = Vx SHL 1.
            uint8_t x = (opcode & 0x0F00) >> 8; 

            V[0xF] = (V[x] >> 7) & 0x1; 

            V[x] = V[x] << 1; 
            break;
        
        default:
            std::cout << "uknown opcode" << std::hex << opcode << std::endl;
            break;
        }
        break;

    case 0x9000:
        //Skip next instruction if Vx != Vy.
        if(V[(opcode & 0x0F00) >> 8] != V[(opcode & 0x00F0) >> 4])
            pc += 2;
        break;
    
    case 0xA000:
        //Set I = nnn.
        index = (opcode & 0x0FFF);
        break;
    
    case 0xB000:
        //Jump to location nnn + V0.
        pc = (opcode & 0x0FFF) + V[0];
        break;
    
    case 0xC000:
        // Generate a random byte (0 to 255), AND it with kk, and store in Vx.
        V[(opcode & 0x0F00) >> 8] = (rand() % 256) & (opcode & 0x00FF);
        break;
    
    case 0xD000:
        //Display n-byte sprite starting at memory location I at (Vx, Vy), set VF = collision.
        uint8_t Vx = (opcode & 0x0F00) >> 8;
        uint8_t Vy = (opcode & 0x00F0) >> 4;
        uint8_t sprite_bytes = opcode & 0x000F;

        //handle out of bounds coordinates
        uint8_t x = V[Vx] % WIDTH;
        uint8_t y = V[Vy] % HEIGHT;

        V[0xF] = 0;
        for(int i = 0;i < sprite_bytes;i++)
        {
            uint8_t sprite_byte = MEMORY[index + i];
            for(int j = 0;j < 8;j++)
            {
                uint8_t pixel = (sprite_byte >> (7 - j)) & 1;
                uint32_t *screen = &display[y + i][x + j];

                if(pixel)
                {
                    //check if there is already a pixel on in this position
                    if(*screen == 0xFFFFFFFF)
                    {
                        V[0xf] = 1;
                    }

                    *screen ^= 0xFFFFFFFF;
                }

            }
        }
        break;

    case 0xE000:
        switch(opcode & 0x000F)
        {
            case 0xE:
                //Skip next instruction if key with the value of Vx is pressed.
                uint8_t Vx = (opcode & 0x0F00) >> 8;

                if(key[Vx])
                {
                    pc += 2;
                }
                break;
            
            case 0x1:
                //Skip next instruction if key with the value of Vx is not pressed.
                uint8_t Vx = (opcode & 0x0F00) >> 8;

                if(!key[Vx])
                {
                    pc += 2;
                }
                break;
            
            default:
                std::cout << "uknown opcode" << std::hex << opcode << std::endl;
                break;
        }
        break;
    
    case 0xF000:
        switch(opcode & 0x00FF)
        {
            case 0x07:
                //Set Vx = delay timer value.
                uint8_t Vx = (opcode & 0x0F00) >> 8;

                V[Vx] = delay_timer;
                break;
            
            case 0x0A:
                //Wait for a key press, store the value of the key in Vx.
                uint8_t Vx = (opcode & 0x0F00) >> 8;

                bool keyPressed = false;
                for(int i = 0;i < 16;i++)
                {
                    if(key[i])
                    {
                        V[Vx] = i;
                        keyPressed = true;
                        break;
                    }
                }
                if(!keyPressed)
                    pc -=2;
                break;
            
            case 0x15:
                //Set delay timer = Vx.
                uint8_t Vx = (opcode & 0x0F00) >> 8;
                delay_timer = Vx;
                break;
                
            case 0x18:
                //Set sound timer = Vx.
                uint8_t Vx = (opcode & 0x0F00) >> 8;
                sound_timer = Vx;
                break;
            
            case 0x1E:
                //Set I = I + Vx.
                uint8_t Vx = (opcode & 0x0F00) >> 8;
                index += Vx;
                break;

            case 0x29:
                //Set I = location of sprite for digit Vx.
                uint8_t Vx = (opcode & 0x0F00) >> 8;
                uint8_t digit = V[Vx];

                index = 0x50 + (digit * 5);
                break;
                
            case 0x33:
                //Store BCD representation of Vx in memory locations I, I+1, and I+2.
                uint8_t Vx = (opcode & 0x0F00) >> 8; 
                uint8_t value = V[Vx]; 
            
                MEMORY[index] = value / 100;           
                MEMORY[index + 1] = (value / 10) % 10; 
                MEMORY[index + 2] = value % 10;        
            
                break;

            case 0x55:
                //Store registers V0 through Vx in memory starting at location I.
                uint8_t Vx = (opcode & 0x0F00) >> 8;

                for (uint8_t i = 0; i <= Vx; ++i)
                {
                    MEMORY[index + i] = V[i];
                }
                break;
            
            case 0x65:
                //Read registers V0 through Vx from memory starting at location I.
                uint8_t Vx = (opcode & 0x0F00) >> 8;
                for(int i = 0; i <= Vx;i++)
                {
                    V[i] = MEMORY[index + i];
                }
                break;
                

        }
        default:
                std::cout << "uknown opcode" << std::hex << opcode << std::endl;
                break;
    
    
    }
}

int main()
{
    Chip8 chip8;

    const char *path = "../roms/demo/1dcell.ch8";

    int result = chip8.loadRom(path);

    std::cout << std::hex << (int)chip8.getMemoryAt(0x200) << ' ' << std::hex << (int)chip8.getMemoryAt(0x201);
}