#include <iostream>
#include <list>
#include <algorithm>
#include <fstream>
using namespace std;

// A class that represents an undirected graph
class Graph
{
    int V;    // No. of vertices
    list<int> *adj;    // A dynamic array of adjacency lists
public:
    // Constructor and destructor
    Graph(int V)
    {
        this->V = V;
        adj = new list<int>[V];
    }
    ~Graph()
    {
        delete [] adj;
    }

    void printGraph()
    {
        for (int v = 0; v < V; ++v)
        {
            cout << "\n Adjacency list of vertex "<< v ;
            for (auto x : adj[v])
                cout << "-> " << x;
            printf("\n");
         }
    }
    // function to add an edge to graph
    void addEdge(int v, int w);

    // Prints greedy coloring of the vertices
    void greedyColoring();
};

void Graph::addEdge(int v, int w)
{
    adj[v].push_back(w);
    adj[w].push_back(v);  // Note: the graph is undirected
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

void Graph::greedyColoring()
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

    cout << "Sorted vertices \n";
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

    //printing output
    for(int i = 0;i < V; i++) {
        cout<<"vertex: "<<desc_degrees[i].v<<" C"<<desc_degrees[i].color<<endl;
    }
    cout<<"No. of colors needed: "<<c - 1;
}

// Driver program to test above function
int main()
{
    /* Graph g1(5);
    g1.addEdge(0, 1);
    g1.addEdge(0, 2);
    g1.addEdge(1, 2);
    g1.addEdge(1, 3);
    g1.addEdge(2, 3);
    g1.addEdge(3, 4);
    g1.printGraph();
    cout << "Coloring of Graph 1 \n";
    g1.greedyColoring();

    Graph g2(5);
    g2.addEdge(0, 1);
    g2.addEdge(0, 2);
    g2.addEdge(1, 2);
    g2.addEdge(1, 4);
    g2.addEdge(2, 4);
    g2.addEdge(4, 3);
    g2.printGraph();
    cout << "\nColoring of Graph 2 \n";
    g2.greedyColoring();*/

    Graph g3(100);

    ifstream infile("example.txt");
    int a, b;
    while (infile >> a >> b)
        g3.addEdge(a, b); 
    

    //g3.printGraph();
    g3.greedyColoring();
    return 0;

}   