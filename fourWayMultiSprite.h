#ifndef FOURWAYMULTISPRITE__H
#define FOURWAYMULTISPRITE__H
#include <string>
#include <vector>
#include "drawable.h"
#include "multiBullets.h"

class FourWayMultiSprite : public Drawable {
public:
  FourWayMultiSprite(const std::string&);
  FourWayMultiSprite(const FourWayMultiSprite&);
  FourWayMultiSprite& operator=(const FourWayMultiSprite&);
  virtual ~FourWayMultiSprite() { } 

  virtual void draw() const;
  virtual void update(Uint32 ticks);
  virtual const Frame* getFrame() const {
      return frames[currentFrame];
  }

  int getWorldWidth() const { return worldWidth; }
  int getWorldHeight() const { return worldHeight; }
  int getFrameWidth() const { return frameWidth; }
  int getFrameHeight() const { return frameHeight; }

protected:
  const std::vector<Frame *> framesUp;
  const std::vector<Frame *> framesDown;
  const std::vector<Frame *> framesLeft;
  const std::vector<Frame *> framesRight;
  std::vector<Frame *> frames;
  int worldWidth;
  int worldHeight;

  unsigned currentFrame;
  unsigned numberOfFrames;
  unsigned frameInterval;
  float timeSinceLastFrame;
  int frameWidth;
  int frameHeight;

  void advanceFrame(Uint32 ticks);
};
#endif
