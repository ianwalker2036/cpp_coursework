#include <iostream>
#include <vector>
#include <string.h>

#include "message.h"

using namespace std;

/* --------------------------------------------------------------------------- */
/* Constructor function for a Message. This requires a source Host int adress,
   a destination Host int adress, and a character string for a message. It
   dynamically allocates memory for a character array of the message string a 
   Host wishes to send. */
/* --------------------------------------------------------------------------- */
Message::Message(int s, int d, const char *mess) {
    this->message = new char [strlen(mess)+1];
    strcpy(this->message, mess);
    this->source = s;
    this->destination = d;
}

/* --------------------------------------------------------------------------- */
/* Destructor function for a Message. Since a Message dynamically allocates 
   memory on the heap for the message string, the called destructor must delete
   this memory, lest it create a memory leak. */
/* --------------------------------------------------------------------------- */
Message::~Message() {
    delete [] message;
}

/* --------------------------------------------------------------------------- */
/* Function to print the contents of the Message's string to the screen. */
/* --------------------------------------------------------------------------- */
void Message::printMessage() {
    cout << message <<endl;
}

/* --------------------------------------------------------------------------- */
/* Function to return the int address of the destination Host. */
/* --------------------------------------------------------------------------- */
int Message::getDestination() {
  return destination;
}

/* --------------------------------------------------------------------------- */
/* Function to return the int address of the source Host. */
/* --------------------------------------------------------------------------- */
int Message::getSource() {
  return source;
}

