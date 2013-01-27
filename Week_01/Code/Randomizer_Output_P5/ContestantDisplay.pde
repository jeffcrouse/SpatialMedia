class ContestantDisplay {
  
  color   fillColor = color(255,255,255);
  float   alpha     = 0;
  String  current = "";
  PFont   font, smallFont;
  PVector dims;
  PVector pos;
  
  private boolean bActive = false;
  
  ContestantDisplay( String _font, int fontSize ){
    smallFont = createFont( _font, fontSize );
    font      = createFont( _font, 80 );
    dims = new PVector(width * 3/4, 160);
    pos  = new PVector( width/2, height/2);
  };
  
  void draw(){
    if ( bActive ){
      alpha += 10;
      if ( alpha > 255 ){
        alpha = 255;
      }
    } else {
      alpha *= .75;
      if ( alpha < 0 ) alpha = 0;
    }
    rectMode(CENTER);
    fill(0, alpha * .5);
    rect(pos.x, pos.y, width, height);
    fill(fillColor, alpha);
    rect(pos.x, pos.y, dims.x, dims.y);
    rectMode(CORNER);
    fill(0, alpha);
    textFont(smallFont);
    float fontY = (pos.y - dims.y/2) + 10 + smallFont.getSize();
    text("Next Up:", pos.x - dims.x/2 + 10, fontY );
    fontY += font.getSize();
    textFont(font);
    text(current, pos.x - dims.x/2 + 10, fontY );
    fill(255);
  };
  
  void activate( String _current ){
    bActive = true;
    current = _current;
  }
  
  void deactivate(){
    bActive = false;
  }

};
