#ifndef CHIP8_H
#define CHIP8_H


class Chip8{
    public:
        u_int8_t V[16]{0};
        u_int8_t sysMemory[4096]{0};
        u_int8_t stackPointer{0};
        u_int8_t delayTimer{0};
        u_int8_t soundTimer{0};
        u_int8_t inputKeys[16]{0};
        u_int16_t stack[16]{0};
        u_int16_t I{0};
        u_int16_t programCounter{0};
        u_int16_t opcode{0};
        u_int32_t videoOut[64 * 32]{0};

        u_int8_t fontset[80] =
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

        Chip8();
        void cycle();
        void loadROM(char const* romName);

        // Opcode implimentation.
        void OP_00E0();
        void OP_00EE();
        void OP_1NNN();
        void OP_2NNN();
        void OP_3XNN();
        void OP_4XNN();
        void OP_5XY0();
        void OP_6XNN();
        void OP_7XNN();
        void OP_8XY0();
        void OP_8XY1();
        void OP_8XY2();
        void OP_8XY3();
        void OP_8XY4();
        void OP_8XY5();
        void OP_8XY6();
        void OP_8XY7();
        void OP_8XYE();
        void OP_9XY0();
        void OP_ANNN();
        void OP_BNNN();
        void OP_CXNN();
        void OP_DXYN();
        void OP_EX9E();
        void OP_EXA1();
        void OP_FX07();
        void OP_FX0A();
        void OP_FX15();
        void OP_FX18();
        void OP_FX1E();
        void OP_FX29();
        void OP_FX33();
        void OP_FX55();
        void OP_FX65();
};

#endif