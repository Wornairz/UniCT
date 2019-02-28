Baloon b;
double energy;
ArrayList<Spear> ss;

void setup() {
  size(512, 512);
  b = new Baloon(250, 500-25);
  energy = 0;
  ss = new ArrayList<Spear>();
  frameRate(60);
}

void draw() {
  background(0, 255, 255);
  noStroke();
  fill(255);
  rect(0, 500, 512, 12);

  if (keyPressed)
  {
    if (((key=='a')||(key=='A'))&&(energy>-3))
      energy-=0.2;
    if (((key=='d')||(key=='D'))&&(energy<3))
      energy+=0.2;
  } else {
    if (energy>0 && energy-0.05>=-3)
      energy -= 0.05;
    else if (energy<0 && energy+0.05<=3)
      energy += 0.05;
  }
  for (Spear s : ss) {
    s.sposta();
    s.disegna();
    if (b.collide(s))
      noLoop();
  }
  b.sposta(energy);
  if (b.posX+25>=512 || b.posX-25<=0)
    energy = -energy;
  b.disegna();
  if (round(random(100))<10)
    ss.add(new Spear(random(512), -60, random(3, 8)));
}

void keyPressed() {
  if (key == 'r' || key == 'R') {
    loop();
    setup();
  }
}
