#include <iostream>
#include <unistd.h>
#include "Board.h"


using namespace std;

void run(Board &gameBoard){

  float speed = 100000;

  while (1){

    gameBoard.play();
    usleep(speed);
  }

}

int main(){

  Board gameBoard;
  run(gameBoard);
  return 0;  
}



