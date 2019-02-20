PImage Im, ImGam, ImDiff;
float gam ;

void setup(){
  background(0);
  size(768, 300);
  gam = 1;
  Im = loadImage("immagine.jpg");
  Im.resize(256, 256);
  Im.filter(GRAY);
  ImGam = gamma(Im, gam);
  ImDiff = difference(Im, ImGam);
  immagini();
  testo();
}

void draw(){
}

PImage gamma(PImage I, float k){
  PImage R = createImage(I.width, I.height, GRAY);
  R.loadPixels();
  I.loadPixels();
  float c = 255.0/pow(255,k);
  for(int i=0; i<I.pixels.length; i++){
    float in = red(I.pixels[i]);
    float out = c * pow(in, k);
    R.pixels[i] = color(out);
  }
  R.updatePixels();
  return R;
}

PImage difference(PImage I1, PImage I2){
  PImage O = createImage(I1.width, I2.height, GRAY);
  I1.loadPixels();
  I2.loadPixels();
  O.loadPixels();
  for(int i=0; i<O.pixels.length; i++){
    O.pixels[i] = color(abs(red(I1.pixels[i])-red(I2.pixels[i])));
  }
  O.updatePixels();
  return O;
  
}

void testo(){
  fill(255);
  textSize(30);
  text("Originale", 35, 290);
  text("Gamma: " + (nfs(gam,1,2)), 256+35, 290);
  text("Differenza", 512+35, 290);
}

void immagini(){
  image(Im, 0, 0);
  image(ImGam, 256, 0);
  image(ImDiff, 512, 0);
}


void keyPressed(){
  background(0);
  if(key == '+' && gam <10){
    gam += 0.1;
    ImGam = gamma(Im, gam);
    ImDiff = difference(Im, ImGam);
  }
  if(key == '-' && gam >0.09){
    gam -= 0.1;
    ImGam = gamma(Im, gam);
    ImDiff = difference(Im, ImGam);
  }
  immagini();
  testo();
}
