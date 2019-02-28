PImage I;
int soglia;
boolean flag;

void setup(){
  size(512, 512);
  I = loadImage("immagine.jpg");
  I.filter(GRAY);
  I.resize(512, 512);
  image(I, 0, 0);
  soglia = 128;
  flag = false;
}

void draw(){
}

void keyPressed(){
  if(key == 't' || key == 'T'){
    PImage R = applicaSoglia(I, soglia);
    flag = true;
    image(R, 0, 0);
  }
  
  if((key == 'r' || key == 'R') && flag){
    soglia -= 1;
    PImage R = applicaSoglia(I, soglia);
    image(R, 0, 0);
  }
  
  if((key == 'y' || key == 'Y') && flag){
    soglia += 1;
    PImage R = applicaSoglia(I, soglia);
    image(R, 0, 0);
  }
}

PImage applicaSoglia(PImage Img, int soglia){
  PImage R = Img.copy();
  R.loadPixels();
  for(int i=0; i<R.pixels.length; i++){
    if(green(R.pixels[i])<soglia)
      R.pixels[i] = color(0);
  }
  R.updatePixels();
  return R;
}
