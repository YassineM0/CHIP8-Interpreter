#include <iostream>
#include <stdio.h>
#include <cstring>

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

    opcode = 0;
    index = 0;
    sp = 0;
    delay_timer = 0;
    sound_timer = 0;

    memset(MEMORY, 0, sizeof(MEMORY));
    memset(V, 0, sizeof(V));
    memset(stack, 0, sizeof(stack));
    memset(key, 0, sizeof(key));
    memset(display, 0, sizeof(display));

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "Failed to initialize SDL: " << SDL_GetError() << std::endl;
        exit(1);
    }

    window = SDL_CreateWindow("CHIP-8", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1200, 500, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGB332, SDL_TEXTUREACCESS_STREAMING, WIDTH, HEIGHT);

    // load font starting from 0x50
    for (unsigned int i = 0; i < fontSet_size; i++)
    {
        MEMORY[FONTSET_START_ADDRESS + i] = fontSet[i];
    }
}
Chip8::~Chip8()
{
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}


void Chip8::updateGraphics()
{
    if (!texture || !renderer)
    {
        std::cerr << "Error: SDL texture or renderer is not initialized!" << std::endl;
        return;
    }

    SDL_UpdateTexture(texture, nullptr, display, WIDTH * sizeof(uint32_t));
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, nullptr, nullptr);
    SDL_RenderPresent(renderer);
}


bool Chip8::ProcessInput(uint8_t* keys)
	{
		bool quit = false;

		SDL_Event event;

		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
				case SDL_QUIT:
				{
					quit = true;
				} break;

				case SDL_KEYDOWN:
				{
					switch (event.key.keysym.sym)
					{
						case SDLK_ESCAPE:
						{
							quit = true;
						} break;

						case SDLK_x:
						{
							keys[0] = 1;
						} break;

						case SDLK_1:
						{
							keys[1] = 1;
						} break;

						case SDLK_2:
						{
							keys[2] = 1;
						} break;

						case SDLK_3:
						{
							keys[3] = 1;
						} break;

						case SDLK_q:
						{
							keys[4] = 1;
						} break;

						case SDLK_w:
						{
							keys[5] = 1;
						} break;

						case SDLK_e:
						{
							keys[6] = 1;
						} break;

						case SDLK_a:
						{
							keys[7] = 1;
						} break;

						case SDLK_s:
						{
							keys[8] = 1;
						} break;

						case SDLK_d:
						{
							keys[9] = 1;
						} break;

						case SDLK_z:
						{
							keys[0xA] = 1;
						} break;

						case SDLK_c:
						{
							keys[0xB] = 1;
						} break;

						case SDLK_4:
						{
							keys[0xC] = 1;
						} break;

						case SDLK_r:
						{
							keys[0xD] = 1;
						} break;

						case SDLK_f:
						{
							keys[0xE] = 1;
						} break;

						case SDLK_v:
						{
							keys[0xF] = 1;
						} break;
					}
				} break;

				case SDL_KEYUP:
				{
					switch (event.key.keysym.sym)
					{
						case SDLK_x:
						{
							keys[0] = 0;
						} break;

						case SDLK_1:
						{
							keys[1] = 0;
						} break;

						case SDLK_2:
						{
							keys[2] = 0;
						} break;

						case SDLK_3:
						{
							keys[3] = 0;
						} break;

						case SDLK_q:
						{
							keys[4] = 0;
						} break;

						case SDLK_w:
						{
							keys[5] = 0;
						} break;

						case SDLK_e:
						{
							keys[6] = 0;
						} break;

						case SDLK_a:
						{
							keys[7] = 0;
						} break;

						case SDLK_s:
						{
							keys[8] = 0;
						} break;

						case SDLK_d:
						{
							keys[9] = 0;
						} break;

						case SDLK_z:
						{
							keys[0xA] = 0;
						} break;

						case SDLK_c:
						{
							keys[0xB] = 0;
						} break;

						case SDLK_4:
						{
							keys[0xC] = 0;
						} break;

						case SDLK_r:
						{
							keys[0xD] = 0;
						} break;

						case SDLK_f:
						{
							keys[0xE] = 0;
						} break;

						case SDLK_v:
						{
							keys[0xF] = 0;
						} break;
					}
				} break;
			}
		}

		return quit;
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

    printf("ROM file loaded successfully: %s (%ld bytes)",
           filename,
           fileSize);
    fclose(file);
    return 1;
}

uint8_t x, y;
uint16_t sum;

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
            x = (opcode & 0x0F00) >> 8;
            y = (opcode & 0x00F0) >> 4;

            sum = V[x] + V[y];

            V[0xF] = (sum > 255) ? 1 : 0;
            V[x] = sum & 0xFF;
            break;

        case 0x5:
            // Set Vx = Vx - Vy, set VF = NOT borrow.
            x = (opcode & 0x0F00) >> 8;
            y = (opcode & 0x00F0) >> 4;

            V[0xF] = (V[x] > V[y]) ? 1 : 0;
            V[x] = V[x] - V[y];
            break;

        case 0x6:
            // Set Vx = Vx SHR 1.
            x = (opcode & 0x0F00) >> 8;

            V[0xF] = V[x] & 0x1;
            V[x] = V[x] >> 1;
            break;

        case 0x7:
            // Set Vx = Vy - Vx, set VF = NOT borrow.
            x = (opcode & 0x0F00) >> 8;
            y = (opcode & 0x00F0) >> 4;

            V[0xF] = (V[y] > V[x]) ? 1 : 0;
            V[x] = V[y] - V[x];
            break;

        case 0xE:
            // Set Vx = Vx SHL 1.
            x = (opcode & 0x0F00) >> 8;

            V[0xF] = V[x] >> 7;
            V[x] = V[x] << 1;
            break;
        }
        break;

    default:
        std::cerr << "Unknown opcode: " << std::hex << opcode << std::endl;
        break;
    }
}

uint8_t* Chip8::getKey()
{
    return key;
}

void Chip8::decrementTimers() {
    if (delay_timer > 0) delay_timer--;
    if (sound_timer > 0) sound_timer--;
}