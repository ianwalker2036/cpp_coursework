#ifndef ROOK_HPP
#define ROOK_HPP

#include <cstring>
#include <map>

#include "ChessPiece.hpp" 

using namespace std;

class Rook : public ChessPiece {
public:
/* --------------------------------------------------------------------------- */
/* Constructor function for Rook, utilizes the constructor for ChessPiece. */
/* --------------------------------------------------------------------------- */
  Rook(char c);

/* --------------------------------------------------------------------------- */
/* Prints a unicode character representing the Rook for either black or white
   depending on the Rook's colour. */
/* --------------------------------------------------------------------------- */
  virtual void printPiece();

/* --------------------------------------------------------------------------- */
/* Validates the move of Rook from sq1 to sq2 on a given ChessBoard, board. The
   function returns True if the Rook moves on any unblocked path within a
   row or column.*/
/* --------------------------------------------------------------------------- */
  virtual bool validateMove(string sq1, string sq2, 
			    map<string, ChessPiece *> &board);

/* --------------------------------------------------------------------------- */
/* Prints Rook, used to communicate with the players which piece is moving
   or if another piece is capturing it. */
/* --------------------------------------------------------------------------- */
  virtual void printName();

/* --------------------------------------------------------------------------- */
/* Resolves a move for the Rook, if firstMove is 1, sets firstMove to 0. */
/* --------------------------------------------------------------------------- */
  virtual void resolveMove(int dist);

/* --------------------------------------------------------------------------- */
/* Function to check for an en passant move, always returns false since a Rook
   cannot perform such a move. */
/* --------------------------------------------------------------------------- */
  virtual bool checkEnPassant(string sq1, string sq2, 
			      map<string, ChessPiece*> &board);

/* --------------------------------------------------------------------------- */
/* Function to check for a valid pawn promotion move, Rook cannot perform this
   move and so always returns false.*/
/* --------------------------------------------------------------------------- */
  virtual bool checkPromotion(string sq);

/* --------------------------------------------------------------------------- */
/* Function to check for a valid castling move, always returns false.*/
/* --------------------------------------------------------------------------- */
  virtual bool checkCastling(string sq1, string sq2, 
			     map<string, ChessPiece*> &board);
};

#endif
