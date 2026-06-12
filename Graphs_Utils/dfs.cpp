#include<bits/stdc++.h>
using namespace std;

// Simple FS using Adjacency List (without using the class structure)

void dfs(int node, int n, vector<vector<int>>&adj, vector<int>&ans, vector<bool>&vis){
    vis[node] = true;
    ans.push_back(node); // dont return anything it just updates the ans vector
    for(auto it : adj[node]){
        if(!vis[it]){
            dfs(it, n, adj, ans, vis);
        }
    }   
}

int main(){
   //whatever code you want 
   int n, m;
   vector<vector<int>>adj(n); // will be given
   int cnt = 0;
   vector<int>ans;
   vector<bool>vis(n, false);
   for(int i = 0; i < n; i++){
       if(!vis[i]){
           dfs(i, n, adj, ans, vis);
           cnt++; // needed to count provinces
       }
   }
   return ans;  
}