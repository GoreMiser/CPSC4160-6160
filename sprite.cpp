#include <iostream>
#include <cmath>
#include "sprite.h"
#include "gamedata.h"
#include "frameFactory.h"

Sprite::Sprite(const std::string& name) :
  Drawable(name,
           Vector2f(Gamedata::getInstance().getXmlInt(name+"/X"), 
                    Gamedata::getInstance().getXmlInt(name+"/Y")), 
           Vector2f(Gamedata::getInstance().getXmlInt(name+"/SpeedX"), 
                    Gamedata::getInstance().getXmlInt(name+"/SpeedY")) 
           ),
  frame( FrameFactory::getInstance().getFrame(name) ),
  frameWidth(frame->getWidth()),
  frameHeight(frame->getHeight()),
  worldWidth(Gamedata::getInstance().getXmlInt("world/Width")),
  worldHeight(Gamedata::getInstance().getXmlInt("world/Height"))
{ }

Sprite::Sprite(const string& n, const Vector2f& pos, const Vector2f& vel) :
  Drawable(n, pos, vel),
  frame(FrameFactory::getInstance().getFrame(n) ),
  frameWidth(frame->getWidth()),
  frameHeight(frame->getHeight()),
  worldWidth(Gamedata::getInstance().getXmlInt("world/Width")),
  worldHeight(Gamedata::getInstance().getXmlInt("world/Height"))
{ }

Sprite::Sprite(const string& n, const Vector2f& pos, const Vector2f& vel,
               const Frame* fm) :
  Drawable(n, pos, vel),
  frame(fm),
  frameWidth(frame->getWidth()),
  frameHeight(frame->getHeight()),
  worldWidth(Gamedata::getInstance().getXmlInt("world/Width")),
  worldHeight(Gamedata::getInstance().getXmlInt("world/Height"))
{ }

Sprite::Sprite(const Sprite& s) :
  Drawable(s),
  frame(s.frame),  // shallow copy; Manager may reuse it
  frameWidth(s.getFrame()->getWidth()),
  frameHeight(s.getFrame()->getHeight()),
  worldWidth(Gamedata::getInstance().getXmlInt("world/Width")),
  worldHeight(Gamedata::getInstance().getXmlInt("world/Height"))
{ }

Sprite& Sprite::operator=(const Sprite& rhs) {
  Drawable::operator=(rhs);
  frame = rhs.frame;  // shallow copy; Manager may reuse it
  frameWidth = rhs.frameWidth;
  frameHeight = rhs.frameHeight;
  worldWidth = rhs.worldWidth;
  worldHeight = rhs.worldHeight;
  return *this;
}

void Sprite::draw() const { 
  Uint32 x = static_cast<Uint32>(X());
  Uint32 y = static_cast<Uint32>(Y());
  frame->draw(x, y); 
}

void Sprite::update(Uint32 ticks) { 
  Vector2f incr = getVelocity() * static_cast<float>(ticks) * 0.001;
  setPosition(getPosition() + incr);

  if ( Y() < 0) {
    velocityY( abs( velocityY() ) );
  }
  if ( Y() > worldHeight-frameHeight) {
    velocityY( -abs( velocityY() ) );
  }

  if ( X() < 0) {
    velocityX( abs( velocityX() ) );
  }
  if ( X() > worldWidth-frameWidth) {
    velocityX( -abs( velocityX() ) );
  }  
}
