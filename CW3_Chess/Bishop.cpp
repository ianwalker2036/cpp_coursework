#include <iostream>
#include <cstring>
#include <map>

#include "ChessPiece.hpp"
#include "Bishop.hpp"

#define SQUARE_LENGTH 3

using namespace std;

/* --------------------------------------------------------------------------- */
/* Constructor function for Bishop, utilizes the constructor for ChessPiece. */
/* --------------------------------------------------------------------------- */
Bishop::Bishop(char c) : ChessPiece(c) {}


/* --------------------------------------------------------------------------- */
/* Prints a unicode character representing the Bishop for either black or white
   depending on the Bishop's colour. */
/* --------------------------------------------------------------------------- */
void Bishop::printPiece() {
  if (this->colour == 'b') {
    cout << "\u265D";
  } else {
    cout << "\u2657";
  }
}


/* --------------------------------------------------------------------------- */
/* Validates the move of Bishop from sq1 to sq2 on a given ChessBoard, board. The
   function returns True if the Bishop moves on any unblocked path within a
   diagonal.*/
/* --------------------------------------------------------------------------- */
bool Bishop::validateMove(string sq1, string sq2, 
			  map<string, ChessPiece *> &board) { 
  char col1 = sq1[0];
  char col2 = sq2[0];
  int row1 = static_cast<int>(sq1[1]) - 48;  
  int row2 = static_cast<int>(sq2[1]) - 48;
  
  int rowdif = ((row1>=row2) ? row1-row2 : row2-row1);
  int coldif = ((col1>=col2) ? col1-col2 : col2-col1);

  if (rowdif != coldif) {
    return 0; // Bishops may only move diagonally
  }

  // now loop through the diagonal path between the two squares, if any 
  // contain another piece, the move is invalid.
  for (int x = 1; x <= rowdif; x++) {
    int rowmult = ((row2>=row1) ? 1 : -1);
    int colmult = ((col2>=col1) ? 1 : -1);
    
    char column = col1 + colmult*x;
    char row = row1 + rowmult*x + 48;
    
    char sq[SQUARE_LENGTH] = {column, row, '\0'};
    map<string, ChessPiece *>::iterator i = board.find(sq);

    if (i->second != NULL) {
      if ((x != rowdif) || (x == rowdif && 
			    this->getColour() == (i->second)->getColour())) 
      {
	return 0; // Cannot pass through another piece nor can it end the move 
	          // on a piece of the same colour.
      }
    }
  }

  // if none of the above conditions hold, then the move is valid.
  return 1;
}


/* --------------------------------------------------------------------------- */
/* Prints Bishop, used to communicate with the players which piece is moving
   or if another piece is capturing it. */
/* --------------------------------------------------------------------------- */
void Bishop::printName() {
  cout << "Bishop";
}


/* --------------------------------------------------------------------------- */
/* Resolves a move for the Bishop, if firstMove is 1, sets firstMove to 0. */
/* --------------------------------------------------------------------------- */
void Bishop::resolveMove(int dist) {
  this->setFirstMove();
}


/* --------------------------------------------------------------------------- */
/* Function to check for an en passant move, always returns false since a Bishop
   cannot perform such a move. */
/* --------------------------------------------------------------------------- */
bool Bishop::checkEnPassant(string sq1, string sq2, 
			    map<string, ChessPiece*> &board) {
  return 0; // A Bishop cannot perform en passant.
}

/* --------------------------------------------------------------------------- */
/* Function to check for a valid pawn promotion move, Bishop cannot perform this
   move and so always returns false.*/
/* --------------------------------------------------------------------------- */
bool Bishop::checkPromotion(string sq) {
  return 0;
}

/* --------------------------------------------------------------------------- */
/* Function to check for a valid castling move, always returns false.*/
/* --------------------------------------------------------------------------- */
bool Bishop::checkCastling(string sq1, string sq2, 
			     map<string, ChessPiece*> &board) {
    return 0;
  }
