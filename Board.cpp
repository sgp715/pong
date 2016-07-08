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


  // add some coloring
  start_color();			/* Start color 			*/
  init_pair(1, COLOR_GREEN, COLOR_BLACK);
  attron(COLOR_PAIR(1));

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
  int playerStartingX = 74;
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


void Board::followBall(Paddle &paddle){

  int quarter = maxX / 4;
  
  if (gameBall.getX() < (quarter + 3)){
    if (gameBall.getXDirection() == -1){
      int direction = gameBall.getYDirection();
      movePaddleDirection(paddle, direction);
    }
  }

}


void Board::movePaddleDirection(Paddle &paddle, int direction){
  
  // if we are at the edge, do nothing
  int x = paddle.getX();
  int * ys = paddle.getYs();
  if ((ys[0] == 1) && (direction == -1)){
      return;
  }
      
  if ((ys[4] == maxY - 2) && (direction == 1)){
    return;
  }

  // otherwise set the direction and move
  paddle.setYDirection(direction);
  movePaddle(paddle);

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

void Board::bouncePaddle(Paddle &paddle){

  int xDirection = gameBall.getXDirection();
  int yDirection = gameBall.getYDirection();

  int x = gameBall.getX();
  int y = gameBall.getY();

  int paddleX = paddle.getX();
  int * paddleYs = paddle.getYs();

  
  if ((paddleX + 1 == x) || (paddleX - 1 == x)){
    if ((paddleYs[0] <= y) && paddleYs[4] >= y){
      gameBall.flipXDirection();
    }
  }


  if (paddleX == x){
    if ((paddleYs[0] - 1 == y) || (paddleYs[4] + 1 == y)){
      gameBall.flipYDirection();
    }
  }

  
  if ((xDirection == 1) && (yDirection == 1)){
    if (paddleX - 1 == x){
      if (paddleYs[0] - 1 == y){
	gameBall.flipXDirection();
	gameBall.flipYDirection();
      }
    }
  }

  else if ((xDirection == 1) && (yDirection == -1)){
    if (paddleX - 1 == x){
      if (paddleYs[4] + 1 == y){
	gameBall.flipXDirection();
	gameBall.flipYDirection();
      }
    }
  }

  else if ((xDirection == -1) && (yDirection == 1)){
    if (paddleX + 1 == x){
      if (paddleYs[0] - 1 == y){
	gameBall.flipXDirection();
	gameBall.flipYDirection();
      }
    }
  }

  else if ((xDirection == -1) && (yDirection == -1)){
    if (paddleX + 1 == x){
      if (paddleYs[4] + 1 == y){
	gameBall.flipXDirection();
	gameBall.flipYDirection();
      }
    }
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

  // see if we have to bounce of either paddle
  bouncePaddle(playerPaddle);
  bouncePaddle(leftPaddle);

  gameBall.move();
  placeCharacter(gameBall.getX(), gameBall.getY(), gameBall.getShape());

}

void Board::play(){

  char c;
  while((c = getch()) != 'q'){


    // if we have hit either wall the game is over
    // declare a winner and move on
    int x = gameBall.getX();
    if (x == maxX - 2){
      move(12, 25);
      printw("You lose. Better luck next time...");
      break;
    } else if (x == 1){
      move(12, 25);
      printw("Winner, winner chicken dinner!");
      break;
    }
    
    // control the computer player
    followBall(leftPaddle);
 
    // check if player is trying move their paddle
    int up = 3;
    int down = 2;
    if (c == up){
      movePaddleDirection(playerPaddle, -1);
    } else if (c == down){
      movePaddleDirection(playerPaddle, 1);
    }

    int speed = 100000;
    usleep(speed);    
   
    // move the ball forward
    moveBall();
 

  }
  
}

void Board::placeCharacter(int x, int y, char c){

  // add the specified character onto the board
  move(y, x);
  addch(c);

}

