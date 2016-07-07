#include <iostream>
#include <unistd.h>
#include "Board.h"
#include "Ball.h"


using namespace std;

void run(Board &gameBoard){

  float speed = 1;

  // place the ball and paddles in initial starting positions
  Ball gameBall;
  gameBoard.placeCharacter(gameBall.getX(), gameBall.getY(), gameBall.getShape());
  
  while (1){

    gameBoard.printBoard();
    gameBall.move();
    gameBoard.placeCharacter(gameBall.getX(), gameBall.getY(), gameBall.getShape());

    sleep(speed);
  }

}

int main(){

  Board gameBoard;
  run(gameBoard);
  return 0;  
}



