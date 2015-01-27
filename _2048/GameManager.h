#include "Position.h"
#include "Tile.h"
#include "Vector.h"
#include "Grid.h"


class GameManager {
public:
  GameManager();
  void restart();
  void keepPlaying();
  bool isGameTerminated();
  void setup();

  void addStartTiles();
  void addRandomTile();
  void actuate();
  void moveTile(Tile tile, Position cell);
  void move(int direction);
  void getVector(int direction);
  //int* buildTraversals(Vector vector);
  void findFarthestPosition(Position cell, Vector vector);

  bool movesAvailable();
  bool tileMatchesAvailable();

  bool positionsEqual(Position pos, Tile second);
  bool gameStarted;
  bool gameOver;
  void updateScore(int value);
  
  
  // Debugging:
  void printBoard();
  void displayBoard(); 
  Grid grid;
private:
  

};





