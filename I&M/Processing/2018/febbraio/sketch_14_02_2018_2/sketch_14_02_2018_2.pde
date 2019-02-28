float alfa;
PImage img, rImg;
void setup(){
  size(758, 256);
  alfa = 0.5;
  img = loadImage("immagine.jpg");
  img.resize(256, 256);
  rImg = randomIm(256,256);
}

void draw(){
  image(rImg , 0, 0);
  image(img, 256, 0);
  image(combine(img, rImg, alfa), 512, 0);
}

PImage randomIm(int N, int M){
  PImage R = createImage(N, M, RGB);
  int max = (int) 'a' + 'c';
  R.loadPixels();
  for(int i = 0; i<R.pixels.length; i++){
    R.pixels[i] = color(round(random(max)), round(random(max)), round(random(max)));
  }
  R.updatePixels();
  return R;
}

PImage combine(PImage I1, PImage I2, float a){
  PImage R = createImage(I1.width, I2.height, RGB);
  R.loadPixels();
  for(int i=0; i<I1.pixels.length; i++){
    R.pixels[i] = color(round(red(I1.pixels[i])*a) + round(red(I2.pixels[i])*(1-a)) , round(green(I1.pixels[i])*a) + round(green(I2.pixels[i])*(1-a)) , round(blue(I1.pixels[i])*a) + round(blue(I2.pixels[i])*(1-a)) );
  }
  R.updatePixels();
  return R;
}

void keyPressed(){
  if(key == '+' && alfa < 1.0){
    alfa+=0.1;
  }
  if(key == '-' && alfa > 0.0){
    alfa-=0.1;
  }
}
