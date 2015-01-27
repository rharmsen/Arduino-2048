
#include "GameManager.h"
#include <Arduino.h>
#include <TrueRandom.h>

GameManager::GameManager(){
  gameStarted = false;
}

void GameManager::setup() {
  gameStarted = true;
  grid.empty();
  addStartTiles();

}

void GameManager::printBoard() {
  grid.print();
  
}

void GameManager::addStartTiles() {
   addRandomTile();
   addRandomTile();
}

void GameManager::addRandomTile() {
  
  if (grid.cellsAvailable()) {
    int value = (TrueRandom.random(2)+1)*2;
    grid.setValue(grid.randomAvailableCell(),value);
  }
  grid.calculateInvidValues();
}

// Restart the game
void GameManager::restart() {
  setup();
}

// Return true if the game is lost, or has won and the user hasn't kept playing
bool GameManager::isGameTerminated() {
  return !(movesAvailable());
}


void GameManager::moveTile(Tile tile, Position cell) {
  //  cells[cell.x][cell.y]
  //  tile.updatePosition(cell);
}

void printPos(Position pos) {
  Serial.print("Pos: (");
  Serial.print(pos.x);
  Serial.print(",");
  Serial.print(pos.y);
  Serial.println(")");
}

void printTile(Tile tile) {
  Serial.print("Tile: (");
  Serial.print(tile.x);
  Serial.print(",");
  Serial.print(tile.y);
  Serial.print(") =");
  Serial.println(tile.value);
}

void GameManager::move(int dir) {
  //direction:  0: up, 1: right, 2: down, 3: left
  Vector vector(dir);
  bool moved = false;
  int traversalsx[4];
  int traversalsy[4];

  for (char i  = 0; i < GridSize; i++) {
    if (vector.x == 1) {
      traversalsx[i] = (GridSize-1)-i;
    }
    else {
      traversalsx[i] = i;
    }
    if (vector.y == 1) {
      traversalsy[i] = (GridSize-1)-i;
    }
    else {
      traversalsy[i] = i;
    }
  }

  grid.prepareTiles();

  
  for (char xa = 0; xa < GridSize; xa++) {
    for (char ya = 0; ya < GridSize; ya++) {
      char x = traversalsx[xa];
      char y = traversalsy[ya];
      Position cell(x,y);
    
      if (!grid.isEmptyCell(x,y)) {
        Tile current = grid.getTile(x,y);
        
        Position farthest(x,y);
        Position next(x,y);

        do {
          farthest.fromPosition(next);
          next.addDelta(vector.x,vector.y);
        }
        while (grid.withinBounds(next) && grid.cellAvailable(next));


        Tile nextTile = grid.getTile(next);

        if (!nextTile.isEmpty() && current.value == nextTile.value && !nextTile.isMerged()) {

          Tile merged(nextTile.x,nextTile.y);
          merged.value = current.value * 2;

          merged.setMergedFrom(current.getPosition(),nextTile.getPosition());
          grid.insertTile(merged);
          grid.removeTile(current);

          current.updatePosition(nextTile.getPosition());

          // Update score
          updateScore(merged.value);

          // TODO CHECK FOR 2048
          
          
        }
        else {
          //   Serial.println("moveTile");
          //    printTile(current);
          //     printPos(farthest);
          grid.moveTile(current,farthest);
          
          if (!((current.x == farthest.x) && (current.y == farthest.y))) {
             moved = true; 
          }
        }

        if (!positionsEqual(cell,current)) {
          moved = true;
        }

      }
    }
  }

  if (moved) {
    addRandomTile();
    
    if (!movesAvailable()) {
      Serial.println("GAMEOVER");
      gameOver = true; // Game over!
    }
  }

  printBoard();

}

void GameManager::updateScore(int value) {
  //Todo
}

bool GameManager::positionsEqual(Position pos, Tile tile) {
  return ((pos.x == tile.x) && (pos.y == tile.y));
}

bool GameManager::movesAvailable() {
    return (grid.cellsAvailable() || tileMatchesAvailable());
}

bool GameManager::tileMatchesAvailable() {
  Tile tile;
  for (char x = 0; x < GridSize; x++) {
    for (char y = 0; y < GridSize; y++) {
      tile = grid.getTile(x, y);

      if (tile.value != 0) {
        for (char direction = 0; direction < 4; direction++) {
          Vector vector(direction);
          Position pos(x,y);
          pos.addDelta(vector.x,vector.y);
          Tile other = grid.getTile(pos);

          if (other.value == tile.value) {
            return true; // These two tiles can be merged
          }
        }
      }
    }
  }

  return false;
}

void GameManager::displayBoard() {
 grid.displayBoard(); 
}




