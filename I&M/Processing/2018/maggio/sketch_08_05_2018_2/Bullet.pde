class Bullet{
  float posX, posY;
  
  Bullet(float posX, float posY){
    this.posX = posX;
    this.posY = posY;
  }
  
  void sposta(){
    posY-=10;
  }
  
  void disegna(){
    noStroke();
    fill(150, 0, 200);
    ellipse(posX, posY, 10, 10);
  }
}
