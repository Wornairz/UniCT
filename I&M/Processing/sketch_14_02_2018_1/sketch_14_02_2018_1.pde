ArrayList<Heart> cuori;

void setup(){
  size(512, 512);
  frameRate(60);
  background(10, 10, 50);
  cuori = new ArrayList();
}

void draw(){
  fill(0,0,40,80);
  rect(0,0,512,512);
  
  if(round(random(100)) < 5 ){
    cuori.add(new Heart(random(512), round(random(-5, 5)), round(random(3, 7))));
  }
  for(Heart cuore : cuori){
    cuore.disegna();
    cuore.sposta();
    cuore.controllaCollisione(mouseX, mouseY);
  }
}
