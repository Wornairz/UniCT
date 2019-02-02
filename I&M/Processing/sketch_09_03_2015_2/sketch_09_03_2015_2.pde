PImage Im;
final int N = 800;

void setup() {
  size(800, 800);
  Im = loadImage("xbox.png");
  Im.resize(800, 800);
  image(Im, 0, 0);
}

void draw() {
}

void keyPressed() {
  if (key == 'a' || key == 'A') {
    dividiImg();
    image(Im, 0, 0);
  }
}

void dividiImg() {
  NW();
  NE();
  SW();
  SE();
}

void NW() {
  for (int i=0; i<N/2; i++) {
    for (int j=0; j<N/2; j++) {
      color tmp = Im.get(i, j);
      Im.set(i, j, color(0.3*red(tmp) + 0.5*green(tmp) + 0.2*blue(tmp)));
    }
  }
}

void NE(){
  for (int i=N/2; i<N; i++) {
    for (int j=0; j<N/2; j++) {
      color tmp = Im.get(i, j);
      Im.set(i, j, color(red(tmp)));
    }
  }
}
void SW(){
  for (int i=0; i<N/2; i++) {
    for (int j=N/2; j<N; j++) {
      color tmp = Im.get(i, j);
      Im.set(i, j, color(green(tmp)));
    }
  }
}
void SE(){
  for (int i=N/2; i<N; i++) {
    for (int j=N/2; j<N; j++) {
      color tmp = Im.get(i, j);
      Im.set(i, j, color(blue(tmp)));
    }
  }
}
