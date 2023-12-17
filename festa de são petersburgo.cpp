#include <iostream>
#include <vector>

/*
Aluno -> Davi Hermógenes Siqueira 202120102
Professor -> Vinicius Vitor dos Santos Dias
GCC218 - Algoritmos em Grafos
*/

using namespace std;
int main() {

    int n, m, k;
    while (cin >> n >> m >> k) {
        vector<vector<int>> relacoes(n + 1, vector<int>(n + 1, 0));
        vector<int> convidados(n + 1, 0);

        int n1, n2;
        //Construindo matriz de adjacencia
        for (int i = 1; i <= m; i++) {
            cin >> n1 >> n2;
            relacoes[n1][n2] = 1;
            relacoes[n2][n1] = 1;
            convidados[n1]++;
            convidados[n2]++;
        }

        bool mudanca = true;
        while (mudanca) {
            mudanca = false;
            for (int i = 1; i <= n; i++) {
                if (convidados[i] > 0 && convidados[i] < k) {
                    for (int j = 1; j <= n; j++) {
                        if (relacoes[i][j] == 1) {
                            relacoes[i][j] = 0;
                            relacoes[j][i] = 0;
                            convidados[j]--;
                        }
                    }
                    convidados[i] = 0;
                    mudanca = true;
                }
            }
        }

    bool possuiConvidado = false; // Verificador
    vector<int> convidadosParaImprimir;
    
    for (int i = 1; i <= n; i++) {
        if (convidados[i] >= k) {
            possuiConvidado = true;
            convidadosParaImprimir.push_back(i);
        }
    }
    if (!possuiConvidado) {
        cout<<0;
    } else {
        for (int i = 0; i < convidadosParaImprimir.size(); i++) {
            if (i > 0) cout << " ";
            cout << convidadosParaImprimir[i];
        }
    }
    cout<<endl;
    }
    return 0;
};
