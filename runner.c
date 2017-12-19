#include <stdio.h>
#include "myLib.h"
#include "objects.h"
#include "draw.h"
#include "game.h"

int main() {
  short done = 0;
  REG_DISPCTL = MODE3 | BG2_ENABLE;
  videoBuffer = videoBuffer;
  while(!done) {
    drawStartScreen();
    
    char score_text[40]; // is the string to be printed with score
    char lives_text[40]; // is the string to be printed with lives
    int score = 0; // players score

    int gravity = 2; // force with which the bird is pulled down

    struct Flappy_Bird flappy = {RED, 1, 30, 30, 8};
  
    int oldX = flappy.x; // stores previous positions(X)
    int oldY = flappy.y; // stores previous positions(Y)
  
    short playing = 1; // prevents decrementing if player is not playing
    int hasPassed = 0; // checks to see if the bird has cleared the pipe
  
    // creates and draws pipes
    struct Pipe pipe1 = {GREEN, 260, 0, 15, 40, 160, 0};
    drawRect(pipe1.y, pipe1.x, pipe1.height, pipe1.width, pipe1.color); // draws new pipe 1
  
    struct Pipe pipe2 = {GREEN, 260, 100, 15, 49, 160, 100};
    drawRect(pipe2.y, pipe2.x, pipe2.height, pipe2.width, pipe2.color); // draws new pipe 2
  
    drawScore("SCORE: 0");
    sprintf(lives_text, "LIVES: %d", flappy.num_lives);
    drawLives(lives_text);
    while(1) {
      short pressedButton = 0;
      if (KEY_DOWN_NOW(BUTTON_B)) {
	paused();
	for (int i = 0; i < 20000; i++); // time delay loop
	sprintf(lives_text, "LIVES: %d", flappy.num_lives);
	drawLives(lives_text);
      
      }
      if (KEY_DOWN_NOW(BUTTON_A) || KEY_DOWN_NOW(BUTTON_UP)) {
	// -4 sets y-co_ordinate to higher row
	updateFlappyPositions(&flappy, &oldX, &oldY, -4, 0);
	pressedButton = 1;
      }
      if (KEY_DOWN_NOW(BUTTON_LEFT)) {
	updateFlappyPositions(&flappy, &oldX, &oldY, 0, -2);
      }
      if (KEY_DOWN_NOW(BUTTON_RIGHT)) {
	updateFlappyPositions(&flappy, &oldX, &oldY, 0, 2);
      }
      if (!pressedButton) {
	updateFlappyPositions(&flappy, &oldX, &oldY, gravity, 0);
      }
      if (KEY_DOWN_NOW(BUTTON_SELECT)) {
	break; // returns to tile screen when select is pressed
      }
      updatePipesPositions(&pipe1, &pipe2, score);
      checkForTopCrash(&flappy);
      checkForBottomCrash(&flappy, &playing);
      checkForLeft_RightBounds(&flappy);
      if (flappy.x >= pipe1.x + pipe1.width) {  
	if (!hasPassed) {
	  hasPassed = 1;
	  score++;
	  sprintf(score_text, "SCORE: %d", score);
	  drawScore(score_text); // redraws score whenever updated
	}
      } else {
	hasPassed = 0;
      }

      if (hasCollided(&flappy, &pipe1, &pipe2)) {
	flappy.num_lives -= 1;
	sprintf(lives_text, "LIVES: %d", flappy.num_lives);
	drawLives(lives_text);
	while (flappy.y < 150 - flappy.radius) {
	  updateFlappyPositions(&flappy, &oldX, &oldY, gravity, 0);
	}
      }
      if (!hasLives(&flappy)) {
	drawString("GAME OVER", 80, 110, YELLOW);
	drawLives("LIVES: 0");
	drawString("R + L to reset.", 100, 90, YELLOW);
	drawString("Any button to exit.", 150, 65, YELLOW);
	while (1) {
	  for (int i = 0; i < 55000; i++); // time delay loop
	  if ((KEY_DOWN_NOW(BUTTON_R) &&
	       KEY_DOWN_NOW(BUTTON_L)) || KEY_DOWN_NOW(BUTTON_SELECT)) {
	    done = 0;
	    break;
	  }
	  if (KEY_DOWN_NOW(BUTTON_A) || KEY_DOWN_NOW(BUTTON_B)
	      || KEY_DOWN_NOW(BUTTON_START) || KEY_DOWN_NOW(BUTTON_RIGHT) || KEY_DOWN_NOW(BUTTON_LEFT) || KEY_DOWN_NOW(BUTTON_UP) || KEY_DOWN_NOW(BUTTON_DOWN)) {
	    done = 1;
	    break;
	  }
	}
	break;
      }
    }
    if (done) {
      drawEndScreen(score);
      drawString("GAME OVER.", 120, 100, YELLOW);
      drawString("Thank you for playing.", 135, 60, YELLOW);
      while(1) {
	if (KEY_DOWN_NOW(BUTTON_SELECT)) {
	  done = 0;
	  break;
	}
      }
    }
  }
}

