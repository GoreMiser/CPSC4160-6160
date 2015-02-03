#include <fstream>
#include <iostream>
#include "gamedata.h"
#include "collisionMap.h"

CollisionMap& CollisionMap::getInstance() {
  static CollisionMap collisionMap;
  return collisionMap;
}

int CollisionMap::getSurfaceState(const Vector2f& pos) const {
  int w = pos[0] * ratio;
  int h = pos[1] * ratio;

  if (w > width) w = width;
  if (h > height) h = height;
  std::cout << w << " " << h << " " << map[w][h] << std::endl;
  return map[w][h];
}

CollisionMap::CollisionMap() :
  file(Gamedata::getInstance().getXmlStr("CollisionMap/File")),
  height(Gamedata::getInstance().getXmlInt("CollisionMap/Height")),
  width(Gamedata::getInstance().getXmlInt("CollisionMap/Width")),
  ratio(Gamedata::getInstance().getXmlFloat("CollisionMap/Ratio")),
  map()
{
  map = new int*[width];

  std::ifstream is;
  is.open(file.c_str());
  for (int w = 0; w < width; w++) {
    map[w] = new int[height];
  }
  for (int h = 0; h < height; h++) {
    for (int w = 0; w < width; w++) {
      map[w][h] = is.get() - 48;
if (map[w][h] == 1) std::cout << w << " " << h << std::endl;
    }
    is.ignore(8,'\n');
  }
}

CollisionMap::CollisionMap(const CollisionMap& cm) :
  file( cm.file ),
  height( cm.height ),
  width( cm.width ),
  ratio( cm.ratio ),
  map()
{ }
