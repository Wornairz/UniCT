Gun pistol;
ArrayList<Asteroid> asteroidi;

void setup(){
  size(512, 512);
  frameRate(60);
  pistol = new Gun(250, 450);
  asteroidi = new ArrayList<Asteroid>();
}

void draw(){
  background(20, 200, 255);
  if(round(random(100))<5)
    asteroidi.add(new Asteroid(-50, random(256), random(2,7), random(-2, 2)));
  for(Asteroid a : asteroidi){
    a.disegna();
    a.sposta();
    for(Bullet b : pistol.proiettili){
      a.collide(b);
    }
  }
  pistol.disegna();
  pistol.sposta();
}

void keyPressed(){
  if(key == 'a' || key == 'A'){
    pistol.shot();
  }
}
