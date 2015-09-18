#include <iostream>
#include <iomanip>
#include <fstream>
#include <cassert>
#include <cstring>
#include <cctype>
#include <cstdlib>

using namespace std;

#include "tube.h"


/* You are pre-supplied with the functions below. Add your own 
   function definitions to the end of this file. */

/* internal helper function which allocates a dynamic 2D array */
char **allocate_2D_array(int rows, int columns) {
  char **m = new char *[rows];
  assert(m);
  for (int r=0; r<rows; r++) {
    m[r] = new char[columns];
    assert(m[r]);
  }
  return m;
}

/* internal helper function which deallocates a dynamic 2D array */
void deallocate_2D_array(char **m, int rows) {
  for (int r=0; r<rows; r++)
    delete [] m[r];
  delete [] m;
}

/* internal helper function which gets the dimensions of a map */
bool get_map_dimensions(const char *filename, int &height, int &width) {
  char line[512];
  
  ifstream input(filename);

  height = width = 0;

  input.getline(line,512);  
  while (input) {
    if ( (int) strlen(line) > width)
      width = strlen(line);
    height++;
    input.getline(line,512);  
  }

  if (height > 0)
    return true;
  return false;
}

/* pre-supplied function to load a tube map from a file*/
char **load_map(const char *filename, int &height, int &width) {

  bool success = get_map_dimensions(filename, height, width);
  
  if (!success)
    return NULL;

  char **m = allocate_2D_array(height, width);
  
  ifstream input(filename);

  char line[512];
  char space[] = " ";

  for (int r = 0; r<height; r++) {
    input.getline(line, 512);
    strcpy(m[r], line);
    while ( (int) strlen(m[r]) < width )
      strcat(m[r], space);
  }
  
  return m;
}

/* pre-supplied function to print the tube map */
void print_map(char **m, int height, int width) {
  cout << setw(2) << " " << " ";
  for (int c=0; c<width; c++)
    if (c && (c % 10) == 0) 
      cout << c/10;
    else
      cout << " ";
  cout << endl;

  cout << setw(2) << " " << " ";
  for (int c=0; c<width; c++)
    cout << (c % 10);
  cout << endl;

  for (int r=0; r<height; r++) {
    cout << setw(2) << r << " ";    
    for (int c=0; c<width; c++) 
      cout << m[r][c];
    cout << endl;
  }
}

/* pre-supplied helper function to report the errors encountered in Question 3 */
const char *error_description(int code) {
  switch(code) {
  case ERROR_START_STATION_INVALID: 
    return "Start station invalid";
  case ERROR_ROUTE_ENDPOINT_IS_NOT_STATION:
    return "Route endpoint is not a station";
  case ERROR_LINE_HOPPING_BETWEEN_STATIONS:
    return "Line hopping between stations not possible";
  case ERROR_BACKTRACKING_BETWEEN_STATIONS:
    return "Backtracking along line between stations not possible";
  case ERROR_INVALID_DIRECTION:
    return "Invalid direction";
  case ERROR_OFF_TRACK:
    return "Route goes off track";
  case ERROR_OUT_OF_BOUNDS:
    return "Route goes off map";
  }
  return "Unknown error";
}

/* presupplied helper function for converting string to direction enum */
Direction string_to_direction(const char *token) {
  const char *strings[] = {"N", "S", "W", "E", "NE", "NW", "SE", "SW"};
  for (int n=0; n<8; n++) {
    if (!strcmp(token, strings[n])) 
      return (Direction) n;
  }
  return INVALID_DIRECTION;
}


/* Function to return the position of a given symbol on the map,
   if no symbol exists, returns false with coordinates (-1, -1) */

bool get_symbol_position(char **map, int height, int width, char target, int &r, int &c) {
  for (r = 0; r < height; r++) {
    for (c = 0; c < width; c++) {
      if (map[r][c] == target) {
	return true; // if you find the target character, return true and the
	             // current r and c
      }
    }
    c = 0; // reset column indicator for next row
  }
  c = r = -1;
  return false;
}


/* Function to return the symbol for a given station or line,
   if none exist return ' ' */
char get_symbol_for_station_or_line(const char name[]) {

  ifstream in_stations, in_lines;

  const char stations_file[] = "stations.txt";
  const char lines_file[] = "lines.txt";

  in_stations.open(stations_file);
  in_lines.open(lines_file);

  char c;
  char a[80];

  if (!strcmp(name, "")) { // catches if an empty string has been passed
    return c = ' ';
  }

  /* First, check for the symbol in the stations file. */
  while (in_stations) {
    in_stations.get(c);
    in_stations.get();
    in_stations.getline(a, 80);

    if (!strcmp(a,name)) {
      return c;
    }
  }
  /* Now, check for the symbol in the lines file. */
  while (in_lines) {
    in_lines.get(c);
    in_lines.get();
    in_lines.getline(a, 80);

    if (!strcmp(a,name)) {
      return c;
    }
  }
  return c = ' ';
}
 

/* Function to check if route valid */

int validate_route(char **map, int height, int width, const char start[], char route[], char end[]) {

  /* These will allow us to keep track of previous two steps */
  int r1 = 0;
  int c1 = 0;
  int r2 = 0;
  int c2 = 0;
  int r3 = 0;
  int c3 = 0;

  if (!isalnum(get_symbol_for_station_or_line(start))) {
    return -1; // error: the station entered was invalid
  }

  get_symbol_position(map, height, width, get_symbol_for_station_or_line(start), r3, c3);
  
  int i = 0;
  int transfers = 0;
  
  if (!strcmp(route,"")) {
    get_station_name(map[r3][c3],end);
    return transfers; // catch case for empty route: remain at station.
  }
  
  while (route[i] != '\0') {
    if (!(route[i] == 'W' || route[i] == 'E'
	  || route[i] == 'S' || route[i] == 'N')) {
      return -5; // this will catch routes with no values or routes with invalid
                 // non-numeric or alphabetic characters.
    }

    r1 = r2;
    c1 = c2;
    r2 = r3;
    c2 = c3;

    int count = 0;
    while (isalnum(route[i])) { //This will read the string until a comma, 
                                //or end of string sentinal is reached.
      if (count == 0) { // Need to check for 'EE', 'EN', 'SSSS', etc.
	if (route[i] == 'E') {
	  c3 += 1;} else if (route[i] == 'W') {
	  c3 -= 1;} else if (route[i] == 'N') {
	  r3 -= 1;} else if (route[i] == 'S') {
	  r3 += 1;} else {
	  return -5;} // check if route entered contains valid characters
      } else if ((count == 1) && (route[i-1] == 'E' || route[i-1] == 'W')) {
	return -5; // catches directions like 'EN', 'WS', etc.
      } else if (count == 1) { 
	if (route[i] == 'E') {
	  c3 += 1;} else if (route[i] == 'W') {
	  c3 -= 1;} else {
	  return -5;} // check if route entered contains valid characters
      } else {
	return -5; // between commas, more than 2 characters is invalid
      }

      if ((r3 < 0 || c3 < 0) || (r3>=height || c3 >= width)) {
	return -7; // check if out of bounds
      }

      count++;
      i++;
    }

    if (map[r3][c3] == ' ') {
      return -6; //check if off rails, if the current character is a space, then
                 //we have gone off the rails.
    }

    if ((map[r2][c2] != map[r3][c3]) && 
	(!isalnum(map[r2][c2]) && !isalnum(map[r3][c3]))) {
      return -3; //check for line hopping not at stations, 
                 //if the characters in the current and previous 
                 //element of the map are not the same, and 
                 //neither the previous nor the current are a 
                 //station, then we have hopped between lines 
                 //not at a station.
    }

    if ((r1 == r3 && c1 == c3) && (!isalnum(map[r2][c2]))) {
      return -4; //check for backtracking between stations, if the current and 
                 //two steps before are the same location, and the element in
                 //between is not a station, then we have backtracked.
    }

    if ((r1 == r3 && c1 == c3) && (isalnum(map[r2][c2]))) {
      transfers++; //if we have switched directions while on the same line, but
                   //have transferred at a station, count this as an additional 
                   //transfer.
    }

    if (isalnum(map[r2][c2]) && (map[r1][c1]!=map[r3][c3])) {
      transfers++; // if the characters in the element two steps ago and current
                   // element are not the same, and the previous element was a 
                   // station, then we have switched lines.
    }

    if (route[i] != '\0') { // This catches the loop from stepping off the end 
                            // of the string and continuing. 
      i++;
    }
  }

  if (!isalnum(map[r3][c3])) {
    return -2; //check if final step is at a station
  }
  get_station_name(map[r3][c3], end);
  return transfers - 1; //Note: we over count the number of transfers by one
                        //because the very first step counts as a transfer under
                        //the condition above.

}

/* Function to return the station name for a given station symbol, if none exist,
   do not modify string. */
void get_station_name(char c, char name[]) {
  ifstream in_stations;
  const char stations_file[] = "stations.txt";
  in_stations.open(stations_file);

  char b;
  char a[200];

  while (in_stations) {
    in_stations.get(b);
    in_stations.get();
    in_stations.getline(a, 200);

    if (b == c) {
      strcpy(name,a);
    }
  }

}
