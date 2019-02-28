class Gun{
  float posX, posY;
  ArrayList<Bullet> proiettili;
  
  Gun(float posX, float posY){
    this.posX = posX;
    this.posY = posY;
    proiettili = new ArrayList<Bullet>();
  }
  
  void sposta(){
    posX = mouseX;
    for(Bullet b : proiettili){
      b.sposta();
    }
  }
  
  void shot(){
    proiettili.add(new Bullet(posX, posY-40));
  }
  
  void disegna(){
    noStroke();
    fill(20);
    rectMode(CENTER);
    rect(posX, posY, 20, 70);
    for(Bullet b : proiettili){
      b.disegna();
    }
  }
}
