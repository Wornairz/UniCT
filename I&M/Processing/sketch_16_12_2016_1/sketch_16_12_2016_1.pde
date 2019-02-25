ArrayList<Planet> pianeti;

void setup(){
  size(500, 500);
  pianeti = new ArrayList<Planet>();
  frameRate(60);
}

void draw(){
  noStroke();
  fill(0, 0, 0, 40);
  rect(0, 0, 500, 500);
  
  for(Planet p : pianeti){
    p.disegna();
  }
}

void keyPressed(){
  if(key == 'n' || key == 'N'){
    pianeti.add(new Planet(round(random(50, 450)), round(random(50, 450)), round(random(15, 45)), color(255,255,random(0,255))));
  }
}
