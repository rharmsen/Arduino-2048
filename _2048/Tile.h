//#include "Position.h"

class Tile {
public:
  char x,y;
  int value;
  
  Position previousPosition;
  Position mergedFrom[2];
 
  
  Tile(char _x, char _y) {
     x = _x;
     y = _y; 
     value = 0;
  }
  
  Tile( char _x, char _y, char _value) {
     x = _x;
     y = _y;
     value = _value; 
  }
   
  Tile() {
    
  }
  
  void fromPosition(Position pos) {
     x = pos.x;
    y = pos.y; 
  }
  
  void setMergedFrom(Position posa, Position posb) {
    mergedFrom[0] = posa;
    mergedFrom[1] = posb;
  }
  
  Position getPosition() {
    Position pos(x,y);
    return pos;
  }
  
  void savePosition() {
    previousPosition = Position(x,y);
  }
  
  void resetMerged() {
    mergedFrom[0].emptyPosition();
    mergedFrom[1].emptyPosition();
  }
  
  bool isMerged() {
    return (!mergedFrom[0].isEmpty()); 
  }

  void updatePosition(Position position) {
    x = position.x;
    y = position.y;
  }
  
  bool isEmpty() {
    return (value == 0);
  }
};


