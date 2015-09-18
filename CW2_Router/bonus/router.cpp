#include <iostream>
#include <string>
#include <vector>
#include <map>

#include "router.h"
#include "host.h"
#include "message.h"


using namespace std;

/* --------------------------------------------------------------------------- */
/* Constructor function for Router. */
/* --------------------------------------------------------------------------- */
Router::Router(int n) : number(n), asked(0) {}

/* --------------------------------------------------------------------------- */
/* Function to return the int number of the Router. */
/* --------------------------------------------------------------------------- */
int Router::getNumber() {
  return this->number;
}

bool Router::getAsked() {
  return this->asked;
}

void Router::setAsked(bool a) {
  this->asked = a;
}
/* --------------------------------------------------------------------------- */
/* Function to Connect two Routers together by swapping their route tables:
   the function checks for various invalid scenarios, then updates the routers'
   neighborRouters, and transmit routeMap to each other.*/
/* --------------------------------------------------------------------------- */
void Router::connectTo(Router &r) {
  
  Router *other_router = &r;

  // Check to see if a Router is attempting to connect to itself.
  if (other_router == this) {
    cout << "Sorry, a router cannot connect to itself." << endl;
    return;
  }
  // Check to see if the Router is attempting to connect to a Router with the 
  // same address.
  if (other_router->getNumber() == this->getNumber()) {
    cout << "Sorry, these routers are not the same, but have the same network "
         << "address, so cannot connect." << endl;
    return;
  }
  
  // Now check to see if two separate networks are attempting to connect to 
  // each other, but contain Routers with the same network addresses. 

  if (this->checkIfNetworkCombineSameRouters(other_router)) {
    return;
  }
  if (other_router->checkIfNetworkCombineSameRouters(this)) {
    return;
  }

  // Now check to see if two separate networks are attempting to connect to 
  // each other, but each ontain a Host with the same network address.
  if (this->checkIfNetworkCombineSameHosts(other_router)) {
    return;
    } 
  
  // IF ALL CHECKS PASS, update neighbor tables and transmit routes.
  (this->neighborRouters).insert(
				 pair<int, Router *>
				 (other_router->getNumber(), other_router));

  (other_router->neighborRouters).insert(
					 pair<int, Router*>
					 (this->getNumber(), this));

  this->transmitRoutes();

  other_router->transmitRoutes();

}

/* --------------------------------------------------------------------------- */
/* This function sends all the routes in a Router's routeMap to each Router 
   in its neighborTable. */
/* --------------------------------------------------------------------------- */
void Router::transmitRoutes() {
  for (multimap<int, vector<int> >::iterator i = (this->routeMap).begin();
       i != (this->routeMap).end();
       i++) 
  {
    vector<int> route = i->second;
    route.insert(route.begin(), this->getNumber());
    for (multimap<int, Router *>::iterator ri = (this->neighborRouters).begin();
	 ri != (this->neighborRouters).end();
         ri++) 
    {
      this->updateNeighbor(ri->second, route);
    }
  }
}

/* --------------------------------------------------------------------------- */
/* This function sends a route to a Router, which then checks the route before 
   adding the route to its routeMap. */
/* --------------------------------------------------------------------------- */
void Router::updateNeighbor(Router *r, vector<int> v) {

  // First, we check the route to see if the Router is included, if so the call 
  // ends. This ensures that the process of transmitting routes terminates. 
  for(vector<int>::iterator i = v.begin();
      i != v.end() - 1; // Since the routes include a Host as final entry, need 
                        // to terminate loop BEFORE final entry is checked. 
      i++)
  {
    if (*i == r->getNumber()) {
      return; 
    }
  }
  
  // Second, we check the exisiting routeMap for exact copies of the route, 
  // if so the call ends. This prevents multiple copies of the same route in a 
  // router's routeMap.
  pair<multimap<int,vector<int> >::iterator, 
       multimap<int,vector<int> >::iterator> range;
  range = (r->routeMap).equal_range(*(v.end()-1));

  for (multimap<int,vector<int> >::iterator i = range.first;
       i != range.second;
       i++) 
  {
    if (i->second == v) return;
  }

  // Finally, we add the route to the Router's routeMap in the form:
  // <Host id, route>, and recurse for all the Router's neighbors.

  (r->routeMap).insert(pair<int, vector<int> >(*(v.end()-1), v));
  v.insert(v.begin(), r->getNumber());

  for(multimap<int, Router *>::iterator i = (r->neighborRouters).begin();
      i != (r->neighborRouters).end();
      i++) 
  {
    updateNeighbor(i->second, v);
  }
}

/* --------------------------------------------------------------------------- */
/* This function connects a Router to a Host: the function first checks for 
   invalid scenarios, then updates its neighborHosts table, and updates the
   routers in its routeMap of the new connection.*/
/* --------------------------------------------------------------------------- */
void Router::connectTo(Host &h) {

  if ((this->routeMap).count(h.getNumber()) > 0) {
    if (h.getConnection() != NULL) {
      cout << "Sorry, but you must disconnect from your current router and " 
           << "reconnect." << endl;
      return;
    } else {
      cout << "Sorry, but you are currently using a name already in the network,"
	   << " this must be reassigned." << endl;
      return;
    }
  }
  
  // Update neighborHosts table.
  (this->neighborHosts).insert(pair<int, Host*>(h.getNumber(), &h));

  // Add entry to the routeMap.
  vector<int> route (1); 
  *(route.begin()) = h.getNumber();
  (this->routeMap).insert(pair<int, vector<int> >(h.getNumber(), route));

  // Have the Host update its connection.
  h.connectTo(this);

  // Update the Router's neighbors of the new connection.
  route.insert(route.begin(), this->getNumber());
  for (multimap<int, Router *>::iterator ri = (this->neighborRouters).begin();
       ri != (this->neighborRouters).end();
       ri++) 
  {
    this->updateNeighbor(ri->second, route);
  }
}

/* --------------------------------------------------------------------------- */
/* Function to disconnect a Host from a Router: removes the entries associated
   with the Host from the Router's neighborHost and routeMap, then updates 
   the router's neighbor routers about the disconnection. */
/* --------------------------------------------------------------------------- */
void Router::disconnect(Host &h) {
  // Check if the Host is actually connected to the Router, if not throw error.
  if ((this->neighborHosts).count(h.getNumber()) == 0) {
    cout << "Sorry, but Host " << h.getNumber() << " is not connected to Router "
         << this->getNumber() << ", so cannot disconnect from it." << endl;
    return;
  }

  // Remove the connection from neighborHosts, routeMap, and the Host. 
  (this->neighborHosts).erase(h.getNumber());
  (this->routeMap).erase(h.getNumber());

  h.disconnectFrom(this);
  
  // Update the Router's neighbors of the deletion of the connection.
  for (multimap<int, Router *>::iterator ri = (this->neighborRouters).begin();
       ri != (this->neighborRouters).end();
       ri++) 
  {
    this->updateNeighborDisconnectHost(ri->second, h);
  }
}

/* --------------------------------------------------------------------------- */
/* This function allows a router to process an alert about a connection
   deletion from a neighbor, and update its neighbors about the deletion. */
/* --------------------------------------------------------------------------- */
void Router::updateNeighborDisconnectHost(Router *r, Host &h) {
  // If the Host does not appear in its routeMap, end function call.
  if ((r->routeMap).count(h.getNumber()) == 0) {
    return;
  }

  (r->routeMap).erase(h.getNumber());
  
  for (multimap<int, Router *>::iterator ri = (r->neighborRouters).begin();
       ri != (r->neighborRouters).end();
       ri++) 
  {
    r->updateNeighborDisconnectHost(ri->second, h);
  }
}

/* --------------------------------------------------------------------------- */
/* Function to disconnect a Router from a Router: the function first checks for 
   invalid scenarios, then updates its neighborHosts table, and updates the
   routers in its routeMap of the removed connections */
/* --------------------------------------------------------------------------- */
void Router::disconnectFrom(Router &r) {
  Router *other_router = &r;
  // If the Router is trying to disconnect from itself, end function call.
  if (other_router == this) {
    cout << "Sorry, a router cannot disconnect from itself." << endl;
    return;
  }
  
  // If the Routers trying to disconnect are not connected, end function call.
  if ((this->neighborRouters).count(other_router->getNumber()) == 0) {
    cout << "Sorry, Router " << this->getNumber() << " and Router " 
         << other_router->getNumber() << " are not connected, and so cannot "
         << "disconnect from one another." << endl;
  }
  
  // Remove the Routers from each others' neighborRouters tables.
  (this->neighborRouters).erase(other_router->getNumber());
  (other_router->neighborRouters).erase(this->getNumber());

  // Removes from this Router's routeMap all routes which include the other
  // Router as a first step.
  for (multimap<int, vector<int> >::iterator i = (this->routeMap).begin();
       i != (this->routeMap).end();)
  {
    multimap<int, vector<int> >::iterator erase_i = i; // we must create another 
                                                       // iterator because erase 
                                                       // removes the multimap 
                                                       // element AND invalidates 
                                                       // the iterator
    i++;

    vector<int> v = erase_i->second;
    if (v[0] == other_router->getNumber()) {
      (this->routeMap).erase(erase_i);
    }
  }

  // Removes from the other router's routeMap all routes which include this
  // Router as a first step.
  for (multimap<int, vector<int> >::iterator i = (other_router->routeMap).begin();
       i != (other_router->routeMap).end();)
  {
    multimap<int, vector<int> >::iterator erase_i = i;
    i++;

    vector<int> v = erase_i->second;
    if (v[0] == this->getNumber()) {
      (other_router->routeMap).erase(erase_i);
    }
  }

  // Update each Router's neighbors of the deletion of the connection.
  this->updateNeighborDisconnectRouter(this->getNumber(), 
				       other_router->getNumber());

  other_router->updateNeighborDisconnectRouter(this->getNumber(), 
					       other_router->getNumber());

}

/* --------------------------------------------------------------------------- */
/* This function is used to update a router of a deleted connection between 
   two routers. This is accomplished by searching the Router's routeMap for all
   instances of the connection: either (router1, router2) or (router2, router1)
   in its routes and removing these entries. If no such entries are found, the
   function call terminates. The router then updates all its neighbor routers of 
   the deleted connection. */
/* --------------------------------------------------------------------------- */
void Router::updateNeighborDisconnectRouter(int num_router1, int num_router2) {
  // The process is carried out for each neighbor of the calling Router's 
  // neighbor table. The calling Router will already have been updated of the
  // disconnection.
  for (multimap<int, Router *>::iterator ri = (this->neighborRouters).begin();
       ri != (this->neighborRouters).end();
       ri++)
  {
    Router *r = ri->second;
    int count = 0; // count tracks the number of deletions that occur. 

    for (multimap<int, vector<int> >::iterator i = (r->routeMap).begin();
         i != r->routeMap.end();)
    {
      multimap<int, vector<int> >::iterator erase_i = i;
      i++;

      // This loop deletes an entry from the routeMap if it contains the
      // connection (router1, router2) or (router2, router1).
      int prev_num = -999;
      vector<int> v = erase_i->second;
      for (vector<int>::iterator vi = v.begin();
           vi != v.end() -1;
           vi++)
      {
	if (((num_router1 == *vi) && (num_router2 == prev_num)) ||
	    ((num_router2 == *vi) && (num_router1 == prev_num)))
        {
	  (r->routeMap).erase(erase_i);
          count++;
          break; // Once a connection instance is found and route deleted, 
	         // should break from the loop. 
	}
	prev_num = *vi;
      }
    }
    
    // If no such connections were found in any entry of the routeMap, then 
    // end the funciton call. This provides a base case for the recursion, so 
    // the method terminates.
    if (count == 0) {
      return;
    }

    // Call the function on the current Router pointed to by r.
    r->updateNeighborDisconnectRouter(num_router1, num_router2);
  }
}

/* --------------------------------------------------------------------------- */
/* This function dictates the actions of a Router when it receives a Message 
   either from a Host or from another Router. If there is no connection to the 
   destination Host, the router outputs an error message. If the Router is 
   connected to the destination Host directly, it forwards the message to the 
   Host. Otherwise, it finds the shortest route to the destination Host from its
   routeMap and passes the Message to the next router in the route. */
/* --------------------------------------------------------------------------- */
void Router::receiveMessage(Message &message) {
  // If there is no route to the destination Host, end the call.
  if (routeMap.count(message.getDestination()) == 0) {
    cout << "Routing of Message Failed at Router " << this->getNumber() << endl << endl;
    return;
  }

  // If the Router is directly connected to the destination Host, forward the 
  // Message to that Host.
  if ((neighborHosts).count(message.getDestination())!=0) {
    // The following line is complex, but is only used once in the program,
    // therefore I did not put it in an abstraction function. The line finds the
    // address of the destination Host in the Router's neighbor table and tells
    // that Host to receive the Message.
    ((neighborHosts.find(message.getDestination()))->second)->
      receiveMessage(message);
    return;
  }
   
  // From the possible routes in the routeMap which lead to the destination Host,
  // select the route with the fewest steps.
  pair<multimap<int,vector<int> >::iterator, 
       multimap<int,vector<int> >::iterator> range;
  range = routeMap.equal_range(message.getDestination());
  
  unsigned int min_length = ((range.first)->second).size();
  multimap<int,vector<int> >::iterator min_i = range.first;

  for (multimap<int, vector<int> >::iterator i = range.first;
       i != range.second;
       i++)
    {
      if ((i->second).size() < min_length) {
	min_length = (i->second).size();
	min_i = i;
      }
    }
  
  // Forward the message to the next neighboring Router in the route.
  vector<int> route = min_i->second;
  Router *next_hop = (neighborRouters.find(route[0]))->second;
  cout << "Router " << this->getNumber() << " forwarded a message to Router "
       << next_hop->getNumber() << endl << endl;
  next_hop -> receiveMessage(message);
}


/* --------------------------------------------------------------------------- */
/* Function to check if two Routers are connect within the same network, if so
   then returns TRUE. Is used when checking if a connection is being attempted 
   between two Routers in which the addresses of other Routers maybe the same. */
/* --------------------------------------------------------------------------- */
bool Router::isRouterInNetwork(int num, Router* r) {
  // Uses bool asked == 1 as a base case, if a Router has already been asked, 
  // then the current answer will not matter. Used to ensure termination, if the
  // Router r does not appear in the same network.
  if (this->getAsked() == 1) {
    return 0;
  }

  this->setAsked(1);

  // If we can find the Router address in the neighbor table, and the pointers
  // match then they are in the same network.
  if (((this->neighborRouters).count(num) > 0) && 
      (((this->neighborRouters).find(num))->second == r)) 
  {
    return 1; 
  }
  
  // A router now asks its neighbors if they are connected to the Router r,
  // as soon as one responds affirmitively, then they are in the same network. 
  int answer = 0;
  for (multimap<int, Router *>::iterator i =(this->neighborRouters).begin();
       i != (this->neighborRouters).end();
       i++)
  {
    answer = (answer + (i->second)->isRouterInNetwork(num, r));
    if (answer >= 1) {
      return 1;

    }
  }
  return 0;
}

/* --------------------------------------------------------------------------- */
/* Function used to reset the asked attribute of all Routers in a network, must
   be used after the isRouterInNetwork() function is called.*/
/* --------------------------------------------------------------------------- */
void Router::resetAsked() {
  if (this->getAsked() == 0) {
    return;
  }
  this->setAsked(0);
  for (multimap<int, Router *>::iterator i =(this->neighborRouters).begin();
       i != (this->neighborRouters).end();
       i++)
  {
    (i->second)->resetAsked();
  }
}

/* --------------------------------------------------------------------------- */
/* Function to check if a certain router with addres num appears in a Router's
   routeMap, if so returns TRUE. This function is used with isRouterInNetwork()
   to distinguish cases in which two separate networks attempt to connect, but
   they contain Routers with the same network addresses. */
/* --------------------------------------------------------------------------- */
bool Router::isRouterInTable(int num) {
  // First, read through the neighbor table for a match.
  for (multimap<int, Router*>::iterator j = (this->neighborRouters).begin();
       j != (this->neighborRouters).end();
       j++)
  {
    if ((j->first) == num) {
      return 1;
    }
  }

  // Now, read through the parts of the entries of the routeMap that 
  // correspond with Router address numbers.
  for (multimap<int, vector<int> >::iterator i = (this->routeMap).begin();
       i != (this->routeMap).end();
       i++)
  {
    for (vector<int>::iterator j = (i->second).begin();
	 j != ((i->second).end()-1);
	 j++)
    {
      if (*j == num) {
	return 1;
      }
    }
  }
  
  return 0;
}

/* --------------------------------------------------------------------------- */
/* Function to check if two separate networks are attempting to combine, but 
   they contain Router addresses that are the same, if so returns TRUE. If so, 
   throws an error message as this case would lead to address confusion within
   networks. */
/* --------------------------------------------------------------------------- */
bool Router::checkIfNetworkCombineSameRouters(Router *other_router) {
  // First, check whether the Routers are in the same network, if they are then
  // no other check matters, best to get this out of the way first.
  if (this->isRouterInNetwork(other_router->getNumber(), other_router)) {
    this->resetAsked();    
    return 0;
  }
  this->resetAsked();

  // Second, check whether the other Router is the offending Router with the same
  // address as a Router in THIS's network.
  if ((this->isRouterInTable(other_router->getNumber())) && 
      !(this->isRouterInNetwork(other_router->getNumber(), other_router)))
  {
    this->resetAsked();
    cout << "Sorry, but you are attempting to combine separate networks in which" 
	 << " a router address is currently in use in both networks." << endl;
    return 1;
  }
  this->resetAsked();

  // Finally, read through the other Router's network and see if a Router member 
  // address is also found in the Router's network. If so, then the two networks
  // have conflicting router names.
  for (multimap<int, vector<int> >::iterator i =(other_router->routeMap).begin();
       i != (other_router->routeMap).end();
       i++)
  {
    for (vector<int>::iterator vi = (i->second).begin();
	 vi != ((i->second).end()-1);
	 vi++)
    {
      if ((this->isRouterInTable(*vi)))
	{
	  this->resetAsked();
	  cout << "Sorry, but you are attempting to combine separate networks in" 
	       << " which a router address is currently in use in both networks."
	       << endl;
	  return 1;
	}
      this->resetAsked();      
    }
  }

  // Otherwise, the connection is fine in this regard.
  return 0;
}

/* --------------------------------------------------------------------------- */
/* Function to check if two separate networks are attempting to combine, but 
   they contain Host addresses that are the same, if so returns TRUE. If so, 
   throws an error message as this case would lead to address confusion within
   networks. */
/* --------------------------------------------------------------------------- */
bool Router::checkIfNetworkCombineSameHosts(Router *other_router) {
  // Only need to worry about this type of address conflict if the routers are
  // not in the same network.
  if (!(other_router->isRouterInNetwork(this->getNumber(), this))) {
    other_router->resetAsked();
    // Read through each Host in the routeMap, since this provides a full list
    // of Host addresses in a Router's network.
    for (multimap<int, vector<int> >::iterator i = (this->routeMap).begin();
	 i != (this->routeMap).end();
	 i++)
    {
      for (multimap<int, vector<int> >::iterator j = 
	     (other_router->routeMap).begin();
	   j != (other_router->routeMap).end();
	   j++)
      {
	if (i->first == j->first) {
	  cout << "Sorry, you are trying to combine separate networks, but "
	       << "Hosts in each network share the same address." << endl;
	  return 1;
	}
      }
    }
  }

  //Otherwise, the connection is fine in this regard.
  other_router->resetAsked();
  return 0;
} 

/* --------------------------------------------------------------------------- */
/* Prints the contents of a Router's routing table:[host_number, [route]]. */
/* --------------------------------------------------------------------------- */
void Router::printRoutingTable() {
    for (multimap<int, vector<int> >::iterator i = (this->routeMap).begin();
         i != (this->routeMap).end();
         i++)  {
            cout << "[" << i->first << ", [" ;
            for (vector<int>::iterator j = (i->second).begin();
                 j != (i->second).end();
                 j++) {
                    if (j != (i->second).begin()) {
                        cout << ", ";
                    }
                    cout << *j;
                 }
            cout << "]]" << endl;
         }
}

/* --------------------------------------------------------------------------- */
/* Prints the contents of a Router's neighboring routers table:
   (router_number, ...). */
/* --------------------------------------------------------------------------- */
void Router::printNeighborTable() {
    cout << "(";
    for (multimap<int, Router *>::iterator i = (this->neighborRouters).begin();
         i != (this->neighborRouters).end();
         i++) {
            if (i != (this->neighborRouters).begin()) {
                cout << ", ";
            }
            cout << i->first;
         }
    cout << ")" << endl;
}

/* --------------------------------------------------------------------------- */
/* Prints the contents of a Router's neighboring Hosts table:
   (host_number, ...). */
/* --------------------------------------------------------------------------- */
void Router::printNeighborHostsTable() {
    cout << "(";
    for (multimap<int, Host *>::iterator i = (this->neighborHosts).begin();
         i != (this->neighborHosts).end();
         i++) {
            if (i != (this->neighborHosts).begin()) {
                cout << ", ";
            }
            cout << i->first;
         }
    cout << ")" << endl;
}

