class Baloon{
  float posX, posY;
  
  Baloon(float posX, float posY){
    this.posX = posX;
    this.posY = posY;
  }
  
  void disegna(){
    noStroke();
    fill(255, 70, 50);
    ellipse(posX, posY, 50, 50);
  }
  
  void sposta(double e){
    posX += e;
  }
  
  boolean collide(Spear s){
    if(dist(posX, posY, s.posX+10, s.posY+40)<=25)
      return true;
    return false;
  }
}
