#include <string>
#include <ncurses.h>
#include "Ball.h"
#include "Paddle.h"


using namespace std;


class Board{

  string boardString;
  int boardWidth;
  int boardLength;
  int maxX;
  int maxY;
  Ball gameBall;
  Paddle leftPaddle;
  Paddle playerPaddle;

 public:
  Board();
  ~Board();
  void moveBall();
  void movePaddle(Paddle &paddle);
  void movePaddleDirection(Paddle &, int);
  void followBall(Paddle &);
  void bouncePaddle(Paddle &paddle);
  void play();
  void placeCharacter(int x, int y, char c);

};


