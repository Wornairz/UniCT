class Led{
  float posX, posY;
  color c;
  boolean acceso;
  
  Led(float posX, float posY, color c){
    this.posX = posX;
    this.posY = posY;
    this.c = c;
    acceso = false;
  }
  
  void accendi(){ acceso = true; }
  
  void spegni(){ acceso = false; }
  
  void disegna(){
    noStroke();
    if(acceso)
      fill(c);
    else
      fill(0);
    
    ellipse(posX, posY, 10, 10);
  }
}
