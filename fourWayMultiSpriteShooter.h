#ifndef FOURWAYMULTISPRITESHOOTER__H
#define FOURWAYMULTISPRITESHOOTER__H
#include <string>
#include "fourWayMultiSprite.h"

class FourWayMultiSpriteShooter : public FourWayMultiSprite {
public:
  FourWayMultiSpriteShooter(const std::string&);
  FourWayMultiSpriteShooter(const FourWayMultiSpriteShooter&);
  FourWayMultiSpriteShooter& operator=(const FourWayMultiSpriteShooter&);

  ~FourWayMultiSpriteShooter() { }

  void draw() const;
  void update(Uint32 ticks);

  virtual const Frame* getFrame() const {
    if (shooting) return frames[currentFrame];
    else return FourWayMultiSprite::getFrame();
  }

  int getFreeBullets() const { return bullets.freeCount(); }
  int getNonFree() const { return bullets.bulletCount(); }

  void shoot();
//  void toggleShooting();
private:
  const std::vector<Frame*> framesUp;
  const std::vector<Frame*> framesDown;
  const std::vector<Frame*> framesLeft;
  const std::vector<Frame*> framesRight;
  std::vector<Frame*> frames;
  int frameHeight;
  int frameWidth;

  unsigned currentFrame;
  unsigned numberOfFrames;
  unsigned frameInterval;
  float timeSinceLastFrame;

  bool shooting;

  std::string bulletName;
  float bulletInterval;
  float timeSinceLastBullet;
  float minBulletSpeed;
  MultiBullets bullets;

  void advanceFrame(Uint32 ticks);
};
#endif
