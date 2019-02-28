class Ball{
  float posX, posY;
  int r;
  float sY;
  
  Ball(float posX, float posY, int r){
    this.posX = posX;
    this.posY = posY;
    this.r = r;
    sY = 5;
  }
  
  void sposta(){
    posY += sY;
  }
  
  void checkLimit(int limiteInf, int limiteSup){
    if(posY <= limiteInf || posY >= limiteSup)
      sY = -sY;
  }
  
  void disegna(){
    noStroke();
    fill(255, 0, 0);
    ellipse(posX, posY, r*2, r*2);
  }
}

class HyperBall extends Ball{
  color c;
  
  HyperBall(float posX, float posY, int r){
    super(posX, posY, r);
    c = color(0, 0, 255);
  }
  
  void checkMouse(){
    if(dist(posX, posY, mouseX, mouseY)<r)
      c = color(random(255), random(255), random(255));
  }
  
  void disegna(){
    noStroke();
    fill(c);
    ellipse(posX, posY, r*2, r*2);
  }
}
