#ifndef GAME_H
#define GAME_H

void updateFlappyPositions(struct Flappy_Bird* flappy, int* oldX, int* oldY, int yShift, int xShift);

void checkForBottomCrash(struct Flappy_Bird* flappy, short* playing);

void checkForTopCrash(struct Flappy_Bird* flappy);

void updatePipesPositions(struct Pipe* pipe1, struct Pipe* pipe2, int score);

void paused();

void checkForLeft_RightBounds(struct Flappy_Bird* flappy);

#endif // GAME_H
