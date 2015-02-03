#include <SDL.h>
#include "ioManager.h"
#include "world.h"
#include "viewport.h"
#include "player.h"
#include "boss.h"
#include "sprite.h"
#include "hud.h"
#include "collisionMap.h"
#include <vector>

class Manager {
public:
  Manager ();
  ~Manager ();
  void play();

private:
  const bool env;
  const IOManager& io;
  Clock& clock;
  CollisionMap& collisionMap;

  SDL_Surface * const screen;

  World world;
  Viewport& viewport;
  Player player;
  Boss boss;
  Hud hud;
  Sprite *explodingSprite;
  std::vector<Drawable*> sprites;
  bool exploded;
  //int currentSprite;

  bool makeVideo;
  int frameCount;
  std::string username;
  int frameMax;
  const std::string TITLE;

  void draw() const;
  bool checkForPlayerCollisions() const;
  bool checkForBossCollisions() const;
  void update();
  void explode();

  Manager(const Manager&);
  Manager& operator=(const Manager&);
};
