#ifndef CHIP8_H
#define CHIP8_H


class chip8{
    public:

    unsigned char sysMemory[4096];

    unsigned char V[16];

    void initialize();
    void cycle();


};

#endif