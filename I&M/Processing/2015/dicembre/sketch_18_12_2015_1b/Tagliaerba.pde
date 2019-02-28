class Tagliaerba{
  int vel;
  
  Tagliaerba(){
    vel = 5;
  }
  
  void disegnaScia(int pmX, int pmY, int n){
    noStroke();
    pushMatrix();
    translate(pmX+15, pmY+15);
    rotate(radians(vel%360));
    fill(200, 128, 0);
    rect(-15, -15, 30, 30);
    popMatrix();
  }
  
  void disegna(int mX, int mY, int n){
    noStroke();
    vel+=n;
    pushMatrix();
    translate(mX+15, mY+15);
    rotate(radians(vel%360));
    fill(88, 88, 88);
    rect(-15, -15, 30, 30);
    fill(0, 0, 0);
    ellipse(0, 0, 10, 10);
    popMatrix();
  }
}
