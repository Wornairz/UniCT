PImage Im1, Im2;
float K;

void setup(){
  Im1 = loadImage("immagine1.jpg");
  Im2 = loadImage("immagine2.jpg");
  Im1.resize(256, 256);
  Im2.resize(256, 256);
  size(512, 512);
  K=0.5;
  stampa();
}


void stampa(){
  image(Im1, 0, 0);
  image(Im2, 0, 256);
  image(fusion(Im1, Im2, K), 256, 0);
  image(subtract(Im1, Im2, K), 256, 256);
}

void draw(){
}

PImage fusion(PImage I1, PImage I2, float k){
  PImage R = createImage(I1.width, I2.height, RGB);
  I1.loadPixels();
  I2.loadPixels();
  for(int i=0; i<I1.pixels.length; i++){
    float rosso = k*red(I1.pixels[i]) + (1-k)*red(I2.pixels[i]);
    float verde = k*green(I1.pixels[i]) + (1-k)*green(I2.pixels[i]);
    float blu = k*blue(I1.pixels[i]) + (1-k)*blue(I2.pixels[i]);
    R.pixels[i] = color(rosso, verde, blu); 
  }
  R.updatePixels();
  return R;
}


PImage subtract(PImage I1, PImage I2, float k){
  PImage R = createImage(I1.width, I2.height, RGB);
  I1.loadPixels();
  I2.loadPixels();
  for(int i=0; i<I1.pixels.length; i++){
    float rosso = red(I1.pixels[i]) - k*red(I2.pixels[i]);
    float verde = green(I1.pixels[i]) - k*green(I2.pixels[i]);
    float blu = blue(I1.pixels[i]) - k*blue(I2.pixels[i]);
    R.pixels[i] = color(rosso, verde, blu); 
  }
  R.updatePixels();
  return R;
}

void keyPressed(){
  if(key == '+' && K<1)
    K+=0.05;
  if(key == '-' && K>0)
    K-=0.05;
  stampa();
}
