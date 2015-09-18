#include "ChessPiece.hpp"

using namespace std;


/* --------------------------------------------------------------------------- */
/* Constructor function for ChessPiece. Initializes the pieces colour and sets 
   firstMove to 1. */
/* --------------------------------------------------------------------------- */
ChessPiece::ChessPiece(char c) : firstMove(1), colour(c) {}

/* --------------------------------------------------------------------------- */
/* Destructor function for ChessPiece. */
/* --------------------------------------------------------------------------- */
ChessPiece::~ChessPiece() {}

/* --------------------------------------------------------------------------- */
/* Function to return the char colour of a ChessPiece. */
/* --------------------------------------------------------------------------- */
char ChessPiece::getColour() {
  return this->colour;
}

/* --------------------------------------------------------------------------- */
/* Function to return the bool firstMove of a ChessPiece. */
/* --------------------------------------------------------------------------- */
bool ChessPiece::getFirstMove() {
  return this->firstMove;
}


/* --------------------------------------------------------------------------- */
/* Function to update the attribute firstMove of a ChessPiece. */
/* --------------------------------------------------------------------------- */
void ChessPiece::setFirstMove() {
  if (this->firstMove == 1) {
    this->firstMove = 0;
  }
}
