PImage Im, ImH, ImHN;
int h, k, n;

void setup(){
  size(768, 256);
  Im = loadImage("immagine.jpg");
  Im.resize(256, 256);
  Im.filter(GRAY);
  h = round(random(1, 256));
  k = round(random(1, 256));
  n = round(random(3, 11));
  ImH = hash(Im, h, k);
  h = round(random(1, 256));
  k = round(random(1, 256));
  n = round(random(3, 11));
  ImHN = hash(Im, h, k, n);
}

void draw(){
  image(Im, 0, 0);
  image(ImH, 256, 0);
  image(ImHN, 512, 0);
}


PImage hash(PImage I, int h, int k, int n){
  PImage R = I.copy();
  
  for(int i=0; i<R.width; i++){
    for(int j=0; j<R.height; j++){
      PImage tmp = I.get(i, j, n, n);
      float[] array = new float[n*n];
      tmp.loadPixels();
      for(int g=0; g<n*n; g++){
        array[g] = red(tmp.pixels[g]);
      }
      array = sort(array);
      //println(array[n*n-1]);
      R.set(i, j, color(array[n*n-1]));
    }
  }
  
  return hash(R, h, k);
}



PImage hash(PImage I, int h, int k){
  PImage R = I.copy();
  for(int i=0; i<R.width; i++){
    R.set(i, k, color(0));
    R.set(i, h, color(0));
    R.set(k, i, color(0));
    R.set(h, i, color(0));
  }
  return R;
}

void keyPressed(){
  if(key == 'r' || key == 'R')
    setup();
}
