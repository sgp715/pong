#include <iostream>
#include <string>
#include "Board.h"

using namespace std;

Board::Board(){

  boardString = "";

  string edge = "---------------------------------------------\n";
  string width = "|                      |                    |\n";

  // create the board: width = 45, hieght = 20
  boardString.append(edge);
  for (int i = 0; i < 20; i++){
    boardString.append(width);
  }  
  boardString.append(edge);

  boardWidth = width.length();
  boardLength = 22;
  
}


void Board::printBoard(){


  cout << boardString << endl;
  
}

void Board::placeCharacter(int x, int y, char c){


  // make sure we are adding within the board contraints
  if ((x < 1) || (y < 1)){
      cout << "adding to index less than board" << endl;
      return;
    }

  if ((x > boardWidth - 4) || (y > boardLength - 3)){
      cout << "adding to index greated than board" << endl;
      return;
    }

  // add the specified character into the board
  int position = x + boardWidth;
  position += (y * boardWidth);
  boardString[position] = c;

}

