
class Position {
    public:
    char x,y;
  
  Position() {
    x = 0;
    y = 0;
  }
  
  Position(char _x, char _y) {
    x = _x;
    y = _y;
  }  
  
  void emptyPosition() {
    x= -1;
    y= -1;
  }
  
  void fromPosition(Position pos) {
     x = pos.x;
    y = pos.y; 
  }
  
  bool isEmpty() {
     return (x == -1); 
  }
  
  void addDelta(char _x, char _y) {
     x += _x;
     y += _y; 
  }
};
