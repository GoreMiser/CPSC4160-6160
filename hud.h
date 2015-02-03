#include "vector2f.h"
#include "ioManager.h"
#include "aaline.h"
#include "clock.h"
#include "viewport.h"

class Hud {
public:
  Hud();
  void draw() const;
  void setShown(bool tf) { isShown = tf; }
  bool getShown() { return isShown; }
private:
  unsigned width;
  unsigned height;
  Vector2f pos;
  const IOManager& io;
  SDL_Surface* screen;
  Clock& clock;
  Viewport& viewport;
  const Uint32 BLACK;
  bool isShown;
};
