class Alieno{
  int posX;
  int posY;
  boolean alive;
  boolean nirvana;
  float energia;
  Pozzetto vicino;
  
  Alieno(int posX, int posY){
    this.posX = posX;
    this.posY = posY;
    energia = random(0, 1);
    nirvana = false;
    alive = true;
  }
  
  void setPozzetto(Pozzetto p){
    vicino = p;
  }
  
  void kill(){
    alive = false;
  }
  
  void sposta(){
    if(vicino.posX < posX){
      posX-=1;
    }
    else if(vicino.posY < posY){
      posY-=1;
    }
    else if(vicino.posX > posX){
      posX+=1;
    }
    else if(vicino.posY > posY){
      posY+=1;
    }
  }
  
  void collide(){
    if(posX >= vicino.posX-10 && posX <= vicino.posX+10 && posY >= vicino.posY-10 && posY <= vicino.posY+10 ){
      nirvana = true;
    }
  }
  
  void scalaEnergia(){
    energia-=0.1;
    if(energia <= 0)
      kill();
  }
  
  void disegna(){
    if(!nirvana){
      if(alive){
        fill(0, 100, 0);
        rect(posX, posY, 10, 10);
      }
      else{
        fill(0, 0, 0);
        rect(posX, posY, 10, 10);
      }
    }
  }
}
