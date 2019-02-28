class Torpedo{
  float posX, posY;
  float velX;
  ArrayList<Smoke> fumi; 
  
  Torpedo(float posX, float posY, float velX){
    this.posX = posX;
    this.posY = posY;
    this.velX = velX;
    fumi = new ArrayList<Smoke>();
  }
  
  void sposta(){
    posX += velX;
    for(Smoke fumo : fumi){
      fumo.sposta();
    }
  }
  
  void generaSmoke(){
    int diametrofumo = round(random(10, 30));
    fumi.add(new Smoke(posX-30, posY, diametrofumo/10, diametrofumo, color(round(random(20, 220)))));
  }
  
  void disegna(){
    noStroke();
    fill(100, 20, 20);
    rect(posX, posY, 100, 20);
    ellipse(posX+100, posY+10, 20, 20);
    for(Smoke fumo : fumi){
      fumo.disegna();
    }
  }
  
}
