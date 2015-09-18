#include <iostream>
#include <cstring>
#include <map>

#include "ChessPiece.hpp"
#include "King.hpp"




using namespace std;

/* --------------------------------------------------------------------------- */
/* Constructor function for King, utilizes the constructor for ChessPiece. */
/* --------------------------------------------------------------------------- */
King::King(char c) : ChessPiece(c) {}


/* --------------------------------------------------------------------------- */
/* Prints a unicode character representing the King for either black or white
   depending on the King's colour. */
/* --------------------------------------------------------------------------- */
void King::printPiece() {
  if (this->colour == 'b') {
    cout << "\u265A";
  } else {
    cout << "\u2654";
  }
}


/* --------------------------------------------------------------------------- */
/* Validates the move of King from sq1 to sq2 on a given ChessBoard, board. The
   function returns True if the King moves to any of the eight squares 
   surrounding his current location not currently occupied by a piece of the 
   same colour.*/
/* --------------------------------------------------------------------------- */
bool King::validateMove(string sq1, string sq2, 
			map<string, ChessPiece *> &board) { 
  char col1 = sq1[0];
  char col2 = sq2[0];
  int row1 = static_cast<int>(sq1[1]) - 48;  
  int row2 = static_cast<int>(sq2[1]) - 48;

  int rowdif = ((row1>=row2) ? row1-row2 : row2-row1);
  int coldif = ((col1>=col2) ? col1-col2 : col2-col1);
  
  if (checkCastling(sq1, sq2, board)) {
    return 1; // Castling is a special case defined below.
  }

  if (rowdif > 1 || coldif > 1) {
    return 0; // King can only move one space in any direction. change for castling
  }

  map<string, ChessPiece *>::iterator i = board.find(sq2); 
  if (i->second != NULL) {
    if ((i->second)->getColour() == this->getColour()) {
      return 0; // Cannot move into a space already occupied if not attacking.
    }
  }

  // if none of the above conditions hold, then the move is valid.
  return 1;
}


/* --------------------------------------------------------------------------- */
/* Prints King, used to communicate with the players which piece is moving
   or if another piece is capturing it. */
/* --------------------------------------------------------------------------- */
void King::printName() {
  cout << "King";
}


/* --------------------------------------------------------------------------- */
/* Resolves a move for the King, if firstMove is 1, sets firstMove to 0. */
/* --------------------------------------------------------------------------- */
void King::resolveMove(int dist) {
  this->setFirstMove();
}


/* --------------------------------------------------------------------------- */
/* Function to check for an en passant move, always returns false since a King
   cannot perform such a move. */
/* --------------------------------------------------------------------------- */
bool King::checkEnPassant(string sq1, string sq2, 
			  map<string, ChessPiece*> &board) {
  return 0; // A King cannot perform en passant.
}


/* --------------------------------------------------------------------------- */
/* Function to check for a valid pawn promotion move, King cannot perform this
   move and so always returns false.*/
/* --------------------------------------------------------------------------- */
bool King::checkPromotion(string sq) {
  return 0;
}

/* --------------------------------------------------------------------------- */
/* Function to check for a valid castling move, a King can initiate this move if, 
   neither he nor the target Rook have moved during the game, the squares between 
   the Rook and the King are unoccupied, and the King does not cross or end in 
   a square in which he would be in check.*/
/* --------------------------------------------------------------------------- */
 bool King::checkCastling(string sq1, string sq2,
			 map<string, ChessPiece*> &board) {
  if (this->firstMove == 0) {
    return 0; // if the King has moved it cannot castle.
  }
  if (sq1[1] != sq2[1]) {
    return 0; // must move within same row.
  }
  if (sq1[0] != 'E' || (sq2[0] != 'G' && sq2[0] != 'C')) {
    return 0; // move must be to C or G in the King's row.
  }
  
  char col = ((sq2[0] == 'C') ? 'A' : 'H');
  char sq[3] = {col, sq1[1], '\0'};
  
  map<string, ChessPiece *>::iterator i = board.find(sq);
  if (i->second == NULL) {
    return 0;
  }
  
  if ((i->second)->getFirstMove() != 1) {
    return 0; // the Rook may mot have moved.
  }
  
  char x = ((sq1[0] < sq2[0]) ? sq1[0] + 1 : 'B');
  char max = ((sq1[0] < sq2[0]) ? 'G' : 'D');
  
  for (; x<=max; x++) {
    char sqi[3] = {x, sq1[1], '\0'};
    i = board.find(sqi);
    if (i->second != NULL) {
      return 0; // There can be no pieces between the King and the Rook.
    }
  }
  
  return 1;
 }
