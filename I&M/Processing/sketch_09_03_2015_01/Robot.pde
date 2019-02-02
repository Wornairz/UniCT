class Robot{

int stato = 0;
int posX = 0;
int posY = 0;

void cambiaStato(int stato){
  this.stato = stato%3;
}
  
void posOffset(int dx, int dy){
  fill(255, 255, 255);
  rect(posX, posY, 25,25);
  posX += dx;
  posY += dy;
}

Robot(){
  stato = int(random(3));
  posX = 250;
  posY = 250;
}

void disegna(){
  
  if(stato == 0)
    fill(255,0,0);
  else if(stato == 1)
    fill(0, 255, 0);
  else
    fill(0, 0, 255);
    
  rect(posX, posY, 25,25);
}

}
