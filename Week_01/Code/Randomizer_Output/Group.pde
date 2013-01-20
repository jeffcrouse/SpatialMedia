class Group {

  String   studentOne = "";
  String   studentTwo = "";
  String   assignment = "";
  boolean  studentOneSelected = false;
  boolean  studentTwoSelected = false;
  
  private int drawX,drawY,w,h;
  
  Group( int _x, int _y, int _w, int _h ){
    drawX = _x;
    drawY = _y;
    w = _w;
    h = _h;
  }
  
  void draw(){
    int x = drawX;
    int y = drawY;
    
    fill(10,50,11);
    text( assignment, x,y);
    y += 10;
    
    if ( studentOneSelected ) fill(255);
    else fill(130,159,180);
    rect(x,y,w,h/2);
  
    fill(0);
    text(studentOne, x + 4, y+fontSize+ 2);
    
    y += h/2;
    
    if ( studentTwoSelected ) fill(255);
    else fill(45,86,117);
    rect(x,y,w,h/2);
    
    fill(0);
    text(studentTwo, x+ 4, y+fontSize+ 2);
  };

};
