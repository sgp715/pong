#include <iostream>
#include "Paddle.h"

using namespace std;

Paddle::Paddle(){

  shape = '#';

  xPos = 5;
  yPositions[1] = 1;
  yPositions[2] = 2;
  yPositions[3] = 3;
  yPositions[4] = 4;
  paddleLength = 4;
  
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

void Paddle::flipYDirection(){

  yDirection = yDirection * -1;
}

void Paddle::move(){

  for (int i = 0; i < paddleLength; i++){
    yPositions[i] = yPositions[i] + yDirection;
  }

}
