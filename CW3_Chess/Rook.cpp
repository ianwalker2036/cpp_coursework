#include <iostream>
#include <cstring>
#include <map>

#include "ChessPiece.hpp"
#include "Rook.hpp"

#define SQUARE_LENGTH 3

using namespace std;

/* --------------------------------------------------------------------------- */
/* Constructor function for Rook, utilizes the constructor for ChessPiece. */
/* --------------------------------------------------------------------------- */
Rook::Rook(char c) : ChessPiece(c) {}


/* --------------------------------------------------------------------------- */
/* Prints a unicode character representing the Rook for either black or white
   depending on the Rook's colour. */
/* --------------------------------------------------------------------------- */
void Rook::printPiece() {
  if (this->colour == 'b') {
    cout << "\u265C";
  } else {
    cout << "\u2656";
  }
}


/* --------------------------------------------------------------------------- */
/* Validates the move of Rook from sq1 to sq2 on a given ChessBoard, board. The
   function returns True if the Rook moves on any unblocked path within a
   row or column.*/
/* --------------------------------------------------------------------------- */
bool Rook::validateMove(string sq1, string sq2, map<string, ChessPiece *> &board) { 
  char col1 = sq1[0];
  char col2 = sq2[0];
  int row1 = static_cast<int>(sq1[1]) - 48;  
  int row2 = static_cast<int>(sq2[1]) - 48;

  int rowdif = ((row1>=row2) ? row1-row2 : row2-row1);
  int coldif = ((col1>=col2) ? col1-col2 : col2-col1);
  
  if (rowdif > 0 && coldif > 0) {
    return 0; // Rooks may only move within same row or column.
  }

  // Set the correct parameters for the loop below, depending on whether the move
  // is within a row or a column and whether it is forwards or backwards.
  char x, max, target;
  if (rowdif > 0) {
    x = ((sq1[1]>sq2[1]) ? sq2[1] : sq1[1] + 1);
    max = ((sq1[1]>sq2[1]) ? sq1[1] - 1 : sq2[1]);
    target = sq2[1];
  } else if (coldif > 0) {
    x = ((sq1[0]>sq2[0]) ? sq2[0] : sq1[0] + 1);
    max = ((sq1[0]>sq2[0]) ? sq1[0] - 1: sq2[0]);
    target = sq2[0];
  }

  // Loop through the path to ensure there are no pieces in the way.
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

  // if none of the above conditions hold, then the move is valid.
  return 1;
}


/* --------------------------------------------------------------------------- */
/* Prints Rook, used to communicate with the players which piece is moving
   or if another piece is capturing it. */
/* --------------------------------------------------------------------------- */
void Rook::printName() {
  cout << "Rook";
}


/* --------------------------------------------------------------------------- */
/* Resolves a move for the Rook, if firstMove is 1, sets firstMove to 0. */
/* --------------------------------------------------------------------------- */
void Rook::resolveMove(int dist) {
  this->setFirstMove();
}


/* --------------------------------------------------------------------------- */
/* Function to check for an en passant move, always returns false since a Rook
   cannot perform such a move. */
/* --------------------------------------------------------------------------- */
bool Rook::checkEnPassant(string sq1, string sq2, map<string, ChessPiece*> &board) {
  return 0; // A Rook cannot perform en passant.
}

/* --------------------------------------------------------------------------- */
/* Function to check for a valid pawn promotion move, Rook cannot perform this
   move and so always returns false.*/
/* --------------------------------------------------------------------------- */
bool Rook::checkPromotion(string sq) {
  return 0;
}

/* --------------------------------------------------------------------------- */
/* Function to check for a valid castling move, always returns false.*/
/* --------------------------------------------------------------------------- */
bool Rook::checkCastling(string sq1, string sq2, 
			     map<string, ChessPiece*> &board) {
    return 0;
  }
