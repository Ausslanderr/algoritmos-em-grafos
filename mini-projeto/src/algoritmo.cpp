/*
Algoritmos em Grafos - GCC218
Professor Vinicius Vitor dos Santos Dias
Mini-Projeto
Davi Hermógenes Siqueira - 202120102
*/

#include <bits/stdc++.h>
using namespace std;


#define INF 99999

void imprimirSolucao(int** dist, int V, vector<vector<int>>& caminhos, bool aux);
void floydWarshall(int** dist, int V, vector<vector<int>>& caminhos);
void encontrarVerticesFrequentes(const vector<vector<int>>& caminhos, int V, int** dist);
void imprimirCaminhos(vector<vector<int>>& caminhos, int origem, int dest, vector<int>& freqs) {
    cout << "Caminho de " << origem << " para " << dest << ": ";
    stack<int> s;
    int atual = dest;
    while (atual != -1) {
        s.push(atual);
        atual = caminhos[origem][atual];
    }
    while (!s.empty()) {
        cout << s.top() << " ";
        freqs[s.top()]++;
        s.pop();
    }
    cout << endl;
}

int main() {
    cout<<"Qual base de dados gostaria de analisar ?"<<endl;
    cout<<"Digite: \n 1 p/ a amostra e; \n 2 p/ a completa"<<endl;
    int amostraEscolhida;
    cin>>amostraEscolhida;

    // Declarar o objeto ifstream fora do if/else
    ifstream cerebro;

    if (amostraEscolhida == 1) {
        cerebro.open("amostra-grafo.txt");
    } else {
        cerebro.open("fly-drosophila_medulla_1.txt");
    }

        int verticeA, verticeB;

        // Usar um vector para armazenar as arestas do grafo dinamicamente
        vector<pair<int, int>> arestas;

        if (cerebro.is_open()) {
            while (cerebro >> verticeA >> verticeB) {
                arestas.push_back({verticeA, verticeB});
            }
            cerebro.close();
        }

        // Encontrar o número máximo de vértices
        int numVertices = 0;
        for (const auto& aresta : arestas) {
            numVertices = max(numVertices, max(aresta.first, aresta.second));
        }
        numVertices++; // Incrementar para obter o número real de vértices

        // Alocar dinamicamente a matriz e o vetor de caminhos
        int** grafo = new int*[numVertices];
        for (int i = 0; i < numVertices; i++) {
            grafo[i] = new int[numVertices];
            fill(grafo[i], grafo[i] + numVertices, INF);
        }

        // Inicializar a matriz com 0 nas diagonais, distancia para eles mesmos é sempre zero.
        for (int i = 0; i < numVertices; i++) {
            grafo[i][i] = 0;
        }

        // Preencher a matriz de adjacência com base nas arestas do grafo
        for (const auto& aresta : arestas) {
            // Assuming all weights are 1
            grafo[aresta.first][aresta.second] = 1; // Assumindo um grafo não direcionado
            grafo[aresta.second][aresta.first] = 1; //Preciso fazer a ida e a volta para simular isso
        }

        // criando e inicializando o vetor dinâmico de caminhos
        vector<vector<int>> caminhos(numVertices, vector<int>(numVertices, -1));
        floydWarshall(grafo, numVertices, caminhos);
        cout << "Os dados foram analisados." << endl;
        encontrarVerticesFrequentes(caminhos, numVertices, grafo);
        int resposta;
        while (true){
            cout << "Caso queira visualizar, digite: ";
            cout<<"\n1 para visualizar matriz \n2 para visualizar vetor de caminhos \nou 0 para encerrar"<< endl;
            cout << ": ";
            cin >> resposta;
            switch (resposta){
                case 0:
                    return 0; //Xd.
                case 1:
                    imprimirSolucao(grafo, numVertices, caminhos, true);
                    break;
                case 2:
                    imprimirSolucao(grafo, numVertices, caminhos, false);
                    break;
                }
        }
        // Deallocate the dynamically allocated memory
        for (int i = 0; i < numVertices; i++) {
            delete[] grafo[i];
        }
        delete[] grafo;

        return 0;
}
void floydWarshall(int** dist, int V, vector<vector<int>>& caminhos) {
    int i, j, k;
    for (k = 0; k < V; k++) {
        for (i = 0; i < V; i++) {
            for (j = 0; j < V; j++) {
                if (dist[i][j] > (dist[i][k] + dist[k][j]) && (dist[k][j] != INF && dist[i][k] != INF)) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    caminhos[i][j] = k; // Rastro do caminho
                }
            }
        }
    }
}
void imprimirSolucao(int** dist, int V, vector<vector<int>>& caminhos, bool aux) {
    vector<int> frequencias(V, 0);
    if (aux) {
        cout << "A seguinte matriz mostra as distâncias mais curtas entre cada par de vértices \n";
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                if (dist[i][j] == INF)
                    cout << "INF"
                         << " ";
                else
                    cout << dist[i][j] << "   ";
            }
            cout << endl;
        }
    }

    // Imprimir os caminhos
    else {
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                if (i != j && caminhos[i][j] != -1) {
                    imprimirCaminhos(caminhos, i, j, frequencias);
                }
            }
        }
    }
}
void encontrarVerticesFrequentes(const vector<vector<int>>& caminhos, int V, int **dist) {
    unordered_map<int, int> freqMap; // Mapa para armazenar a frequência dos vértices
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (i != j && caminhos[i][j] != -1) {
                freqMap[caminhos[i][j]]++;
            }
        }
    }

    vector<pair<int, int>> freqPairs(freqMap.begin(), freqMap.end());
    sort(freqPairs.begin(), freqPairs.end(), [](const pair<int, int>& a, const pair<int, int>& b) {
        return a.second > b.second;
    });
    // Encontrar até 5 vértices mais frequentes
    cout << "Neurônios mais frequentes nos caminhos mínimos:" << endl;
    for (int i = 0; i < min(5, static_cast<int>(freqPairs.size())); ++i) {
        cout << "Neurônio " << freqPairs[i].first << ": " << freqPairs[i].second << " vezes" << endl;
    }
    cout << "Estes neurônios são centrais para o funcionamento eficiente da rede Neural analisada." << endl;
}

