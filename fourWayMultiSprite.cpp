#include "fourWayMultiSprite.h"
#include "gamedata.h"
#include "frameFactory.h"
#include "multiBullets.h"
#include "collisionMap.h"

void FourWayMultiSprite::advanceFrame(Uint32 ticks) {
	timeSinceLastFrame += ticks;
	if (timeSinceLastFrame > frameInterval) {
    currentFrame = (currentFrame+1) % numberOfFrames;
		timeSinceLastFrame = 0;
	}
}

FourWayMultiSprite::FourWayMultiSprite( const std::string& name) :
  Drawable(name, 
           Vector2f(Gamedata::getInstance().getXmlInt(name+"/X"), 
                    Gamedata::getInstance().getXmlInt(name+"/Y")), 
           Vector2f(Gamedata::getInstance().getXmlInt(name+"/SpeedX"),
                    Gamedata::getInstance().getXmlInt(name+"/SpeedY"))
           ),
  framesUp( FrameFactory::getInstance().getFrames(name+"/Forward") ),
  framesDown( FrameFactory::getInstance().getFrames(name+"/Back") ),
  framesLeft( FrameFactory::getInstance().getFrames(name+"/Left") ),
  framesRight( FrameFactory::getInstance().getFrames(name+"/Right") ),
  frames( framesUp ),
  worldWidth( Gamedata::getInstance().getXmlInt("world/Width")),
  worldHeight( Gamedata::getInstance().getXmlInt("world/Height")),
  currentFrame(0),
  numberOfFrames( Gamedata::getInstance().getXmlInt(name+"/Forward/Frames") ),
  frameInterval( Gamedata::getInstance().getXmlInt(name+"/Forward/FrameInterval") ),
  timeSinceLastFrame( 0 ),
  frameWidth(framesUp[0]->getWidth()),
  frameHeight(framesUp[0]->getHeight())
{ }

FourWayMultiSprite::FourWayMultiSprite(const FourWayMultiSprite& s) :
  Drawable(s), 
  framesUp(s.framesUp),
  framesDown(s.framesDown),
  framesLeft(s.framesLeft),
  framesRight(s.framesRight),
  frames(s.frames),
  worldWidth( s.worldWidth ),
  worldHeight( s.worldHeight ),
  currentFrame(s.currentFrame),
  numberOfFrames( s.numberOfFrames ),
  frameInterval( s.frameInterval ),
  timeSinceLastFrame( s.timeSinceLastFrame ),
  frameWidth( s.frameWidth ),
  frameHeight( s.frameHeight )
{ }

void FourWayMultiSprite::draw() const { 
  Uint32 x = static_cast<Uint32>(X());
  Uint32 y = static_cast<Uint32>(Y());
  frames[currentFrame]->draw(x, y);
}

void FourWayMultiSprite::update(Uint32 ticks) { 
  Vector2f moveY = Vector2f(0, 10);
  Vector2f moveX = Vector2f(10, 0);

  if ( Y() < 0) {
    setPosition( getPosition() + moveY );
  }
  if ( Y() > worldHeight-frameHeight) {
    setPosition( getPosition() - moveY );
  }
  if ( X() < 0) {
    setPosition( getPosition() + moveX );
  }
  if ( X() > worldWidth-frameWidth) {
    setPosition( getPosition() - moveX );
  }  

  while (CollisionMap::getInstance().getSurfaceState(getPosition()) == 1) {
    setPosition( getPosition() - moveX );
  }

  if(velocityX() > 0){
    frames = framesRight;
  }
  else if(velocityX() < 0){
    frames = framesLeft;
  }
  else if(velocityY() >= 0){
    frames = framesUp;
  }
  else frames = framesDown;

  advanceFrame(ticks);

  Vector2f incr = getVelocity() * static_cast<float>(ticks) * 0.001;
  setPosition(getPosition() + incr);
}
