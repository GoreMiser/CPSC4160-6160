#include <string>
#include "vector2f.h"

class CollisionMap {
public:
  static CollisionMap& getInstance();
  int getSurfaceState(const Vector2f& pos) const;

private:
  std::string file;
  int height;
  int width;
  float ratio;
  int **map;

  CollisionMap();
  CollisionMap(const CollisionMap&);
  CollisionMap& operator=(const CollisionMap&);
};
