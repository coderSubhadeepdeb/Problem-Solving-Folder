#include<bits/stdc++.h>
using namespace std;

//SIMPLE QUEUE

vector<int> shortestPath(int src, int n, vector<vector<pair<int,int>>>&adj){ // might be a weighted graph vector<vector<pair<int,int>>>&adj
    queue<int>q;
    q.push(src);
    vector<int>dist(n,1e9);
    dist[src] = 0;

    while(!q.empty()){
        int node = q.front();
        q.pop();
        for(auto it: adj[node]){
            int adjNode = it.first;
            int wt = it.second;
            if(dist[adjNode] > wt + dist[node]){
                dist[adjNode] = wt + dist[node];
                q.push(adjNode);
            }
        }
    }
    return dist; // containing 1e9
}

//DIJKSTRAS ALGORITHM

vector<int> dijkstra(int src, int n, vector<vector<pair<int,int>>>&adj){
    priority_queue<pair<int,int>,vector<pair<int,int>>, greater<pair<int,int>>>pq;
    pq.push({0,src});
    vector<int>dist(n,1e9);
    dist[src] = 0;

    while(!pq.empty()){
        int d = pq.top().first;
        int node = pq.top().second;
        pq.pop();
        if(d>dist[node]) continue;
        for(auto it: adj[node]){
            int adjNode = it.first;
            int wt = it.second;
            if(dist[adjNode] > wt + dist[node]){
                dist[adjNode] = wt + dist[node];
                pq.push({dist[adjNode],adjNode});
            }
        }
    }
    return dist; // containing 1e9
}


//USING SET<PAIR<INT,INT>> DATA STRUCTURE

vector<int> shortestPathUsingSet(int src, int n, vector<vector<pair<int,int>>>&adj){
    set<pair<int,int>>st;
    st.insert({0,src});
    vector<int>dist(n,1e9);
    dist[src] = 0;

    while(!st.empty()){
        auto it = *(st.begin());
        int d = it.first;
        int node = it.second;
        st.erase(it);
        for(auto it: adj[node]){
            int adjNode = it.first;
            int wt = it.second;
            if(dist[adjNode] > wt + dist[node]){
                if(dist[adjNode]!=1e9) st.erase({dist[adjNode],adjNode}); // IMPORTANT STEP THIS IS THE REASON WE USE SET TO OPTIMIZE

                dist[adjNode] = wt + dist[node];
                st.insert({dist[adjNode],adjNode});
            }
        }
    }
    return dist; // containing 1e9
}