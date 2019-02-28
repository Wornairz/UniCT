LedString[] ls;
int fr;

void setup() {
  size(500, 500);
  fr = 10;
  frameRate(fr);
  ls = new LedString[5];
  for (int i=0; i<5; i++) {
    //int pos = round(random(40,400));
    ls[i] = new LedString(round(random(40, 400)), round(random(40, 400)), round(random(2, 15)), color( round(random(255)), round(random(255)), round(random(255)) ));
  }
}

void draw() {
  background(255);
  for (int i=0; i<5; i++) {
    ls[i].disegna();
  }
}

void keyPressed() {
  if (key == 'c' || key == 'C') {
    for (int i=0; i<5; i++) {
      ls[i].cambiaStato();
    }
  }
  
  if (key == '+' && fr < 50) {
    fr++;
    frameRate(fr);
  }
  if (key == '-' && fr > 1) {
    fr--;
    frameRate(fr);c
  }
}
