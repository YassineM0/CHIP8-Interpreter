#define SDL_MAIN_HANDLED
#include "chip8.h"
#include <thread>
#include <chrono>

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " <ROM file>" << std::endl;
        return 1;
    }

    Chip8 chip8;
    // chip8.loadRom(argv[1]);

    std::cout << "Initializing CHIP-8 Emulator..." << std::endl;
    if (!chip8.loadRom(argv[1]))
    {
        std::cerr << "Failed to load ROM: " << argv[1] << std::endl;
        return 1;
    }
    std::cout << "ROM loaded successfully!" << std::endl;

    while (true)
    {
        std::cout << "Starting CHIP-8 Emulator...\n";
        std::cout << "Emulating cycle..." << std::endl;
        chip8.emulateCycle();
        std::cout << "Processing input..." << std::endl;
        auto key = chip8.getKey();
        if (key != nullptr)
        {
            chip8.ProcessInput(key);
        }

        std::cout << "Updating graphics..." << std::endl;
        chip8.updateGraphics();
        std::cout << "Decrementing timers..." << std::endl;
        chip8.decrementTimers();
        // std::this_thread::sleep_for(std::chrono::milliseconds(16)); // 60Hz
        SDL_Delay(16);
    }

    return 0;
}
