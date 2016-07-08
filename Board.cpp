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


  int playerStartingY = 5;
  int playerStartingX = 75;
  playerPaddle = Paddle(playerStartingX, playerStartingY);

  int playerPaddleX = playerPaddle.getX();
  int * playerPaddleYs = playerPaddle.getYs();
  for(int i = 0; i < playerPaddle.getPaddleLength(); i++){
    placeCharacter(playerPaddleX, playerPaddleYs[i], playerPaddle.getShape());
  }

}

Board::~Board(){

  nodelay(stdscr, false);
  getch();
  endwin();
}

void Board::movePlayerPaddle(int direction){
  
  // if we are at the edge, do nothing
  int x = playerPaddle.getX();
  int * ys = playerPaddle.getYs();
  if ((ys[0] == 1) && (direction == -1)){
      return;
  }
      
  if ((ys[4] == maxY - 2) && (direction == 1)){
    return;
  }

  // otherwise set the direction and move
  playerPaddle.setYDirection(direction);
  movePaddle(playerPaddle);

}

void Board::movePaddle(Paddle &paddle){

  // clear the old paddle
  int oldX = paddle.getX();
  int * oldYs = paddle.getYs();
  for (int i = 0; i < paddle.getPaddleLength(); i++){
    placeCharacter(oldX, oldYs[i], ' ');
  }

  // move the paddle
  paddle.move();
  
  int x = paddle.getX();
  int * ys = paddle.getYs();
  // set the new paddle
  for (int i = 0; i < paddle.getPaddleLength(); i++){
    placeCharacter(x, ys[i], paddle.getShape());
  }

  // turn the paddle around
  if ((ys[0] == 1) || (ys[4] == maxY - 2)){
    paddle.flipYDirection();
  }
  
}

void Board::moveBall(){

  int x = gameBall.getX();
  int y = gameBall.getY();

  // move the ball 
  placeCharacter(x, y, ' '); 

  // if we he either wall 
  if ((x == 1) || (x == maxX - 2)){
    gameBall.flipXDirection();
  }

  // if we hit the cieling
  if ((y == 1) || (y ==  maxY - 2)){
    gameBall.flipYDirection();
  }

  int leftPaddleX = leftPaddle.getX();
  int * leftPaddleYs = leftPaddle.getYs();
  int playerPaddleX = playerPaddle.getX();
  int * playerPaddleYs = playerPaddle.getYs();

  if ((playerPaddleX + 1 == x) || (playerPaddleX - 1 == x)){
    if ((playerPaddleYs[0] <= y) && playerPaddleYs[4] >= y){
      gameBall.flipXDirection();
    }
  }

  if ((playerPaddleX + 1 == x) || (playerPaddleX - 1 == x)){
   if ((playerPaddleYs[0] <= y) && playerPaddleYs[4] >= y){
      gameBall.flipXDirection();
    }
  }


  gameBall.move();
  placeCharacter(gameBall.getX(), gameBall.getY(), gameBall.getShape());

}

void Board::play(){

  char c;
  while((c = getch()) != 'q'){

    int speed = 100000;
    usleep(speed);

    moveBall();
    movePaddle(leftPaddle);

    int up = 3;
    int down = 2;
    if (c == up){
      movePlayerPaddle(-1);
    } else if (c == down){
      movePlayerPaddle(1);
    }

  }
  
}

void Board::placeCharacter(int x, int y, char c){

  // add the specified character onto the board
  move(y, x);
  addch(c);

}

