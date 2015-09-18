#ifndef PAWN_HPP
#define PAWN_HPP

#include <cstring>
#include <map>

#include "ChessPiece.hpp" 

using namespace std;

class Pawn : public ChessPiece {
private:
  bool passDanger; // bool to indicate whether a Pawn is in danger of an en 
                   // passant attack. 
public:
/* --------------------------------------------------------------------------- */
/* Constructor function for Pawn, utilizes the constructor for ChessPiece. 
   Initializes passDanger to 0.*/
/* --------------------------------------------------------------------------- */
  Pawn(char c);

/* --------------------------------------------------------------------------- */
/* Prints a unicode character representing the Pawn for either black or white
   depending on the Pawn's colour. */
/* --------------------------------------------------------------------------- */
  virtual void printPiece();

/* --------------------------------------------------------------------------- */
/* Validates the move of Pawn from sq1 to sq2 on a given ChessBoard, board. The
   function returns True if the Pawn moves one or two squares, if it is the first 
   move for the pawn, forward or one square forward diagonally, if attacking.*/
/* --------------------------------------------------------------------------- */
  virtual bool validateMove(string sq1, string sq2, 
			    map<string, ChessPiece *> &board);
/* --------------------------------------------------------------------------- */
/* Function to check a valid attack for a Pawn. Since attacks are in a different
   direction for a Pawn, helper functions are useful. Returns true if the target
   square is occupied by an opposing piece. */
/* --------------------------------------------------------------------------- */
  bool checkAttack(string sq1, string sq2, map<string, ChessPiece *> &board);

/* --------------------------------------------------------------------------- */
/* Function to check a valid move for a Pawn. Since attacks are in a different
   direction for a Pawn, helper functions are useful. Returns true if the target
   square is within two forward moves if there is no piece in either the first
   as well as, if moving two squares, second square. */
/* --------------------------------------------------------------------------- */
  bool checkMove(string sq1, string sq2, map<string, ChessPiece *> &board, 
		 int dist);

/* --------------------------------------------------------------------------- */
/* Prints Pawn, used to communicate with the players which piece is moving
   or if another piece is capturing it. */
/* --------------------------------------------------------------------------- */
  virtual void printName();

/* --------------------------------------------------------------------------- */
/* Resolves a move for the Pawn, if firstMove is 1, sets firstMove to 0. If first
   move and moved 2 squares, sets passDanger to 1. If it is not the first move,
   and the passDanger is 1, set passDanger to 0. Used with en passant checks.*/
/* --------------------------------------------------------------------------- */
  virtual void resolveMove(int dist);

/* --------------------------------------------------------------------------- */
/* Function to check for an en passant move, must check that a diagonal move has
   an unoccupied target and the piece behind it is a Pawn of the opposing side
   with passDanger == 1. */
/* --------------------------------------------------------------------------- */
  virtual bool checkEnPassant(string sq1, string sq2, 
			      map<string, ChessPiece*> &board);

/* --------------------------------------------------------------------------- */
/* Function to check for a valid pawn promotion move, if the pawn reaches one 
   end of the board or the other, returns True.*/
/* --------------------------------------------------------------------------- */
  virtual bool checkPromotion(string sq);

/* --------------------------------------------------------------------------- */
/* Function to check for a valid castling move, always returns false.*/
/* --------------------------------------------------------------------------- */
  virtual bool checkCastling(string sq1, string sq2, 
			     map<string, ChessPiece*> &board);
};

#endif
