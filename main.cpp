#include <iostream>
#include <limits>
#include <queue>
#include <vector>
using namespace std;


void adj_matrix_bfs(vector< vector<bool> >& adj_matrix,
        vector<int>& labels,
        int source, int n) {
    queue<int> q;
    q.push(source);
    labels[source] = 0;

    while (!q.empty()) {
        int current = q.front();
        q.pop();

        for (int neighbor = 0; neighbor < n; ++neighbor) {
            if (adj_matrix[current][neighbor]) {
                if (labels[neighbor] > labels[current] + 1) {
                    labels[neighbor] = labels[current] + 1;
                    q.push(neighbor);
                }
            }
        }
    }
}


void csr_bfs(vector<int> vertices, vector<int> edges, vector<int> labels,
        int source, int n) {
    queue<int> q;
    q.push(source);
    labels[source] = 0;

    while (!q.empty()) {
        int current = q.front();
        q.pop();

        int start = vertices[current];
        int end = n;
        if (current + 1 < n) {
            end = vertices[current + 1];
        }

        for (int offset = start; offset < end; ++offset) {
            int neighbor = edges[offset];
            if (labels[neighbor] > labels[current] + 1) {
                labels[neighbor] = labels[current] + 1;
                q.push(neighbor);
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

    vector<int> labels;
    for (int i = 0; i < n; ++i) {
        labels.push_back(numeric_limits<int>::max());
    }

    adj_matrix_bfs(adj_matrix, labels, 0, n);
}


void adj_matrix_half_connected_test(int n) {
    vector<vector<bool> > adj_matrix(n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            adj_matrix[i].push_back(false);
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < (i + n / 2) && j < n; ++j) {
            adj_matrix[i][j] = true;
        }

        if (i + n / 2 > n) {
            for (int j = 0; j < (i + n / 2) % n; ++j) {
                adj_matrix[i][j] = true;
            }
        }
    }

    vector<int> labels;
    for (int i = 0; i < n; ++i) {
        labels.push_back(numeric_limits<int>::max());
    }

    adj_matrix_bfs(adj_matrix, labels, 0, n);
}


void csr_ring_test(int n) {
    vector<int> vertices;
    vector<int> edges;
    for (int i = 0; i < n; ++i) {
        vertices.push_back(i);
        if (i < n - 1) {
            edges.push_back(i + 1);
        } else {
            edges.push_back(0);    
        }
    }

    vector<int> labels;
    for (int i = 0; i < n; ++i) {
        labels.push_back(numeric_limits<int>::max());
    }

    csr_bfs(vertices, edges, labels, 0, n);
}


void csr_half_connected_test(int n) {
    vector<int> vertices;
    vector<int> edges;

    int offset = 0;
    for (int i = 0; i < n; ++i) {
        vertices.push_back(offset);
        for (int j = i + 1; j < (i + n / 2) && j < n; ++j) {
            edges.push_back(j);
            ++offset;
        }

        if (i + n / 2 > n) {
            for (int j = 0; j < (i + n / 2) % n; ++j) {
                edges.push_back(j);
                ++offset;
            }
        }
    }

    vector<int> labels;
    for (int i = 0; i < n; ++i) {
        labels.push_back(numeric_limits<int>::max());
    }

    csr_bfs(vertices, edges, labels, 0, n);
 
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

