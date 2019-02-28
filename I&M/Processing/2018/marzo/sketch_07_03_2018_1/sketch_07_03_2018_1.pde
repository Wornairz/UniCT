PImage Im;
int N, K, cont;

void setup(){
  Im = loadImage("immagine.jpg");
  Im.resize(512, 512);
  size(1024, 512);
  frameRate('c'-60);
  N = 1;
  K = 20+4;
  cont = 0;
}


void draw(){
  image(Im, 0, 0);
  image(grid(Im, (int) pow(2, N)), 512, 0);
  if(++cont == K){
    cont = 0;
    if(++N == 9)
      N = 1;
  }
}

PImage grid(PImage I, int n){
  PImage R = I.copy();
  PImage tmp;
  for(int i=0; i<n; i++){
    for(int j=0; j<n; j++){
      tmp = R.get(R.width/n*i, R.height/n*j, R.width/n, R.height/n);
      R.set(R.width/n*i, R.height/n*j, stretching(tmp));
    }
  }
  return R;
}

PImage stretching(PImage I){
  PImage R = createImage(I.width, I.height, RGB);
  I.loadPixels();
  
  float[] maxC = {0,0,0};
  float[] minC = {255, 255, 255};
  
  for(int i=0; i<I.pixels.length; i++){
    if(red(I.pixels[i])>maxC[0])
      maxC[0] = red(I.pixels[i]);
    if(green(I.pixels[i])>maxC[1])
      maxC[1] = green(I.pixels[i]);
    if(blue(I.pixels[i])>maxC[2])
      maxC[2] = blue(I.pixels[i]);
      
    if(red(I.pixels[i])<minC[0])
      minC[0] = red(I.pixels[i]);
    if(green(I.pixels[i])<minC[1])
      minC[1] = green(I.pixels[i]);
    if(blue(I.pixels[i])<minC[2])
      minC[2] = blue(I.pixels[i]);
  }
  
  R.loadPixels();
  for(int i=0; i<R.pixels.length; i++){
    float rosso = (red(I.pixels[i])-minC[0])/(maxC[0]-minC[0])*255;
    float verde = (green(I.pixels[i])-minC[1])/(maxC[1]-minC[1])*255;
    float blu   = (blue(I.pixels[i])-minC[2])/(maxC[2]-minC[2])*255;
    R.pixels[i] = color(rosso, verde, blu);
  }
  R.updatePixels();
  
  return R;
}
