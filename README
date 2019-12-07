# kNN search on moving objects with V-Tree

<p>In the transportation system, k nearest neighbor is a critical technique to find the near objects. For instance, Uber utilizes kNN to help users find sharing vehicles. In this program, I create a data structure, called V-Tree to implement kNN search, and use object-oriented programming to model the nodes of the tree. The way of constructing the tree, and algorithms are based on a paper(in the reference) from Tsinghua Uinversity, and the following definition is extracted from the paper. If you want to understand deeper how the algorithms work, please study the whole paper.</p>

## Content
[TOC]


## How to build a V-Tree?

- In the following example, I will use the map provided from the paper to demonstrate how to separate a map into four subgraphs. The V-Tree is a balanced tree, so every node should have the same vertices.

### Find the subgrapgs of the V-Tree

- 1. According to f equals to two, we separate the map into two subgraphs, and we get the Level 1 as in Fig 1.

- 2. Since the vertices in nodes are more than four, we need to keep separating the tree until the vertices in a node in less or equal than four.

Figure 1.
![](https://i.imgur.com/cSGyeQv.png)



### Create Distance Matrix for each node

<p>After the V-Tree is established, the distance matrix will not be updated, and this is one of the reasons why the V-Tree is faster. In this program, I will use the distance matrix provided by the authors. The distance matrix of every node is shown in Fig. 2</p>

Figure 2.
![](https://i.imgur.com/38zpafe.png)


### Create LNAV Lists, and active object lists

<p>In each node, every vertex should hold an LNAV list to store its nearest active vertex. For instance, in L2 graph, the node has v1 to v4 nodes, and every node needs to store the nearest vertex, and also an object list, storing how many vehicles in the vertex.</p>


## Algorithms

### Boundary Vertex
<p>The vertex which connects to another vertex in another graph is defined as a boundary vertex, and the parent of subgraphs will record boundary vertexes of both subgraphs.</p>

### SPDist: shortest path distance
<p>This algorithm is used to find the distance of any two vertices on the map. To find the shortest path, there are two cases. First, if the two vertices are in the same subgraph, then the shortest path must exist in the subgraph. In the other case, the shortest path must path the boundary vertices of the graph. In my implementation, the OOP structure can use recursive to find the SPDist.</p>

:::warning
LNAVDistGav (β, v) = SPDist(β, v) + L[β]Gav .δ
:::


### Updating V-Tree
<p>To model the road system with the V-tree, we also need to figure out how to add, delete a vehicle. Moreover, while the vehicle is moving, the distance to the destination should become shorter. In my implementation, the vehicle will move toward the destination as time goes by, and the vehicle will return to the start point when it reaches the destination.</p>

- Note: To be specific, while adding a new object to a vertex, the ancestor of the subgraph also has to be updated because the nearest vertex may be different after adding the new vehicle. According to the authors, updating is the advantage of distributed tree data structure since the complexity will be reduced to O(log(n)).

### gnav, nnav
- gnav is used to find the global nearest vertex. The nearest vertex may in other graphs, so this function has to make sure whether the gnav is in the same subgraph or in another graph.

- nnav is the next nearest active vertex. The algorithm is to delete the vertex which has been found in the last gnav and find the next gnav.

::: info
With gnav and nnav, we can now build kNN algorithm.
:::

### kNN

- 1. Maintain a sorted queue which length is k.

- 2. If the algorithm finds a shorter distance to an object, it will pop an object in the list and insert the new vertex into the queue.

- 3. After the searching, we can see the list of the shortest vertex.

:::success
So far, we have discussed how to build a V-Tree with a vertices map, and how to use the data structure to complete the kNN search. In the following, I will use Window Form to demonstrate the data structure and show how to interact with the interface.
:::

## Implement kNN search with GUI

- In fugure 3, it is a snapshot of my interface. The blue squares represent the vertices, the black lines are the roads connecting the vertices, and the red points represent vehicles. The users can use add the Vehicle button to add a new object to an edge and press the kNN search button to search.

Fig.3
![](https://i.imgur.com/9v3r2ki.png)


- After pressing knn search, users can input the searching center and the number of nearest objects the users want to search for. The result of searching will show immediately after returning to Map Form screen. The light-blue center represents the searching center, and the circled objects are the objects that are near to the center.




- Fig. 4
 ![](https://i.imgur.com/hYD4cf0.png)

- Fig. 5 - searching result
 ![](https://i.imgur.com/L0dP9CQ.png)

 ## Discussion

 <p>In the V-Tree model, the algorithm may miss some objects which are actually closer to the object. The reason is the algorithm uses the vertices as the searching nodes, i.e. the calculation of shortest distance must pass through at least a vertex. Hence, in some cases, although the object is closer, the distance becomes longer after including the distance of reaching vertices. For instance, in fig 6. a red point on edge 6 to 13 is closer than the point on 15 to 16, but since the car is moving toward 13, the algorithm needs to pass through vertex 13 to reach the object..</p>



- Fig. 6
![](https://i.imgur.com/NbyJupy.png)


## Reference
https://ieeexplore.ieee.org/document/7930011
