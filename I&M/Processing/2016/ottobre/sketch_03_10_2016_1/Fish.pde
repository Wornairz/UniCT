class Fish{
  float posX, posY;
  float vx, vy;
  color c;
  ArrayList<Bubble> bolle;
  
  Fish(float posX, float posY, float vx, float vy, color c){
    this.posX = posX;
    this.posY = posY;
    this.vx = vx;
    this.vy = vy;
    this.c = c;
    bolle = new ArrayList();
  }
  
  void sposta(){
    posX += vx;
    posY += vy;
    for(Bubble bolla : bolle){
      bolla.sposta();
    }
  }
  
  void generaBubble(){
    int d = round(random(10, 30));
    bolle.add(new Bubble(posX+60, posY, d, d/10));
  }
  
  void disegna(){
    noStroke();
    fill(c);
    ellipse(posX, posY, 80, 50);
    triangle(posX-80, posY-25, posX-80, posY+25, posX-40, posY);
    fill(0);
    ellipse(posX+30, posY, 5, 5);
    for(Bubble bolla : bolle){
      bolla.disegna();
    }
  }
}
