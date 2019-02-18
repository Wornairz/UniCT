Orologio orologio;
int countSec, countMin, countOre;
int fr;


void setup(){
  size(500, 500);
  orologio = new Orologio(250, 250, round(random(60)), round(random(60)), round(random(12)));
  fr = 1;
  frameRate(fr);
  countSec = countMin = countOre = 0;
}

void draw(){
  orologio.aumentaSecondi();
  orologio.disegna();
}

void keyPressed(){
  if(key == '+'){
    fr++;
    frameRate(fr);
  }
  if(key == '-' && fr > 1){
    fr--;
    frameRate(fr);
  }
}
