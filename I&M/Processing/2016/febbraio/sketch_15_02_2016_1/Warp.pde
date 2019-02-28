class Warp{
  float posX, posY;
  color c;
  int angolo;
  float potenza;
  ArrayList<Bullet> proiettili;
  
  Warp(float posX, float posY, int angolo, float potenza, color c){
    this.posX = posX;
    this.posY = posY;
    this.angolo = angolo;
    this.potenza = potenza;
    this.c = c;
    proiettili = new ArrayList<Bullet>();
  }
  
  void shot(){
    proiettili.add(new Bullet(posX, posY, (potenza*cos(angolo)), (potenza*sin(angolo)), c));
  }
  
  void disegna(){
    noStroke();
    fill(0);
    ellipse(posX, posY, 35, 35);
    fill(200);
    ellipse(posX, posY, 30, 30);
    fill(c);
    ellipse(posX, posY, 25, 25);
  }
  
  void collide(float mX, float mY){
    if(mX>=posX-25 && mX<=posX+25 && mY>=posY-25 && mY<=posY+25){
      
    }
  }
}
