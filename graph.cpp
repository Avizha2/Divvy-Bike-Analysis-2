/*graph.cpp*/

#include <iostream>
#include <string>
#include <vector>
#include <queue> 
#include <set>

#include "graph.h"

using namespace std;


//
// Constructor:
//
Graph::Graph(int N)
{
  this->NumVertices = 0;
  this->NumEdges = 0;
  this->Capacity = N;

  this->Vertices = new Edge*[N];
  this->Names = new string[N];

}


//
// Destructor:
//
Graph::~Graph()
{
  //
  // Future work:
  //
}


//
// AddVertex:
//
// Adds the given vertex v to the graph, returning true if
// successful and false if not.  The add fails if (1) the
// graph is full, or (2) the vertex already exists in the
// graph.
//
bool Graph::AddVertex(string v)
{
   //
   // if the graph is "full", i.e. cannot hold more vertices,
   // then return false:
   //
   // TODO #1
   //
   if(this->NumVertices == this->Capacity)
      return false;
   
   //
   // if the vertex name already exists in the graph,
   // then return false.  To determine, perform a linear
   // search of the Names array; note that in C++ you
   // compare strings using ==, no strcmp needed:
   //
   // TODO #2
   //
   for (int x = 0; x < this->NumVertices; ++x)
  {
   if(this->Names[x] == v)
      return false;
      
   }
   //
   // there's room to add another vertex, so grab next index
   // and initialize that linked-list to empty, and store
   // vertex's name:
   //
   int i = this->NumVertices;

   this->Vertices[i] = nullptr;  // head of LL: null
   this->Names[i] = v;           // copy vertex string:

   this->NumVertices++;
   return true;
}


//
// AddEdge:
//
// Adds an edge from src to dest, with the given weight, returning
// true if successful and false if not.  The add fails if the src
// or dest vertex do not exist.
//
bool Graph::AddEdge(string src, string dest, int weight)
{
   int S = -1,D = -1;
   // 
   // First, lookup src vertex in Names array and obtain index S; if
   // not found, return false:
   //
    for (int x = 0; x < this->NumVertices; ++x)
  {
   if(this->Names[x] == src)
     S = x;
   }
   
   //
   // Second, lookup dest vertex in Names array and obtain index D, if
   // not found, return false:
   //
    for (int x = 0; x < this->NumVertices; ++x)
  {
   if(this->Names[x] == dest)
      D = x;
   }
   
   if(S == -1 || D == -1)
      return false;
   //
   // Now add an edge (S,D,weight) to the front of S's linked-list.
   // You'll need to allocate a new edge using new, store S, D and
   // weight, and then insert at head of S's linked-list in the
   // Vertices array:
   //
   Edge *e = new Edge();
    e->Src = S;
    e->Dest = D;
    e->Weight = weight;
    
   Edge *prev = nullptr;
   Edge *edge = this->Vertices[S];
  while (edge != nullptr)
  {
     if(e->Dest < edge->Dest)
     {
      break;     
     }
    if(e->Dest == edge->Dest && e->Weight <= edge->Weight) 
    {
        break;
    }
     prev = edge;
    edge = edge->Next;
  }
  if(prev == nullptr)
  {
      e->Next = edge;
    this->Vertices[S] = e;
  }
  else
  {
   e->Next = edge;
   prev->Next = e;
  }
   //
   // increment the # of edges and return true:
   //
   this->NumEdges++;
   
   return true;
}


 bool  Graph::FindEdge(string src, string dest, int &i)
 {
    int S = -1,D = -1;
   // 
   // First, lookup src vertex in Names array and obtain index S; if
   // not found, return false:
   //
    for (int x = 0; x < this->NumVertices; ++x)
  {
   if(this->Names[x] == src)
     S = x;
   }
   
   //
   // Second, lookup dest vertex in Names array and obtain index D, if
   // not found, return false:
   //
    for (int x = 0; x < this->NumVertices; ++x)
  {
   if(this->Names[x] == dest)
      D = x;
   }
   
   if(S == -1 || D == -1)
      return false;    
 
  Edge *edge = this->Vertices[S];
  while (edge != nullptr)
  {
    if(edge->Dest == D && edge->Src == S)
        return true;
    edge = edge->Next;  
  }
    return false;
 }


//
// PrintGraph:
//
// Prints the graph, typically for debugging purposes.
//
void Graph::PrintGraph(string title)
{
  cout << ">>Graph: " << title << endl;
  cout << "  # of vertices: " << this->NumVertices << endl;
  cout << "  # of edges:    " << this->NumEdges << endl;
  cout << "  Capacity:      " << this->Capacity << endl;

  cout << "  Vertices:" << endl;

  for (int v = 0; v < this->NumVertices; ++v)
  {
    cout << "    " << v << " (" << this->Names[v] << "): ";

    Edge *edge = this->Vertices[v];
    while (edge != nullptr)
    {
      cout << "(" << edge->Src << "," << edge->Dest << "," << edge->Weight << ")";

      edge = edge->Next;
      if (edge != nullptr)
        cout << ", ";
    }

    cout << endl;
  }
}

//
// GetVertices:
//
// Returns a set containing all vertices in the graph.
//
set<string> Graph::GetVertices()
{
   set<string>  vertices;

      for( int i = 0; i < this->NumVertices; ++i)
   {
       vertices.insert(this->Names[i]);
   }
   return vertices;
}


//
// GetNeighbors:
//
// Returns a set containing all the vertices adjacent to v.
// If v does not exist in the graph, the returned set is
// empty.
//
set<string> Graph::GetNeighbors(string v)
{
  set<string>  neighbors;
int S;
   for (int x = 0; x < this->NumVertices; ++x)
  {
    if(this->Names[x] == v)
         S = x;
   }
    
  Edge *edge = this->Vertices[S];
  while (edge != nullptr)
  {
   neighbors.insert(this->Names[edge->Dest]);
    edge = edge->Next;
  }

  return neighbors;
}


//
// GetEdgeWeights:
//
// Returns a vector containing all the weights for edges 
// from src to dest.  The weights are in ascending order,
// and may contain duplicates (since it is legal for there
// to be 2 different edges from src to dest with the same
// weight).  If src or dest do not exist in the graph, the
// returned vector is empty.
//
vector<int> Graph::GetEdgeWeights(string src, string dest)
{
   vector<int> weights;
   
   int S,D;
   for (int x = 0; x < this->NumVertices; ++x)
  {
    if(this->Names[x] == src)
         S = x;
    if(this->Names[x] == dest)
         D = x;   
   }

  Edge *edge = this->Vertices[S];
  while (edge != nullptr)
  {
   if(edge ->Dest == D)  
       weights.push_back(edge->Weight);
    edge = edge->Next;
  }

   return weights;
}


vector<int> Graph::iNeighbors(int S)
{
  vector<int>  neighbors;
    
    
  Edge *edge = this->Vertices[S];
  while (edge != nullptr)
  {
   neighbors.push_back(edge->Dest);
    edge = edge->Next;
  }

  return neighbors;
}

//
// BFS:
//
// Performs a breadth-first search starting from vertex v, returning
// a vector that denotes the order in vertices were visited.  If v
// does not exist in the graph, an empty vector is returned.
//
// NOTE that a vertex will appear at most once in the returned vector,
// since once a vertex is visited, it is never visited again.
//
vector<string> Graph::BFS(string v)
{
  vector<string>  visited;
  queue<int>      frontierQueue;
  set<int>        discoveredSet;
  
  int start;
  
   for (int x = 0; x < this->NumVertices; ++x)
  {
    if(this->Names[x] == v)
         start = x;
   }
  
  if(start < 0)
    return visited;

  frontierQueue.push(start);
  discoveredSet.insert(start);
  
  while(!frontierQueue.empty())
  {
      int current = frontierQueue.front();
      visited.push_back(this->Names[current]);
      frontierQueue.pop();
      vector<int> V = iNeighbors(current);
      for(int adjV : V)
      {
          if ( discoveredSet.find(adjV) == discoveredSet.end() )  // not found:
          {
            frontierQueue.push(adjV);
            discoveredSet.insert(adjV);
          }
      }
  }
  
  
  
  return visited;
}

int Graph::GetNumVertices()
{
 return  this->NumVertices;
}
int Graph::GetNumEdges()
{
 return  this->NumEdges;
}
void Graph::changeWeight(string src, string dest)
{
   int S,D;
    for (int x = 0; x < this->NumVertices; ++x)
  {
   if(this->Names[x] == src)
     S = x;
   }
    for (int x = 0; x < this->NumVertices; ++x)
  {
   if(this->Names[x] == dest)
      D = x;
   }
   
  Edge *edge = this->Vertices[S];
  while (edge != nullptr)
  {
    if(edge->Dest == D && edge->Src == S)
        edge->Weight++;
    edge = edge->Next;  
  }
}