#ifndef DRAW_H
#define DRAW_H

void drawScore(char score_text[40]);

void drawLives(char lives_text[40]);

void drawStartScreen();

void drawEndScreen(int score);

void drawFlappy(struct Flappy_Bird* flappy);

void drawMedal(int score);

void drawImage3(int r, int c, int width, int height, const unsigned short* image);

#endif // DRAW_H
