PImage Im, ImSP, ImMed;

void setup(){
  size(768, 256);
  Im = loadImage("immagine.jpg");
  Im.resize(256, 256);
  ImSP = saltPepper(Im, 10);
  ImMed = mediano(ImSP, 5);
}

void draw(){
  image(Im, 0, 0);
  image(ImSP, 256, 0);;
  image(ImMed, 512, 0);
}


PImage saltPepper(PImage I, int k){
  PImage R = I.copy();
  I.loadPixels();
  for(int i=0; i<I.pixels.length; i++){
    float tmp = random(100);
    if(tmp < k){
      if(tmp<k/2)
        R.pixels[i] = color(255);
      else if(tmp>=k/2)
        R.pixels[i] = color(0);
    }
  }
  R.updatePixels();
  return R;
}


PImage mediano(PImage I, int n){
  PImage R = I.copy();
  
  float[] rossi, verdi, blu;
  rossi = verdi = blu = new float[n*n];
  
  for(int i=0; i<I.width; i++){
    for(int j=0; j<I.height; j++){
      
      PImage tmp = I.get(i-n/2, j-n/2, n, n);
      tmp.loadPixels();
      
      
      for(int k=0; k<tmp.pixels.length; k++){
        rossi[k] = red(tmp.pixels[k]);
        verdi[k] = green(tmp.pixels[k]);
        blu[k] = blue(tmp.pixels[k]);
      }
      rossi = sort(rossi);
      verdi = sort(verdi);
      blu = sort(blu);
      
      float medRed = rossi[n*n/2];
      float medGreen = verdi[n*n/2];
      float medBlue = blu[n*n/2];
      
      R.set(i, j, color(medRed, medGreen, medBlue));
    }
  }
  return R;
}


/*PImage mediano(PImage I, int n){
  PImage R = I.copy();
  float medRed, medGreen, medBlue;
  float[] rossi, verdi, blu;
  rossi = verdi = blu = new float[n*n];
  R.loadPixels();
  for(int i=0; i<R.pixels.length; i+=n*n){
    for(int j=i; j<i+n*n; j++){
      rossi[j-i] = red(R.pixels[j]);
      verdi[j-i] = green(R.pixels[j]);
      blu  [j-i] = blue(R.pixels[j]);
    }
    
    rossi = sort(rossi);
    verdi = sort(verdi);
    blu   = sort(blu);
    
    medRed = rossi[floor(n/2)];
    medGreen = verdi[floor(n/2)];
    medBlue = blu[floor(n/2)];
    
    for(int j=i; j<i+n*n; j++){
      R.pixels[i] = color(medRed, medGreen, medBlue);
    }
  }
  R.updatePixels();
  return R;
}*/
