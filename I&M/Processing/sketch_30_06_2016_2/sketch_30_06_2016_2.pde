PImage Im;
int R; //gregrado

void setup() {
  size(512, 300);
  Im = loadImage("immagine.jpeg");
  Im.resize(256, 256);
  R = 0;
  stampa();
}

void draw() {
}

void stampa() {
  background(0);
  image(Im, 0, 0);
  image(dropResolution(Im, R), 256, 0);
  textSize(42);
  if (R>=5)
    fill(255, 0, 0);
  else fill(255);
  text("Degrado = " + R, 130, 290);
}


PImage downScale(PImage I) {
  PImage R = createImage(I.width/2, I.height/2, RGB);
  for (int i=0; i<R.width; i++) {
    for (int j=0; j<R.height; j++) {
      R.set(i, j, I.get(i*2, j*2));
    }
  }
  return R;
}


PImage upScale(PImage I) {
  PImage R = createImage(I.width*2, I.height*2, RGB);
  for (int i=0; i<R.width; i++) {
    for (int j=0; j<R.height; j++) {
      R.set(i, j, I.get(i/2, j/2));
    }
  }
  return R;
}

PImage dropResolution(PImage I, int n) {
  PImage R = I;
  for (int i=0; i<n; i++) {
    R = downScale(R);
  }
  for (int i=0; i<n; i++) {
    R = upScale(R);
  }
  return R;
}

void keyPressed() {
  if (key == '+' && R<8) {
    R++;
  }
  if (key == '-' && R>0) {
    R--;
  }
  stampa();
}
