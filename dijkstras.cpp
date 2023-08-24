#include <bits/stdc++.h>
using namespace std;

class Vertex;

class Edge {
public:
    Vertex* targetVertex;
    int weight;
    Edge(Vertex* target, int w) : targetVertex(target), weight(w) {}
};

class Vertex {
public:
    int id;
    vector<Edge> neighbours;
    Vertex(int _id) : id(_id) {}
};

class Graph {
    vector<Vertex> vertices;
    vector<Edge> edges;

public:
    Graph(int size) {
        vertices.reserve(size);
        for (int i = 0; i < size; i++) {
            vertices.emplace_back(i);
        }
    }

    void addEdge(int from, int to, int weight) {
        Vertex* fromVertex = &vertices[from];
        Vertex* toVertex = &vertices[to];
        edges.emplace_back(toVertex, weight);
        fromVertex->neighbours.push_back(Edge(toVertex, weight));
        toVertex->neighbours.push_back(Edge(fromVertex, weight));
    }

    vector<int> dijkstra(int start) {
        vector<int> dist(vertices.size(), INT_MAX);
        dist[start] = 0;
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        pq.push({0, start});

        while (!pq.empty()) {
            int currDist = pq.top().first;
            int currVertexId = pq.top().second;
            pq.pop();

            if (currDist > dist[currVertexId]) {
                continue;
            }

            for (const Edge& edge : vertices[currVertexId].neighbours) {
                int newDist = currDist + edge.weight;
                if (newDist < dist[edge.targetVertex->id]) {
                    dist[edge.targetVertex->id] = newDist;
                    pq.push({newDist, edge.targetVertex->id});
                }
            }
        }

        return dist;
    }

    // Rest of the methods...
};

int main() {
    Graph graph(5);
    graph.addEdge(0, 1, 3);
    graph.addEdge(1, 2, 5);
    graph.addEdge(2, 3, 2);
    graph.addEdge(3, 4, 4);

    // Dijkstra's shortest path from vertex 0
    vector<int> shortestDistances = graph.dijkstra(0);
    for (int distance : shortestDistances) {
        cout << distance << " ";
    }
    cout << endl;

    // Rest of the main...
}
