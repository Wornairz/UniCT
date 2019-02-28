final int N = 400;
final int k = 100;
final int h = 30;
Alieno[] alieni = new Alieno[k];
Pozzetto[] pozzetti = new Pozzetto[h];

void settings(){
  size(N, N);
}

void setup(){
  for(int i=0; i<h; i++){
    pozzetti[i] = new Pozzetto(round(random(N)), round(random(N)));
  }
  for(int i=0; i<k; i++){
    alieni[i] = new Alieno(round(random(N)), round(random(N)));
    float mindist = N*N;
    int indicemin = 0;
    for(int j=0; j<h; j++){
      float testmin = sqrt(pow(pozzetti[j].posX - alieni[i].posX , 2) + pow(pozzetti[j].posY - alieni[i].posY , 2));
      if(testmin<mindist){
        mindist = testmin;
        indicemin = j;
      }
    }
    alieni[i].setPozzetto(pozzetti[indicemin]);
  }
}

void draw(){
  background(200);
  int contamorti = 0;
  for(int i=0; i<k; i++){
    if(alieni[i].nirvana || !alieni[i].alive)
      contamorti++;
    alieni[i].disegna();
  }
  for(int i=0; i<h; i++){
    pozzetti[i].disegna();
  }
  if(contamorti == k){
    background(0);
    fill(255, 255, 0);
    textSize(72);
    textAlign(CENTER);
    text("GAME OVER", N/2, N/2);
    noLoop();
  }
}

void keyPressed(){
  if(key == 'n' || key == 'N'){
    for(int i=0; i<k; i++){
      if(alieni[i].alive){
        alieni[i].sposta();
        alieni[i].collide();
        alieni[i].scalaEnergia();
      }
    }
  }
}
