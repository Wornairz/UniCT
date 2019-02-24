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
  return R;
}


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
  }
  stampa();
}
