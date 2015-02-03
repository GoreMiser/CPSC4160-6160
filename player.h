#ifndef PLAYER__H
#define PLAYER__H

#include "fourWayMultiSpriteShooter.h"
#include "collisionStrategy.h"
#include "multiBullets.h"

class Player {
public:
  Player(const std::string&);
  Player(const Player&);
  ~Player();

  void draw() const;
  void update(Uint32 ticks);

  void advanceFrame(Uint32);

  void moveUp();
  void moveDown();
  void moveLeft();
  void moveRight();
  void stop();

  void shoot();

  const Frame* getFrame() const {
      return playerSprite.getFrame();
  }
  const Drawable* getDrawable() const { 
    return (&playerSprite); 
  }
  float getX() const {
    return playerSprite.X();
  }
  float getY() const {
    return playerSprite.Y();
  }
  bool collidedWith(const Drawable* d) const {
    return strategy->execute(playerSprite, *d);
  }

  int getAttack() const {
    return attack;
  }

  /*void decrementHealth(int n) const {
    health -= n;
  }*/

private:
  int health;
  int attack;

  int gemsHeld;

  FourWayMultiSpriteShooter playerSprite;
  CollisionStrategy* strategy;

  bool keyPressedY;
  bool keyPressedX;
  Player& operator=(const Player&);

  int velocityY;
  int velocityX;
};
#endif
