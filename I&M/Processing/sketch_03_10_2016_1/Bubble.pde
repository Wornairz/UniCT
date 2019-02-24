class Bubble{
  float posX, posY;
  int d;
  int vel;
  
  Bubble(float posX, float posY, int d, int vel){
    this.posX = posX;
    this.posY = posY;
    this.d = d;
    this.vel = vel;
  }
  
  void sposta(){
    posY -= vel;
  }
  
  void disegna(){
    noStroke();
    fill(0, 255, 255);
    ellipse(posX, posY, d, d);
    fill(255);
    ellipse(posX-d/4, posY-d/4, d/4, d/4);
  }
}
