class Satellite{
  float cx, cy;
  int r;
  float d;
  
  Satellite(int cx, int cy, float d){
    this.cx = cx;
    this.cy = cy;
    this.d = d;
    r = round(random(360));
  }
  
  void modificaCentro(float cx, float cy){
    this.cx = cx;
    this.cy = cy;
  }
  
  void modificaAngolo(){
    r+=5;
    r%=360;
  }
  
  void disegna(){
    noStroke();
    fill(0, 255, 255);
    pushMatrix();
    translate(cx, cy);
    rotate(radians(r));
    ellipse(d, d, 10, 10);
    popMatrix();
    modificaAngolo();
  }
}
