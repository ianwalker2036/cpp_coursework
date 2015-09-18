/* NOTE: SOME PARTS OF CODE MAY BE A BIT COMPLEX, BUT THE INTENTION IS TO HAVE A
   PROGRAM THAT ALLOWS FOR THE CREATION OF AS MANY NETWORKS MADE OF ROUTERS AND 
   HOSTS AS DESIRED, BUT DOES NOT RELY ON A SINGLE CLASS KNOWING ALL OF THESE
   OBJECTS IN EXISTENCE. INSTEAD, THIS CODE CHECKS FOR ADDRESS CLASHES AS 
   POTENTIAL CONNECTIONS BETWEEN NETWORKS ARE MADE.
*/

#ifndef ROUTER_H
#define ROUTER_H
#include <string>
#include <vector>
#include <map>

using namespace std;

class Host;
class Message;

class Router {
private:
  int number;                           // int represents the address of Router.

  bool asked;                           // bool used to terminate certain
                                        // functions, specifically 
                                        // isRouterInNetwork().

  multimap<int, vector<int> > routeMap; // Keeps track of all possible routes to
                                        // all possible Hosts connected to the
                                        // Router directly, or indirectly via 
                                        // connected Routers. The key int is the 
                                        // address of a Host. The route is a 
                                        // vector of integers whose last entry is
                                        // the Host address, and the preceding
                                        // the Routers needed to pass through.

  multimap<int, Router *> neighborRouters; // Keeps track of all Routers a Router
                                           // is connected to. The Key is the int
                                           // address of a Router, which is 
                                           // associated with the Router's memory
                                           // address.

  multimap<int, Host*> neighborHosts; // Keeps trak of all Hosts the Router is 
                                      // directly connected to. The key is the
                                      // int address of a Host, which is 
                                      // associated with the Host's memory 
                                      // address.
public:
/* --------------------------------------------------------------------------- */
/* Constructor function for Router. */
/* --------------------------------------------------------------------------- */
  Router(int n);

/* --------------------------------------------------------------------------- */
/* Function to return the int number of the Router. */
/* --------------------------------------------------------------------------- */
  int getNumber();

/* --------------------------------------------------------------------------- */
/* Function to return the bool asked of the Router. */
/* --------------------------------------------------------------------------- */
  bool getAsked();

/* --------------------------------------------------------------------------- */
/* Function to reset the bool asked of the Router. */
/* --------------------------------------------------------------------------- */
  void setAsked(bool a);
  
/* --------------------------------------------------------------------------- */
/* Function to Connect two Routers together by swapping their route tables:
   the function checks for various invalid scenarios, then updates the routers'
   neighborRouters, and transmit routeMap to each other.*/
/* --------------------------------------------------------------------------- */
  void connectTo(Router &r);

/* --------------------------------------------------------------------------- */
/* This function sends a route to a Router, which then checks the route before 
   adding the route to its routeMap. */
/* --------------------------------------------------------------------------- */
  void transmitRoutes();

/* --------------------------------------------------------------------------- */
/* This function sends a route to a Router, which then checks the route before 
   adding the route to its routeMap. */
/* --------------------------------------------------------------------------- */
  void updateNeighbor(Router *r, vector<int> v);

/* --------------------------------------------------------------------------- */
/* This function connects a Router to a Host: the function first checks for 
   invalid scenarios, then updates its neighborHosts table, and updates the
   routers in its routeMap of the new connection.*/
/* --------------------------------------------------------------------------- */
  void connectTo(Host &h);

/* --------------------------------------------------------------------------- */
/* Function to disconnect a Host from a Router: removes the entries associated
   with the Host from the Router's neighborHost and routeMap, then updates 
   the router's neighbor routers about the disconnection. */
/* --------------------------------------------------------------------------- */
  void disconnect(Host &h);

/* --------------------------------------------------------------------------- */
/* This function allows a router to process an alert about a connection
   deletion from a neighbor, and update its neighbors about the deletion. */
/* --------------------------------------------------------------------------- */
  void updateNeighborDisconnectHost(Router *r, Host &h);

/* --------------------------------------------------------------------------- */
/* Function to disconnect a Router from a Router: the function first checks for 
   invalid scenarios, then updates its neighborHosts table, and updates the
   routers in its routeMap of the removed connections */
/* --------------------------------------------------------------------------- */
  void disconnectFrom(Router &r);

/* --------------------------------------------------------------------------- */
/* This function is used to update a router of a deleted connection between 
   two routers. This is accomplished by searching the Router's routeMap for all
   instances of the connection: either (router1, router2) or (router2, router1)
   in its routes and removing these entries. If no such entries are found, the
   function call terminates. The router then updates all its neighbor routers of 
   the deleted connection. */
/* --------------------------------------------------------------------------- */
  void updateNeighborDisconnectRouter(int num_router1, int num_router2);

/* --------------------------------------------------------------------------- */
/* This function dictates the actions of a Router when it receives a Message 
   either from a Host or from another Router. If there is no connection to the 
   destination Host, the router outputs an error message. If the Router is 
   connected to the destination Host directly, it forwards the message to the 
   Host. Otherwise, it finds the shortest route to the destination Host from its
   routeMap and passes the Message to the next router in the route. */
/* --------------------------------------------------------------------------- */
  void receiveMessage(Message &message);

/* --------------------------------------------------------------------------- */
/* Function to check if two Routers are connect within the same network, if so
   then returns TRUE. Is used when checking if a connection is being attempted 
   between two Routers in which the addresses of other Routers maybe the same. */
/* --------------------------------------------------------------------------- */
  bool isRouterInNetwork(int num, Router* R);

/* --------------------------------------------------------------------------- */
/* Function used to reset the asked attribute of all Routers in a network, must
   be used after the isRouterInNetwork() function is called.*/
/* --------------------------------------------------------------------------- */
  void resetAsked();

/* --------------------------------------------------------------------------- */
/* Function to check if a certain router with addres num appears in a Router's
   routeMap, if so returns TRUE. This function is used with isRouterInNetwork()
   to distinguish cases in which two separate networks attempt to connect, but
   they contain Routers with the same network addresses. */
/* --------------------------------------------------------------------------- */
  bool isRouterInTable(int num);

/* --------------------------------------------------------------------------- */
/* Function to check if two separate networks are attempting to combine, but 
   they contain Router addresses that are the same, if so returns TRUE. If so, 
   throws an error message as this case would lead to address confusion within
   networks. */
/* --------------------------------------------------------------------------- */
  bool checkIfNetworkCombineSameRouters(Router *other_router);

/* --------------------------------------------------------------------------- */
/* Function to check if two separate networks are attempting to combine, but 
   they contain Host addresses that are the same, if so returns TRUE. If so, 
   throws an error message as this case would lead to address confusion within
   networks. */
/* --------------------------------------------------------------------------- */
  bool checkIfNetworkCombineSameHosts(Router *other_router);

/* --------------------------------------------------------------------------- */
/* Prints the contents of a Router's routing table:[host_number, [route]]. */
/* --------------------------------------------------------------------------- */
  void printRoutingTable(); 

/* --------------------------------------------------------------------------- */
/* Prints the contents of a Router's neighboring routers table:
   (router_number, ...). */
/* --------------------------------------------------------------------------- */
  void printNeighborTable();

/* --------------------------------------------------------------------------- */
/* Prints the contents of a Router's neighboring Hosts table:
   (host_number, ...). */
/* --------------------------------------------------------------------------- */
  void printNeighborHostsTable();

};

#endif
