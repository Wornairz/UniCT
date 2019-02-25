class Bullet{
  float posX, posY;
  float sx, sy;
  color c;
  
  Bullet(float posX, float posY, float sx, float sy, color c){
    this.posX = posX;
    this.posY = posY;
    this.sx = sx;
    this.sy = sy;
    this.c = c;
  }
  
  void sposta(){
    posX+=sx;
    posY+=sy;
  }
  
  void disegna(){
    noStroke();
    fill(c);
    ellipse(posX, posY, 10, 10);
  }
  
}
