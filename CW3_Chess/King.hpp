#ifndef KING_HPP
#define KING_HPP

#include <cstring>
#include <map>

#include "ChessPiece.hpp" 

using namespace std;

class King : public ChessPiece {
public:
/* --------------------------------------------------------------------------- */
/* Constructor function for King, utilizes the constructor for ChessPiece. */
/* --------------------------------------------------------------------------- */
  King(char c);

/* --------------------------------------------------------------------------- */
/* Prints a unicode character representing the King for either black or white
   depending on the King's colour. */
/* --------------------------------------------------------------------------- */
  virtual void printPiece();

/* --------------------------------------------------------------------------- */
/* Validates the move of King from sq1 to sq2 on a given ChessBoard, board. The
   function returns True if the King moves to any of the eight squares 
   surrounding his current location not currently occupied by a piece of the 
   same colour.*/
/* --------------------------------------------------------------------------- */
  virtual bool validateMove(string sq1, string sq2, 
			    map<string, ChessPiece *> &board);

/* --------------------------------------------------------------------------- */
/* Prints King, used to communicate with the players which piece is moving
   or if another piece is capturing it. */
/* --------------------------------------------------------------------------- */
  virtual void printName();

/* --------------------------------------------------------------------------- */
/* Resolves a move for the King, if firstMove is 1, sets firstMove to 0. */
/* --------------------------------------------------------------------------- */
  virtual void resolveMove(int dist);

/* --------------------------------------------------------------------------- */
/* Function to check for an en passant move, always returns false since a King
   cannot perform such a move. */
/* --------------------------------------------------------------------------- */
  virtual bool checkEnPassant(string sq1, string sq2, 
			      map<string, ChessPiece*> &board);

/* --------------------------------------------------------------------------- */
/* Function to check for a valid pawn promotion move, King cannot perform this
   move and so always returns false.*/
/* --------------------------------------------------------------------------- */
  virtual bool checkPromotion(string sq);

/* --------------------------------------------------------------------------- */
/* Function to check for a valid castling move, a King can initiate this move if, 
   neither he nor the target Rook have moved during the game, the squares between 
   the Rook and the King are unoccupied, and the King does not cross or end in 
   a square in which he would be in check.*/
/* --------------------------------------------------------------------------- */
  bool checkCastling(string sq1, string sq2, map<string, ChessPiece*> &board);
};

#endif
