#include <iostream>
#include "Ball.h"


using namespace std;


Ball::Ball(){

  // how's the ball gonna look 
  shape = 'O';


  // setting it in motion
  xPos = 10;
  yPos = 10;
  xDirection = 1;
  yDirection = 1;

}

char Ball::getShape(){
  return shape;
}

int Ball::getX(){
  return xPos;
}

int Ball::getY(){
  return yPos;
}

int Ball::getXDirection(){
  return xDirection;
}

int Ball::getYDirection(){
  return yDirection;
}

void Ball::flipXDirection(){
  
  xDirection *= -1;
}

void Ball::flipYDirection(){
  yDirection *= -1;
}

void Ball::move(){

  xPos += xDirection;
  yPos += yDirection;

}
