ArrayList<Torpedo> torpedi;


void setup(){
  size(512, 512);
  torpedi = new ArrayList<Torpedo>();
  frameRate(60);
  
}

void draw(){
  background(50, 200, 255);
  for(Torpedo torpedo : torpedi){
    torpedo.disegna();
    torpedo.sposta();
    if(round(random(1)) == 1){
      torpedo.generaSmoke();
    }
  }
}

void keyPressed(){
  if(key == 'n' || key == 'N'){
    torpedi.add(new Torpedo(-50, random(50, 450), random(5, 10)));
  }
}
