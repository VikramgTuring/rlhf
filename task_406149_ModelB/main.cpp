#include<bits/stdc++.h>
using namespace std;
#define MAX_VERTICES 100
int adj[MAX_VERTICES][MAX_VERTICES];
int vertices;
int colors;

int firstAvailableColor(vector<bool>& used_colors, int size)
{
    for (int i = 0; i < size; i++)
    {
        if (!used_colors[i])
        {
            used_colors[i] = true;
            return i;
        }
    }
    return -1;  // No available color, backtrack
}

int minColors(vector<int>& arr)
{
    int v = arr.size();
    vector<bool> used_colors(colors, false);
    for (int i = 0; i < v; i++)
    {
        vector<int> adj_colored;
        for(int j = 0; j < v; j++)
        {
            if(adj[arr[i]][j] == 1 && arr[j] != -1)
                adj_colored.push_back(arr[j]);
        }
        int color = firstAvailableColor(used_colors, colors);
 
        if (color == -1)
        {
            colors++;
            used_colors.resize(colors, false);
            color = firstAvailableColor(used_colors, colors);
        }
        arr[i] = color;
    }
    return colors;
}
int32_t main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    vertices = 5;
    colors = 0;
    int n = 5;
    vector<int> graph_color;
    for (int i = 0; i < vertices; i++)
        graph_color.push_back(-1);

    //Initialize the graph with given edges
    memset(adj, 0, sizeof(adj));
    adj[0][1] = 1; 
    adj[0][3] = 1; 
    adj[1][2] = 1; 
    adj[1][4] = 1; 
    adj[2][3] = 1;
    
    colors = minColors(graph_color);
    
    cout << "Minimum colors required: " << colors << endl;
    cout << "Coloring scheme: ";
    for (int i : graph_color) {
        cout << i << " ";
    }
    cout << endl;
 
    return 0;
}
