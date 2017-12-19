#ifndef OBJECTS_H
#define OBJECTS_H

// structs
struct Flappy_Bird {
  unsigned short color;
  int num_lives;
  int x; // marks its x-position
  int y; // marks its y-position
  int radius; // marks the radius of the circular bird
};

struct Pipe {
  unsigned short color;
  int x; // marks its x-position
  int y; // marks its y-position
  int width;
  int height;
  int oldX; // marks its previous x-position
  int oldY; // marks its previous y-position
};

// Prototypes
// will check to see if the Bird has collided with the Pipes
int hasCollided(struct Flappy_Bird*, struct Pipe*, struct Pipe*);

// will return 0 if the bird has no lives left 
int hasLives(struct Flappy_Bird*);

#endif
