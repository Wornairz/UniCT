class LedString {
  float posX, posY;
  int n;
  color c;
  int stato;
  Led[] array;
  int last;

  LedString(float posX, float posY, int n, color c) {
    this.posX = posX;
    this.posY = posY;
    this.n = n;
    this.c = c;
    stato = 0;
    array = new Led[n];
    for (int i=0; i<n; i++) {
      array[i] = new Led(posX + i*15, posY, c);
    }
  }

  void controllaStato() {
    if (stato == 0) {
      for (int i=0; i<n; i++) {
        array[i].spegni();
      }
    } else if (stato == 1) {
      for (int i=0; i<n; i++) {
        array[i].accendi();
      }
    } else if (stato == 2) {
      for (int i=0; i<n; i++) {
        array[i].spegni();
      }
      last = (last+1)%n;
      array[last].accendi();
    }
  }

  void cambiaStato(){
    stato = (stato + 1)%3;
  }

  void disegna() {
    stroke(0);
    line(posX, posY, posX+(n-1)*15, posY);
    controllaStato();
    for (int i=0; i<n; i++) {
      array[i].disegna();
    }
  }
}
