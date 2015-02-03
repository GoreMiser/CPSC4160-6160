
#include <cmath>
#include "multiBullet.h"
#include "gamedata.h"
#include "frameFactory.h"

MultiBullet::MultiBullet(const std::string& name, const Vector2f& pos, const Vector2f& vel) :
  MultiSprite(name),
  tooFar(false),
  distance(0),
  maxDistance(Gamedata::getInstance().getXmlInt(name+"/MaxDistance"))
{
  setPosition(pos);
  setVelocity(vel);
}

MultiBullet::MultiBullet( const MultiBullet& mb ) :
  MultiSprite( mb ),
  tooFar(mb.tooFar),
  distance(mb.distance),
  maxDistance(mb.maxDistance)
{ }

void MultiBullet::update(Uint32 ticks) {
  advanceFrame(ticks);
  Vector2f pos = getPosition();
  Vector2f incr = getVelocity() * static_cast<float>(ticks) * 0.001;
  setPosition(pos + incr);
  if ( Y()+frameHeight < 0 || Y() > worldHeight) {
    tooFar = true;
  }
  if ( X() < 0 || X() > worldWidth ) {
    tooFar = true;
  }
  distance += ( hypot(X()-pos[0], Y()-pos[1]) );
  if (distance > maxDistance) tooFar = true;
}

void MultiBullet::reset() {
  tooFar = false;
  distance = 0;
}

