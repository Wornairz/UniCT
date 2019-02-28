
Robot[] robots = new Robot[12];
int counter = 0;
boolean cambio = false;

void setup(){
  size(500,500);
  background(0);
  for(int i=0; i<12; i++){
    robots[i] = new Robot();
  }
}

void draw(){
  if(counter++ >= 100)
    cambio = true;
  for(int i=0; i<12; i++){
    robots[i].posOffset(int(random(-5, 5)),int(random(-5, 5)));
    robots[i].disegna();
    if(cambio)
      robots[i].cambiaStato(int(random(3)));
  }
  if(cambio){
    cambio = false;
    counter = 0;
  }
}

void keyPressed(){
  if(key == 'r' || key == 'R'){
    background(0);
    for(int i=0; i<12; i++){
      robots[i] = new Robot();
    }
  }
}
