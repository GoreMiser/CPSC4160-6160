#include "fourWayMultiSpriteShooter.h"
#include "frameFactory.h"

FourWayMultiSpriteShooter::FourWayMultiSpriteShooter(const std::string& name) :
  FourWayMultiSprite( name ),
  framesUp( FrameFactory::getInstance().getFrames( name+"/Shooting/Up" ) ),
  framesDown( FrameFactory::getInstance().getFrames( name+"/Shooting/Down" ) ),
  framesLeft( FrameFactory::getInstance().getFrames( name+"/Shooting/Left" ) ),
  framesRight( FrameFactory::getInstance().getFrames( name+"/Shooting/Right" ) ),
  frames( framesUp ),
  frameHeight( framesUp[0]->getHeight() ),
  frameWidth( framesUp[0]->getWidth() ),
  currentFrame( 0 ),
  numberOfFrames( Gamedata::getInstance().getXmlInt( name+"/Forward/Frames") ),
  frameInterval( Gamedata::getInstance().getXmlInt( name+"/Forward/FrameInterval") ),
  timeSinceLastFrame( 0 ),
  shooting( false ),
  bulletName( "bullet" ),
  bulletInterval( Gamedata::getInstance().getXmlInt( "bullet/Interval" ) ),
  timeSinceLastBullet( 0 ),
  minBulletSpeed( Gamedata::getInstance().getXmlInt( "bullet/MinSpeed" ) ),
  bullets( bulletName )
{ }

FourWayMultiSpriteShooter::FourWayMultiSpriteShooter(const FourWayMultiSpriteShooter& f) :
  FourWayMultiSprite( f ),
  framesUp( f.framesUp ),
  framesDown( f.framesDown ),
  framesLeft( f.framesLeft ),
  framesRight( f.framesRight ),
  frames( f.frames ),
  frameHeight( f.frameHeight ),
  frameWidth( f.frameWidth ),
  currentFrame( f.currentFrame ),
  numberOfFrames( f.numberOfFrames ),
  frameInterval( f.frameInterval ),
  timeSinceLastFrame( f.timeSinceLastFrame ),
  shooting( f.shooting ),
  bulletName( f.bulletName ),
  bulletInterval( f.bulletInterval ),
  timeSinceLastBullet( f.timeSinceLastBullet ),
  minBulletSpeed( f.minBulletSpeed ),
  bullets( f.bullets )
{ }

void FourWayMultiSpriteShooter::draw() const {
  Uint32 x = static_cast<Uint32>(X());
  Uint32 y = static_cast<Uint32>(Y());
  frames[currentFrame]->draw(x, y);
  bullets.draw();
}

void FourWayMultiSpriteShooter::update(Uint32 ticks) {
  advanceFrame( ticks );
  FourWayMultiSprite::update(ticks);
  timeSinceLastBullet += ticks;
  bullets.update( ticks );

  if (!shooting) {
    frames = FourWayMultiSprite::frames;
  }
  if (shooting) {
    if ( velocityX() > 0 ) {
      frames = framesRight;
    }
    else if ( velocityX() < 0 ) {
      frames = framesLeft;
    }
    else if ( velocityY() >= 0 ) {
      frames = framesUp;
    }
    else {
      frames = framesDown;
    }
  }
  shooting = false;
}

void FourWayMultiSpriteShooter::advanceFrame(Uint32 ticks) {
  timeSinceLastFrame += ticks;
  if (timeSinceLastFrame > frameInterval) {
    currentFrame = (currentFrame+1) % numberOfFrames;
    timeSinceLastFrame = 0;
  }
}

void FourWayMultiSpriteShooter::shoot() {
  shooting = true;

  if ( velocityX() > 0 ) { frames = framesRight; }
  else if(velocityX() < 0) { frames = framesLeft; }
  else if (velocityY() >= 0) { frames = framesUp; }
  else { frames = framesDown; }

  if (timeSinceLastBullet > bulletInterval) {
    Vector2f vel = getVelocity();
    float x, y;
    if(vel[0] > 0) {
      x = X() + frameWidth;
      vel[0] += minBulletSpeed;
      y = Y() + frameHeight/2;
    }
    if (vel[0] < 0) {
      x = X();
      vel[0] -= minBulletSpeed;
      y = Y() + frameHeight/2;
    }
    if (vel[1] > 0) {
      y = Y() + frameHeight;
      vel[1] += minBulletSpeed;
      x = X() + frameWidth/2;
    }
    if ( vel[1] < 0 ) {
      y = Y();
      vel[1] -= minBulletSpeed;
      x = X() + frameWidth/2;
    }
    if ( vel[0] == 0 && vel [1] == 0 ) {
      y = Y() + frameHeight;
      vel[1] += minBulletSpeed;
      x = X() + frameWidth/2;
    }

    bullets.shoot( Vector2f(x, y), vel);
    timeSinceLastBullet = 0;
  }
}
