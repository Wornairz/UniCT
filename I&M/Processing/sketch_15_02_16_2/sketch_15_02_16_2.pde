PImage Im;

void settings(){
  Im = loadImage("immagine.jpeg");
  Im.resize(300, 256);
  size(Im.width*3, Im.height+30);
}

void setup(){
  background(0);
  image(Im, 0, 0);
  PImage ImCMY = rgb2cmy(Im);
  image(ImCMY, Im.width, 0);
  imageCMY(ImCMY, Im.width*2, 0);
  fill(255);
  textSize(28);
  text("RGB Originale", 0+25, Im.height+25);
  text("CMY in RGB", Im.width+25, Im.height+25);
  text("CMY corretta", Im.width*2+25, Im.height+25);
}

PImage rgb2cmy(PImage I){
  PImage R = I.copy();
  I.loadPixels();
  R.loadPixels();
  for(int i=0; i<I.pixels.length; i++){
    R.pixels[i] = color(255-red(I.pixels[i]), 255-green(I.pixels[i]), 255-blue(I.pixels[i]));
  }
  R.updatePixels();
  return R;
}

PImage cmy2rgb(PImage I){
  PImage R = I.copy();
  I.loadPixels();
  R.loadPixels();
  for(int i=0; i<I.pixels.length; i++){
    R.pixels[i] = color(255-red(I.pixels[i]), 255-green(I.pixels[i]), 255-blue(I.pixels[i]));
  }
  R.updatePixels();
  return R;
}

void imageCMY(PImage I, int x, int y){
  image(cmy2rgb(I), x, y);
}
