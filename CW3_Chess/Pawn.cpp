#include <iostream>
#include <cstring>
#include <map>

#include "ChessPiece.hpp"
#include "Pawn.hpp"

#define SQUARE_LENGTH 3

using namespace std;

/* --------------------------------------------------------------------------- */
/* Constructor function for Pawn, utilizes the constructor for ChessPiece. 
   Initializes passDanger to 0.*/
/* --------------------------------------------------------------------------- */
Pawn::Pawn(char c) : ChessPiece(c), passDanger(0) {}


/* --------------------------------------------------------------------------- */
/* Prints a unicode character representing the Pawn for either black or white
   depending on the Pawn's colour. */
/* --------------------------------------------------------------------------- */
void Pawn::printPiece() {
  if (this->colour == 'b') {
    cout << "\u265F";
  } else {
    cout << "\u2659";
  }
}


/* --------------------------------------------------------------------------- */
/* Validates the move of Pawn from sq1 to sq2 on a given ChessBoard, board. The
   function returns True if the Pawn moves one or two squares, if it is the first 
   move for the pawn, forward or one square forward diagonally, if attacking.*/
/* --------------------------------------------------------------------------- */
bool Pawn::validateMove(string sq1, string sq2, 
			map<string, ChessPiece *> &board) { 
  
  char col1 = sq1[0];
  char col2 = sq2[0];
  int row1 = static_cast<int>(sq1[1]) - 48;  
  int row2 = static_cast<int>(sq2[1]) - 48;
  
  if ((row2 <= row1) && (colour == 'w')) {
    return 0; // Pawn cannot move back.
  } else if ((row1 <= row2) && (colour == 'b')) {
    return 0; // Pawn cannot move back.
  } else if (((row2 - row1) > 1 || (row1 - row2) > 1) && firstMove != 1) {
    return 0; // Pawn cannot move more than 1 space after first move.
  } else if ((col1-col2 > 1) || (col2-col1 > 1)) {
    return 0; // Pawn cannot move more than 1 diagonally.
  } else if (((row2 - row1 > 2) || (row1 - row2 > 2))&& firstMove == 1) {
    return 0; // Pawn cannot move more than 2 spaces if first move.
  } else if (((row2 - row1 == 2) || (row1 - row2 == 2)) && firstMove == 1 
	     && (col1 - col2 > 0 || col2 - col1 > 0)) 
  {
    return 0; // Pawn cannont move diagonally if moving 2 spaces.
  }

  if ((col1-col2 == 1) || (col2-col1 == 1)) {
    return checkAttack(sq1, sq2, board); // Check if the attack is valid.
  }

  int distance = ((row1 > row2) ? row1-row2 : row2-row1);

  return checkMove(sq1, sq2, board, distance); // check if the move is valid.
}


/* --------------------------------------------------------------------------- */
/* Function to check a valid attack for a Pawn. Since attacks are in a different
   direction for a Pawn, helper functions are useful. Returns true if the target
   square is occupied by an opposing piece. */
/* --------------------------------------------------------------------------- */
bool Pawn::checkAttack(string sq1, string sq2, 
		       map<string, ChessPiece *> &board) {
   map<string, ChessPiece *>::iterator i = board.find(sq2);
   if (i->second == NULL || (i->second)->getColour() == this->getColour()) {
     return 0; // Attack must be on opposing side and must be non-empty square.
   } else {
     return 1;
   }
}


/* --------------------------------------------------------------------------- */
/* Function to check a valid move for a Pawn. Since attacks are in a different
   direction for a Pawn, helper functions are useful. Returns true if the target
   square is within two forward moves if there is no piece in either the first
   as well as, if moving two squares, second square. */
/* --------------------------------------------------------------------------- */
bool Pawn::checkMove(string sq1, string sq2, map<string, ChessPiece *> &board, 
		     int dist) {
  
  for (char x = ((sq1[1]>sq2[1]) ? sq1[1] - dist : sq1[1] + 1); 
       x <= ((sq1[1]>sq2[1]) ? sq1[1] - 1 : sq2[1]);
       x++) 
  { 
    char sq[SQUARE_LENGTH] = {sq1[0], x, '\0'};
    map<string, ChessPiece *>::iterator i = board.find(sq); 
    if (i->second != NULL) {
      return 0; // Must move to an empty spot.
    }
  }

  return 1;
}


/* --------------------------------------------------------------------------- */
/* Prints Pawn, used to communicate with the players which piece is moving
   or if another piece is capturing it. */
/* --------------------------------------------------------------------------- */
void Pawn::printName() {
  cout << "Pawn";
}


/* --------------------------------------------------------------------------- */
/* Resolves a move for the Pawn, if firstMove is 1, sets firstMove to 0. If first
   move and moved 2 squares, sets passDanger to 1. If it is not the first move,
   and the passDanger is 1, set passDanger to 0. Used with en passant checks.*/
/* --------------------------------------------------------------------------- */
void Pawn::resolveMove(int dist) {
  if (this->firstMove == 1 && dist == 2) {
    this->passDanger = 1;
    this->setFirstMove();
    return;
  }
  if (this->firstMove == 0 && this->passDanger == 1) {
    this->passDanger = 0;
    return;
  }

  if (this->firstMove == 1) {
    this->setFirstMove();
  }
}


/* --------------------------------------------------------------------------- */
/* Function to check for an en passant move, must check that a diagonal move has
   an unoccupied target and the piece behind it is a Pawn of the opposing side
   with passDanger == 1. */
/* --------------------------------------------------------------------------- */
bool Pawn::checkEnPassant(string sq1, string sq2, map<string, ChessPiece*> &board) {
    map<string, ChessPiece *>::iterator a = board.find(sq2);
    if (a->second != NULL) {
      return 0; // if a piece occupies the target square then 
    }
    return 1;
}

/* --------------------------------------------------------------------------- */
/* Function to check for a valid pawn promotion move, if the pawn reaches one 
   end of the board or the other, returns True.*/
/* --------------------------------------------------------------------------- */
bool Pawn::checkPromotion(string sq) {
  if (this->colour == 'b' && sq[1] == '1') {
    return 1; 
  } else if (this->colour == 'w' && sq[1] == '8') {
    return 1;
  }

  return 0;
}

/* --------------------------------------------------------------------------- */
/* Function to check for a valid castling move, always returns false.*/
/* --------------------------------------------------------------------------- */
bool Pawn::checkCastling(string sq1, string sq2, 
			     map<string, ChessPiece*> &board) {
    return 0;
  }
