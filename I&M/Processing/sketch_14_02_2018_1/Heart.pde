class Heart {
  float posX, posY;
  boolean alive;
<<<<<<< HEAD
  int sx;
  float sy;
=======
  float sx, sy;
>>>>>>> 099c6caeebd6889474797a24b85989b91416b5de
  color colore;

  Heart(float posX, int sx, int sy) {
    this.posX = posX;
    posY = 450;
    alive = true;
    this.sx = sx;
    this.sy = -sy;
    colore = color(255, 80, 80);
  }

  void sposta() {
    posX += sx;
<<<<<<< HEAD
    if (!alive) {
      sy += 0.1 + (464 % 21 / 80);
    }
=======
    if(!alive)
      sy += 0.1 + (00464 % 21) / 80;
>>>>>>> 099c6caeebd6889474797a24b85989b91416b5de
    posY += sy;
  }

  void kill() {
    alive = false;
    colore = color(160, 160, 160);
  }

  void controllaCollisione(float mx, float my) {
    if (mx>posX-30 && mx<posX+30 && my>posY-30 && my<posY+30)
      kill();
  }

  void disegna() {
    noFill();
    //rect(posX-30, posY-30, 60, 60);
    fill(colore);
    noStroke();
    ellipse(posX-11, posY-13, 30, 30);
    ellipse(posX+11, posY-13, 30, 30);
    triangle(posX-25.5, posY-8, posX+25.5, posY-8, posX, posY+30);
    /*pushMatrix();
     translate(posX, posY);
     rotate(PI);
     triangle(0, 0, +20, -30, -20, -30);
     popMatrix();*/
  }
}
