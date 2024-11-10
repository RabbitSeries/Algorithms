// Edge greedy, union search set.
#include <vector>
#include <queue>
#include <iostream>
#include <algorithm>
#include <cassert>

#define vmax 100
int vcnt = vmax;

typedef struct edgeInfo {
    edgeInfo( int _edgeW ) : edgeW( _edgeW ) {};
    int nextV;
    int edgeW;
    //    bool visited = false;
} edgeInfo;

typedef struct nodeInfo {
    std::vector<edgeInfo> outEdgeList;
} nodeInfo;

std::vector<nodeInfo> graph( vcnt );

std::vector<int> father( vcnt );

struct cmp {
    bool operator()( std::tuple<int, int, int> t1, std::tuple<int, int, int> t2 ) {
        // ! Fault logic.
        // return std::get<0>(t1)>std::get<0>(t2)?true:
        //        std::get<1>(t1)>std::get<1>(t2)?true:
        //        std::get<2>(t1)>std::get<2>(t2)
        //        ;
        return std::get<0>( t1 ) != std::get<0>( t2 ) ? std::get<0>( t1 ) > std::get<0>( t2 ) :
            std::get<1>( t1 ) != std::get<1>( t2 ) ? std::get<1>( t1 ) > std::get<1>( t2 ) :
            std::get<2>( t1 ) > std::get<2>( t2 )
            ;
    }
};

std::priority_queue<std::tuple<int, int, int>, std::vector<std::tuple<int, int, int>>, cmp> minVisit;

typedef struct mstNode {
    std::vector<int> outEdgeList;
    int inDegree = 0;
} mstNode;

std::vector<mstNode> mstTree( vcnt );
std::vector<int> mstPre( vcnt );

int findFather( int s ) {
    if( s == father[s] ) return s;
    else {
        father[s] = findFather( father[s] );
        return father[s];
    }
}

void addToSet( int s, int des ) {
    father[findFather( des )] = findFather( s );
}

void Kruskal() {
    for( int nodeCnt = 0; nodeCnt < graph.size(); nodeCnt++ ) {
        for( int nextVCnt = 0; nextVCnt < graph[nodeCnt].outEdgeList.size(); nextVCnt++ ) {
            minVisit.emplace( graph[nodeCnt].outEdgeList[nextVCnt].edgeW, nodeCnt, nextVCnt );
        }
    }
    for( int i = 0; i < vcnt; i++ ) {
        father[i] = i;
    }
    while( !minVisit.empty() ) {
        auto [minEdgeW, minEdgeSourceNode, edgeIndex] = minVisit.top();
        minVisit.pop();
        int nextV = graph[minEdgeSourceNode].outEdgeList[edgeIndex].nextV;
        if( findFather( minEdgeSourceNode ) != findFather( nextV ) ) {
            addToSet( minEdgeSourceNode, nextV );
            // Once found the minimal edge in the unvisited edge-set, add it directly to the mstTree.
            mstTree[minEdgeSourceNode].outEdgeList.push_back( nextV );
            mstTree[nextV].inDegree++;
        }
    }
}

void mstTraverse() {
    int start = -1;
    for( int i = 0; i < vcnt; i++ ) {
        if( mstTree[i].inDegree == 0 ) {
            start = i;
            break;
        }
    }
    std::queue<int> printQue;
    printQue.push( start );
    while( !printQue.empty() ) {
        int levelSize = printQue.size();
        for( int i = 0; i < levelSize; i++ ) {
            int parent = printQue.front();
            printQue.pop();
            std::cout << parent << " ";
            for( int j = 0; j < mstTree[parent].outEdgeList.size(); j++ ) {
                printQue.push( mstTree[parent].outEdgeList[j] );
            }
        }
        std::cout << std::endl;
    }
}
// Function to add an edge to the graph for testing
void addEdge( int u, int v, int weight ) {
    edgeInfo edge( weight );
    edge.nextV = v;
    graph[u].outEdgeList.push_back( edge );
}

void testKruskal() {
    // Reset global variables for testing
    vcnt = 4;  // Setting vertex count for this specific test
    graph.assign( vcnt, nodeInfo() );
    mstTree.assign( vcnt, mstNode() );
    minVisit = std::priority_queue<std::tuple<int, int, int>, std::vector<std::tuple<int, int, int>>, cmp>();

    // Create a simple connected graph:
    //      0
    //     / \
    //   (1)  (3)
    //   /     \
    //  1--(1)--2
    //   \     /
    //    (2) (2)
    //      3

    // Add edges to the graph
    addEdge( 0, 1, 1 );
    addEdge( 1, 0, 1 );  // Since this is undirected, add both directions

    addEdge( 0, 2, 3 );
    addEdge( 2, 0, 3 );

    addEdge( 1, 2, 1 );
    addEdge( 2, 1, 1 );

    addEdge( 1, 3, 2 );
    addEdge( 3, 1, 2 );

    addEdge( 2, 3, 2 );
    addEdge( 3, 2, 2 );

    // Run Kruskal's algorithm
    Kruskal();

    // Verify that the MST has the correct structure (edges 0-1, 1-2, 1-3)
    int mstEdgeCount = 0;
    for( int i = 0; i < vcnt; ++i ) {
        mstEdgeCount += mstTree[i].outEdgeList.size();
    }

    // In an MST for 4 nodes, we expect 3 edges
    assert( mstEdgeCount == 3 );

    // Verify specific edges are in the MST
    std::vector<std::pair<int, int>> expectedEdges = {
        {0, 1}, {1, 2}, {1, 3}
    };

    for( const auto& edge : expectedEdges ) {
        bool found = false;
        for( int v : mstTree[edge.first].outEdgeList ) {
            if( v == edge.second ) {
                found = true;
                break;
            }
        }
        assert( found && "Expected edge not found in MST" );
    }

    std::cout << "All tests passed!" << std::endl;
}

int main() {
    testKruskal();
    return 0;
}
