<<<<<<< HEAD
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
=======
PImage Im, ImUQ, ImLQ;
int N;


void setup(){
  size(768, 280);
  Im = loadImage("immagine.jpeg");
  Im.resize(256, 256);
  Im.filter(GRAY);
  N = 10;
  stampa();
}

void draw(){
}

void stampa(){
  background(0);
  image(Im, 0, 0);
  ImUQ = uniQuant(Im, N);
  ImLQ = logQuant(Im, N);
  image(ImUQ, 256, 0);
  image(ImLQ, 512, 0);
  textSize(20);
  text("Originale", 20, 275);
  text("N = " + N, 150, 275);
  text("Uniforme", 256+20, 275);
  text("Logartmica", 512+20, 275);
}


PImage uniQuant(PImage I, int k){
  PImage R = I.copy();
  I.loadPixels();
  for(int i=0; i<I.pixels.length; i++){
    float quant = floor(red(I.pixels[i])*k/256); 
    R.pixels[i] = color(int(255*quant/(k-1)));
    
  }
  R.updatePixels();
>>>>>>> df3c43726ddcefdf87a478c8f663672860332f8b
  return R;
}


<<<<<<< HEAD
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
=======
PImage logQuant(PImage I, int k){
  PImage R = I.copy();
  R.loadPixels();
  I.loadPixels();
  for(int i=0; i<I.pixels.length; i++){
    float quant = floor(log(red(I.pixels[i]))*k/log(256)); 
    R.pixels[i] = color(255*quant/(k-1));
  }
  R.updatePixels();
  return R;
}

void keyPressed(){
  if(key == '+' && N<256){
    N++;
  }
  if(key == '-' && N>2){
    N--;
>>>>>>> df3c43726ddcefdf87a478c8f663672860332f8b
  }
  stampa();
}
