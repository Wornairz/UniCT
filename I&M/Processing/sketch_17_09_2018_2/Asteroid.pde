class Asteroid{
  float posX, posY;
  int H;
  
  Asteroid(float posX, float posY, int H){
    this.posX = posX;
    this.posY = posY;
    this.H = H;
  }
  
  void sposta(BlackHole b){
    //float distanza = sqrt(pow(posX-b.posX, 2)+pow(posY-b.posY, 2));
    float distanza = dist(posX, posY, b.posX, b.posY);
    posX -= (posX-b.posX)/distanza*3;
    posY -= (posY-b.posY)/distanza*3;
  }
  
  void disegna(){
    noStroke();
    fill(140, 60, 20);
    ellipse(posX, posY, H, H);
  }
}
