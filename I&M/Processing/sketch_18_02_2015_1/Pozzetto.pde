class Pozzetto{
  int posX;
  int posY;
  
  Pozzetto(int posX, int posY){
    this.posX = posX;
    this.posY = posY;
  }
  
  
  void disegna(){
    fill(0, 255, 255);
    ellipse(posX, posY, 10, 10);
  }
  
}
