#include <HardwareSerial.h>
#include <Arduino.h>

enum MoveDirection {
  UP, DOWN, LEFT, RIGHT
};


#define Board_Rows 4
#define Board_Cols 4
class Board {
  public:
  Board();
  void PrintBoard();
  void AddRandomTile();
  bool IsFull();
  int EmptyTiles();
  
  
  bool MoveBoard(MoveDirection dir);
  
  private:
  
  int tiles[4][4];
};


