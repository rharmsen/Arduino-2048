#include "Board.h"


Board::Board() {
  // Add 2 random tiles
  AddRandomTile();
  AddRandomTile();
}

void Board::PrintBoard() {
  Serial.println("Board");

  for (int row = 0; row < Board_Rows; row++) {
    //Serial.print(row);

    for (int column = 0; column < Board_Cols; column++) {

      Serial.print(tiles[row][column]);
      Serial.print("\t");
    }
    Serial.println("");
  }
}

bool Board::IsFull() {
  return (EmptyTiles() == 0);
}

/**
 * Adds a random 2 or 4 tile to the board
 */
void Board::AddRandomTile() {
  int emptyTiles = EmptyTiles();

  int getal = (random(2)+1)*2;

  // Pick a tile from the list of empty tiles
  int emptyTile = random(emptyTiles);
  Serial.print("New tile: ");
  Serial.print(getal);

  Serial.print(" Nummer: ");
  Serial.println(emptyTile);

  // Find that random tile and fill it with the new number
  for (int row = 0; row < Board_Rows; row++) {
    for (int column = 0; column < Board_Cols; column++) {

      if (tiles[row][column]==0) {
        if (emptyTile == 0) {
          Serial.print(row);
          Serial.print(",");
          Serial.print(column);
          Serial.println("");
          tiles[row][column] = getal;
        }
        emptyTile--;
      }

    }
  }
}

/**
 * Return the amount of empty tiles on the board
 */
int Board::EmptyTiles() {
  int count = 0;
  for (int row = 0; row < Board_Rows; row++) {
    for (int column = 0; column < Board_Cols; column++) {
      // Look for zero to check if the board is full
      if (tiles[row][column]==0) {
        count++;
      }
    }
  }
  return count;
}



