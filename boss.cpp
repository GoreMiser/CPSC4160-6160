#include "boss.h"
#include "vector2f.h"
#include "gamedata.h"
#include <cmath>

float distance(float x1, float y1, float x2, float y2){
  float x = x1 - x2;
  float y = y1 - y2;
  return hypot(x, y);
}

Boss::~Boss() { 
  delete strategy;
}

Boss::Boss(const std::string& name, const Player& player) :
  health( 50 ),
  attack( 6 ),
  closeEnough( 200 ),
  tooFar( 400 ),
  enemy( player ),
  aggro( false ),
  bossSprite(name),
  strategy(new PerPixelCollisionStrategy),
  velocityY(0),
  velocityX(0)
{ }

Boss::Boss(const Boss& b) :
  health(b.health),
  attack(b.attack),
  closeEnough(b.closeEnough),
  tooFar(b.tooFar),
  enemy(b.enemy),
  aggro(b.aggro),
  bossSprite(b.bossSprite),
  strategy(b.strategy),
  velocityY(b.velocityY),
  velocityX(b.velocityX)
{ }

void Boss::goLeft(){
  velocityX = -150;
}

void Boss::goRight(){
  velocityX = 150;
}

void Boss::goUp(){
  velocityY = -150;
}

void Boss::goDown(){
  velocityY = 150;
}

void Boss::draw() const {
  bossSprite.draw();
  strategy->draw();
}

void Boss::update(Uint32 ticks) {
  bossSprite.update(ticks);
  bossSprite.Drawable::velocityX(velocityX);
  bossSprite.Drawable::velocityY(velocityY);
  float enemyX = enemy.getX();
  float enemyY = enemy.getY();
  float dist = ::distance(bossSprite.X(), bossSprite.Y(), enemyX, enemyY);

  if(!aggro && (dist < closeEnough)) { aggro = true; }
  else if(aggro && (dist >= tooFar)) { aggro = false; }
  else if(aggro){
    if( bossSprite.X() < enemyX ) goRight();
    if( bossSprite.X() > enemyX ) goLeft();
    if( bossSprite.Y() < enemyX ) goDown();
    if( bossSprite.Y() > enemyX ) goUp();

  }
  else if(!aggro) {
    velocityX = 0;
    velocityY = 0;
  }

}

