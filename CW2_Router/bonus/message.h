#ifndef MESSAGE_H
#define MESSAGE_H

#include <vector>

using namespace std;

class Message {
private:
  int source;      // int to keep track of a Message's source Host.

  int destination; // int to keep track of a Message's destination Host.

  char *message;   // Points to a dynamically allocated character array.

public:

/* --------------------------------------------------------------------------- */
/* Constructor function for a Message. This requires a source Host int adress,
   a destination Host int adress, and a character string for a message. It
   dynamically allocates memory for a character array of the message string a 
   Host wishes to send. */
/* --------------------------------------------------------------------------- */
  Message(int s, int d, const char *mess);

/* --------------------------------------------------------------------------- */
/* Destructor function for a Message. Since a Message dynamically allocates 
   memory on the heap for the message string, the called destructor must delete
   this memory, lest it create a memory leak. */
/* --------------------------------------------------------------------------- */
  ~Message();

/* --------------------------------------------------------------------------- */
/* Function to print the contents of the Message's string to the screen. */
/* --------------------------------------------------------------------------- */
  void printMessage();

/* --------------------------------------------------------------------------- */
/* Function to return the int address of the destination Host. */
/* --------------------------------------------------------------------------- */
  int getDestination();

/* --------------------------------------------------------------------------- */
/* Function to return the int address of the source Host. */
/* --------------------------------------------------------------------------- */
  int getSource();
};

#endif
