#include <iostream>
#include <cassert>
#include <cstring>

using namespace std;

#include "tube.h"

int main() {

  /* This section illustrates the use of the pre-supplied non-helper functions. */
  /* Be aware that there are also two pre-supplied helper functions */
  cout << "============== Pre-supplied functions ==================" << endl << endl;

  char **map;
  int height, width;

  cout << "Loading tube map with load_map():";
  /* loads the map from the file "map.txt" and sets height and width */
  map = load_map("map.txt", height, width);
  assert(map);
  cout << " done (height = " << height << ", width = " << width << ")." << endl << endl;

  cout << "Printing map with print_map():" << endl;
  /* prints the map with row and column numbers */
  print_map(map,height,width);
  cout << endl;

  cout << "====================== Question 1 ======================" << endl << endl;
  
  int r, c;
  bool success = get_symbol_position(map, height, width, 'T', r, c);
  cout << "The symbol 'T' is ";
  if (success) 
    cout << "found at (" << r << "," << c << ")";
  else
    cout << "not found.";
  cout << endl << endl;

  success = get_symbol_position(map, height, width, '4', r, c);
  cout << "The symbol '4' is ";
  if (success) 
    cout << "found at (" << r << "," << c << ")";
  else
    cout << "not found.";
  cout << endl << endl;

  success = get_symbol_position(map, height, width, 'z', r, c);
  cout << "The symbol 'z' is ";
  if (success) 
    cout << "found at (" << r << "," << c << ")";
  else
    cout << "not found.";
  cout << endl << endl;

  success = get_symbol_position(map, height, width, '\0', r, c);
  cout << "The symbol '\0' is ";
  if (success) 
    cout << "found at (" << r << "," << c << ")";
  else
    cout << "not found.";
  cout << endl << endl;

  cout << "====================== Question 2 ======================" << endl << endl;
  
  cout << "The symbol for Victoria station is '" << get_symbol_for_station_or_line("Victoria") << "'" << endl << endl;

  cout << "The symbol for Oxford Circus station is '" << get_symbol_for_station_or_line("Oxford Circus") << "'" << endl << endl;

  cout << "The symbol for the District Line is '" << get_symbol_for_station_or_line("District Line") << "'" << endl << endl;

  /* Birmingham station is not on the Tube map, so this should return ' ' */ 
  cout << "The symbol for Birmingham station is '" << get_symbol_for_station_or_line("Birmingham") << "'" << endl << endl;

  /* '' station is not on the Tube map, so this should return ' ' */ 
  cout << "The symbol for station is '" << get_symbol_for_station_or_line("") << "'" << endl << endl;

 /* Edgware Road station is not on the Tube map, so this should return ' ' */ 
  cout << "The symbol for Edgware Road station is '" << get_symbol_for_station_or_line("Edgware Road") << "'" << endl << endl;

 /* Edgware Road (Circle Line) is a station on the Tube map, so this should return 'B' */ 
  cout << "The symbol for Edgware Road (Circle Line) station is '" << get_symbol_for_station_or_line("Edgware Road (Circle Line)") << "'" << endl << endl;

  cout << "====================== Question 3 ======================" << endl << endl;
  
  char route[512], destination[512] = "nowhere";

  /* valid route to Leicester Square with 1 line change */
  strcpy(route, "S,SE,S,S,E,E,E,E,E,E,E,E,E,E,E");
  cout << "Starting at Oxford Circus and taking the steps:" << endl;
  cout << route << endl;
  int result = validate_route(map, height, width, "Oxford Circus", route, destination);
  if (result >= 0)
    cout << "is a valid route with " << result << " line change(s) ending at " << destination << "." << endl;
  else 
    cout << "is an invalid route (" << error_description(result) << ")" << endl;
  cout << endl;

  /* invalid route because of line hopping between stations */ 
  strcpy(route, "N,N,N,N,N,NE,W");
  cout << "Starting at London Bridge and taking the steps:" << endl;
  cout << route << endl;
  result = validate_route(map, height, width, "London Bridge", route, destination);
  if (result >= 0)
    cout << "is a valid route with " << result << " line change(s) ending at " << destination << "." << endl;
  else 
    cout << "is an invalid route (" << error_description(result) << ")" << endl;
  cout << endl;

  /* invalid route because of backtracking between stations */
  strcpy(route, "W,W,E,W,W,W");
  cout << "Starting at Sloane Square and taking the steps:" << endl;
  cout << route << endl;
  result = validate_route(map, height, width, "Sloane Square", route, destination);
  if (result >= 0)
    cout << "is a valid route with " << result << " line change(s) ending at " << destination << "." << endl;
  else 
    cout << "is an invalid route (" << error_description(result) << ")" << endl;
  cout << endl;

  /* invalid route because route goes outside of map bounds */
  strcpy(route, "E,NE,SE,SE,SE");
  cout << "Starting at Marylebone and taking the steps:" << endl;
  cout << route << endl;
  result = validate_route(map, height, width, "Marylebone", route, destination);
  if (result >= 0)
    cout << "is a valid route with " << result << " line change(s) ending at " << destination << "." << endl;
  else 
    cout << "is an invalid route (" << error_description(result) << ")" << endl;
  cout << endl;


  /* invalid route because route goes off rails */
  strcpy(route, "SE,S,S,E,E,E");
  cout << "Starting at Paddington and taking the steps:" << endl;
  cout << route << endl;
  result = validate_route(map, height, width, "Paddington", route, destination);
  if (result >= 0)
    cout << "is a valid route with " << result << " line change(s) ending at " << destination << "." << endl;
  else 
    cout << "is an invalid route (" << error_description(result) << ")" << endl;
  cout << endl;

  /* invalid route because of invalid character */
  strcpy(route, "E,E,E,!E,E"); 
  cout << "Starting at Paddington and taking the steps:" << endl;
  cout << route << endl;
  result = validate_route(map, height, width, "Paddington", route, destination);
  if (result >= 0)
    cout << "is a valid route with " << result << " line change(s) ending at " << destination << "." << endl;
  else 
    cout << "is an invalid route (" << error_description(result) << ")" << endl;
  cout << endl;

  /* invalid route because of invalid character */
  strcpy(route, "E,E,E,Q,E"); // Invalid route string
  cout << "Starting at Paddington and taking the steps:" << endl;
  cout << route << endl;
  result = validate_route(map, height, width, "Paddington", route, destination);
  if (result >= 0)
    cout << "is a valid route with " << result << " line change(s) ending at " << destination << "." << endl;
  else 
    cout << "is an invalid route (" << error_description(result) << ")" << endl;
  cout << endl;

  /* invalid because no such station exists in london */
  strcpy(route, "E,N,S,S,S");
  cout << "Starting at Union Station and taking the steps:" << endl;
  cout << route << endl;
  result = validate_route(map, height, width, "Union Station", route, destination);
  if (result >= 0)
    cout << "is a valid route with " << result << " line change(s) ending at " << destination << "." << endl;
  else 
    cout << "is an invalid route (" << error_description(result) << ")" << endl;
  cout << endl;
  /* valid route, 0 line changes, but many stations passed through */
  strcpy(route, "E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,E"); 
  cout << "Starting at Gloucester Rd and taking the steps:" << endl;
  cout << route << endl;
  result = validate_route(map, height, width, "Gloucester Rd", route, destination);
  if (result >= 0)
    cout << "is a valid route with " << result << " line change(s) ending at " << destination << "." << endl;
  else 
    cout << "is an invalid route (" << error_description(result) << ")" << endl;
  cout << endl;

  /* valid route, 3 line chages. */
  strcpy(route, "E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,S,S,S,S,S,S,S,S,S,S,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,S,S,S,S");
  cout << "Starting at Paddington and taking the steps:" << endl;
  cout << route << endl;
  result = validate_route(map, height, width, "Paddington", route, destination);
  if (result >= 0)
    cout << "is a valid route with " << result << " line change(s) ending at " << destination << "." << endl;
  else 
    cout << "is an invalid route (" << error_description(result) << ")" << endl;
  cout << endl;

  /* valid route, 3 line chages, loop */
  strcpy(route, "E,E,E,E,E,E,E,E,E,E,E,E,E,E,E,S,S,S,S,S,S,S,S,S,S,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,N,N,N,N,N,N,N,N,N,NE");
  cout << "Starting at Paddington and taking the steps:" << endl;
  cout << route << endl;
  result = validate_route(map, height, width, "Paddington", route, destination);
  if (result >= 0)
    cout << "is a valid route with " << result << " line change(s) ending at " << destination << "." << endl;
  else 
    cout << "is an invalid route (" << error_description(result) << ")" << endl;
  cout << endl;


  /* invalid routes, 'missing' a direction */
 strcpy(route, "E,,E,E,E,E");
  cout << "Starting at Paddington and taking the steps:" << endl;
  cout << route << endl;
  result = validate_route(map, height, width, "Paddington", route, destination);
  if (result >= 0)
    cout << "is a valid route with " << result << " line change(s) ending at " << destination << "." << endl;
  else 
    cout << "is an invalid route (" << error_description(result) << ")" << endl;
  cout << endl;

  /* empty route string, valid, but stay at same station */
 strcpy(route, "");
  cout << "Starting at Paddington and taking the steps:" << endl;
  cout << route << endl;
  result = validate_route(map, height, width, "Paddington", route, destination);
  if (result >= 0)
    cout << "is a valid route with " << result << " line change(s) ending at " << destination << "." << endl;
  else 
    cout << "is an invalid route (" << error_description(result) << ")" << endl;
  cout << endl;

  /* Invalid route characters */
strcpy(route, ",,");
  cout << "Starting at Paddington and taking the steps:" << endl;
  cout << route << endl;
  result = validate_route(map, height, width, "Paddington", route, destination);
  if (result >= 0)
    cout << "is a valid route with " << result << " line change(s) ending at " << destination << "." << endl;
  else 
    cout << "is an invalid route (" << error_description(result) << ")" << endl;
  cout << endl;

  /* invalid route as goes out of bounds to the east */
strcpy(route, "E");
  cout << "Starting at Aldgate and taking the steps:" << endl;
  cout << route << endl;
  result = validate_route(map, height, width, "Aldgate", route, destination);
  if (result >= 0)
    cout << "is a valid route with " << result << " line change(s) ending at " << destination << "." << endl;
  else 
    cout << "is an invalid route (" << error_description(result) << ")" << endl;
  cout << endl;

  /* invalid route as goes out of bounds to the south */
strcpy(route, "S"); 
  cout << "Starting at Southwark and taking the steps:" << endl;
  cout << route << endl;
  result = validate_route(map, height, width, "Southwark", route, destination);
  if (result >= 0)
    cout << "is a valid route with " << result << " line change(s) ending at " << destination << "." << endl;
  else 
    cout << "is an invalid route (" << error_description(result) << ")" << endl;
  cout << endl;

  /* Valid route, goes back and forth between stations */ 
strcpy(route, "W,W,W,W,E,E,E,E,W,W,W,W"); 
  cout << "Starting at Victoria and taking the steps:" << endl;
  cout << route << endl;
  result = validate_route(map, height, width, "Victoria", route, destination);
  if (result >= 0)
    cout << "is a valid route with " << result << " line change(s) ending at " << destination << "." << endl;
  else 
    cout << "is an invalid route (" << error_description(result) << ")" << endl;
  cout << endl;

  /* invalid route, has direction WW */ 
strcpy(route, "WW,W,W,E,E,E,E,W,W,W,W"); 
  cout << "Starting at Victoria and taking the steps:" << endl;
  cout << route << endl;
  result = validate_route(map, height, width, "Victoria", route, destination);
  if (result >= 0)
    cout << "is a valid route with " << result << " line change(s) ending at " << destination << "." << endl;
  else 
    cout << "is an invalid route (" << error_description(result) << ")" << endl;
  cout << endl;

 /* invalid route, has direction EN */ 
strcpy(route, "EN,W,W,E,E,E,E,W,W,W,W"); 
  cout << "Starting at Victoria and taking the steps:" << endl;
  cout << route << endl;
  result = validate_route(map, height, width, "Victoria", route, destination);
  if (result >= 0)
    cout << "is a valid route with " << result << " line change(s) ending at " << destination << "." << endl;
  else 
    cout << "is an invalid route (" << error_description(result) << ")" << endl;
  cout << endl;

 /* invalid route, has direction SSS */ 
strcpy(route, "SSS,W,W,E,E,E,E,W,W,W,W"); 
  cout << "Starting at Victoria and taking the steps:" << endl;
  cout << route << endl;
  result = validate_route(map, height, width, "Victoria", route, destination);
  if (result >= 0)
    cout << "is a valid route with " << result << " line change(s) ending at " << destination << "." << endl;
  else 
    cout << "is an invalid route (" << error_description(result) << ")" << endl;
  cout << endl;

 /* invalid route, contains 'EQ' */ 
strcpy(route, "W,W,W,W,E,E,EQ,E,W,W,W,W"); 
  cout << "Starting at Victoria and taking the steps:" << endl;
  cout << route << endl;
  result = validate_route(map, height, width, "Victoria", route, destination);
  if (result >= 0)
    cout << "is a valid route with " << result << " line change(s) ending at " << destination << "." << endl;
  else 
    cout << "is an invalid route (" << error_description(result) << ")" << endl;
  cout << endl;

 /* invalid route, contains 'EN' */ 
strcpy(route, "W,W,W,W,E,E,EN,E,W,W,W,W"); 
  cout << "Starting at Victoria and taking the steps:" << endl;
  cout << route << endl;
  result = validate_route(map, height, width, "Victoria", route, destination);
  if (result >= 0)
    cout << "is a valid route with " << result << " line change(s) ending at " << destination << "." << endl;
  else 
    cout << "is an invalid route (" << error_description(result) << ")" << endl;
  cout << endl;

 /* invalid route, contains 'EE' */ 
strcpy(route, "W,W,W,W,E,E,EE,E,W,W,W,W"); 
  cout << "Starting at Victoria and taking the steps:" << endl;
  cout << route << endl;
  result = validate_route(map, height, width, "Victoria", route, destination);
  if (result >= 0)
    cout << "is a valid route with " << result << " line change(s) ending at " << destination << "." << endl;
  else 
    cout << "is an invalid route (" << error_description(result) << ")" << endl;
  cout << endl;

 /* invalid route, contains 'e' */ 
strcpy(route, "W,W,W,W,E,E,e,E,W,W,W,W"); 
  cout << "Starting at Victoria and taking the steps:" << endl;
  cout << route << endl;
  result = validate_route(map, height, width, "Victoria", route, destination);
  if (result >= 0)
    cout << "is a valid route with " << result << " line change(s) ending at " << destination << "." << endl;
  else 
    cout << "is an invalid route (" << error_description(result) << ")" << endl;
  cout << endl;

 /* invalid route, contains 'SSSS' */ 
strcpy(route, "W,W,W,W,E,E,E,E,W,W,W,SSSS"); 
  cout << "Starting at Victoria and taking the steps:" << endl;
  cout << route << endl;
  result = validate_route(map, height, width, "Victoria", route, destination);
  if (result >= 0)
    cout << "is a valid route with " << result << " line change(s) ending at " << destination << "." << endl;
  else 
    cout << "is an invalid route (" << error_description(result) << ")" << endl;
  cout << endl;

  return 0;
}
