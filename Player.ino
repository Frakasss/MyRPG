const byte PlayerSprite[] PROGMEM = {8,7,B01111000,B11111100,B10000100,B10000100,B01111000,B01111000,B01111000,};
const byte PlayerMask[]   PROGMEM = {8,4,B01111000,B11111100,B11111100,B11111100};
const byte PlayerLegs00[] PROGMEM = {8,1,B01001000};
const byte PlayerLegs01[] PROGMEM = {8,1,B00110000};
const byte PlayerLegs02[] PROGMEM = {8,1,B00001000};
const byte PlayerLegs03[] PROGMEM = {8,1,B01000000};
const byte* PlayerLegsH[] ={PlayerLegs00,PlayerLegs01,PlayerLegs01};
const byte* PlayerLegsV[] ={PlayerLegs00,PlayerLegs02,PlayerLegs03};



//#####################################################
//#####################################################
void output_player(){
  if(gamestatus!=2 && gamestatus!=3 && gamestatus!=5 && gamestatus!=6){
    gb.display.setColor(WHITE);
    gb.display.drawBitmap(player.x,player.y,PlayerMask);
    gb.display.setColor(BLACK);
    gb.display.drawBitmap(player.x,player.y,PlayerSprite);
    switch(player.dir){
      case 0:
      gb.display.drawPixel(player.x+2,player.y+2);
      gb.display.drawPixel(player.x+4,player.y+2);
      gb.display.drawPixel(player.x+6,player.y+1);
      if(gb.buttons.repeat(BTN_RIGHT,1)){
        gb.display.drawBitmap(player.x,player.y+7,PlayerLegsH[anim/2]);
      }else{
        gb.display.drawBitmap(player.x,player.y+7,PlayerLegsH[0]);
      }
      break;
      
      case 1:
      gb.display.drawPixel(player.x+1,player.y+2);
      gb.display.drawPixel(player.x+3,player.y+2);
      gb.display.drawPixel(player.x-1,player.y+1);
      if(gb.buttons.repeat(BTN_LEFT,1)){
        gb.display.drawBitmap(player.x,player.y+7,PlayerLegsH[anim/2]);
      }else{
        gb.display.drawBitmap(player.x,player.y+7,PlayerLegsH[0]);
      }
      break;
      
      case 2:
      gb.display.drawPixel(player.x+1,player.y+2);
      gb.display.drawPixel(player.x+4,player.y+2); 
      if(gb.buttons.repeat(BTN_DOWN,1)){
        gb.display.drawBitmap(player.x,player.y+7,PlayerLegsV[anim/2]);
      }else{
        gb.display.drawBitmap(player.x,player.y+7,PlayerLegsV[0]);
      }
      break;
  
      case 3:
      if(gb.buttons.repeat(BTN_UP,1)){
        gb.display.drawBitmap(player.x,player.y+7,PlayerLegsV[anim/2]);
      }else{
        gb.display.drawBitmap(player.x,player.y+7,PlayerLegsV[0]);
      }
      break;
    }
  }
}

//#####################################################
//#####################################################
void fctnt_movePlayer(){  
  switch(gamestatus){
    case 0:
      if(gb.buttons.repeat(BTN_B,1)){player.speeed = 2;}
      else{player.speeed = 1;}
      
      if(gb.buttons.repeat(BTN_RIGHT,1)){
        player.dir=0;
        if(player.x<=78){
          move_right();
        }else{
          if((map_current/3)==((map_current+1)/3)){
            map_current++;
            dir=0;
            vert_current=0;
            vert_previous=0;
            horiz_current=84;
            horiz_previous=0;
            gamestatus=1;
          } 
        }
      }

      if(gb.buttons.repeat(BTN_LEFT,1)){
        player.dir=1;
        if(player.x>0){
          move_left();
        }else{
          if((map_current/3)==((map_current-1)/3) && (map_current-1>=0)){
            map_current--;
            dir=1;
            vert_current=0;
            vert_previous=0;
            horiz_current=-84;
            horiz_previous=0;
            gamestatus=1;
          }
        }
      }
      
      if(gb.buttons.repeat(BTN_UP,1)){
        player.dir=3;      
        if(player.y>0){
          move_up();
        }else{
          if((map_current-3)>=0){
            map_current=map_current-3;
            dir=3;
            vert_current=-48;
            vert_previous=0;
            horiz_current=0;
            horiz_previous=0;
            gamestatus=1;
          }
        }
      }

    if(gb.buttons.repeat(BTN_DOWN,1)){
      player.dir=2;      
      if(player.y<42){
        move_down();
      }else{
        if((map_current+3)<9){
          map_current=map_current+3;
          dir=2;
          vert_current=48;
          vert_previous=0;
          horiz_current=0;
          horiz_previous=0;
          gamestatus=1;
        }
      }
    }
    break;

    case 1:
      switch(dir){
        case 0: 
        if(player.x-slidespeed>0){player.x = player.x-slidespeed;}
        else{player.x=0;gamestatus=0;map_previous=map_current;}
        break;
        case 1: 
        if(player.x+slidespeed<78){player.x = player.x+slidespeed;}
        else{player.x=78;gamestatus=0;map_previous=map_current;}
        break;
        case 2: 
        if(player.y-slidespeed>0){player.y = player.y-slidespeed;}
        else{player.y=0;gamestatus=0;map_previous=map_current;}
        break;
        case 3: 
        if(player.y+slidespeed<42){player.y = player.y+slidespeed;}
        else{player.y=42;gamestatus=0;map_previous=map_current;}
        break;
      }
    break;

    case 4:
      player.speeed = 1;
      if(gb.buttons.repeat(BTN_RIGHT,1)){player.dir=0;move_right();}
      if(gb.buttons.repeat(BTN_LEFT,1)){player.dir=1;move_left();}
      if(gb.buttons.repeat(BTN_UP,1)){player.dir=3;move_up();}
      if(gb.buttons.repeat(BTN_DOWN,1)){player.dir=2;move_down();}
    break;
  }
}


//#####################################################
//#####################################################
void fctnt_checkIn(){
  switch(gamestatus){
    case 0:
    for(i=0;i<2;i++){
      if(mapSpecial[i].sprite==map_current){
         if(player.x > mapSpecial[i].x && player.x < mapSpecial[i].x+5 && player.y < mapSpecial[i].y && player.y > mapSpecial[i].y-2){
          gamestatus = 2;
          animTransition=0;
          house_current = mapSpecial[i].typ;
          map_previous = i;
         }
      }
    }
    break;
  }
}

//#####################################################
//#####################################################
void fctnt_checkOut(){
  switch(gamestatus){
    case 4:
    if(player.y>42){
      animTransition=0;
      player.x = mapSpecial[map_previous].x;
      player.y = mapSpecial[map_previous].y;
      player.dir = 2;
      gamestatus = 5;
      map_previous = map_current;
    }
    break;
  }
}

//#####################################################
//#####################################################
void move_right(){
  check01=0;
  for(i=player.y+5;i<player.y+7;i++){
    if(gb.display.getPixel(player.x+4+player.speeed,i)){check01=1;}
  }
  if(check01==0){player.x=player.x+player.speeed;}
}

//#####################################################
//#####################################################
void move_left(){
  check01=0;
  for(i=player.y+5;i<player.y+7;i++){
    if(gb.display.getPixel(player.x+1-player.speeed,i)){check01=1;}
  }
  if(check01==0){player.x=player.x-player.speeed;}
}

//#####################################################
//#####################################################
void move_up(){
  check01=0;
  for(i=player.x+1;i<player.x+5;i++){
    if(gb.display.getPixel(i,player.y+4)){check01=1;}
  }
  if(check01==0){player.y=player.y-player.speeed;}
}

//#####################################################
//#####################################################
void move_down(){
  check01=0;
  for(i=player.x+1;i<player.x+5;i++){
    if(gb.display.getPixel(i,player.y+8)){check01=1;}
  }
  if(check01==0){player.y=player.y+player.speeed;}
}

