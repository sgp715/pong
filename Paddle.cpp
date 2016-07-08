#include <iostream>
#include "Paddle.h"

using namespace std;

Paddle::Paddle(){

 shape = '#';

  xPos = 5;
  paddleLength = 5;
  for (int i = 0; i < paddleLength; i++){
    yPositions[i] = i + 2;
  }
   
  yDirection = 1;


}

Paddle::Paddle(int startingX, int startingY){

  shape = '#';

  xPos = startingX;
  paddleLength = 5;
  for (int i = 0; i < paddleLength; i++){
    yPositions[i] = startingY + i;
  }
   
  yDirection = 1;

}

char Paddle::getShape(){
  
  return shape;
}

int Paddle::getX(){

  return xPos;
}

int * Paddle::getYs(){

  return yPositions;
}

int Paddle::getPaddleLength(){

  return paddleLength;
}

int Paddle::getYDirection(){

  return yDirection;
}

void Paddle::setYDirection(int direction){

  yDirection = direction;
}

void Paddle::flipYDirection(){

  yDirection = yDirection * -1;
}

void Paddle::move(){

  for (int i = 0; i < paddleLength; i++){
    yPositions[i] = yPositions[i] + yDirection;
  }

}

/*
PlayerPaddle::PlayerPaddle(){

  
}*/

/*
ComputerPaddle::ComputerPaddle(){

  
}*/
