#include <iostream>
#include <map>
#include <cstring>

#include "ChessBoard.hpp"
#include "ChessPiece.hpp"

#include "Bishop.hpp"
#include "King.hpp"
#include "Knight.hpp"
#include "Pawn.hpp"
#include "Queen.hpp"
#include "Rook.hpp"

#define SQUARE_LENGTH 3

using namespace std;


/* --------------------------------------------------------------------------- */
/* Constructor function for ChessBoard. The first player to move is always white
   and initial board setup is always the same, black pieces in rank 7-8, white 
   pieces in rank 1-2.*/
/* --------------------------------------------------------------------------- */
ChessBoard::ChessBoard() : turn('w'), endgame(0) {
  char colour;
  // set up a board in the standard starting positions of chess pieces.
  for (char c = 'A'; c <= 'H'; c++) {
    for (int i = 8; i > 0; i--) {

      colour = ((i > 2) ? 'b' : 'w');
      ChessPiece *piece = NULL;
      if ((i > 2) && (i < 7)) {
	piece = NULL;
      } else if (i == 7 || i == 2) {
	piece = new Pawn(colour);
      } else if (c == 'A' || c == 'H') {
	piece = new Rook(colour);	
      } else if (c == 'B' || c == 'G') {
	piece = new Knight(colour);
      } else if (c == 'C' || c == 'F') {
	piece = new Bishop(colour);
      } else if (c == 'D') {
	piece = new Queen(colour);
      } else if (c == 'E') {
	piece = new King(colour);
      }
      char row = 48 + i;
      char square[SQUARE_LENGTH] = {c, row, '\0'};
      (this->board).insert(pair<string, ChessPiece *>(square, piece));
    }
  }
  
  // Enter the starting locations of the two Kings.
  (this->kingLocations).insert(pair<char, string>('w', "E1"));
  (this->kingLocations).insert(pair<char, string>('b', "E8"));

  cout << "A new chess game is started!" << endl;
}

/* --------------------------------------------------------------------------- */
/* Destructor function for ChessBoard. */
/* --------------------------------------------------------------------------- */
ChessBoard::~ChessBoard() {}

/* --------------------------------------------------------------------------- */
/* Function to reset a ChessBoard to the inital conditions, ready for a new game.
 */
/* --------------------------------------------------------------------------- */
void ChessBoard::resetBoard() {
  ChessBoard cp2;
  for (map<string, ChessPiece *>::iterator i = (this->board).begin();
       i != (this->board).end();
       i++) 
  {
    if (i->second != NULL) {
      delete i->second;
    }    
  }
  this->board = cp2.board;
  this->turn = 'w';
  this->kingLocations = cp2.kingLocations;
  this->endgame = 0;  
}


/* --------------------------------------------------------------------------- */
/* Function to print the contents of the board to the screen, showing both the 
   location of the pieces and the square names. */
/* --------------------------------------------------------------------------- */
void ChessBoard::printBoard() {
  int count = 1;
  for (map<string, ChessPiece *>::iterator i = (this->board).begin();
       i != (this->board).end();
       i++) 
  {
    cout << "|";
    if (i->second == NULL) {
      cout << " ";
    } else { 
      (i->second)->printPiece();
    }
    if (count == 8) {
      cout << endl;
      for (int col = 0; col < 16; col++) {
	cout << "_";
      }
      cout << endl;
      count = 0;
    }
    count++;
  }

  count = 1;
  for (map<string, ChessPiece *>::iterator i = (this->board).begin();
       i != (this->board).end();
       i++) 
  {
    cout << "|";
    cout << (i->first)[0] << (i->first)[1];
    if (count == 8) {
      cout << endl;
      for (int col = 0; col < 16; col++) {
	cout << "_";
      }
      cout << endl;
      count = 0;
    }
    count++;
  }
}


/* --------------------------------------------------------------------------- */
/* Function to verify the legality of and resolve moves submitted by the players.
   This is accomplished by first going through a series of checks to ensure the 
   submitted moves are acceptable given the conditions of the ChessBoard. It then
   checks the validity of the move via the behavior of the ChessPiece in question
   , please consult ChessPiece.hpp for these behaviors. It then checks whether 
   either player is in check, resolves a valid move, and checks for endgame 
   conditions. */
/* --------------------------------------------------------------------------- */
void ChessBoard::submitMove(const char *square1, const char *square2) {
  char col1, col2, row1, row2;
  
  // First, check if the Board has already reached an endgame scenario.
  if (this->endgame == 1) {
    cout << "This game is already finished." << endl;
    return;
  }

  // Then, ensure the two squares submitted are each two characters long, if not,
  // at least one move is invalid.
  if (strlen(square1)!=2 || strlen(square2)!=2) {
    cout << "Error: move invalid, square does not exist." << endl;
    return;
  }

  // Then, ensure the first characters in each square are between A and H or 
  // between a and h, if not, the square is invalid. Converts lowercase 
  // characters into uppercase characters.
  if (((square1[0] >= 'A' && square1[0] <= 'H') || 
      (square1[0] >= 'a' && square1[0] <= 'h')) 
      && ((square2[0] >= 'A' && square2[0] <= 'H') ||
	  (square2[0] >= 'a' && square2[0] <= 'h'))) 
  {
    col1 = ((square1[0] >= 'a') ? square1[0] - 32: square1[0]);
    col2 = ((square2[0] >= 'a') ? square2[0] - 32: square2[0]);
  } else {
    cout << "Error: column specified invalid." << endl;
    return;
  }
  
  //Then, ensure that the second character in each square is between '1' and '8'.
  if ((square1[1] >= '1' && square1[1] <= '8') && 
      (square2[1] >= '1' && square2[1] <= '8')) 
  {
    row1 = square1[1];  
    row2 = square2[1];
  } else {
    cout << "Error: row specified invalid." << endl;
    return;
  }
  char sq1[SQUARE_LENGTH] = {col1, row1, '\0'};
  char sq2[SQUARE_LENGTH] = {col2, row2, '\0'};

  // Ensures that the piece will actually end its move in a different square.
  if (!(strcmp(sq1,sq2))) {
    cout << "Error: piece does not move."<<endl;
    return;
  }

  // Find the square on the chessboard to ensure that there is indeed a piece in 
  // the first square.
  map<string, ChessPiece *>::iterator i = (this->board).find(sq1);

  if (i->second == NULL) {
    cout << "There is no piece at position "
	 << sq1[0] << sq1[1] << "!" << endl;
    return;
  }

  // Verify that the colour of the piece that is about to move matches the colour
  // of the current turn.
  if (turn != (i->second)->getColour()) {
    cout << "It is not " << ((turn == 'b') ? "White" : "Black")
	 << "'s turn to move!" << endl;
    return;
  }

  // Validate  move of the piece from sq1 to sq2, if the piece cannot do so as
  // determined by the behavior of the piece's type, then the move is invalid.
  if (!((i->second)->validateMove(sq1, sq2, this->board))) {
    cout << (((i->second)->getColour() == 'w') ? "White" : "Black") << "'s ";
    (i->second)->printName();
    cout << " cannot move to " << sq2[0] << sq2[1] << "!" << endl;
    return;
  }

  // If all previous checks have passed, we must now resolve the move and 
  // ensure a player is not producing a move that will leave the player's King 
  // in check. This is accomplished by first moving the piece to the second
  // square and checking for check. Note that we must keep track of the piece 
  // in the target square, as the result of this move may be invalid, and the 
  // pieces will need to be switched back. 
  map<string, ChessPiece *>::iterator a = (this->board).find(sq2);
  ChessPiece* target = a->second;
  
  // Find the location of the King whose colour matches the turn. 
  map<char, string>::iterator king_loc = (this->kingLocations).find(this->turn);
  
  //Necessary for moves which involve two pieces, castling and en passant.
  map<string, ChessPiece*>::iterator b;
  map<string, ChessPiece*>::iterator c;
  ChessPiece* secondPiece;
  bool castling = 0;

  // If the piece who is moving is the King, then make sure his entry in the 
  // location table is updated to reflect the move.
  if (!(king_loc->second).compare(i->first)) {
    if ((i->second)->checkCastling(sq1, sq2, board)) {
      castling = 1;
      char colr = ((sq1[0] < sq2[0]) ? 'H' : 'A');
      char colr_target = ((sq1[0] < sq2[0]) ? 'F' : 'D');
      char sqr[SQUARE_LENGTH] = {colr, sq1[1], '\0'};
      char sqr_tar[SQUARE_LENGTH] = {colr_target, sq1[1], '\0'};
      b = (this->board).find(sqr);
      c = (this->board).find(sqr_tar);
      if ((this->checkCheck((i->second)->getColour(), king_loc->second)) ||
	  (this->checkCheck((i->second)->getColour(), a->first)) ||
	  (this->checkCheck((i->second)->getColour(), c->first))) 
      {
	cout << "King cannot castle through check." << endl;
	return;
      }
      secondPiece = b->second;
      c->second = secondPiece; //switch the Rook and his castle position.
      b->second = NULL;
    }
    king_loc->second = a->first;
  }
  
  a->second = i->second;
  i->second = NULL;

  // Check to see if the move results in putting the player's King in check.
  // If it does, the move is invalid, switch back the piece and King locations
  // and return an error. Also, keep track of whether the opposing player's King 
  // is put into check by the move. 
  bool check = 0; 
  char colour = 'w';
  for (int x = 1; x<=2; x++) {
    king_loc = (this->kingLocations).find(colour);
    if (this->checkCheck(colour, king_loc->second)){
      if (this->turn == colour) {
	i->second = a->second;
	a->second = target;
	if (!(king_loc->second).compare(a->first)) {
	  king_loc->second = i->first;
	}
	cout << "This move would place your King in check." << endl;
	return;
      }
      check = 1;
    }
    colour = 'b';
  }
 
  // Now that the move has been shown to not place the player's King into check,
  // finish resolving the move, first switch the piece back to the current
  // position. 
  king_loc = (this->kingLocations).find(this->turn);
  if (!(king_loc->second).compare(a->first)) {
    if (castling == 1) {
      c->second = NULL; //switch the Rook back.
      b->second = secondPiece;      
    }
    king_loc->second = i->first;
  }  
  i->second = a->second;
  a->second = target;
  
  // Print the name of the piece, its current location, and location at the end
  // of the move.
  cout << (((i->second)->getColour() == 'w') ? "White" : "Black") << "'s ";
  (i->second)->printName();
  cout << " moves from " << sq1[0] << sq1[1] << " to " << sq2[0] << sq2[1];
  
  // If the second square is occupied, it must be because it is a piece of the
  // opposing side, print the name of the piece which is to be taken.
  if (a->second != NULL) {
    cout << " taking " << (((a->second)->getColour() == 'w') ? "White" : "Black") << "'s ";
    (a->second)->printName();
  }
  cout << endl; 
  
  // Next, resolve the move on the ChessBoard's board, switch the pieces an
  // update the King's location if necessary.
  if (a->second != NULL) {
    delete a->second;
  }
  a->second = i->second;
  i->second = NULL;
  
  king_loc = (this->kingLocations).find(this->turn);
  if (!(king_loc->second).compare(i->first)) {
    if (castling == 1) {
      cout << (((b->second)->getColour() == 'w') ? "White" : "Black") << "'s ";
      (b->second)->printName();
      cout << " moves from " << b->first  << " to " << c->first << endl;     
      c->second = secondPiece; //switch the Rook and his castle position.
      b->second = NULL;
    }
    king_loc->second = a->first;
  }

  // Finally, compute the row distance traveled by the piece and resolve any
  // internal characteristics according to the piece's type.
  int dist = ((sq2[1] > sq1[1]) ? sq2[1]-sq1[1] : sq1[1]-sq2[1]);
  (a->second)->resolveMove(dist);

  // Now, check if a the move implies a pawn promotion.
  if ((a->second)->checkPromotion(sq2)) {
    cout << ((turn == 'b') ? "Black" : "White") << "'s " ;
    (a->second)->printName();
    cout << " has may be promoted. Which piece should it be promoted to?" 
	 << endl;
    char x;
    while (x!='B' && x!='K' && x!='Q' && x!='R') {
      cout << "Enter (B,K,Q,R)" << endl;
      cin >> x;
    }
    ChessPiece *newPiece;
    if (x == 'B') {
      newPiece = new Bishop(turn);
    } else if (x == 'K') {
      newPiece = new Knight(turn);
    } else if (x == 'Q') {
      newPiece = new Queen(turn);
    } else if (x == 'R') {
      newPiece = new Rook(turn);
    }
    
    a->second = newPiece;
    cout << ((turn == 'b') ? "Black" : "White") << " ";
    (a->second)->printName();
    cout << " now at " << sq2[0] << sq2[1] << endl;
    
    char inCheck = ((turn == 'w') ? 'b' : 'w');    
    king_loc = (this->kingLocations).find(inCheck);
    
    if (this->checkCheck(inCheck, king_loc->second)){    
      check = 1;
    }
  }

  // Now, check for the endgame conditions of checkmate and stalemate.
  // First, check for checkmate, if check == 1, then the opposing player is in 
  // check, verify that they are not also in checkmate.
  if (check == 1) { 
    char inCheck = ((turn == 'w') ? 'b' : 'w');
    king_loc = (this->kingLocations).find(inCheck);

    if (this->checkCheckmate(inCheck, king_loc->second)) {
      cout << ((turn == 'w') ? "Black" : "White") << " is in checkmate" << endl;
      return;
    } else {
      cout << ((turn == 'w') ? "Black" : "White") << " is in check" << endl;
    }
  }

  // Even if the opposing player is not in check, it is possible the game will 
  // end via stalemate if every possible move of the opposing player would result
  // in check from the current board position.
  char inStalemate = ((turn == 'w') ? 'b' : 'w');
  king_loc = (this->kingLocations).find(inStalemate);

  if (this->checkCheckmate(inStalemate, king_loc->second)) {
    cout << ((turn == 'w') ? "Black" : "White") << " is in stalemate" << endl;
    return;
  }

  // Increment the turn.
  this->nextTurn();
}


/* --------------------------------------------------------------------------- */
/* Function to increment the turn of the ChessBoard, if the turn is 'w', then 
   will switch to 'b', or if 'b', then 'w'. */
/* --------------------------------------------------------------------------- */
void ChessBoard::nextTurn() {
  this->turn = ((this->turn == 'b') ? 'w' : 'b');
}


/* --------------------------------------------------------------------------- */
/* Function to check if the current position of the board leaves the side,
   colour, in check. It does this by looping through all the pieces of the
   opposing side on the board and asking if they are able to make an attack on 
   colour's King. If at least one can, then the player colour is in check. */   
/* --------------------------------------------------------------------------- */
bool ChessBoard::checkCheck(char colour, string loc_king) {
  for (map<string, ChessPiece *>::iterator i = (this->board).begin();
       i != (this->board).end();
       i++)
  {
    if ((i->second == NULL)) {
      continue; // If there is no piece in the square continue.
    }

    if (colour != (i->second)->getColour()) {
      if ((i->second)->validateMove(i->first, loc_king, this->board)) {
	return 1; // If at least one opposing piece has a line of attack to the 
	          // King, then colour is in check.
      }
    }
  }
  
  // If no opposing piece can attack the King, then the move does not result in 
  // check.
  return 0;
}


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
bool ChessBoard::checkCheckmate(char colour, string loc_king) {
  // First, loop through all of the possible moves for the King.
  char row_min = ((loc_king[1] > '1') ? loc_king[1] - 1 : loc_king[1]);
  char row_max = ((loc_king[1] < '8') ? loc_king[1] + 1 : loc_king[1]);
  char col_min = ((loc_king[0] > 'A') ? loc_king[0] - 1 : loc_king[0]);
  char col_max = ((loc_king[0] < 'H') ? loc_king[0] + 1 : loc_king[0]);
  
  map<string, ChessPiece *>::iterator i = (this->board).find(loc_king);
  ChessPiece *king = i->second;

  for (char x = row_min; x <= row_max; x++) {
    for (char y = col_min; y <= col_max; y++) {      

      char sq[SQUARE_LENGTH] = {y, x, '\0'};   
      map<string, ChessPiece *>::iterator a = (this->board).find(sq);
      ChessPiece *potential = a ->second;   
      
      // swap the King and the potential location, if it's a valid move, then 
      // check if he is in check, swap the pieces back and continue if he is.
      if ((king->validateMove(loc_king, sq, this->board))) {

	a->second = king;
	i->second = NULL; 

	if (!(this->checkCheck(colour, sq))) {
	  i->second = king;
	  a->second = potential;
	  return 0; // If the King can move out of check then, it is not checkmate
	  } 

	i->second = king;
	a->second = potential;

      }
    }
  }

  // Now, loop through all pieces on the board on the same side.   
  for (map<string, ChessPiece *>::iterator other = (this->board).begin();
       other != (this->board).end();
       other++) 
  {
    if (other->second == NULL || (other->second)->getColour() != colour) {
      continue; // if there is no piece in the square or it is of the opposing
                // side, continue. 
    }
    if (!(other->first).compare(loc_king)) {
      continue; // if the piece is the King for the side in question, continue
                // since it has already been checked if it can move.
    }

    // Now, for each square on the board, see if the piece can legally move to 
    // it and then check if the King is in check. The first piece that can 
    // legally move and not leave the King in check means the side is not in 
    // checkmate or stalemate.
    for (char x = '1'; x <= '8'; x++) {
      for (char y = 'A'; y <= 'H'; y++) {
	char sq[SQUARE_LENGTH] = {y, x, '\0'};   	
	if (((other->second)->validateMove(other->first, sq, this->board))) {	
	  map<string, ChessPiece *>::iterator a = (this->board).find(sq);
	  ChessPiece *potential = a ->second;   
	  a->second = other->second;
	  other->second = NULL;
	  if (!(this->checkCheck(colour, loc_king))) {
	    other->second = a->second;
	    a->second = potential;
	    return 0; // If a piece can move so there is no check then, it is not
	              // checkmate or stalemate.	  
	  }
	  other->second = a->second;
	  a->second = potential;	  
	}
      }
    }
  }

  // If there does not exist a legal move that does not leave the side in check,
  // then the board has reached an endgame condition.
  this->endgame = 1;
  return 1;
}


/* --------------------------------------------------------------------------- */
/* Helper function to update the location of a King in the ChessBoard's 
   kingLocations map. */
/* --------------------------------------------------------------------------- */
void ChessBoard::updateKingLoc(char colour, string square) {
  map<char, string>::iterator i = (this->kingLocations).find(colour);
  i->second = square;
}


/* --------------------------------------------------------------------------- */
/* Helper function to return the location of a King in the ChessBoard's 
   kingLocations map. */
/* --------------------------------------------------------------------------- */
string ChessBoard::returnKingLoc(const char colour) {
  map<char, string>::iterator i = (this->kingLocations).find(colour);
  return i->second;
}

