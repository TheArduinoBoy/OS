#include "print.h"

Print::Print(Framebuffer* framebuffer, PSF1_FONT* psf1_font) {
    Print::colour = 0xffffffff;
    Print::CursorPosition = {0, 0};
    Print::framebuffer = framebuffer;
    Print::psf1_font = psf1_font;
}

void Print::setColor(unsigned int colour) {
    Print::colour = colour;
}
Point Print::getCursorPosition() {
    return Print::CursorPosition;
}
void Print::setCursor(Point point) {
    Print::CursorPosition = point;
}
void Print::setCursor(unsigned int x, unsigned int y) {
    Print::CursorPosition = {x, y};
}

void Print::putChar(char chr, unsigned int xOff, unsigned int yOff) {
    unsigned int* pixPtr = (unsigned int*)framebuffer->BaseAddress;
    char* fontPtr = (char*)psf1_font->glyphBuffer + (chr * psf1_font->psf1_Header->charsize);
    for (unsigned long y = yOff; y < yOff + 16; y++){
        for (unsigned long x = xOff; x < xOff+8; x++){
            if ((*fontPtr & (0b10000000 >> (x - xOff))) > 0){
                    *(unsigned int*)(pixPtr + x + (y * framebuffer->PixelsPerScanLine)) = colour;
                }

        }
        fontPtr++;
    }
}
void Print::print(const char* str) {
    char* chr = (char*)str;
    while(*chr != 0){
        if(*chr == '\n') { CursorPosition.X = 0; CursorPosition.Y += 16; }
        else { putChar(*chr, CursorPosition.X, CursorPosition.Y); CursorPosition.X+=8; }
        if(CursorPosition.X + 8 > framebuffer->Width)
        {
            CursorPosition.X = 0;
            CursorPosition.Y += 16;
        }
        chr++;
    }
}