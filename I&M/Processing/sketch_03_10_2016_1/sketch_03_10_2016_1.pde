ArrayList<Fish> pesci;

void setup() {
  size(500, 500);
  frameRate(60);
  pesci = new ArrayList<Fish>();
}

void draw() {
  background(30, 155, 255);
  for (Fish pesce : pesci) {
    pesce.sposta();
    if (round(random(100))<2) {
      pesce.generaBubble();
    }
    pesce.disegna();
  }
}

void keyPressed(){
  if(key == 'n' || key == 'N'){
    pesci.add(new Fish(-50, random(50, 450), round(random(1,4)), random(-1.5, 1.5), color(random(255), random(255), random(255))));
  }
}
