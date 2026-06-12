#include<bits/stdc++.h>
using namespace std;

// Simple BFS using Adjacency List (without using the class structure)

vector<int> bfs(int src, int n, vector<vector<int>>&adj){
    vector<int>ans;
    queue<int>q;
    q.push(src);
    vector<bool>vis(n, false);
    vis[src] = true;
    while(!q.empty()){
        int node = q.front();
        q.pop();
        ans.push_back(node);
        for(auto it : adj[node]){
            if(!vis[it]){
                vis[it] = true;
                q.push(it);
            }
        }
    }
    return ans;
}

int main(){
   //whatever code you want 
}