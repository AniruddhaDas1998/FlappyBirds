#include <stdlib.h>
#include "myLib.h"
#include "objects.h"
#include "draw.h"

void checkForLeft_RightBounds(struct Flappy_Bird* flappy) {
  if (flappy -> x <= 20) {
    flappy -> x = 20;
  }
  if (flappy -> x >= 220) {
    flappy -> x = 220;
  }
}

void paused() {
  drawRect(150, 180, 10, 40, BLACK);
  drawString("PAUSED", 150, 200, YELLOW);
  drawString("A to continue", 150, 85, YELLOW);
  while(1) {
    if (KEY_DOWN_NOW(BUTTON_A)) {
      break;
    }
  }
  drawRect(150, 85, 10, 85, BLACK); // For prompt
  drawRect(150, 200, 10, 40, BLACK); // for "PAUSED"
}

// efficiently updates position of pipes by only drawing segments of the rectangle
void updatePipesPositions(struct Pipe* pipe1, struct Pipe* pipe2, int score) {
  if (pipe1 -> x >= 0) {
      int xShift = 2; // sets speed at what pipes move
      xShift += (score / 32); // increases xShift after player gets 32
      xShift = xShift <= 3 ? xShift : 3; // sets maximum xShift to 3
      // PIPE 1
      drawRect(pipe1 -> oldY, pipe1 -> oldX + pipe1 -> width, pipe1 -> height, xShift, BLACK); // erases trail of old pipe1
      pipe1 -> x -= xShift;
      drawRect(pipe1 -> y, pipe1 -> x, pipe1 -> height, xShift, GREEN); // draws greater pipe
      pipe1 -> oldX = pipe1 -> x;
      pipe1 -> oldY = pipe1 -> y;
  
      // PIPE 2
      drawRect(pipe2 -> oldY - 1, pipe2 -> oldX + pipe2 -> width, pipe2 -> height + 1, xShift + 1, BLACK); // erases trail of old pipe2
      // 1 was subtracted to ordinate and added to height to fix random green pixels being generated above the pipe
      pipe2 -> x -= xShift;
      drawRect(pipe2 -> y, pipe2 -> x, pipe2 -> height, xShift, GREEN); // draws greater pipe
      pipe2 -> oldX = pipe2 -> x;
      pipe2 -> oldY = pipe2 -> y;
      if (pipe1 -> x > 230) { 
      	// draws a rectangle at the edge of the screen
	drawRect(pipe1 -> height, pipe1 -> x, pipe2 -> y - pipe1 -> height, xShift + 2, BLACK);
      } 
  } else { // executes after pipe goes off screen
    int h = rand() % 50;
    int num_rows = 149; // 150 -160 are for writing
    int min_height = 30; // minimum height of pipe 1
    int gap = 45; // gap between the pipes
    gap -= 3* (score / 8); // decrements gap by 3 for every 8 score points the player gets
    gap = gap >= 30 ? gap : 30; // sets minumum gap to 20
    // resets pipe1
    pipe1 -> x = 240;
    pipe1 -> y = 0;
    
    // places black rectangle where pipe used to be
    drawRect(0, 0, pipe1 -> height, pipe1 -> width + 2, BLACK); // width + 2 accounts for when xShift changes
    pipe1 -> height = min_height + h;
    pipe1 -> oldY = pipe1 -> y;
    
    // resets pipe2
    pipe2 -> x = 240;
    pipe2 -> y = min_height + gap + h;
    
    // places black rectangle where pipe used to be
    drawRect(pipe2 -> oldY, 0, pipe2 -> height, pipe2 -> width + 2, BLACK); // width + 2 accounts for when the xShift changes
    pipe2 -> height = num_rows - pipe2 -> y;
    pipe2 -> oldY = pipe2 -> y;
  }
}

void checkForTopCrash(struct Flappy_Bird* flappy) {
  if (flappy -> y <= 0) {
    flappy -> y = 0;
  }
}

void checkForBottomCrash(struct Flappy_Bird* flappy, short* playing) {
  if (flappy -> y > 140) {
    flappy -> y = 140; // prevents bird from going out of bounds by falling
    if (*playing) {
      flappy -> num_lives -= 1;
      *playing = 0;
    }
  }
}

void updateFlappyPositions(struct Flappy_Bird* flappy, int* oldX, int* oldY, int yShift, int xShift) {
    waitForVBlank();
    videoBuffer = videoBuffer; // to avoid complier warnings
    // keeping in mind y => row, x => column
    drawRect(*oldY, *oldX, flappy -> radius + 1, flappy -> radius + 1, BLACK);
    drawRect(flappy -> y, flappy -> x, flappy -> radius + 1, flappy -> radius + 1, flappy -> color);
    drawFlappy(flappy);
    setPixel(*oldY, *oldX, BLACK); // marks the x and y of bird
    setPixel(flappy -> y, flappy -> x, flappy -> color);

    *oldX = flappy -> x; // saves earlier positions
    *oldY = flappy -> y; // saves earlier positions

    flappy -> y += yShift;
    flappy -> x += xShift; 
}

