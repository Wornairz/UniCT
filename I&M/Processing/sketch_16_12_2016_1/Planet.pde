class Planet{
  float posX, posY;
  float s;
  color c;
  float v;
  Satellite sat;
  
  Planet(int posX, int posY, float s, color c){
    this.posX = posX;
    this.posY = posY;
    this.s = s;
    this.c = c;
    
    sat = new Satellite(posX, posY, 2*s);
  }
  
  void modificaCentro(){
    v = random(-0.5, 0.5);
    posX += v;
    posY += v;
    sat.modificaCentro(posX, posY);
  }
  
  void disegna(){
    noStroke();
    fill(c);
    ellipse(posX+v, posY+v, s, s);
    sat.disegna();
    modificaCentro();
  }
  
}
