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


void adj_matrix_bfs(vector< vector<bool> >& adj_matrix,
        vector<Node>& nodes,
        int source, int n) {
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
}


void adj_matrix_ring_test(int n) {
    vector<vector<bool> > adj_matrix(n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            adj_matrix[i].push_back(false);
        }
    }
    for (int i = 0; i < n; ++i) {
        if (i < n - 1) {
            adj_matrix[i][i + 1] = true;
        } else {
            adj_matrix[i][0] = true;
        }
    } 

    vector<Node> nodes;
    for (int i = 0; i < n; ++i) {
        nodes.push_back(Node(i, numeric_limits<int>::max()));
    }

    adj_matrix_bfs(adj_matrix, nodes, 0, n);
}


void adj_matrix_half_connected_test(int n) {
    
}


// TODO: decide what signature will look like.
void csr_bfs();


void csr_ring_test(int n) {
    
}


void csr_half_connected_test(int n) {
    
}


int main() {
    int n;
    cin >> n;
    adj_matrix_ring_test(n);
    adj_matrix_half_connected_test(n);
    csr_ring_test(n);
    csr_half_connected_test(n);

    return 0;
}

