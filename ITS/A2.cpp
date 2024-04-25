#include<iostream>
#include<omp.h>
#include<vector>
#include<chrono>
using namespace std;
using namespace std::chrono; 

class Graph
{
    int V;
    vector<vector<int>> adj;
    public: 
    Graph(int V): V(V), adj(V){}

    void addEdge(int v, int w)
    {
        adj[v].push_back(w);
    }

    void parallelDFS(int startVertex)
    {
        vector<bool> visited(V, false);
        parallelDFSUtil(startVertex, visited);
    }
    void parallelDFSUtil(int v, vector<bool> visited)
    {
        visited[v] = true;
        cout<<v<<" ";

        #pragma omp parallel for
        for(int i =0; i<adj[v].size(); i++)
        {
            int n = adj[v][i];
            if(!visited[n])
            {
                parallelDFSUtil(n, visited);
            }
        }
    }
};

int main(){

    Graph g(8);

    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(1, 4);
    g.addEdge(2, 5);
    g.addEdge(2, 6);
    g.addEdge(3, 7);

    cout<<"DFS Traversal: ";
    auto start_time = high_resolution_clock::now();
    g.parallelDFS(0);
    auto stop_time = high_resolution_clock::now();
    auto time = duration_cast<duration<double>>(stop_time - start_time).count();
    cout<<endl;
    cout<<"Parallel Time: "<<time<<" secs"<<endl;


    
    
    
    
    return 0;
}