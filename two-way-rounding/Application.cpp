#include <cmath>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>
#include <stddef.h>
#include <limits>
using namespace std;
#define MAX 100
struct Node {
    int id;
    int distance;
    Node(int id, int distance) : id(id), distance(distance) {}
};

struct NodeComparator {
    bool operator()(const Node& a, const Node& b)
    {
        return a.distance > b.distance;
    }
};
struct Edge {
    int src;
    int dest;
    int weight;
    Edge(int src, int dest, int weight) : src(src), dest(dest), weight(weight) {}
};

// Định nghĩa 1 graph
class Graph
{
private:
    int num_nodes_;
    vector<Edge> edges;

public:
    Graph(int numNodes) : num_nodes_(numNodes) {}

    // Thêm 1 cạnh vào graph
    void AddEdge(int src, int dest, int weight) {
        edges.emplace_back(src, dest, weight);
    }

    // Tính toán đường đi ngắn nhất giữa hai nút 
    int ShortestPath(int start, int end) {
        //Khởi tạo khoảng cách đến vô cùng và thêm nút bắt đầu vào hàng đợi
        unordered_map<int, int> distances;
        for (int i = 0; i < num_nodes_; i++) {
            distances[i] = numeric_limits<int>::max();
        }
        distances[start] = 0;
        priority_queue<Node, vector<Node>, NodeComparator> queue;
        queue.emplace(start, 0);
        // Xử lý các nút trong hàng đợi
        while (queue.empty() == 0) {
            Node current = queue.top();
            queue.pop();
            int currentId = current.id;
            int currentDistance = current.distance;

            // Kiểm tra xem chúng ta đã đến nút cuối chưa
            if (currentId == end) {
                return currentDistance;
            }
            // Cập nhật khoảng cách của các nút lân cận
            for (const Edge& edge : edges) {
                if (edge.src == currentId) {
                    int dest = edge.dest;
                    int weight = edge.weight;
                    int newDistance = currentDistance + weight;
                    if (newDistance < distances[dest]) {
                        distances[dest] = newDistance;
                        queue.emplace(dest, newDistance);
                    }
                }
            }
        }
        // không thể tìm thấy đường dẫn đến nút cuối và trả về -1
        return -1;
    }
};
int two_way_round(double x)
{
    double fractional_part = x - floor(x);
    if (fractional_part < 0.5)
    {
        return floor(x);
    }
    else if (fractional_part > 0.5)
    {
        return ceil(x);
    }
    else
    {
        if (int(x) % 2 == 0)
            return floor(x);
        return ceil(x);
    }
}
int main()
{
   
   
    Graph graph(5);  // Tao graph voi 5 Node

   //Them canh vao graph
    graph.AddEdge(0, 1, 10);
    graph.AddEdge(0, 2, 20);
    graph.AddEdge(1, 3, 5);
    graph.AddEdge(2, 3, 15);
    graph.AddEdge(2, 4, 10);
    graph.AddEdge(3, 4, 5);

    double threshold = 0.5;
    double distances[] = { 8.5, 15.2, 20.7, 11.5, 5.1, 6.3 };
    for (double& distance : distances) {
        distance = two_way_round(distance);
    }

    // Sử dụng khoảng cách được làm tròn làm trọng số của các cạnh
    graph.AddEdge(0, 1, distances[0]);
    graph.AddEdge(0, 2, distances[1]);
    graph.AddEdge(1, 3, distances[2]);
    graph.AddEdge(2, 3, distances[3]);
    graph.AddEdge(2, 4, distances[4]);
    graph.AddEdge(3, 4, distances[5]);

    // Tính đường đi ngắn nhất giữa node 0 và node 4
    int shortestPath = graph.ShortestPath(0,4 );
    cout << "Shortest path: " << shortestPath << endl;

    return 0;
}
