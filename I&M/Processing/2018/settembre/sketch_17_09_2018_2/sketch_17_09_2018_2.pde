BlackHole bh;
ArrayList<Asteroid> asteroidi;

void setup(){
  size(512, 512);
  bh = new BlackHole(256, 256);
  asteroidi = new ArrayList<Asteroid>();
}

void draw(){
  background(200);
  if(round(random(100))<15){
    asteroidi.add(new Asteroid(random(512), random(512), round(random(5, 25))));
  }
  for(Asteroid asteroide : asteroidi){
    asteroide.disegna();
    asteroide.sposta(bh);
  }
  bh.collide(asteroidi);
  bh.sposta();
  bh.disegna();
}

void keyPressed(){
  if(key == 'r' || key == 'R'){
    setup();
  }
}
