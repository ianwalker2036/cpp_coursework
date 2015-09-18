#include <iostream>
#include <cstring>
#include <map>

#include "ChessPiece.hpp"
#include "Knight.hpp"

using namespace std;

/* --------------------------------------------------------------------------- */
/* Constructor function for Knight, utilizes the constructor for ChessPiece. */
/* --------------------------------------------------------------------------- */
Knight::Knight(char c) : ChessPiece(c) {}


/* --------------------------------------------------------------------------- */
/* Prints a unicode character representing the Knight for either black or white
   depending on the Knight's colour. */
/* --------------------------------------------------------------------------- */
void Knight::printPiece() {
  if (this->colour == 'b') {
    cout << "\u265E";
  } else {
    cout << "\u2658";
  }
}

/* --------------------------------------------------------------------------- */
/* Validates the move of Knight from sq1 to sq2 on a given ChessBoard, board. The
   function returns True if the Knight moves to any unblocked square in a "L"
   formation, i.e. moves two columns and on row, or moves two rows and one 
   column. Note, the Knight ignores other pieces in between the squares.*/
/* --------------------------------------------------------------------------- */
bool Knight::validateMove(string sq1, string sq2, 
			  map<string, ChessPiece *> &board) {
  char col1 = sq1[0];
  char col2 = sq2[0];
  int row1 = static_cast<int>(sq1[1]) - 48;  
  int row2 = static_cast<int>(sq2[1]) - 48; 

  int rowdif = ((row1>=row2) ? row1-row2 : row2-row1);
  int coldif = ((col1>=col2) ? col1-col2 : col2-col1);

  map<string, ChessPiece *>::iterator i = board.find(sq2); 
  if ((i->second != NULL) && ((i->second)->getColour() == this->getColour())) {
    return 0; // Cannot end in a square occupied by same side
  }

  if (!((rowdif == 1 || coldif == 1) && (rowdif == 2 || coldif == 2))) {
    return 0; // Knight must move in "L" formation.
  }

  // if none of the above conditions hold, then the move is valid.
  return 1;
}


/* --------------------------------------------------------------------------- */
/* Prints Knight, used to communicate with the players which piece is moving
   or if another piece is capturing it. */
/* --------------------------------------------------------------------------- */
void Knight::printName() {
  cout << "Knight";
}


/* --------------------------------------------------------------------------- */
/* Resolves a move for the Knight, if firstMove is 1, sets firstMove to 0. */
/* --------------------------------------------------------------------------- */
void Knight::resolveMove(int dist) {
  this->setFirstMove();
}


/* --------------------------------------------------------------------------- */
/* Function to check for an en passant move, always returns false since a Knight
   cannot perform such a move. */
/* --------------------------------------------------------------------------- */
bool Knight::checkEnPassant(string sq1, string sq2, 
			    map<string, ChessPiece*> &board) {
  return 0; // A Knight cannot perform en passant.
}

/* --------------------------------------------------------------------------- */
/* Function to check for a valid pawn promotion move, Knight cannot perform this
   move and so always returns false.*/
/* --------------------------------------------------------------------------- */
bool Knight::checkPromotion(string sq) {
  return 0;
}

/* --------------------------------------------------------------------------- */
/* Function to check for a valid castling move, always returns false.*/
/* --------------------------------------------------------------------------- */
bool Knight::checkCastling(string sq1, string sq2, 
			     map<string, ChessPiece*> &board) { 
    return 0;
  }
