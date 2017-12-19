#include "myLib.h"

void setPixel(int row, int col, unsigned short color) {
  videoBuffer[OFFSET(row, col, 240)] = color;
}

void waitForVBlank() {
  while (SCANLINECOUNTER > 160);
  while (SCANLINECOUNTER < 160);
}

void drawChar(int row, int col, char ch, unsigned short color) {
   for (int r = 0; r < 8; r++) { 
     for (int c = 0; c < 6; c++) { 
       if (fontdata_6x8[OFFSET(r, c, 6) + ch * 48] == 1) { 
   	setPixel(r + row, c + col, color); 
       } 
    }
  } 
}

void drawRect(int row, int col, int height, int width, unsigned short color) {
  for(int r=0; r<height; r++) {
    REG_DMA3SAD = (u32)&color; // This is always an address!
    REG_DMA3DAD = (u32)&videoBuffer[OFFSET(row+r, col, 240)]; // This is always an address!
    REG_DMA3CNT = (width) | DMA_ON | DMA_DESTINATION_INCREMENT | DMA_SOURCE_FIXED;
  }
}

void drawString(char* text, int row, int col, unsigned short color) {
  int c = 0;
  while (text[c]) {
    drawChar(row, col + (c * 6), text[c], color);
    c++;
  }
}
