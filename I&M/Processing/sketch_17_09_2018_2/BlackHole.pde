class BlackHole{
  float posX, posY;
  int D;
  
  BlackHole(float posX, float posY){
    this.posX = posX;
    this.posY = posY;
    D = 50;
  }
  
  void sposta(){
    posX = mouseX;
    posY = mouseY;
  }
  
  void collide(ArrayList<Asteroid> asteroidi){
    ArrayList<Asteroid> daRimuovere = new ArrayList<Asteroid>();
    for(Asteroid asteroide : asteroidi){
      float distanza = dist(posX, posY, asteroide.posX, asteroide.posY);
      if(distanza<(D/2+asteroide.H/2)){
        daRimuovere.add(asteroide);
        D++;
      }
    }
    asteroidi.removeAll(daRimuovere);
  }
  
  void disegna(){
    noStroke();
    fill(0);
    ellipse(posX, posY, D, D);
  }
}
