#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

struct conjuntoDisjunto {
    int* predecessor, *g, tamanho, conjunto1, conjunto2;
    int encontrar(int i) {
        if (predecessor[i] == -1)
            return i;
        return predecessor[i] = encontrar(predecessor[i]);
    }
    void unir(int x, int y) {
        conjunto1 = encontrar(x);
        conjunto2 = encontrar(y);
        if (conjunto1 != conjunto2) {
            if (g[conjunto1] < g[conjunto2]) {
                predecessor[conjunto1] = conjunto2;
            }
            else if (g[conjunto1] > g[conjunto2]) {
                predecessor[conjunto2] = conjunto1;
            }
            else {
                predecessor[conjunto2] = conjunto1;
                g[conjunto1] += 1;
            }
        }
    }
    conjuntoDisjunto(int tamanho) {
        this->tamanho = tamanho;
        predecessor = new int[tamanho];
        g = new int[tamanho];
        for (int i = 0; i < tamanho; i++) {
            predecessor[i] = -1;
            g[i] = 1;
        }
    }
};
class Grafo {
    private:
        vector<vector<int>> lista_arestas;
        int V;
    public:
        void adicionarAresta(int aresta1, int aresta2, int custo) {
            lista_arestas.push_back({ custo, aresta1, aresta2 });
        }
        void kruskal() {
            sort(lista_arestas.begin(), lista_arestas.end());
            conjuntoDisjunto s(V);
            int custoTotal = 0;
            int custo, aresta1, aresta2;
            for (int i = 0; i < lista_arestas.size(); i++) {
                custo = lista_arestas[i][0];
                aresta1 = lista_arestas[i][1];
                aresta2 = lista_arestas[i][2];
                if (s.encontrar(aresta1) != s.encontrar(aresta2))
                    {
                    s.unir(aresta1, aresta2);
                    custoTotal += custo;
                    }
                }cout << custoTotal << endl;
        }
        Grafo(int V) {
            this->V = V;
        }
    };
int main() {
    int vertices, arestas;
    while (cin >> vertices >> arestas){
        if (vertices==0 && arestas ==0){
            break;
        }
        Grafo g(vertices);
        for(int i = 0; i < arestas; i++) {
            int v1, v2, custo;
            cin >> v1 >> v2 >> custo;
            g.adicionarAresta(v1, v2, custo);
        }
        g.kruskal();
    }
    return 0;
}
