#include "Jug.h"

Jug::Jug(int a, int b, int c, int d, int e, int f, int g, int h, int i)
{
     Ca = a;
     Cb = b;
     N = c;
     cfA = d;
     cfB = e;
     ceA = f;
     ceB = g;
     cpAB = h;
     cpBA = i;
    
    
}

Jug::~Jug()
{
    
}

int Jug::solve(string &solution)
{
   
    // You will want to verify the costs are positive and 0 < Ca ≤ Cb and N ≤ Cb ≤ 1000
    if (Ca < 0 || Ca > Cb || Cb < 0 || N > Cb || Cb > 1000 || N > 1000 || N < 0)
    {
        solution = "";
        return -1;
    }
    create_graph();
    Dijksra();
    int i = goal_index(N);
    if (vertices.at(i).distance == INT_MAX || vertices.at(i).distance == 0)
    {
        solution = "";
        return 0;
    }
    else
    {
        build_string_test(solution);
        //store string
        return 1;
    }
}

void Jug::Dijksra()
{
    vertices.at(0).distance = 0;
    vertices.at(0).visited = true;
   
    
    priority_queue<pair<int, int>, vector<pair<int,int> >, prioritize>  q;
    
    q.push(make_pair(0, 0));
    
    while(!q.empty())
    {
    pair<int,int> a = q.top();
  
    // cout << a.first << endl;
    // cout << a.second << endl;
    q.pop();
  
    Vertex u = vertices.at(a.first);
   
    list<pair<int,int> > :: iterator it;
    
    for(it = u.neighbors.begin(); it != u.neighbors.end(); ++it)
    {
  
        if(vertices.at(it->first).distance > (u.distance + it->second))
        { 
           
            vertices.at(it->first).distance = u.distance + it->second;
            vertices.at(it->first).prev = &vertices.at(a.first);
             
        }
        
        if(vertices.at(it->first).visited == false)
        {
            
            q.push(make_pair(it->first, vertices.at(it->first).distance));
            vertices.at(it->first).visited = true;
        }
    }
        
     }
    
}




void Jug::create_graph()
{
    Vertex A;
    vertices.push_back(A);
    
    for (unsigned int i = 0; i < vertices.size(); ++i)
    {
        fillA(i);
        fillB(i);
        emptyA(i);
        emptyB(i);
        fillAB(i);
        fillBA(i);
    }
    return;
}

void Jug::fillA(int index)
{
     Vertex temp;
     temp.JugA = Ca;
     temp.JugB = vertices.at(index).JugB;
  
     if(does_exist(temp))
         {
             int i = get_index(temp);
            pair<int,int> newPair;
             newPair = make_pair(i,cfA);
             vertices.at(index).neighbors.push_back(newPair);
             return;
         }
         else
         {
          vertices.push_back(temp);
          int i = get_index(temp);
            pair<int,int> newPair;
             newPair = make_pair(i,cfA);
             vertices.at(index).neighbors.push_back(newPair);
             return;   
         }
     
            
}

void Jug::fillB(int index)
{
     Vertex temp;
     temp.JugA = vertices.at(index).JugA;
     temp.JugB = Cb;
   
     
  if(does_exist(temp))
         {
             int i = get_index(temp);
            pair<int,int> newPair;
             newPair = make_pair(i,cfB);
             vertices.at(index).neighbors.push_back(newPair);
             return;
         }
         else
         {
          vertices.push_back(temp);
          int i = get_index(temp);
            pair<int,int> newPair;
             newPair = make_pair(i,cfB);
             vertices.at(index).neighbors.push_back(newPair);
              
             return;   
         }
}

void Jug::emptyA(int index)
{
    Vertex temp;
    temp.JugA = 0;
    temp.JugB = vertices.at(index).JugB;
     
     if(does_exist(temp))
         {
             int i = get_index(temp);
            pair<int,int> newPair;
             newPair = make_pair(i,ceA);
             vertices.at(index).neighbors.push_back(newPair);
             return;
         }
         else
         {
          vertices.push_back(temp);
          int i = get_index(temp);
            pair<int,int> newPair;
             newPair = make_pair(i,ceA);
             vertices.at(index).neighbors.push_back(newPair);
            
             return;   
         }
     
    
}

void Jug::emptyB(int index)
{
    Vertex temp;
    temp.JugA = vertices.at(index).JugA;
    temp.JugB = 0;   
       if(does_exist(temp))
         {
             int i = get_index(temp);
            pair<int,int> newPair;
             newPair = make_pair(i,ceB);
             vertices.at(index).neighbors.push_back(newPair);
             return;
         }
         else
         {
          vertices.push_back(temp);
          int i = get_index(temp);
            pair<int,int> newPair;
             newPair = make_pair(i,ceB);
             vertices.at(index).neighbors.push_back(newPair);
            
             return;   
         }
     
    
}

void Jug::fillAB(int index)
{
    Vertex temp;
    temp.JugA = vertices.at(index).JugA;
    temp.JugB = vertices.at(index).JugB;
    
    if(temp.JugB == Cb)
    {
        // already at capacity, so just push onto the adjacency list
        pair<int,int> newPair;
             newPair = make_pair(index,cpAB);
             vertices.at(index).neighbors.push_back(newPair);
             return;
    }
   
    else if(temp.JugA + temp.JugB > Cb)
    {
        temp.JugA = temp.JugA - (Cb - temp.JugB);
        temp.JugB = Cb;
        
    }
    else
    {
        temp.JugB = temp.JugB + temp.JugA;
        temp.JugA = temp.JugA - temp.JugA;
    }
    
    
    
   if(does_exist(temp))
         {
             int i = get_index(temp);
            pair<int,int> newPair;
             newPair = make_pair(i,cpAB);
             vertices.at(index).neighbors.push_back(newPair);
             return;
         }
         else
         {
          vertices.push_back(temp);
          int i = get_index(temp);
            pair<int,int> newPair;
             newPair = make_pair(i,cpAB);
             vertices.at(index).neighbors.push_back(newPair);
       
             return;   
         }
     
}

void Jug::fillBA(int index)
{
    Vertex temp;
    temp.JugA = vertices.at(index).JugA;
    temp.JugB = vertices.at(index).JugB;
    
    if(temp.JugA == Ca)
    {
        // already at capacity, so just push onto the adjacency list
        pair<int,int> newPair;
             newPair = make_pair(index,cpBA);
             vertices.at(index).neighbors.push_back(newPair);
             return;
    }
   
    else if( (temp.JugA + temp.JugB) > Ca)
    {
        temp.JugB = temp.JugB - (Ca - temp.JugA);
        temp.JugA = Ca;
    }
    else if( (temp.JugA + temp.JugB) == Ca)
    {
        temp.JugB = 0;
         temp.JugA = Ca;
    }
    else
    {
        temp.JugB = temp.JugB - temp.JugB;
        temp.JugA = temp.JugA + temp.JugB;
    }
    
    
    
  if(does_exist(temp))
         {
             int i = get_index(temp);
            pair<int,int> newPair;
             newPair = make_pair(i,cpBA);
             vertices.at(index).neighbors.push_back(newPair);
             return;
         }
         else
         {
          vertices.push_back(temp);
          int i = get_index(temp);
            pair<int,int> newPair;
             newPair = make_pair(i,cpBA);
             vertices.at(index).neighbors.push_back(newPair);

             return;   
         }
     
}

void Jug::test()
{
    create_graph();
    list<pair<int,int> > :: iterator it;
    for(unsigned int i = 0; i < vertices.size(); ++i)
    {
          cout << "(" << vertices.at(i).JugA << ", " << vertices.at(i).JugB << ")" << endl;
          for (it = vertices.at(i).neighbors.begin(); it != vertices.at(i).neighbors.end(); ++it)
          {
              cout << "Index: " << it->first << " Cost: " << it->second << endl;
          }
          cout << endl;
    }
    Dijksra();
    int index = goal_index(N);
    cout << vertices.at(index).distance;
        
}

bool Jug::does_exist(Vertex a)
{
    for (unsigned int i = 0; i < vertices.size(); ++i)
    {
        if (a.JugA == vertices.at(i).JugA && a.JugB == vertices.at(i).JugB)
        {
            return true;
        }
    }
    
    return false;
}

int Jug::get_index(Vertex a)
{
     for (unsigned int i = 0; i < vertices.size(); ++i)
    {
        if (a.JugA == vertices.at(i).JugA && a.JugB == vertices.at(i).JugB)
        {
            return i;
        }
    }
    return 0;
}

int Jug::goal_index(int target)
{
      for (unsigned int i = 0; i < vertices.size(); ++i)
    {
        if (vertices.at(i).JugA == 0 && vertices.at(i).JugB == target)
        {
            return i;
        }
    }
    return 0;
}

void Jug::build_string_test(string &solution)
{
    list<int> help;
    int i = goal_index(N);

 Vertex u = vertices.at(i);
  while(u.prev)
 {
    int j = get_index(u);
    help.push_front(j);
    u = *u.prev;
 }
 
 help.push_front(0);
   list<int> ::iterator it;
   
while(it != help.end())
 {     
     it = help.begin();
     int a = *it;
     
     help.pop_front();
     it = help.begin();
     int b = *it;
     if(it == help.end())
     {
         break;
     }
     
     fillA_string(a,b,solution);
     fillB_string(a,b,solution);
     emptyA_string(a,b,solution);
     emptyB_string(a,b,solution);
     fillAB_string(a,b,solution);
     fillBA_string(a,b,solution);
     
}

u = vertices.at(i);
 int x = u.distance;
 string Result;          // string which will contain the result

ostringstream convert;   // stream used for the conversion

convert << x;      // insert the textual representation of 'Number' in the characters in the stream

Result = convert.str();
solution = solution + "success " + Result;
 
}

void Jug::fillA_string(int first,int second,string& solution)
{
    if(vertices.at(first).JugA == Ca)
    {
        return;
    }
    else if((vertices.at(first).JugA != Ca) && (vertices.at(second).JugA == Ca) && (vertices.at(first).JugB == vertices.at(second).JugB))
    {
        solution = solution + "fill A\n";
    }
    else
    {
        return;
    }
}

void Jug::fillB_string(int first,int second,string& solution)
{
     if(vertices.at(first).JugB == Cb)
    {
        return;
    }
        else if((vertices.at(first).JugB != Cb) && (vertices.at(second).JugB == Cb) && (vertices.at(first).JugA == vertices.at(second).JugA))
    {
        solution = solution + "fill B\n";
    }
    else
    {
        return;
    }
}
    
void Jug::emptyA_string(int first,int second,string& solution )
{
         if((vertices.at(first).JugA != 0) && (vertices.at(second).JugA == 0) && (vertices.at(first).JugB == vertices.at(second).JugB))
    {
        solution = solution + "empty A\n";
    }
    else
    {
        return;
    }
}
    
    
    
    
    
void Jug::emptyB_string(int first,int second,string& solution)
{
     if((vertices.at(first).JugB != 0) && (vertices.at(second).JugB == 0) && (vertices.at(first).JugA == vertices.at(second).JugA))
    {
        solution = solution + "empty B\n";
    }
    else
    {
        return;
    }
        
        
        
}




void Jug::fillAB_string(int first,int second,string& solution)
{
    if((vertices.at(first).JugA > 0) && (vertices.at(second).JugA == 0) && (vertices.at(second).JugB == (vertices.at(first).JugA + vertices.at(first).JugB)) )
    {
         solution = solution + "pour A B\n";
    }
    else if((vertices.at(first).JugA > 0) && (vertices.at(second).JugA > 0) && 
    
    (vertices.at(second).JugA == (vertices.at(first).JugA - (vertices.at(second).JugB - vertices.at(first).JugB))) 
    
    && (vertices.at(second).JugB  == (vertices.at(first).JugB + (vertices.at(first).JugA - vertices.at(second).JugA))))
    {
        solution = solution + "pour A B\n";
    }
    else
    {
        return;
    }
}


void Jug::fillBA_string(int first,int second,string& solution)
{
     if(vertices.at(first).JugA < Ca && vertices.at(second).JugA == Ca && vertices.at(second).JugB == 0 && vertices.at(first).JugB > 0 )
    {
         solution = solution + "pour B A\n";
    }
    else if (vertices.at(first).JugA < Ca && vertices.at(second).JugA == Ca && vertices.at(first).JugB > 0 
    && (vertices.at(second).JugB == (vertices.at(first).JugB - (vertices.at(second).JugA - vertices.at(first).JugA))))
    {
        solution = solution + "pour B A\n";
    }
    return;
}


  