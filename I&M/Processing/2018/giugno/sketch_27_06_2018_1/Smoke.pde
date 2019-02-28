class Smoke{
  float posX, posY;
  float vel;
  int d;
  color c;
  
  Smoke(float posX, float posY, float vel, int d, color c){
    this.posX = posX;
    this.posY = posY;
    this.vel = vel;
    this.d = d;
    this.c = c;
  }
  
  void sposta(){
    posY -= vel;
  }
  
  void disegna(){
    noStroke();
    fill(c);
    ellipse(posX, posY, d, d);
  }
}
