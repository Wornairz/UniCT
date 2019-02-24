Tagliaerba t;
int N = 5;

void setup(){
  size(500, 500);
  background(50, 160, 30);
  t = new Tagliaerba();
}

void draw(){
  t.disegnaScia(pmouseX, pmouseY, N);
  t.disegna(mouseX, mouseY, N);
}

void keyPressed(){
  if(key == '+' && N < 135){
    N++;
  }
  if(key == '-' && N > 3){
    N--;
  }
  if(key == 'r' || key == 'R'){
    setup();
  }
}
