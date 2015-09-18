#include <iostream>
#include <string>
#include "host.h"
#include "router.h"
#include "message.h"

using namespace std;

/* --------------------------------------------------------------------------- */
/* Constructor function for a Host. Its connection is initialized to NULL. */
/* --------------------------------------------------------------------------- */
Host::Host(int n) : number(n), connection(NULL) {}

/* --------------------------------------------------------------------------- */
/* Function to return the Router* connection of a Host. */
/* --------------------------------------------------------------------------- */
Router* Host::getConnection() {
    return this->connection;
}

/* --------------------------------------------------------------------------- */
/* Function to return the int number of a Host. */
/* --------------------------------------------------------------------------- */
int Host::getNumber() {
    return this->number;
}

/* --------------------------------------------------------------------------- */
/* Function to reset the int number of a Host. */
/* --------------------------------------------------------------------------- */
void Host::setNumber(int num) {
  this->number = num;
}

/* --------------------------------------------------------------------------- */
/* Function used to update the Router* connection of a Host to set connection. */
/* --------------------------------------------------------------------------- */
void Host::connectTo(Router *r) {
    this->connection = r;
}

/* --------------------------------------------------------------------------- */
/* Function to reset the connection of a Host to NULL if it disconnects from 
   a Router. */
/* --------------------------------------------------------------------------- */
void Host::disconnectFrom(Router *r) {
    this->connection = NULL;
}

/* --------------------------------------------------------------------------- */
/* Function for a Host to send a Message to another Host. Takes an integer 
   as the destination Host number and a character string to produce a Message
   and forwards this to the Host's connection Router. */
/* --------------------------------------------------------------------------- */
void Host::send(int destination, const char* message) {
  cout << "Host " << this->getNumber() << " sent a message to Host " << destination << ": " << message << endl << endl;

  Message mess(this->getNumber(), destination, message);
  (this->connection)->receiveMessage(mess);
  
}

/* --------------------------------------------------------------------------- */
/* Function for when a Host receives a message. Prints confirmation of receipt
   and the Message contents to the screen. */
/* --------------------------------------------------------------------------- */
void Host::receiveMessage(Message &message) {

  cout << "Host " << this->getNumber() << " received a message from Host " << message.getSource() << ": ";
  message.printMessage();
  cout << endl;

}
