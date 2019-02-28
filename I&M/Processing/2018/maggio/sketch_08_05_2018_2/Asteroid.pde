class Asteroid{
  float posX, posY;
  float vX, vY;
  boolean stato;
  
  Asteroid(float posX, float posY, float vX, float vY){
    this.posX = posX;
    this.posY = posY;
    this.vX = vX;
    this.vY = vY;
    stato = true;
  }
  
  void sposta(){
    posX+=vX;
    posY+=vY;
    if(!stato)
      vY+=0.2;
    
  }
  
  void disegna(){
    stroke(255, 255, 0);
    strokeWeight(4);
    if(stato)
      fill(150, 0, 10);
    else
      fill(50);
    ellipse(posX, posY, 50, 50);
  }
  
  void collide(Bullet b){
    if(stato)
      if(dist(posX, posY, b.posX, b.posY)<=10+50)
        stato = false;
  }
}
