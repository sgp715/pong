#include <iostream>
#include <string>
#include <unistd.h>
#include "Board.h"

using namespace std;

Board::Board(){

  boardString = "";

  string edge = "-----------------------------------------------\n";
  string width = "|                                             |\n";

  // initialize the screen
  initscr();

  // set some basic settings
  nodelay(stdscr, true);
  keypad(stdscr, true);
  noecho();
  curs_set(0);

  // determine the screen size
  getmaxyx(stdscr, maxY, maxX); 
  
  for (int i = 0; i < maxX; i++){
    addch('-');
  }

  for (int i = 0; i < maxY-2; i++){
    addch('|');
    for (int i = 0; i < maxX - 2; i++){
      addch(' ');
    }
    addch('|');
  }

  for (int i = 0; i < maxX; i++){
    addch('-');
  }

  placeCharacter(gameBall.getX(), gameBall.getY(), gameBall.getShape());

  int startingY = 5;
  int startingX = 5;

  leftPaddle = Paddle(startingX, startingY);
  int leftPaddleX = leftPaddle.getX();
  int * leftPaddleYs = leftPaddle.getYs();
  for(int i = 0; i < leftPaddle.getPaddleLength(); i++){
    placeCharacter(leftPaddleX, leftPaddleYs[i], leftPaddle.getShape());
  }
}

Board::~Board(){

  nodelay(stdscr, false);
  getch();
  endwin();
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

  // turn the paddle around
  if ((ys[0] == 1) || (ys[4] == maxY - 2)){
    leftPaddle.flipYDirection();
  }
  
}

void Board::moveBall(){

  int x = gameBall.getX();
  int y = gameBall.getY();

  // move the ball 
  placeCharacter(x, y, ' '); 

  if ((x == 1) || (x == maxX - 2)){
    gameBall.flipXDirection();
  }

  if ((y == 1) || (y ==  maxY - 2)){
    gameBall.flipYDirection();
  }

  gameBall.move();
  
  placeCharacter(gameBall.getX(), gameBall.getY(), gameBall.getShape());

}

void Board::play(){

  
  while(getch() != 'q'){

    int speed = 100000;
    usleep(speed);

    moveBall();
    moveLeftPaddle();

  }
  
}

void Board::placeCharacter(int x, int y, char c){

  // add the specified character onto the board
  move(y, x);
  addch(c);

}

