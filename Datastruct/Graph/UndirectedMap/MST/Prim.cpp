// Point greedy, transformation form dijistra.
#include <vector>
#include <queue>
#include <map>

#include <iostream>
#include <cassert>

// #include <bits/stdc++.h>
typedef struct edgeInfo {
    int nextV;
    int edgeW;
} edgeInfo;

typedef struct nodeInfo {
    std::vector<edgeInfo> outEdgeList;
    // int nodeW;
} nodeInfo;

#define vmax 100

int vcnt = vmax;

std::vector<nodeInfo> graph( vmax );
// std::vector<bool> visited( vmax, false );
std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<>> minVisit;
std::vector<int> dis( vmax, 1 << 30 >> 0 );

typedef struct mstNode {
    std::vector<int> outEdgeList;
} mstNode;

std::vector<mstNode> mstTree( vcnt );
std::vector<int> preNode( vcnt );

void prim( int s ) {
    // std::memset() function will set value by byte, so only for bool C style array.
    std::fill( dis.begin(), dis.end(), 1 << 30 );
    std::fill( preNode.begin(), preNode.end(), -1 );
    dis[s] = 0;
    minVisit.emplace( 0, s );
    preNode[s] = -1;
    while( !minVisit.empty() ) {
        auto [minDis, minId] = minVisit.top();
        minVisit.pop();
        if( dis[minId] < minDis ) {
            continue;
        }
        // Add into S set. And connect MST tree.
        int preId = preNode[minId];
        if( preId != -1 ) mstTree[preId].outEdgeList.push_back( minId );
        dis[minId] = 0;
        std::vector<edgeInfo> outEdgeList = graph[minId].outEdgeList;
        for( int i = 0; i < outEdgeList.size(); i++ ) {
            auto [nextV, edgeW] = outEdgeList[i];
            // int edgeW = outEdgeList[i].edgeW;
            if( edgeW < dis[nextV] ) {
                dis[nextV] = edgeW;
                preNode[nextV] = minId;
                minVisit.emplace( edgeW, nextV );
            }
        }
    }
}

void testGraphInitialization() {
    // Initialize a small graph to test
    vcnt = 4;
    graph.resize( vcnt );

    //     0
    //   /   \
    //  (1)   (4)
    // /        \
    // 1 --(2)---2
    //  \       /
    //  (5)   (1)
    //    \   /
    //     3
    // Add edges
    graph[0].outEdgeList.push_back( { 1, 1 } );
    graph[0].outEdgeList.push_back( { 2, 4 } );
    graph[1].outEdgeList.push_back( { 0, 1 } );
    graph[1].outEdgeList.push_back( { 2, 2 } );
    graph[1].outEdgeList.push_back( { 3, 5 } );
    graph[2].outEdgeList.push_back( { 0, 4 } );
    graph[2].outEdgeList.push_back( { 1, 2 } );
    graph[2].outEdgeList.push_back( { 3, 1 } );
    graph[3].outEdgeList.push_back( { 1, 5 } );
    graph[3].outEdgeList.push_back( { 2, 1 } );

    // Run the Prim algorithm
    prim( 0 );

    // Check the output MST structure
    assert( mstTree[0].outEdgeList.size() == 1 );
    assert( mstTree[0].outEdgeList[0] == 1 );
    assert( mstTree[1].outEdgeList.size() == 1 );
    assert( mstTree[1].outEdgeList[0] == 2 );
    assert( mstTree[2].outEdgeList.size() == 1 );
    assert( mstTree[2].outEdgeList[0] == 3 );
    assert( mstTree[3].outEdgeList.size() == 0 );

    std::cout << "testGraphInitialization passed!\n";
}

void testDisconnectedGraph() {
    // Test with a graph that has a disconnected component
    vcnt = 5;
    graph.clear();
    graph.resize( vcnt );
    mstTree.clear();
    mstTree.resize( vcnt );

    // Add edges only within a subset of the graph
    graph[0].outEdgeList.push_back( { 1, 3 } );
    graph[1].outEdgeList.push_back( { 0, 3 } );

    // Run Prim's algorithm from node 0
    prim( 0 );

    // Verify that only connected components have been included
    assert( mstTree[0].outEdgeList.size() == 1 );
    assert( mstTree[0].outEdgeList[0] == 1 );
    assert( mstTree[1].outEdgeList.size() == 0 );
    for( int i = 2; i < vcnt; ++i ) {
        assert( mstTree[i].outEdgeList.empty() );
    }

    std::cout << "testDisconnectedGraph passed!\n";
}

void testSingleNodeGraph() {
    // Test with a single node graph
    vcnt = 1;
    graph.clear();
    graph.resize( vcnt );
    mstTree.clear();
    mstTree.resize( vcnt );

    // Run Prim's algorithm
    prim( 0 );

    // Verify no edges in MST
    assert( mstTree[0].outEdgeList.empty() );

    std::cout << "testSingleNodeGraph passed!\n";
}

int main() {
    testGraphInitialization();
    testDisconnectedGraph();
    testSingleNodeGraph();
    std::cout << "All tests passed!\n";
    return 0;
}
