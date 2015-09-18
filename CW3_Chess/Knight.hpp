#ifndef KNIGHT_HPP
#define KNIGHT_HPP

#include <cstring>
#include <map>

#include "ChessPiece.hpp" 

using namespace std;

class Knight : public ChessPiece {
public:
/* --------------------------------------------------------------------------- */
/* Constructor function for Knight, utilizes the constructor for ChessPiece. */
/* --------------------------------------------------------------------------- */
  Knight(char c);

/* --------------------------------------------------------------------------- */
/* Prints a unicode character representing the Knight for either black or white
   depending on the Knight's colour. */
/* --------------------------------------------------------------------------- */
  virtual void printPiece();

/* --------------------------------------------------------------------------- */
/* Validates the move of Knight from sq1 to sq2 on a given ChessBoard, board. The
   function returns True if the Knight moves to any unblocked square in a "L"
   formation, i.e. moves two columns and on row, or moves two rows and one 
   column. Note, the Knight ignores other pieces in between the squares.*/
/* --------------------------------------------------------------------------- */
  virtual bool validateMove(string sq1, string sq2, 
			    map<string, ChessPiece *> &board);

/* --------------------------------------------------------------------------- */
/* Prints Knight, used to communicate with the players which piece is moving
   or if another piece is capturing it. */
/* --------------------------------------------------------------------------- */
  virtual void printName();

/* --------------------------------------------------------------------------- */
/* Resolves a move for the Knight, if firstMove is 1, sets firstMove to 0. */
/* --------------------------------------------------------------------------- */
  virtual void resolveMove(int dist);

/* --------------------------------------------------------------------------- */
/* Function to check for an en passant move, always returns false since a Knight
   cannot perform such a move. */
/* --------------------------------------------------------------------------- */
  virtual bool checkEnPassant(string sq1, string sq2, 
			      map<string, ChessPiece*> &board);

/* --------------------------------------------------------------------------- */
/* Function to check for a valid pawn promotion move, Knight cannot perform this
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
