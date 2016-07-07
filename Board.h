#include <string>
#include "Ball.h"
#include "Paddle.h"


using namespace std;


class Board{

  string boardString;
  int boardWidth;
  int boardLength;
  Ball gameBall;
  Paddle leftPaddle;

 public:
  Board();
  void moveBall();
  void moveLeftPaddle();
  void play();
  void placeCharacter(int x, int y, char c);

};


