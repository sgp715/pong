#include <iostream>
#include <string>
#include "Board.h"

using namespace std;

Board::Board(){

  boardString = "";

  string edge = "-----------------------------------------------\n";
  string width = "|                                             |\n";

  // create the board: width = 46, hieght = 22
  int height = 20;
  boardString.append(edge);
  for (int i = 0; i < height; i++){
    boardString.append(width);
  }  
  boardString.append(edge);

  boardWidth = width.length();
  boardLength = height + 2;

  // place the ball and paddles initially
  placeCharacter(gameBall.getX(), gameBall.getY(), gameBall.getShape());

  int leftPaddleX = leftPaddle.getX();
  int * leftPaddleYs = leftPaddle.getYs();
  for(int i = 0; i < leftPaddle.getPaddleLength(); i++){
    placeCharacter(leftPaddleX, leftPaddleYs[i], leftPaddle.getShape());
  }
  
}

void Board::moveLeftPaddle(){

  // clear the old paddle
  int oldX = leftPaddle.getX();
  int * oldYs = leftPaddle.getYs();
  for (int i = 0; i < leftPaddle.getPaddleLength(); i++){

    placeCharacter(oldX, oldYs[i], ' ');
  }

  // move the paddle
  leftPaddle.move();
  
  int x = leftPaddle.getX();
  int * ys = leftPaddle.getYs();
  // set the new paddle
  for (int i = 0; i < leftPaddle.getPaddleLength(); i++){
    placeCharacter(x, ys[i], leftPaddle.getShape());
  }
  
}

void Board::moveBall(){

  int x = gameBall.getX();
  int y = gameBall.getY();

  // move the ball 
  placeCharacter(x, y, ' '); 

  if ((x == 1) || (x == boardWidth - 4)){
    gameBall.flipXDirection();
  }

  if ((y == 1) || (y ==  boardLength - 3)){
    gameBall.flipYDirection();
  }

  gameBall.move();
  placeCharacter(gameBall.getX(), gameBall.getY(), gameBall.getShape()); 

}

void Board::play(){

  moveBall();

  moveLeftPaddle();
  
  cout << boardString << endl;
  
}

void Board::placeCharacter(int x, int y, char c){

  // add the specified character into the board
  int position = x + boardWidth;
  position += (y * boardWidth);
  boardString[position] = c;

}

