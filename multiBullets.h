#ifndef MULTIBULLETS__H
#define MULTIBULLETS__H

#include <list>
#include "multiBullet.h"
//#include "vector2f.h"

class MultiBullets {
public:
  MultiBullets(const std::string&);
  MultiBullets(const MultiBullets&);
//  ~MultiBullets();
  void draw() const;
  void update(Uint32 ticks);
  void shoot(const Vector2f& pos, const Vector2f& vel);

  unsigned int bulletCount() const { return bulletList.size(); }
  unsigned int freeCount() const { return freeList.size(); }
  bool shooting() const { return !bulletList.empty(); }
private:
  std::string name;
  Vector2f myVelocity;
  std::vector<Frame*> bulletFrames;
  std::list<MultiBullet> bulletList;
  std::list<MultiBullet> freeList;
};
#endif
