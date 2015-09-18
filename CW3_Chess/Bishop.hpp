#ifndef BISHOP_HPP
#define BISHOP_HPP

#include <cstring>
#include <map>

#include "ChessPiece.hpp" 

using namespace std;

class Bishop : public ChessPiece {
public:
/* --------------------------------------------------------------------------- */
/* Constructor function for Bishop, utilizes the constructor for ChessPiece. */
/* --------------------------------------------------------------------------- */
  Bishop(char c);

/* --------------------------------------------------------------------------- */
/* Prints a unicode character representing the Bishop for either black or white
   depending on the Bishop's colour. */
/* --------------------------------------------------------------------------- */
  virtual void printPiece();

/* --------------------------------------------------------------------------- */
/* Validates the move of Bishop from sq1 to sq2 on a given ChessBoard, board. The
   function returns True if the Bishop moves on any unblocked path within a
   diagonal.*/
/* --------------------------------------------------------------------------- */
  virtual bool validateMove(string sq1, string sq2, 
			    map<string, ChessPiece *> &board);

/* --------------------------------------------------------------------------- */
/* Prints Bishop, used to communicate with the players which piece is moving
   or if another piece is capturing it. */
/* --------------------------------------------------------------------------- */
  virtual void printName();

/* --------------------------------------------------------------------------- */
/* Resolves a move for the Bishop, if firstMove is 1, sets firstMove to 0. */
/* --------------------------------------------------------------------------- */
  virtual void resolveMove(int dist);

/* --------------------------------------------------------------------------- */
/* Function to check for an en passant move, always returns false since a Bishop
   cannot perform such a move. */
/* --------------------------------------------------------------------------- */
  virtual bool checkEnPassant(string sq1, string sq2, 
			      map<string, ChessPiece*> &board);

/* --------------------------------------------------------------------------- */
/* Function to check for a valid pawn promotion move, Bishop cannot perform this
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
