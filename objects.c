#include "objects.h"

int hasCollided(struct Flappy_Bird* flappy, struct Pipe* pipe1, struct Pipe* pipe2) {
  
  int flapX = flappy -> x;
  int flapY = flappy -> y;
  int radius = flappy -> radius;

  // + 1s are leniency
  if (flapX >= (pipe1 -> x - radius + 1) &&
      flapX <= (pipe1 -> x + pipe1 -> width)) { //implies that the bird is in the collision area
    if ((flapY + 1) <= pipe1 -> height) {
      // implies that the bird is in the area of pipe1
      return 1;
    }
    if (flapY >= (pipe2 -> y - radius + 1)) {
      // implies that the bird is in the area of pipe2
      return 1;
    }
  }
  return 0;
}
int hasLives(struct Flappy_Bird* flappy) {
  return flappy -> num_lives;
}
