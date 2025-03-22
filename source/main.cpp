#define SDL_MAIN_HANDLED
#include "chip8.h"
#include <thread>
#include <chrono>

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <ROM file>" << std::endl;
        return 1;
    }

    Chip8 chip8;
    chip8.loadRom(argv[1]);

    std::cout << "Initializing CHIP-8 Emulator..." << std::endl;
if (!chip8.loadRom(argv[1])) {
    std::cerr << "Failed to load ROM: " << argv[1] << std::endl;
    return 1;
}
std::cout << "ROM loaded successfully!" << std::endl;

    while (true) {
        chip8.emulateCycle();
        chip8.ProcessInput(chip8.getKey());
        chip8.updateGraphics();
        chip8.decrementTimers();
        std::this_thread::sleep_for(std::chrono::milliseconds(16)); // 60Hz
    }
    getchar();

    return 0;
}
