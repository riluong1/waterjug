#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include <utility>
#include <list>
#include <climits>
#include <set>
#include <sstream>
#include <functional>

using namespace std;



struct Vertex
{
  list<pair<int, int> > neighbors;
  int distance;
  bool visited;
  Vertex* prev;
  int JugA;
  int JugB;
  
  Vertex():distance(INT_MAX),visited(false),prev(0), JugA(0), JugB(0){}
  ~Vertex(){}
};

// class CompareDist
// {
//     friend class Jug;
//     public:
//         bool operator()(Vertex& n1, Vertex& n2)
//         {
//           if (n1.distance > n2.distance) 
//                 return true;
//           else
//                 return false;
//         }
// };

class prioritize{
    
    public: bool operator () (pair<int, int>&p1 ,pair<int, int>&p2){return p1.second>p2.second;}
    
};

class Jug {
    public:
        Jug(int,int,int,int,int,int,int,int,int);
        ~Jug();
   
        //solve is used to check input and find the solution if one exists
        //returns -1 invalid inputs. solution set to empty string.
        //returns 0 if inputs are valid but a solution does not exist. solution set to empty string.
        //returns 1 if solution is found and stores solution steps in solution string.
        int solve(string &solution);
    void create_graph();
    
    private:
    int Ca;
    int Cb;
    int N;
    int cfA;
    int cfB;
    int ceA;
    int ceB;
    int cpAB;
    int cpBA;
   
    vector<Vertex> vertices;    
    bool does_exist(Vertex);
    void fillA(int );
    void fillB(int );
    void emptyA(int );
    void emptyB(int );
    void fillAB(int );
    void fillBA(int );
    void fillA_string(int,int,string& );
    void fillB_string(int,int,string& );
    void emptyA_string(int,int,string& );
    void emptyB_string(int,int,string& );
    void fillAB_string(int,int,string& );
    void fillBA_string(int,int,string&);
    int goal_index(int);
    int get_index(Vertex);
    void Dijksra();
    
    
    
    public:
    void test();
    void build_string_test(string&);
        //anything else you need
};