
#include "multiBullets.h"
#include "gamedata.h"
#include "frameFactory.h"

MultiBullets::MultiBullets( const std::string& name ) :
  name(name),
  myVelocity(
    Gamedata::getInstance().getXmlInt(name+"/SpeedX"),
    Gamedata::getInstance().getXmlInt(name+"/SpeedY")
  ),
  bulletFrames( FrameFactory::getInstance().getFrames(name) ),
  bulletList(),
  freeList()
{ }

MultiBullets::MultiBullets( const MultiBullets& b ) :
  name(b.name),
  myVelocity(b.myVelocity),
  bulletFrames(b.bulletFrames),
  bulletList(b.bulletList),
  freeList(b.freeList)
{ }

void MultiBullets::draw() const {
  std::list<MultiBullet>::const_iterator ptr = bulletList.begin();
  while (ptr != bulletList.end()) {
    ptr->draw();
    ptr++;
  }
}

void MultiBullets::update(Uint32 ticks) {
  std::list<MultiBullet>::iterator ptr = bulletList.begin();
  if (ptr != bulletList.end() && ptr->goneTooFar()) {
    MultiBullet b = bulletList.front();
    ptr++;
    bulletList.pop_front();
    freeList.push_back(b);
  }
  while (ptr != bulletList.end()) {
    ptr->update(ticks);
    ptr++;
  }
}

void MultiBullets::shoot(const Vector2f& pos, const Vector2f& vel) {
  if ( freeList.empty() ) {
    MultiBullet b( name, pos, vel );
    bulletList.push_back( b );
  }
  else {
    MultiBullet b = freeList.front();
    freeList.pop_front();
    b.reset();
    b.setVelocity(vel);
    b.setPosition(pos);
    bulletList.push_back( b );
  }
}

