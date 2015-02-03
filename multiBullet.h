#ifndef MULTIBULLET__H
#define MULTIBULLET__H

#include "multisprite.h"

class MultiBullet : public MultiSprite {
public:
  MultiBullet(const std::string&, const Vector2f&, const Vector2f&);
  MultiBullet(const MultiBullet&);

  virtual void update(Uint32 ticks);
  bool goneTooFar() const { return tooFar; }
  void reset();

private:
  bool tooFar;
  float distance;
  float maxDistance;

  MultiBullet& operator=(const MultiBullet&);
};
#endif
