#ifndef CHESSBOARD_HPP
#define CHESSBOARD_HPP
#include <iostream>
#include <map>

using namespace std;

class ChessPiece;

class ChessBoard {
private:
  char turn; // char to keep track of the current turn, 'w' or 'b'.

  bool endgame; // bool to keep track of whether an endgame condition has 
                // been triggered.

  map <string, ChessPiece *> board; // map with string, corresponding to a square 
                                    // on a chess board of form file-rank, paired
                                    // with a pointer to a ChessPiece.

  map <char, string> kingLocations; // Because of the importance of the King to
                                    // the endgame conditions, this map keeps 
                                    // track of 
public:
/* --------------------------------------------------------------------------- */
/* Constructor function for ChessBoard. The first player to move is always white
   and initial board setup is always the same, black pieces in rank 7-8, white 
   pieces in rank 1-2.*/
/* --------------------------------------------------------------------------- */
  ChessBoard();

/* --------------------------------------------------------------------------- */
/* Destructor function for ChessBoard. */
/* --------------------------------------------------------------------------- */
  ~ChessBoard();

/* --------------------------------------------------------------------------- */
/* Function to reset a ChessBoard to the inital conditions, ready for a new game.
 */
/* --------------------------------------------------------------------------- */
  void resetBoard();

/* --------------------------------------------------------------------------- */
/* Function to print the contents of the board to the screen, showing both the 
   location of the pieces and the square names. */
/* --------------------------------------------------------------------------- */
  void printBoard();

/* --------------------------------------------------------------------------- */
/* Function to verify the legality of and resolve moves submitted by the players.
   This is accomplished by first going through a series of checks to ensure the 
   submitted moves are acceptable given the conditions of the ChessBoard. It then
   checks the validity of the move via the behavior of the ChessPiece in question
   , please consult ChessPiece.hpp for these behaviors. It then checks whether 
   either player is in check, resolves a valid move, and checks for endgame 
   conditions. */
/* --------------------------------------------------------------------------- */
  void submitMove(const char *square1, const char *square2);

/* --------------------------------------------------------------------------- */
/* Function to increment the turn of the ChessBoard, if the turn is 'w', then 
   will switch to 'b', or if 'b', then 'w'. */
/* --------------------------------------------------------------------------- */
  void nextTurn();

/* --------------------------------------------------------------------------- */
/* Function to check if the current position of the board leaves the side,
   colour, in check. It does this by looping through all the pieces of the
   opposing side on the board and asking if they are able to make an attack on 
   colour's King. If at least one can, then the player colour is in check. */   
/* --------------------------------------------------------------------------- */
  bool checkCheck(char colour, string loc_king);

/* --------------------------------------------------------------------------- */
/* Function to check if the current position of the board leaves the side,
   colour, in checkmate. It is also used to determine stalemate, since stalemate 
   occurs under the same conditions except colour's King is not in check. It does 
   this by first checking if the King has a move that would not put him in check. 
   Then, it loops through all the pieces belonging to colour and checks each of 
   their possible moves, to see if any can change to position of the board such
   that the King is not in check. If at least one can, then the player colour is 
   not in checkmate or stalemate. */   
/* --------------------------------------------------------------------------- */
  bool checkCheckmate(char colour, string loc_king);

/* --------------------------------------------------------------------------- */
/* Helper function to update the location of a King in the ChessBoard's 
   kingLocations map. */
/* --------------------------------------------------------------------------- */
  void updateKingLoc(char colour, string square);

/* --------------------------------------------------------------------------- */
/* Helper function to return the location of a King in the ChessBoard's 
   kingLocations map. */
/* --------------------------------------------------------------------------- */
  string returnKingLoc(const char colour);

};

#endif
