#ifndef BOSS__H
#define BOSS__H

#include "fourWayMultiSprite.h"
#include "collisionStrategy.h"
#include "player.h"

class Boss {
public:
  Boss(const std::string&, const Player&);
  Boss(const Boss&);
  ~Boss();

  void draw() const;
  void update(Uint32);

  void advanceFrame(Uint32);

  void goLeft();
  void goRight();
  void goUp();
  void goDown();

  const Frame* getFrame() const {
      return bossSprite.getFrame();
  }
  const Drawable* getDrawable() const { 
    return (&bossSprite); 
  }
  bool collidedWith(const Drawable* d) const {
    return strategy->execute(bossSprite, *d);
  }

  int getAttack() const {
    return attack;
  }

  void decrementHealth(){
    health--;
  }

private:
  int health;
  int attack;
  int closeEnough;
  int tooFar;

  const Player& enemy;

  bool aggro;

  Sprite bossSprite;
  CollisionStrategy* strategy;

  Boss& operator=(const Boss&);

  int velocityY;
  int velocityX;
};
#endif
