# 2492. Minimum Score of a Path Between Two Cities

## Problem Statement

You are given an undirected weighted graph with `n` cities numbered from `1` to `n`.

Each road is represented as:

```cpp
{city1, city2, distance}
```

The graph is connected in such a way that there exists at least one path from city `1` to city `n`.

The **score** of a path is defined as the **minimum edge weight** present on that path.

Return the **minimum possible score** of any path between city `1` and city `n`.

---

# Approach 1 : BFS (Graph Traversal)

## Intuition

The most important observation of this problem is that:

> We are allowed to visit the same city multiple times.

Because revisiting is allowed, we are not restricted to taking a simple path.

Suppose the graph is

```
        8
   1 -------- 2
    \        /
     4      6
      \    /
        3
```

If we want to travel from `1` to `2`, we can even do

```
1 → 3 → 1 → 2
```

or

```
1 → 2 → 3 → 2
```

Since revisiting is allowed, we can freely move anywhere inside the connected component containing city `1`.

Therefore,

> The answer is simply the minimum edge present anywhere inside the connected component containing city `1`.

So instead of searching for paths, we only need to traverse the connected component once and keep track of the minimum edge weight encountered.

Since the graph is undirected, BFS (or DFS) is sufficient.

---

# Algorithm

1. Create an adjacency list.
2. Start BFS from city `1`.
3. Maintain a visited array.
4. Every time we see an edge, update

```cpp
ans = min(ans, edgeWeight);
```

5. Visit all reachable nodes.
6. Return `ans`.

---

# Dry Run

Input

```
n = 4

roads =

1 --9-- 2
|
7
|
3 --5-- 4
```

Adjacency List

```
1 -> (2,9), (3,7)

2 -> (1,9)

3 -> (1,7), (4,5)

4 -> (3,5)
```

Initially

```
Queue

1

Visited

1

Answer = INF
```

---

### Pop 1

Neighbours

```
(2,9)

Answer=min(INF,9)=9

Push 2

----------------

(3,7)

Answer=min(9,7)=7

Push 3
```

Queue

```
2 3
```

---

### Pop 2

Neighbour

```
(1,9)

Answer=min(7,9)=7
```

Nothing to push.

Queue

```
3
```

---

### Pop 3

Neighbour

```
(1,7)

Answer=min(7,7)=7
```

Neighbour

```
(4,5)

Answer=min(7,5)=5

Push 4
```

Queue

```
4
```

---

### Pop 4

Neighbour

```
(3,5)

Answer=min(5,5)=5
```

Queue becomes empty.

Final Answer

```
5
```

---

# Code

```cpp
class Solution {
public:
    int minScore(int n, vector<vector<int>>& roads) {

        vector<vector<pair<int,int>>> adj(n + 1);

        for(auto it : roads){
            adj[it[0]].push_back({it[1], it[2]});
            adj[it[1]].push_back({it[0], it[2]});
        }

        int ans = INT_MAX;
        vector<int> vis(n + 1, 0);
        queue<int> q;
        q.push(1);
        vis[1] = 1;

        while(!q.empty()){
            int node = q.front();
            q.pop();
            for(auto &adjNode : adj[node]){
                ans = min(ans, adjNode.second);
                if(!vis[adjNode.first]){
                    q.push(adjNode.first);
                    vis[adjNode.first] = 1;
                }
            }
        }
        return ans;
    }
};
```

---

# Code Explanation

## Creating the adjacency list

```cpp
vector<vector<pair<int,int>>> adj(n + 1);
```

Each node stores

```
(neighbour, edgeWeight)
```

Example

```
1 --5-- 2
```

Stored as

```
adj[1] = {(2,5)}

adj[2] = {(1,5)}
```

---

## Building the graph

```cpp
for(auto it : roads){

    adj[it[0]].push_back({it[1], it[2]});

    adj[it[1]].push_back({it[0], it[2]});
}
```

Since the graph is undirected, every edge is inserted twice.

---

## Initialize answer

```cpp
int ans = INT_MAX;
```

Initially the minimum edge is unknown.

---

## Visited array

```cpp
vector<int> vis(n + 1, 0);
```

Ensures each city is visited only once.

---

## BFS Queue

```cpp
queue<int> q;

q.push(1);

vis[1] = 1;
```

Start BFS from city `1`.

---

## BFS Traversal

```cpp
while(!q.empty())
```

Traverse every city in the connected component.

---

## Remove current node

```cpp
int node = q.front();

q.pop();
```

---

## Traverse neighbours

```cpp
for(auto &adjNode : adj[node])
```

Each neighbour contains

```
adjNode.first

Neighbour

adjNode.second

Weight
```

---

## Update minimum edge

```cpp
ans = min(ans, adjNode.second);
```

Every edge inside the connected component is checked.

Eventually `ans` becomes the minimum edge in that component.

---

## Visit new nodes

```cpp
if(!vis[adjNode.first]){
    q.push(adjNode.first);
    vis[adjNode.first] = 1;
}
```

Standard BFS traversal.

---

# Why does this work?

Suppose

```
1 ----9---- 2
 \
  \
   4
    \
     3
```

Normally, we would think of finding paths.

But the problem allows revisiting cities.

Therefore, once we can reach a city, we can freely travel anywhere inside that connected component.

Hence the answer becomes

> Minimum edge present in the connected component containing city `1`.

BFS visits exactly that component.

---

# Time Complexity

Building adjacency list

```
O(E)
```

BFS traversal

```
O(V + E)
```

Overall

```
O(V + E)
```

where

- `V` = Number of cities
- `E` = Number of roads

---

# Space Complexity

Adjacency List

```
O(V + E)
```

Visited Array

```
O(V)
```

Queue

```
O(V)
```

Overall

```
O(V + E)
```

---

# Key Takeaway

This problem looks like a shortest path problem at first glance, but it is actually a graph traversal problem.

The crucial observation is:

> Since revisiting cities is allowed, every edge inside the connected component of city `1` can potentially be part of some valid path.

Therefore, simply traversing the connected component once and taking the minimum edge weight gives the correct answer.


# Approach 2 : Disjoint Set Union (Union Find)

## Intuition

The key observation remains the same:

> Since revisiting cities is allowed, we can travel anywhere inside the connected component containing city `1`.

Therefore, instead of finding a particular path, we only need to determine:

1. Which cities belong to the same connected component as city `1`.
2. Among all the roads in that connected component, find the minimum edge weight.

A Disjoint Set Union (DSU) or Union Find data structure is perfect for identifying connected components.

The solution consists of two phases:

- **Phase 1:** Build the connected components using Union Find.
- **Phase 2:** Iterate through every road and consider only those roads whose endpoints belong to the connected component containing city `1`. Among those roads, return the minimum edge weight.

---

# What is Disjoint Set Union (DSU)?

A DSU is a data structure used to efficiently maintain multiple connected components.

Each connected component has one representative called its **root** (or leader).

For example,

```
1 ---- 2 ---- 3

4 ---- 5
```

Initially,

```
{1}
{2}
{3}
{4}
{5}
```

After processing the roads,

```
{1,2,3}

{4,5}
```

Every node inside the same component has the same representative.

---

# Algorithm

### Step 1

Initially every city is its own parent.

```
parent[i]=i
```

Example

```
1

2

3

4
```

Each city forms its own component.

---

### Step 2

Process every road.

For every road

```
u ----- v
```

merge the connected components containing `u` and `v`.

```
parent[find(u)] = find(v)
```

After processing all roads, every connected component is formed.

---

### Step 3

Find the representative of city `1`.

Now iterate over every road.

If one endpoint of that road belongs to the same component as city `1`, then that road also belongs to that connected component.

Update the minimum edge weight.

---

# Dry Run

Input

```
n = 4

roads =

1 --9-- 2
2 --6-- 3
3 --5-- 4
```

---

## Initially

```
Parent

1
2
3
4
```

Array

```
Index : 1 2 3 4

Parent: 1 2 3 4
```

---

## Process Road (1,2)

```
parent[find(1)] = find(2)
```

Since

```
find(1)=1

find(2)=2
```

Update

```
parent[1]=2
```

Tree

```
1
 \
 2
```

Parent Array

```
1 : 2

2 : 2

3 : 3

4 : 4
```

---

## Process Road (2,3)

```
parent[find(2)] = find(3)
```

```
find(2)=2

find(3)=3
```

Update

```
parent[2]=3
```

Tree

```
1
 \
 2
  \
   3
```

Parent Array

```
1 : 2

2 : 3

3 : 3

4 : 4
```

---

## Process Road (3,4)

```
parent[find(3)] = find(4)
```

```
find(3)=3

find(4)=4
```

Update

```
parent[3]=4
```

Tree

```
1
 \
 2
  \
   3
    \
     4
```

Parent Array

```
1 : 2

2 : 3

3 : 4

4 : 4
```

Notice that

```
parent[1]=2
```

but

```
1
```

actually belongs to the component whose representative is

```
4
```

This is why we must always use `find()` instead of directly comparing the parent array.

---

# Why do we use find() instead of parent[] ?

Suppose after all unions,

```
Parent Array

1 : 2

2 : 3

3 : 4

4 : 4
```

Now consider cities `1` and `3`.

If we compare

```cpp
parent[1] == parent[3]
```

we get

```
2 == 4

False
```

which incorrectly suggests that the cities belong to different components.

However,

```
find(1)

1 → 2 → 3 → 4

returns 4

find(3)

3 → 4

returns 4
```

Therefore

```cpp
find(1)==find(3)
```

becomes

```
4==4

True
```

which is correct.

**Important:**

- `parent[i]` stores only the **immediate parent**.
- `find(i)` returns the **representative (root)** of the entire connected component.

Hence the condition

```cpp
find(r[0]) == find(1)
```

correctly checks whether the road belongs to the same connected component as city `1`.

---

# Code

```cpp
class Solution {
public:

    vector<int> parent;
    int find(int i){
        if(parent[i] == i) return i;
        return parent[i] = find(parent[i]);
    }

    int minScore(int n, vector<vector<int>>& roads) {

        parent.resize(n + 1);
        iota(parent.begin(), parent.end(), 0);

        for(auto &r : roads) parent[find(r[0])] = find(r[1]);

        int res = INT_MAX;

        for(auto &r : roads){
            if(find(r[0]) == find(1)) res = min(res, r[2]);
        }
        return res;
    }
};
```

---

# Code Explanation

## Parent Array

```cpp
vector<int> parent;
```

Stores the parent of every node.

Initially every node is its own parent.

---

## Find Function

```cpp
int find(int i){

    if(parent[i]==i)
        return i;

    return parent[i]=find(parent[i]);
}
```

Returns the representative (root) of the connected component.

It also performs **path compression**, making future operations much faster.

Example

Before compression

```
1

↓

2

↓

3

↓

4
```

After calling

```
find(1)
```

the structure becomes

```
1

↓

4

2

↓

4

3

↓

4
```

making subsequent `find()` operations almost constant time.

---

## Initialize DSU

```cpp
parent.resize(n+1);
iota(parent.begin(), parent.end(), 0);
```

Initially

```
parent[i]=i
```

Each node is in its own connected component.

---

## Union Operation

```cpp
for(auto &r : roads)
    parent[find(r[0])] = find(r[1]);
```

For every road,

- Find the representative of both endpoints.
- Merge the two connected components.

This builds all connected components.

---

## Find Minimum Edge

```cpp
for(auto &r : roads){
    if(find(r[0])==find(1))
        res=min(res,r[2]);
}
```

If one endpoint belongs to the same connected component as city `1`, then the entire road belongs to that connected component.

Update the minimum edge weight.

---

# Why does checking only one endpoint work?

Every road

```
u ----- v
```

was already processed during the union phase.

Therefore,

```
find(u)==find(v)
```

for every road.

So checking

```cpp
find(u)==find(1)
```

is sufficient.

Checking both endpoints is unnecessary because both endpoints always belong to the same connected component after all unions.

---

# Time Complexity

Initializing DSU

```
O(N)
```

Union all roads

```
O(E · α(N))
```

Traverse all roads

```
O(E · α(N))
```

Overall

```
O((N + E) · α(N))
```

where

- `N` = Number of cities
- `E` = Number of roads
- `α(N)` = Inverse Ackermann Function (practically ≤ 4 for all real-world inputs)

Hence, the solution is effectively linear.

---

# Space Complexity

Parent Array

```
O(N)
```

No additional graph storage is required.

Overall

```
O(N)
```

---

# Key Takeaway

The problem is **not** about finding a shortest path.

The crucial observation is:

> Since revisiting cities is allowed, every city reachable from city `1` belongs to the same connected component, and every road inside that component can potentially be included in some valid path.

The Union Find approach efficiently identifies this connected component without explicitly traversing the graph. Once the components are built, the answer is simply the minimum edge weight among all roads belonging to the component containing city `1`.