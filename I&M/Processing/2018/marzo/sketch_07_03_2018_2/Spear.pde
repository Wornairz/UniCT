class Spear{
  float posX, posY;
  float vY;
  
  Spear(float posX, float posY, float vY){
    this.posX = posX;
    this.posY = posY;
    this.vY = vY;
  }
  
  void sposta(){
    posY += vY;
  }
  
  void disegna(){
    noStroke();
    fill(50, 150, 250);
    triangle(posX, posY, posX+20, posY, posX+10, posY+40);
  }
}
