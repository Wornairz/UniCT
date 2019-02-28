class Orologio{
  int posX, posY;
  int secondi, minuti, ore;
  
  Orologio(int posX, int posY, int secondi, int minuti, int ore){
    this.posX = posX;
    this.posY = posY;
    this.secondi = secondi;
    this.minuti = minuti;
    this.ore = ore;
  }
  
  void aumentaSecondi(){
    secondi++;
    if(secondi == 60){
      secondi = 0;
      aumentaMinuti();
    }
  }
  void aumentaMinuti(){
    minuti++;
    if(minuti == 60){
      minuti = 0;
      aumentaOre();
    }
  }
  void aumentaOre(){
    ore++;
    if(ore == 12)
      ore = 0;
  }
  
  void disegna(){
    
    strokeWeight(2);
    stroke(20, 200, 20);
    ellipse(posX, posY, 120, 120);
    
    pushMatrix();
    translate(posX, posY);
    rotate(radians(-90+(secondi*6)));
    stroke(0, 0, 0);
    strokeWeight(1);
    line(0, 0, 50, 0);
    popMatrix();
    
    
    pushMatrix();
    translate(posX, posY);
    rotate(radians(-90+(minuti*6)));
    stroke(255, 0, 0);
    strokeWeight(2);
    line(0, 0, 40, 0);
    popMatrix();
    
    
    pushMatrix();
    translate(posX, posY);
    rotate(radians(-90+(ore*30)));
    stroke(0, 0, 255);
    strokeWeight(3);
    line(0, 0, 30, 0);
    popMatrix();
  }
}
