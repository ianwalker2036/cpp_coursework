#ifndef HOST_H
#define HOST_H
#include <string>

using namespace std;

class Router;
class Message;

class Host {
private:
  int number;         // int to represent the Host's adress. 

  Router* connection; // pointer to the Router to which the Host is connected.

public:
/* --------------------------------------------------------------------------- */
/* Constructor function for a Host. Its connection is initialized to NULL. */
/* --------------------------------------------------------------------------- */
  Host(int n);

/* --------------------------------------------------------------------------- */
/* Function to return the Router* connection of a Host. */
/* --------------------------------------------------------------------------- */
  Router* getConnection();

/* --------------------------------------------------------------------------- */
/* Function to return the int number of a Host. */
/* --------------------------------------------------------------------------- */
  int getNumber();

/* --------------------------------------------------------------------------- */
/* Function to reset the int nxumber of a Host. */
/* --------------------------------------------------------------------------- */
  void setNumber(int num);

/* --------------------------------------------------------------------------- */
/* Function used to update the Router* connection of a Host to set connection. */
/* --------------------------------------------------------------------------- */
  void connectTo(Router *r);

/* --------------------------------------------------------------------------- */
/* Function to reset the connection of a Host to NULL if it disconnects from 
   a Router. */
/* --------------------------------------------------------------------------- */
  void disconnectFrom(Router *r);

/* --------------------------------------------------------------------------- */
/* Function for a Host to send a Message to another Host. Takes an integer 
   as the destination Host number and a character string to produce a Message
   and forwards this to the Host's connection Router. */
/* --------------------------------------------------------------------------- */
  void send (int destination, const char* message);

/* --------------------------------------------------------------------------- */
/* Function for when a Host receives a message. Prints confirmation of receipt
   and the Message contents to the screen. */
/* --------------------------------------------------------------------------- */
  void receiveMessage(Message &message);
};

#endif
