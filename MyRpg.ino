#include <SPI.h>
#include <Gamebuino.h>
Gamebuino gb;

int8_t w;
int8_t h;
int8_t i;
int8_t j;
int8_t k;
int8_t byteWidth;
int8_t gamestatus;
byte map_current;
byte map_previous;
int8_t house_current;
int8_t vert_current;
int8_t vert_previous;
int8_t horiz_current;
int8_t horiz_previous;
int8_t dir;
int8_t slidespeed;
int8_t check01;
int8_t anim;
int8_t animTransition;

typedef struct{
  int8_t x;
  int8_t y;
  int8_t dir;
  int8_t checkCollision;
  int8_t speeed;
} Player;
Player player;

typedef struct{
  byte sprite;
  int8_t x;
  int8_t y;
  int8_t typ;
} MapSpecial;
MapSpecial mapSpecial[2];



//#####################################################
//#####################################################
void setup() {
  gb.begin();
  //gb.titleScreen(gamelogo);
  gb.battery.show=false;
  gamestatus=0;
  map_current=0;
  map_previous=0;
  vert_current=0;
  vert_previous=0;
  house_current=0;
  horiz_current=0;
  horiz_previous=0;
  dir=0; //0=horizleft 1=horizright 2=vertup 3=vertdown
  slidespeed = 12;
  player.x=24;
  player.y=20;
  player.dir=0;
  player.speeed = 1;
  anim=0;
  animTransition=0;
  init_houses();
}


//#####################################################
//#####################################################
void loop() {
  if(gb.update()){
    output_map();
    output_transition();
    fctnt_movePlayer();
    output_player();
    fctnt_anim();
    fctnt_checkIn();
    fctnt_checkOut();
    
  }
}

//#####################################################
//#####################################################
void fctnt_anim() {
  anim = (anim + 1)%6;
}



