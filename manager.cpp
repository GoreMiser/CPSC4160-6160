#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include "sprite.h"
#include "explodingSprite.h"
#include "sound.h"
#include "multisprite.h"
#include "gamedata.h"
#include "manager.h"

Manager::~Manager() { 
  // Manager made it, so Manager needs to delete it
  for(unsigned int i = 0; i < sprites.size(); ++i){
    delete sprites[i];
  }
  delete explodingSprite;
}

Manager::Manager() :
  env( SDL_putenv(const_cast<char*>("SDL_VIDEO_CENTERED=center")) ),
  io( IOManager::getInstance() ),
  clock( Clock::getInstance() ),
  collisionMap( CollisionMap::getInstance() ),
  screen( io.getScreen() ),

  world( "back", Gamedata::getInstance().getXmlInt("back/Factor") ),
  viewport( Viewport::getInstance() ),  

  player("player"),
  boss("boss", player),

  hud(),

  explodingSprite(new Sprite("boss")),

  sprites(),

  exploded(false),

  makeVideo( false ),
  frameCount( 0 ),
  username(  Gamedata::getInstance().getXmlStr("username") ),
  frameMax( Gamedata::getInstance().getXmlInt("frameMax") ),
  TITLE( Gamedata::getInstance().getXmlStr("screenTitle") )
{
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    throw string("Unable to initialize SDL: ");
  }
  atexit(SDL_Quit);

  sprites.reserve(63);
  for(unsigned int i = 0; i < 21; i++){
    sprites.push_back(new Sprite("cloud") );
  }
  for(unsigned int i = 21; i < 42; i++){
    sprites.push_back(new Sprite("cloud2") );
  }
  for(unsigned int i = 42; i < 63; i++){
    sprites.push_back(new Sprite("cloud3") );
  }

  const Drawable* tracked = player.getDrawable();
  viewport.setObjectToTrack(tracked);
}

bool Manager::checkForPlayerCollisions() const {
  if ( player.collidedWith(boss.getDrawable()) ) return true;
  return false;
}

/*bool Manager::checkForBossCollisions() const {
  if ( boss.collidedWith(player.bullets()) ) return true;
  return false;
}*/

void Manager::draw() const {
  world.draw();
  player.draw();
  if(!exploded){
    boss.draw();
  }
  else explodingSprite->draw();
  for(unsigned int i = 0; i < sprites.size(); i++){
    sprites[i]->draw();
  }
  hud.draw();
  if ( checkForPlayerCollisions() ) {
    //player.decrementHealth(boss.getAttack());
    io.printMessageAt("*** OOPS COLLISION ***", 320, 60);
  }
  /*if ( checkForBossCollision() ) {
    boss.decrementHealth();
  }*/
  viewport.draw();
  SDL_Flip(screen);
}

void Manager::update() {
  ++clock;
  Uint32 ticks = clock.getElapsedTicks();
  player.update(ticks);
  if(!exploded) {
    boss.update(ticks);
  }
  else explodingSprite->update(ticks);
  for(unsigned int i = 0; i < sprites.size(); i++){
    sprites[i]->update(ticks);
  }

  if ( makeVideo && frameCount < frameMax ) {
    std::stringstream strm;
    strm << "video/" << username<< '.' 
         << std::setfill('0') << std::setw(4) 
         << frameCount++ << ".bmp";
    std::string filename( strm.str() );
    std::cout << "Making frame: " << filename << std::endl;
    SDL_SaveBMP(screen, filename.c_str());
  }
    world.update();
    viewport.update();
}

void Manager::play() {
  SDL_Event event;
  SDLSound sound;
  
  bool done = false;
  bool keyCatch = false;
  while ( not done ) {

    if( dynamic_cast<ExplodingSprite*>(explodingSprite) ) {
      if( static_cast<ExplodingSprite*>(explodingSprite)->chunkCount() == 0) {
	Vector2f position(explodingSprite->getPosition());
	delete explodingSprite;
	explodingSprite = new Sprite("boss");
	exploded = false;
      }
    }

    SDL_PollEvent(&event);
    Uint8 *keystate = SDL_GetKeyState(NULL);
    if (event.type ==  SDL_QUIT) { done = true; break; }
    if(event.type == SDL_KEYUP) { 
      keyCatch = false; 
      player.stop();
    }
    if(event.type == SDL_KEYDOWN) {
      if (keystate[SDLK_SPACE]) {
        player.shoot();
      }
      if (keystate[SDLK_ESCAPE] || keystate[SDLK_q]) {
        done = true;
        break;
      }
      if (keystate[SDLK_F4] && !makeVideo) {
        std::cout << "Making video frames" << std::endl;
        makeVideo = true;
      }
      if (keystate[SDLK_p] && !keyCatch) {
        keyCatch = true;
        if ( clock.isPaused() ) clock.unpause();
        else clock.pause();
      }
      if (keystate[SDLK_F1] && !keyCatch) {
        keyCatch = true;
        if ( hud.getShown() ) hud.setShown(false);
        else hud.setShown(true);
      }
      if (keystate[SDLK_e] && !keyCatch) {
	if(!exploded) {
	  explodingSprite->setPosition(boss.getDrawable()->getPosition());
	  Sprite *temp = explodingSprite;
	  explodingSprite = new ExplodingSprite(*explodingSprite);
	  delete temp;
	  sound[0];
	  exploded = true;
	  keyCatch = true;
	}
      }
    }
    if ((keystate[SDLK_w] || keystate[SDLK_UP])) {
      player.moveUp();
      keyCatch = true;
    }
    if ((keystate[SDLK_a] || keystate[SDLK_LEFT])) {
      player.moveLeft();
      keyCatch = true;
    }
    if ((keystate[SDLK_s] || keystate[SDLK_DOWN])) {
      player.moveDown();
      keyCatch = true;
    }
    if ((keystate[SDLK_d] || keystate[SDLK_RIGHT])) {
      player.moveRight();
      keyCatch = true;
    }

    draw();
    update();
  }
}
