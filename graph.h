/*graph.h*/


#pragma once

#include <string>
#include <vector>

using namespace std;

class Graph
{
private:
  class Edge
  {
  public:
    int   Src, Dest, Weight;
    Edge *Next;
  };

  Edge  **Vertices;
  string *Names;
  int     NumVertices;
  int     NumEdges;
  int     Capacity;

public:
  Graph(int N);
  ~Graph();

  bool AddVertex(string v);
  bool AddEdge(string src, string dest, int weight);
  bool FindEdge(string src, string dest, int &i);

  void PrintGraph(string title);
  
  set<string> GetVertices();
  set<string> GetNeighbors(string v);
  vector<int> GetEdgeWeights(string src, string dest);
  vector<int> iNeighbors(int S);
  vector<string> BFS(string v);
  int GetNumVertices();
  int GetNumEdges();
  void changeWeight(string src, string dest);
};