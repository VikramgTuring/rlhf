#include <iostream>
#include <vector>
using namespace std;

class Graph {
private:
    int V;   // Number of vertices
    vector<vector<int>> adjList; // Adjacency list representation of the graph

public:
    Graph(int V) : V(V), adjList(V) {}

    // Function to add an edge between two vertices
    void addEdge(int u, int v) {
        adjList[u].push_back(v);
        adjList[v].push_back(u); // Undirected graph
    }

    // Get the number of vertices
    int getV() const { return V; }

    // Get the neighbors of a vertex
    vector<int> getNeighbors(int v) const {
        return adjList[v];
    }
};

bool isSafe(Graph& graph, vector<int>& colors, int vertex, int color) {
    for (int neighbor : graph.getNeighbors(vertex)) {
        if (colors[neighbor] == color) {
            return false; // If the neighbor has the same color, it's not safe
        }
    }
    return true;
}

int graphColoringHelper(Graph& graph, vector<int>& colors, int vertex) {
    int V = graph.getV();

    if (vertex >= V) {
        // Base case: If all vertices are colored, return the number of colors used
        return static_cast<int>(*max_element(colors.begin(), colors.end()) + 1);
    }

    for (int color = 0; color <= colors.size(); color++) {
        if (isSafe(graph, colors, vertex, color)) {
            colors[vertex] = color;

            int result = graphColoringHelper(graph, colors, vertex + 1);
            if (result != -1) {
                return result; // If we find a valid coloring, return the number of colors
            }
        }
    }

    // If we reach here, it means no valid coloring was possible with the current branch
    colors[vertex] = -1;
    return -1;
}

int minColors(Graph& graph) {
    int V = graph.getV();
    vector<int> colors(V, -1); // To store the color of each vertex (-1 means not colored)

    return graphColoringHelper(graph, colors, 0);
}

int main() {
    int V = 4;
    Graph graph(V);

    graph.addEdge(0, 1);
    graph.addEdge(0, 3);
    graph.addEdge(1, 2);
    graph.addEdge(1, 4);
    graph.addEdge(2, 3);

    int minColorsNeeded = minColors(graph);

    if (minColorsNeeded != -1) {
        cout << "Minimum colors needed: " << minColorsNeeded << endl;
    }
    else {
        cout << "No valid coloring possible." << endl;
    }
}