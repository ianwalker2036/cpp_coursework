#ifndef CHESSPIECE_HPP
#define CHESSPIECE_HPP

#include <cstring>
#include <map> 
#include <iostream>

using namespace std;

class ChessPiece {
protected:
  bool firstMove; // bool to keep track of whether the ChessPiece has been moved.
  char colour; // char to indicate the side the ChessPiece belongs to.

public:
/* --------------------------------------------------------------------------- */
/* Constructor function for ChessPiece. Initializes the pieces colour and sets 
   firstMove to 1. */
/* --------------------------------------------------------------------------- */
  ChessPiece(char c);

/* --------------------------------------------------------------------------- */
/* Destructor function for ChessPiece. */
/* --------------------------------------------------------------------------- */
  virtual ~ChessPiece(); 

/* --------------------------------------------------------------------------- */
/* Virtual function to validate a move from the ChessBoard, behavior entirely 
   determined by the subclasses.  */
/* --------------------------------------------------------------------------- */
  virtual bool validateMove(string sq1, string sq2, 
			    map<string, ChessPiece *> &board) = 0;

/* --------------------------------------------------------------------------- */
/* Virtual function to print the unicode character representing the ChessPiece, 
   behavior entirely determined by the subclasses.  */
/* --------------------------------------------------------------------------- */
  virtual void printPiece() = 0;

/* --------------------------------------------------------------------------- */
/* Virtual function to print the name representing the ChessPiece, 
   behavior entirely determined by the subclasses.  */
/* --------------------------------------------------------------------------- */
  virtual void printName() = 0;

/* --------------------------------------------------------------------------- */
/* Virtual function to resolve a move which involved the ChessPiece, 
   behavior entirely determined by the subclasses.  */
/* --------------------------------------------------------------------------- */
  virtual void resolveMove(int dist) = 0;

/* --------------------------------------------------------------------------- */
/* Virtual function to check for a valid en passant move, 
   behavior entirely determined by the subclasses.  */
/* --------------------------------------------------------------------------- */
  virtual bool checkEnPassant(string sq1, string sq2, 
			      map<string, ChessPiece*> &board) = 0;

/* --------------------------------------------------------------------------- */
/* Function to return the char colour of a ChessPiece. */
/* --------------------------------------------------------------------------- */
  char getColour();

/* --------------------------------------------------------------------------- */
/* Function to update the attribute firstMove of a ChessPiece. */
/* --------------------------------------------------------------------------- */
  void setFirstMove();

/* --------------------------------------------------------------------------- */
/* Virtual function to check for a valid pawn promotion move, 
   behavior entirely determined by the subclasses.  */
/* --------------------------------------------------------------------------- */
  virtual bool checkPromotion(string sq) = 0;

/* --------------------------------------------------------------------------- */
/* Function to return the bool firstMove of a ChessPiece. */
/* --------------------------------------------------------------------------- */
  bool getFirstMove();

  virtual bool checkCastling(string sq1, string sq2, 
			      map<string, ChessPiece*> &board)=0;
};

#endif
