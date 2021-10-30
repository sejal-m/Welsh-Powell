#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
using namespace std;

class Graph
{
    int V;   
    vector<int> *adj;    
public:
  
    Graph(int V)
    {
        this->V = V;
        adj = new vector<int>[V];
    }
    ~Graph()
    {
        delete [] adj;
    }

    void addEdge(int u, int v);
    void welshPowellColoring();
};

void Graph::addEdge(int u, int v)
{
    adj[u].push_back(v);
    adj[v].push_back(u); 
}

struct vertexDegree
{
    int v;
    int degree;
    int color = -1;
    bool assigned = false;
};

bool compareByDegree(const vertexDegree& x, const vertexDegree& y)
{
    return x.degree > y.degree;
}

int find_index(vertexDegree desc_degrees[], int elem, int V) {
    int i = 0;
    while (i < V)
    {
        if (desc_degrees[i].v == elem) {
            break;
        }
        i++;
    }
    return i;
}

void Graph::welshPowellColoring()
{
    int result[V];
    int chosen_vertex;

    vertexDegree desc_degrees[V];
    for (int i = 0; i < V; i++)
    {
        desc_degrees[i].v = i;
        desc_degrees[i].degree = adj[i].size();
    }


    sort(desc_degrees, desc_degrees+V, compareByDegree);

    cout << "Sorted vertices (descending order of degrees) \n";
    for (int i = 0; i <V; i++)
    {
        cout << desc_degrees[i].v << " ";
    }
    cout<<endl;
    int c = 1;
    
    for(int x = 0;x < V; x++) {

        if(desc_degrees[x].assigned == false) {
            desc_degrees[x].color = c; 
            desc_degrees[x].assigned = true;
        }
        else  { continue; }
        
        for(int y = x+1; y < V; y++) {
            chosen_vertex =  desc_degrees[y].v;

            bool can_choose = true;
            for (auto i = adj[chosen_vertex].begin(); i != adj[chosen_vertex].end(); i++) {                   
                int index = find_index(desc_degrees, *i, V);            
                if(desc_degrees[index].color == c) {
                    can_choose = false;
                    break;
                }   
            }
            if(can_choose && desc_degrees[y].assigned == false) {
                desc_degrees[y].color = c;
                desc_degrees[y].assigned = true;
            }            
        }
        c++;
    }
    c--;
    
    cout<<endl<<"Assigning colors to vertices"<<endl;
    for(int i = 0;i < V; i++) {
        cout<<"vertex: "<<desc_degrees[i].v<<" C"<<desc_degrees[i].color<<endl;
    }
    cout<<endl<<c<< " colors needed to color given graph."<<endl;

    for(int col = 1; col <= c; col++) {
        cout<<"C"<<col<<" : ";
        for(int i = 0;i < V; i++) {
            if(desc_degrees[i].color == col)
                cout<<desc_degrees[i].v<<" ";
        }
        cout<<endl;
    }
}

int main()
{
    ifstream infile("welsh_powell_input.txt");
    int n;
    infile>>n;
    Graph G(n);

    int a, b;
    while (infile >> a >> b)
        G.addEdge(a, b); 

    G.welshPowellColoring();

    infile.close();
    return 0;
}   