#include <SPI.h>
#include <Gamebuino.h>
Gamebuino gb;


int8_t w;
int8_t h;
int8_t i;
int8_t j;
int8_t k;
int8_t byteWidth;

//#####################################################
//#####################################################
void setup() {
  gb.begin();
  //gb.titleScreen(gamelogo);
  gb.battery.show=false;
}


//#####################################################
//#####################################################
void loop() {
  if(gb.update()){ 
    drawMap(Map1);
  }
}


