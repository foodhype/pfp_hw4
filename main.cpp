#include <iostream>
#include <limits>
#include <queue>
#include <vector>
using namespace std;


class Node {
    public:
        int _id;
        int _label;
        Node(int id, int label);
};


Node::Node(int id, int label) {
    _id = id;
    _label = label;
}


int bfs(vector< vector<bool> >& adj_matrix,
        vector<Node>& nodes,
        int source, int m, int n) {
    queue<int> q;
    q.push(source);
    nodes[source]._label = 0;

    while (!q.empty()) {
        int current = q.front();
        q.pop();

        for (int neighbor = 0; neighbor < n; ++neighbor) {
            if (adj_matrix[current][neighbor]) {
                if (nodes[neighbor]._label > nodes[current]._label + 1) {
                    nodes[neighbor]._label = nodes[current]._label + 1;
                    q.push(neighbor);
                }
            }
        }
    }

    return 0;
}


int main() {
    int m, n;
    cin >> m;
    cin >> n;
    vector<vector<bool> > adj_matrix(m);
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            adj_matrix[i].push_back(false);
        }
    }
    for (int i = 0; i < m; ++i) {
        if (i < m - 1) {
            adj_matrix[i][i + 1] = true;
        } else {
            adj_matrix[i][0] = true;
        }
    } 

    vector<Node> nodes;
    for (int i = 0; i < m; ++i) {
        nodes.push_back(Node(i, numeric_limits<int>::max()));
    }

    bfs(adj_matrix, nodes, 0, m, n);

    return 0;
}

