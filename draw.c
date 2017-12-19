#include "objects.h"
#include "myLib.h"
#include "End.h"
#include "draw.h"
#include "Start.h"
#include "Sprite.h"
#include "Low.h"
#include "High.h"
#include "Neutral.h"
#include <stdio.h>

void drawScore(char score_text[40]) {
     // black rectangle is drawn on so as to avoid overwriting on score
    drawRect(150, 30, 10, 40, BLACK);
    drawString(score_text, 150, 5, YELLOW);
}

void drawLives(char lives_text[40]) {
  drawRect(150, 220, 10, 10, BLACK);
  drawString(lives_text, 150, 180, YELLOW);
}

void drawFlappy(struct Flappy_Bird* flappy) {
  drawImage3(flappy -> y, flappy -> x, BLACKBG_WIDTH, BLACKBG_HEIGHT, BlackBG);
}

void drawStartScreen() {
  drawImage3(0, 0, 240, 160, Start);
  drawString("Press A to begin.", 140, 60, YELLOW);
  while(1) {
    if (KEY_DOWN_NOW(BUTTON_A)) {
       drawRect(0, 0, 160, 240, BLACK);
       return;
    }
  }
}

void drawEndScreen(int score) {
  drawImage3(0, 0, 240, 160, GameOver);
  char score_text[40];
  sprintf(score_text, "SCORE: %d", score);

  drawString(score_text, 150, 100, YELLOW);
  drawMedal(score);
  return;
}

void drawMedal(int score) {
  if (score < 5) {
    drawString("Do better.", 100, 180, YELLOW);
    drawImage3(112, 192, LOW_WIDTH, LOW_HEIGHT, Low);
  } else if (score <= 15) {
    drawString("Good Job!", 100, 185, YELLOW);
    drawImage3(112, 192, NEUTRAL_WIDTH, NEUTRAL_HEIGHT, Neutral);
  } else {
    drawString("Wow!", 100, 192, YELLOW);
    drawImage3(112, 192, HIGH_WIDTH, HIGH_HEIGHT, High);
  }
}

void drawImage3(int r, int c, int width, int height, const unsigned short* image) {
  if (width == 240 && height == 160) { // handles case for start and end screen
    for (int i = 0; i < height; i++) {
      DMA[3].src = &image[i * width];
      DMA[3].dst = &videoBuffer[(r + i) * 240];
      DMA[3].cnt = width | DMA_ON | DMA_DESTINATION_INCREMENT | DMA_SOURCE_INCREMENT;
    }
  } else {
    for (int i = 0; i < height; i++) {
      DMA[3].src = &image[i * width];
      DMA[3].dst = &videoBuffer[(r + i) * 240 + c];
      DMA[3].cnt = width | DMA_ON | DMA_DESTINATION_INCREMENT | DMA_SOURCE_INCREMENT;
    }
  }
}

