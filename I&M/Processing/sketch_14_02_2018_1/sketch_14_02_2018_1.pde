ArrayList<Heart> cuori;

void setup(){
  size(512, 512);
  frameRate(60);
  cuori = new ArrayList();
}

void draw(){
<<<<<<< HEAD
  fill(10, 10, 50, 100);
  rect(0,0,512,512);
=======
  fill(0,0,40,80);
  rect(0,0,512,512);
  
>>>>>>> 099c6caeebd6889474797a24b85989b91416b5de
  if(round(random(100)) < 5 ){
    cuori.add(new Heart(random(512), round(random(-5, 5)), round(random(3, 7))));
  }
  for(Heart cuore : cuori){
    cuore.disegna();
    cuore.sposta();
  }
}

void mousePressed(){
  for(Heart cuore : cuori){
    cuore.controllaCollisione(mouseX, mouseY);
  }
}
