#include <iostream>
#include <vector>
#include <set>
#include <limits>
#include <queue>
#include <climits>

using namespace std;

int dijkstra(const vector<vector<pair<int, int>>>& grafo, set<int>& visitados, int origem, int destino, vector<int>& distancias) {

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> minHeap;
    distancias[origem - 1] = 0;
    minHeap.push(make_pair(0, origem));

    while (!minHeap.empty()) {


        pair<int, int> atual = minHeap.top();
        minHeap.pop();
        int verticeAtual = atual.second;

        if (visitados.count(verticeAtual) > 0)
            continue;

        visitados.insert(verticeAtual);

        if (verticeAtual == destino)
            return distancias[verticeAtual - 1];

        for (const auto& aresta : grafo[verticeAtual - 1]) {
            int nodoAdj = aresta.first;
            int peso = aresta.second;

            if (visitados.count(nodoAdj) > 0) continue;

            int novaDistancia = distancias[verticeAtual - 1] + peso;
            if (novaDistancia < distancias[nodoAdj - 1]) {
                distancias[nodoAdj - 1] = novaDistancia;
                minHeap.push(make_pair(novaDistancia, nodoAdj));
            }
        }
    }

    return INT_MAX;
}

void verificaArestas(vector<vector<pair<int, int>>>& grafo, vector<int>& distancias) {

    for (int i = 0; i < grafo.size(); i++) {
        for (int j = 0; j < grafo[i].size(); j++) {
            int nodoAdj = grafo[i][j].first;
            for (int k = 0; k < grafo[nodoAdj - 1].size(); k++) {
                if (grafo[nodoAdj - 1][k].first == i + 1) {
                    grafo[nodoAdj - 1][k].second = 0;
                    grafo[i][j].second = 0;
                }
            }
        }
    }

}

int main() {

    int numeroDeVertices = 0;
    int numeroDeArestas = 0;

    while (cin >> numeroDeVertices >> numeroDeArestas && (numeroDeVertices != 0 || numeroDeArestas != 0)) {


        vector<vector<pair<int, int>>> grafo(numeroDeVertices);
        set<int> visitados;
        vector<int> distancias(numeroDeVertices, INT_MAX);

        for (int i = 0; i < numeroDeArestas; ++i) {
            int origem, destino, peso;
            cin >> origem >> destino >> peso;
            grafo[origem - 1].push_back(make_pair(destino, peso));
        }


        int numeroDeConsultas;
        cin >> numeroDeConsultas;


        verificaArestas(grafo, distancias);
        for (int i = 0; i < numeroDeConsultas; ++i) {
            int origemConsulta, destinoConsulta;
            cin >> origemConsulta >> destinoConsulta;

            visitados.clear();
            fill(distancias.begin(), distancias.end(), INT_MAX);

            int resultado = dijkstra(grafo, visitados, origemConsulta, destinoConsulta, distancias);

            if (resultado == INT_MAX) {
                cout << "Nao e possivel entregar a carta" << endl;
            }
            else {
                cout << resultado << endl;
            }
        }
        cout << endl;
    }
    return 0;
}
