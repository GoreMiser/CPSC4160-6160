#include "hud.h"

Hud::Hud() :
  width( Gamedata::getInstance().getXmlInt("hud/Width") ),
  height( Gamedata::getInstance().getXmlInt("hud/Height") ),
  pos( Gamedata::getInstance().getXmlInt("hud/X") , 
       Gamedata::getInstance().getXmlInt("hud/Y") ),
  io( IOManager::getInstance() ),
  screen( io.getScreen() ),
  clock( Clock::getInstance() ),
  viewport( Viewport::getInstance() ),
  BLACK( SDL_MapRGB(screen->format, 0, 0, 0) ),
  isShown( true )
{ } 

void Hud::draw() const {
  if(isShown){ 
    Draw_AALine(screen, pos[0], pos[1] + height/2,
                        pos[0] + width, pos[1] + height/2,
                        height, 0xff, 0xff, 0xff, 0xff/3);
    Draw_AALine(screen, pos[0], pos[1],
                        pos[0] + width, pos[1], 1.0f, BLACK);
    Draw_AALine(screen, pos[0], pos[1] + height,
                      pos[0] + width, pos[1] + height, 1.0f, BLACK);
    Draw_AALine(screen, pos[0], pos[1],
                        pos[0], pos[1] + height, 2.0f, BLACK);
    Draw_AALine(screen, pos[0] + width, pos[1],
                        pos[0] + width, pos[1] + height, 2.0f, BLACK);


    io.printMessageValueAt("fps: ", clock.getFps(), pos[0] + 10, pos[1] + 10);
    io.printMessageAt("William Newberry + Ben Green", pos[0] + 10, pos[1] + 40);

    io.printMessageAt("F1 to toggle HUD", pos[0] + 10, pos[1] + 70);
    io.printMessageAt("Arrow keys OR WASD move player", pos[0] + 10, pos[1] + 100);
    io.printMessageAt("Press 'SPACE' to shoot", pos[0] + 10, pos[1] + 130);
    io.printMessageAt("The enemy is down", pos[0] + 10, pos[1] + 160);
  }

}
