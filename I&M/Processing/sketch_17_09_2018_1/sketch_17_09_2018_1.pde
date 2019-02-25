PImage Im;
int N;

void setup(){
  size(512, 512);
  Im = loadImage("immagine.jpg");
  Im.resize(512, 512);
  N = 101;
}

void draw(){
  image(Im, 0, 0);
  stroke(0);
  noFill();
  rect(mouseX-N/2, mouseY-N/2, N, N);
  if(mousePressed && mouseButton == LEFT){
    Im = applyArea(Im, mouseX, mouseY, N, false);
  }
  if(mousePressed && mouseButton == RIGHT){
    Im = applyArea(Im, mouseX, mouseY, N, true);
  }
}

PImage lemonFilter(PImage I){
  PImage R = I.copy();
  I.loadPixels();
  for(int i=0; i<I.pixels.length; i++){
    float rosso = red(I.pixels[i]);
    float verde = green(I.pixels[i]);
    float blu = blue(I.pixels[i]);
    R.pixels[i] = color(rosso-(blu/8), verde+blu, 0);
  }
  R.updatePixels();
  return R;
}

PImage orangeFilter(PImage I){
  PImage R = I.copy();
  I.loadPixels();
  for(int i=0; i<I.pixels.length; i++){
    float rosso = red(I.pixels[i]);
    float verde = green(I.pixels[i]);
    float blu = blue(I.pixels[i]);
    R.pixels[i] = color(rosso+blu, verde, 0);
  }
  R.updatePixels();
  return R;
}


PImage applyArea(PImage I, float posX, float posY, int d, boolean f){
  PImage R = I.copy();
  if(f)
    R.set(round(posX-d/2), round(posY-d/2), lemonFilter(R.get(round(posX-d/2), round(posY-d/2), d, d)));
  else
    R.set(round(posX-d/2), round(posY-d/2), orangeFilter(R.get(round(posX-d/2), round(posY-d/2), d, d)));
  return R;
}

void keyPressed(){
  if(key == '+' && N<151)
    N+=2;
  if(key == '-' && N>51)
    N-=2;
  if(key == 'r' || key == 'R')
    setup();
  
}
