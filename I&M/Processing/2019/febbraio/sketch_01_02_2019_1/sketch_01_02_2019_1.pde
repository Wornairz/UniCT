Ball b;
HyperBall hb;

void setup(){
  size(512, 256);
  b = new Ball(random(256), random(256), 40);
  hb = new HyperBall(random(256, 512), random(256), 40);
}

void draw(){
  background(255);
  b.disegna();
  hb.disegna();
  b.sposta();
  hb.sposta();
  b.checkLimit(0, 256);
  hb.checkLimit(0, 256);
  hb.checkMouse();
}

void keyPressed(){
  if(key == 'r' || key == 'R')
    setup();
}
