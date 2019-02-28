PImage Im;
int K, tK;
float mX, mY; 

void setup() {
  size(1024, 512);
  Im = loadImage("immagine.jpg");
  Im.resize(512, 512);
  K = (10*4)+1;
}

void draw() {
  image(Im, 0, 0);
  stroke(0, 255, 0);
  noFill();
  rect(mX-tK/2, mY-tK/2, tK, tK);
  noStroke();
  if (mouseX-K/2>=0 && mouseY-K/2>=0 && mouseX+K/2<=Im.width && mouseY+K/2<=Im.height) {
    mX = mouseX;
    mY = mouseY;
    tK = K;
    fill(regionMean(Im, mouseX, mouseY, K));
    rect(512, 0, 512, 512);
  }
}


color imMean(PImage I) {
  float mediaRosso = 0;
  float mediaVerde = 0;
  float mediaBlu   = 0;
  I.loadPixels();
  for (int i=0; i<I.pixels.length; i++) {
    mediaRosso += red(I.pixels[i]);
    mediaVerde += green(I.pixels[i]);
    mediaBlu   += blue(I.pixels[i]);
  }
  int totpixels = I.width*I.height;
  mediaRosso /= totpixels;
  mediaVerde /= totpixels;
  mediaBlu   /= totpixels;
  return color(mediaRosso, mediaVerde, mediaBlu);
}

color regionMean(PImage I, int x, int y, int n) {
  PImage regione = I.get(x-n/2, y-n/2, n, n);
  return imMean(regione);
}

void keyPressed() {
  if (key == '+' && K+10<250)
    K+=10;
  if (key == '-' && K-10>10)
    K-=10;
}
