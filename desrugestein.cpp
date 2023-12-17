#include <iostream>
#include <vector>
#include <climits>

const int INFINITY = INT_MAX;

struct Graph {
    std::vector<std::vector<int>> adjMatrix;
    int size;

    Graph(int n) : size(n), adjMatrix(n, std::vector<int>(n, INFINITY)) {
        for (int i = 0; i < size; ++i) {
            adjMatrix[i][i] = 0;
        }
    }

    void initialize() {
        for (int i = 0; i < size; ++i) {
            std::fill(adjMatrix[i].begin(), adjMatrix[i].end(), INFINITY);
            adjMatrix[i][i] = 0;
        }
    }

    void floydWarshall() {
        for (int k = 0; k < size; ++k) {
            for (int i = 0; i < size; ++i) {
                for (int j = 0; j < size; ++j) {
                    if (adjMatrix[i][k] < INFINITY && adjMatrix[k][j] < INFINITY) {
                        adjMatrix[i][j] = std::min(adjMatrix[i][j], adjMatrix[i][k] + adjMatrix[k][j]);
                    }
                }
            }
        }
    }

    int shortestDistance(int u, int v) {
        return adjMatrix[u][v];
    }
};

int main() {
    int n, u, v, z, w, queries;

    do {
        std::cin >> n;
        if (n == 0) break;

        Graph g(n * n);
        g.initialize();

        for (int i = n - 1; i >= 0; --i) {
            for (int j = 0; j < n; ++j) {
                std::cin >> u >> v >> z >> w;
                int index = i * n + j;

                if (u == 1) g.adjMatrix[index][index + n] = 1;
                if (v == 1) g.adjMatrix[index][index - n] = 1;
                if (z == 1) g.adjMatrix[index][index - 1] = 1;
                if (w == 1) g.adjMatrix[index][index + 1] = 1;
            }
        }

        g.floydWarshall();

        std::cin >> queries;
        while (queries--) {
            std::cin >> u >> v >> z >> w;
            u = u + v * n;
            z = z + w * n;

            int distance = g.shortestDistance(u, z);
            if (distance != INFINITY) {
                std::cout << distance << '\n';
            } else {
                std::cout << "Impossible\n";
            }
        }
        std::cout << '\n';
    } while (true);

    return 0;
}
