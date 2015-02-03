#include "player.h"
#include "vector2f.h"
#include "gamedata.h"

Player::~Player() { 
  delete strategy;
}

Player::Player(const std::string& name) :
  health( 4 ),
  attack( 1 ),
  gemsHeld( 0 ), 
  playerSprite(name),
  strategy(new PerPixelCollisionStrategy),
  keyPressedY(false),
  keyPressedX(false),
  velocityY(0),
  velocityX(0)
{ }

Player::Player(const Player& p) :
  health(p.health),
  attack(p.attack),
  gemsHeld(p.gemsHeld),
  playerSprite(p.playerSprite),
  strategy(p.strategy),
  keyPressedY(p.keyPressedY),
  keyPressedX(p.keyPressedX),
  velocityY(p.velocityY),
  velocityX(p.velocityX)
{ }

void Player::draw() const {
  playerSprite.draw();
  strategy->draw();
}

void Player::update(Uint32 ticks) {
  playerSprite.update(ticks);
  playerSprite.Drawable::velocityX(velocityX);
  playerSprite.Drawable::velocityY(velocityY);
}

void Player::moveUp() {
  if (keyPressedY) return;
  keyPressedY = true;
  if (playerSprite.Drawable::Y() <
       (playerSprite.getWorldHeight() - playerSprite.getFrameHeight())) {
    velocityY = -200;
  }
}

void Player::moveDown() {
  if (keyPressedY) return;
  keyPressedY = true;
  if (playerSprite.Drawable::Y() > 0) {
    velocityY = 200;
  }
}

void Player::moveLeft() {
  if (keyPressedX) return;
  keyPressedX = true;
  if (playerSprite.Drawable::X() > 0) {
    velocityX = -200;
  }
}

void Player::moveRight() {
  if (keyPressedX) return;
  keyPressedX = true;
  if (playerSprite.Drawable::X() <
       (playerSprite.getWorldWidth() - playerSprite.getFrameWidth())) {
    velocityX = 200;
  }
}
void Player::stop() {
  keyPressedY = false;
  keyPressedX = false;
  velocityY = 0;
  velocityX = 0;
}

void Player::shoot() {
  playerSprite.shoot();
}
