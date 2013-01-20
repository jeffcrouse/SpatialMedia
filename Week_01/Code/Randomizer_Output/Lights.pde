class Lights {
  private PVector points[];  // vector of "lights"
  private float   whichLight = 1;  // which lights are lighting up
  boolean         bActive    = false;
  
  Lights( int x, int y, int w, int h, int r){
    points = new PVector[37];
    
    int index=0;
    // top
    for (int i=0; i < 10; i++ ){
      PVector p = new PVector(lerp( (float) x + r*2, (float)x + r + (w-r),(float)i/10.0f), y);
      points[index] = p;
      index++;
    }
    
    // right
    for (int i=0; i < 8; i++ ){
      PVector p = new PVector(x + w, lerp( (float) y + r*2, (float) y + r + (h-r),(float)i/8.0f) );
      points[index] = p;
      index++;
    }
    
    // bottom
    for (int i=0; i < 11; i++ ){
      PVector p = new PVector(lerp( (float)x + r + (w-r), (float) x + r*2, (float)i/10.0f), y + h);
      points[index] = p;
      index++;
    }
    
    // left
    for (int i=0; i < 8; i++ ){
      PVector p = new PVector(x, lerp((float) y + r + (h-r), (float) y + r *2, (float)i/8.0f));
      points[index] = p;
      index++;
    }
  }
  
  void draw(){
    // draw lights
    for (int i=0; i<points.length; i++){
      if ( (i+1) % whichLight == 0 && bActive ){
        fill(255);
      } else {
        fill(150);
      }
      ellipse(points[i].x, points[i].y, 20, 20 );
    }
    whichLight += .5;
    if ( whichLight >= 4 ) whichLight = 1;
  }
};
