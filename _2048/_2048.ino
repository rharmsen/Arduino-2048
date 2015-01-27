#include <Button.h>
#include "GameManager.h"
#include <TrueRandom.h>
GameManager gameManager;


void setup()
{
  // Setup the game
  gameManager.setup();
  //gameManager.grid.create2048();
}

int moves = 2;

//Button buttonUp =  Button(A5,PULLUP);
Button buttonDown =  Button(A2,PULLUP);
Button buttonLeft =  Button(A4,PULLUP);
Button buttonRight =  Button(A1,PULLUP);

void loop()
{

  // Buttons
  //if(buttonUp.uniquePress())    gameManager.move(0);


  // Display the board every loop
  if (!gameManager.isGameTerminated()) {
    gameManager.displayBoard();
    if(buttonDown.uniquePress())  gameManager.move(2);
    if(buttonLeft.uniquePress())  gameManager.move(3);
    if(buttonRight.uniquePress()) gameManager.move(1);
  } else {
    gameManager.grid.create2048();
  }


}









/*
void printBoard() {
 board.PrintBoard();
 }*/



