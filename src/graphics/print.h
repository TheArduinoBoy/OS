#pragma once

#include "stddef.h"
#include "../util/math.h"
#include "graphics.h"

class Print {
    public:
        Print(Framebuffer* frameBuffer, PSF1_FONT* psf1_font);
        void print(const char* str);
        void setCursor(Point point);
        void setCursor(unsigned int x, unsigned int y);
        Point getCursorPosition();
        void setColor(unsigned int colour);
        void println(const char* str) {
            print(str);
            print("\n");
        }
    private:
        Point CursorPosition;
        Framebuffer* framebuffer;
        PSF1_FONT* psf1_font;
        unsigned int colour;
        void putChar(char chr, unsigned int xOff, unsigned int yOff);
};