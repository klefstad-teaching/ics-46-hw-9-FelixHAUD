#include <gtest/gtest.h>

#include "dijkstras.h"
#include "ladder.h"
#include <iostream>

TEST(DijkstraTest, ShortestPathTest) {
    Graph G;
    G.numVertices = 5;
    G.resize(G.numVertices);

    G[0].push_back(Edge(0, 1, 10));
    G[0].push_back(Edge(0, 2, 5));
    G[1].push_back(Edge(1, 2, 2));
    G[1].push_back(Edge(1, 3, 1));
    G[2].push_back(Edge(2, 1, 3));
    G[2].push_back(Edge(2, 3, 9));
    G[3].push_back(Edge(3, 4, 4));
    G[4].push_back(Edge(4, 0, 7));

    vector<int> previous;

    vector<int> distances = dijkstra_shortest_path(G, 0, previous);

    EXPECT_EQ(distances[0], 0); 
    EXPECT_EQ(distances[1], 8); 
    EXPECT_EQ(distances[2], 5); 
    EXPECT_EQ(distances[3], 9); 
    EXPECT_EQ(distances[4], 13); 
}

TEST(DijkstraTest, ExtractPathTest) {
    Graph G;
    G.numVertices = 5;
    G.resize(G.numVertices);

    G[0].push_back(Edge(0, 1, 10));
    G[0].push_back(Edge(0, 2, 5));
    G[1].push_back(Edge(1, 2, 2));
    G[1].push_back(Edge(1, 3, 1));
    G[2].push_back(Edge(2, 1, 3));
    G[2].push_back(Edge(2, 3, 9));
    G[3].push_back(Edge(3, 4, 4));
    G[4].push_back(Edge(4, 0, 7));
      
    vector<int> previous;

    vector<int> distances = dijkstra_shortest_path(G, 0, previous);

    vector<int> path = extract_shortest_path(distances, previous, 3);

    std::vector<int> expected_path = {0, 2, 1, 3};
    EXPECT_EQ(path, expected_path);
}

TEST(PrintPathTest, ValidPath) {
    Graph G;
    G.numVertices = 5;
    G.resize(G.numVertices);

    G[0].push_back(Edge(0, 1, 2));
    G[1].push_back(Edge(1, 2, 3));
    G[0].push_back(Edge(0, 2, 5));
    G[2].push_back(Edge(2, 3, 1));
    G[3].push_back(Edge(3, 4, 4));

    vector<int> previous;
    vector<int> distances = dijkstra_shortest_path(G, 0, previous);

    vector<int> path = extract_shortest_path(distances, previous, 4);
    int totalWeight = distances[4];

    testing::internal::CaptureStdout(); 
    print_path(path, totalWeight);
    string output = testing::internal::GetCapturedStdout(); 

    string expectedOutput = "Shortest path: Total Weight = 10\n0 -> 2 -> 3 -> 4\n";
    EXPECT_EQ(output, expectedOutput);
}