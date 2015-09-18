#ifndef QUEEN_HPP
#define QUEEN_HPP

#include <cstring>
#include <map>

#include "ChessPiece.hpp" 

using namespace std;

class Queen : public ChessPiece {
public:
/* --------------------------------------------------------------------------- */
/* Constructor function for Queen, utilizes the constructor for ChessPiece. */
/* --------------------------------------------------------------------------- */
  Queen(char c);

/* --------------------------------------------------------------------------- */
/* Prints a unicode character representing the Queen for either black or white
   depending on the Queen's colour. */
/* --------------------------------------------------------------------------- */
  virtual void printPiece();

/* --------------------------------------------------------------------------- */
/* Validates the move of Queen from sq1 to sq2 on a given ChessBoard, board. The
   function returns True if the Queen moves on any unblocked path within a
   column, row, or diagonal.*/
/* --------------------------------------------------------------------------- */
  virtual bool validateMove(string sq1, string sq2, 
			    map<string, ChessPiece *> &board);

/* --------------------------------------------------------------------------- */
/* Prints Queen, used to communicate with the players which piece is moving
   or if another piece is capturing it. */
/* --------------------------------------------------------------------------- */
  virtual void printName();

/* --------------------------------------------------------------------------- */
/* Resolves a move for the Queen, if firstMove is 1, sets firstMove to 0. */
/* --------------------------------------------------------------------------- */
  virtual void resolveMove(int dist);

/* --------------------------------------------------------------------------- */
/* Function to check for an en passant move, always returns false since a Queen
   cannot perform such a move. */
/* --------------------------------------------------------------------------- */
  virtual bool checkEnPassant(string sq1, string sq2, 
			      map<string, ChessPiece*> &board);

/* --------------------------------------------------------------------------- */
/* Function to check for a valid pawn promotion move, Queen cannot perform this
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
