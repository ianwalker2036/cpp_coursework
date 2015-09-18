#include <iostream>
#include <cstring>
#include <map>

#include "ChessPiece.hpp"
#include "Queen.hpp"

#define SQUARE_LENGTH 3

using namespace std;

/* --------------------------------------------------------------------------- */
/* Constructor function for Queen, utilizes the constructor for ChessPiece. */
/* --------------------------------------------------------------------------- */
Queen::Queen(char c) : ChessPiece(c) {}


/* --------------------------------------------------------------------------- */
/* Prints a unicode character representing the Queen for either black or white
   depending on the Queen's colour. */
/* --------------------------------------------------------------------------- */
void Queen::printPiece() {
  if (this->colour == 'b') {
    cout << "\u265B";
  } else {
    cout << "\u2655";
  }
}


/* --------------------------------------------------------------------------- */
/* Validates the move of Queen from sq1 to sq2 on a given ChessBoard, board. The
   function returns True if the Queen moves on any unblocked path within a
   column, row, or diagonal.*/
/* --------------------------------------------------------------------------- */
bool Queen::validateMove(string sq1, string sq2, 
			 map<string, ChessPiece *> &board) { 
  char col1 = sq1[0];
  char col2 = sq2[0];
  int row1 = static_cast<int>(sq1[1]) - 48;  
  int row2 = static_cast<int>(sq2[1]) - 48;

  int rowdif = ((row1>=row2) ? row1-row2 : row2-row1);
  int coldif = ((col1>=col2) ? col1-col2 : col2-col1);
  
  // If the two squares are in different columns, then it must be the case that 
  // they are in the same row or it must be a diagonal move, else the move is 
  // invalid.
  if ((coldif > 0) && (rowdif != 0 && rowdif != coldif)) {
    return 0;
  }

  // If the two squares are in different rows, then it must be the case that 
  // they are in the same column or it must be a diagonal move, else the move is 
  // invalid.
  if ((rowdif > 0) && (coldif != 0 && rowdif != coldif)) {
    return 0;
  }
  
  // Now, we must loop through the squares between sq1 and sq2 to verify ther are
  // no pieces in the way, Queens cannot pass through other pieces and such a
  // move would be invalid.

  // First, we check along the diagonal, if the move is diagonally.
  if (coldif == rowdif) {
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
  } else { // now check along the row or column, if it was a such a move.
    char x, max, target;
    if (rowdif > 0) { // if a move within a row set the parameters for the loop.
      x = ((sq1[1]>sq2[1]) ? sq2[1] : sq1[1] + 1);
      max = ((sq1[1]>sq2[1]) ? sq1[1] - 1 : sq2[1]);
      target = sq2[1];
    } else if (coldif > 0) { // if a move within a column set the parameters.
      x = ((sq1[0]>sq2[0]) ? sq2[0] : sq1[0] + 1);
      max = ((sq1[0]>sq2[0]) ? sq1[0] - 1: sq2[0]);
      target = sq2[0];
    }
    
    for ( ; x<=max ; x++) {
      char sq[SQUARE_LENGTH] = {sq1[0], x, '\0'};
      if (coldif > 0) {
	sq[0] = x;
	sq[1] = sq1[1];
      }
      map<string, ChessPiece *>::iterator i = board.find(sq);
      if (i->second != NULL) {
	if ((x != target) || (x == target && 
			      this->getColour() == (i->second)->getColour())) 
	{ 
	  return 0; // Cannot pass through another piece nor can it end the move
	            // on a piece of the same colour.
	}    
      }
    }
    
  }
  
  // If none of the previous checks fail, the Queen's move is valid.
  return 1;
}


/* --------------------------------------------------------------------------- */
/* Prints Queen, used to communicate with the players which piece is moving
   or if another piece is capturing it. */
/* --------------------------------------------------------------------------- */
void Queen::printName() {
  cout << "Queen";
}


/* --------------------------------------------------------------------------- */
/* Resolves a move for the Queen, if firstMove is 1, sets firstMove to 0. */
/* --------------------------------------------------------------------------- */
void Queen::resolveMove(int dist) {
  this->setFirstMove();
}


/* --------------------------------------------------------------------------- */
/* Function to check for an en passant move, always returns false since a Queen
   cannot perform such a move. */
/* --------------------------------------------------------------------------- */
bool Queen::checkEnPassant(string sq1, string sq2, 
			   map<string, ChessPiece*> &board) {
  return 0; // A Queen cannot perform en passant.
}

/* --------------------------------------------------------------------------- */
/* Function to check for a valid pawn promotion move, Queen cannot perform this
   move and so always returns false.*/
/* --------------------------------------------------------------------------- */
bool Queen::checkPromotion(string sq) {
  return 0;
}

/* --------------------------------------------------------------------------- */
/* Function to check for a valid castling move, always returns false.*/
/* --------------------------------------------------------------------------- */
bool Queen::checkCastling(string sq1, string sq2, 
			     map<string, ChessPiece*> &board) {
    return 0;
  }
