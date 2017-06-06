/*main.cpp*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>

#include "graph.h"

using namespace std;

#define _CRT_SECURE_NO_WARNINGS  // ignore C-related security warnings in Visual Studio:


//
// Defines a Divvy Station:
//
class Station
{
public:
  string Name;
  int    ID;
  double Latitude;
  double Longitude;
  int    Capacity;

  Station(string name, int id, double latitude, double longitude, int capacity)
  {
    Name = name;
    ID = id;
    Latitude = latitude;
    Longitude = longitude;
    Capacity = capacity;
  }
};


//
// Inputs the stations from the given file, adding each station name as a
// vertex to the graph, and storing a new Station object into the vector.
// The graph is passed by reference --- note the & --- so that the changes
// made by the function are returned back.  The vector of Station objects is
// returned by the function.
//
vector<Station> InputStations(Graph& G, string filename)
{
  string line;
  vector<Station> V;

  ifstream input(filename);
  if (!input.good())  // failed to open:
    return V;

  getline(input, line);  // skip first line: column headers
  getline(input, line);  // first line of real data

  while (!input.eof())  // for each line of input:
  {
    stringstream  ss(line);

    // format:
    //   id,name,latitude,longitude,dpcapacity,online_date
    //   456,2112 W Peterson Ave,41.991178,-87.683593,15,5/12/2015
    //   101,63rd St Beach,41.78101637,-87.57611976,23,4/20/2015
    //
    string  stationID, name, latitude, longitude, capacity;

    //
    // parse the line:
    //
    getline(ss, stationID, ',');
    getline(ss, name, ',');
    getline(ss, latitude, ',');
    getline(ss, longitude, ',');
    getline(ss, capacity, ',');

    //
    // Create a new station object:
    //
    Station S(name, 
      stoi(stationID), 
      stod(latitude), 
      stod(longitude), 
      stoi(capacity));

    V.push_back(S);
    G.AddVertex(name);



    getline(input, line);
  }

  return V;
}


//
// Inputs the trips, adding / updating the edges in the graph.  The graph is
// passed by reference --- note the & --- so that the changes made by the 
// function are returned back.  The vector of stations is needed so that 
// station ids can be mapped to names; it is passed by reference only for 
// efficiency (so that a copy is not made).
//
void ProcessTrips(string filename, Graph& G, vector<Station>& stations)
{
  string line;

  ifstream input(filename);
  if (!input.good())  // failed to open:
    return;

  getline(input, line);  // skip first line: column headers
  getline(input, line);  // first line of real data

  while (!input.eof())  // for each line of input:
  {
    stringstream  ss(line);

    // format:
    //   trip_id,starttime,stoptime,bikeid,tripduration,from_station_id,from_station_name,to_station_id,to_station_name,usertype,gender,birthyear
    //   10426561,6/30/2016 23:35,7/1/2016 0:02,5229,1620,329,Lake Shore Dr & Diversey Pkwy,307,Southport Ave & Clybourn Ave,Subscriber,Male,1968
    //
    string  tripID, fromID, toID, skip;

    //
    // parse the input line:
    //
    getline(ss, tripID, ',');
    getline(ss, skip, ',');
    getline(ss, skip, ',');
    getline(ss, skip, ',');
    getline(ss, skip, ',');
    getline(ss, fromID, ',');
    getline(ss, skip, ',');
    getline(ss, toID, ',');
    getline(ss, skip, ',');

    //
    // NOTE: don't trust the names in the trips file, not always accurate.  Trust the 
    // from and to station ids, and then lookup in our vector of stations:
    //
    auto it1 = find_if(stations.begin(), stations.end(), 
                                        [&](const Station& station)
                                        {
                                          if(station.ID == stoi(fromID))
                                            return true;
                                          else
                                            return false;
                                        });
    
    auto it2 = find_if(stations.begin(), stations.end(), 
                                        [&](const Station& station)
                                        {
                                          if(station.ID == stoi(toID))
                                            return true;
                                          else
                                            return false;
                                        });
      int i;                                  
    if(G.FindEdge(it1->Name, it2->Name, i)== true)
    {
      G.changeWeight(it1->Name, it2->Name);
    }
    else
      G.AddEdge(it1->Name, it2->Name, 1);
/*
  string name1,  name2;
  for(vector<Station>::iterator it = stations.begin(); it != stations.end(); ++it) {
      if(*it.ID == tripID)
      {
        name1 = *it.Name;
      }
      if(*it.ID == fromID)
      {
        name2 = *it.Name;
      }
}*/

  /*auto iter = find_if(V.begin(), V.end(),
  [ ](Station S)
  {
      if (S.Name == nameYouAreLookingFor)
        return true;
      else
        return false;
    });
 
  if (iter == V.end())  // not found
  //do nothing
  else  // found it, and iter is ptr to that matching station:
   cout << iter->StationID << endl */
    

    //
    // TODO:
    //  - add new edge or update existing edge for this trip
    //



    getline(input, line);
  }
}


//
// getFileName: 
//
// Inputs a filename from the keyboard, checks that the file can be
// opened, and returns the filename if so.  If the file cannot be 
// opened, an error message is output and the program is exited.
//
string getFileName()
{
  string filename;

  // input filename from the keyboard:
  getline(cin, filename);

  // make sure filename exists and can be opened:
  ifstream file(filename);
  if (!file.good()) 
  {
    cout << "**Error: unable to open '" << filename << "'" << endl << endl;
    std::terminate();
  }

  return filename;
}

void info(int fromID,Graph& G, vector<Station>& stations)
{
  int num=0;
  auto it = find_if(stations.begin(), stations.end(), 
                                        [&](const Station& station)
                                        {
                                          if(station.ID == fromID)
                                            return true;
                                          else
                                          {
                                            return false;
                                          }                                        
                                        });
  if(it == stations.end())
  {
    cout << "** No such station..." << endl;
    return;
  }
  cout << it->Name <<endl;
  cout << "(" <<it->Latitude<<","<<it->Longitude<<")"<<endl;
  cout << "Capacity: " << it->Capacity << endl;
  string v = it->Name;
  set<string> neighbors = G.GetNeighbors(v);
  cout << "# of destination stations:     " << neighbors.size() << endl;
  //string n
      for (string n : neighbors)
      {
         vector<int> weights = G.GetEdgeWeights(v, n);
       for (int w : weights)
         {
            num += w;
         }
      }
      //num += weights.size();
      
  cout << "# of trips to those stations: " << num<< endl;
  cout << "Station: trips" << endl;
  for (string b : neighbors)
  {
    auto it = find_if(stations.begin(), stations.end(), 
                                        [&](const Station& station)
                                        {
                                          if(station.Name == b)
                                            return true;
                                          else
                                            return false;
                                        });
    
    cout << "    " << b << "(" << it->ID << ")" << ": ";
     vector<int> weights = G.GetEdgeWeights(v, b);
     int sum = 0;
    for (int c : weights)
    {
     //cout << c << endl;
     sum+=c;
    }
    //sum = weights.size();
    cout << sum << endl;
 }
}

void bfs(int fromID,Graph& G, vector<Station>& stations)
{
  auto it = find_if(stations.begin(), stations.end(), 
                                        [&](const Station& station)
                                        {
                                          if(station.ID == fromID)
                                            return true;
                                          else
                                          {
                                            return false;
                                          }                                        
                                        });
  if(it == stations.end())
  {
    cout << "** No such station..." << endl;
    return;
  }
  string v = it->Name;
  auto visited = G.BFS(v);
  cout << "# of stations: " << visited.size() << endl;
  for (auto s : visited)
    {
      auto it = find_if(stations.begin(), stations.end(), 
                                        [&](const Station& station)
                                        {
                                          if(station.Name == s)
                                            return true;
                                          else
                                            return false;
                                        });
                                        
      cout << it->ID << ", ";
    }
     cout << "#" << endl;
}

void trips(int fromID, int toID,Graph& G, vector<Station>& stations)
{
  auto it1 = find_if(stations.begin(), stations.end(), 
                                        [&](const Station& station)
                                        {
                                          if(station.ID == fromID)
                                            return true;
                                          else
                                            return false;
                                        });
    
    auto it2 = find_if(stations.begin(), stations.end(), 
                                        [&](const Station& station)
                                        {
                                          if(station.ID == toID)
                                            return true;
                                          else
                                            return false;
                                        });
  if(it1 == stations.end() || it2 == stations.end())
  {
    cout << "** One of those stations doesn't exist..." << endl;
    return;
  }
  cout << it1->Name << "->" << it2->Name << endl;
  int num = 0;
  vector<int> weights = G.GetEdgeWeights(it1->Name, it2->Name);
  
  for (int w : weights)
  {
    num += w;
  }
  
  cout <<  "# of trips: " << num << endl;
}

int main()
{
  int    N = 1000;
  Graph  DivvyGraph(N);

  cout << "** Divvy Graph Analysis **" << endl;

  string stationsFilename = getFileName();
  string tripsFilename = getFileName();

  vector<Station> stations = InputStations(DivvyGraph, stationsFilename);
  ProcessTrips(tripsFilename, DivvyGraph, stations);
  
  cout << ">> Graph:" << endl;
  cout << "   # of vertices: " << DivvyGraph.GetNumVertices() << endl;
  cout << "   # of edges:    " << DivvyGraph.GetNumEdges() << endl;
  cout << ">> Ready:" << endl;

  string cmd;
  int    fromID, toID;

  cout << ">> ";
  cin >> cmd;

  while (cmd != "exit")
  {
    if (cmd == "info")
    {
      cin >> fromID;
      info(fromID,DivvyGraph,stations);
    }
    else if (cmd == "trips")
    {
      cin >> fromID; 
      cin >> toID;
      trips(fromID, toID,DivvyGraph,stations);
    }
    else if (cmd == "bfs")
    {
      cin >> fromID;
      bfs(fromID,DivvyGraph,stations);
    }
    else if (cmd == "debug")
    {
      DivvyGraph.PrintGraph("Divvy Graph");
    }
    else
    {
      cout << "**Invalid command, try again..." << endl;
    }
    cout << ">> ";
    cin >> cmd;
  }
  cout << "**Done**" << endl;
  return 0;
}