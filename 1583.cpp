#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <queue>

using namespace std;

void adicionaArestasAdj(queue<pair<int, int>>& fila, vector<pair<int, int>> nodosAdj) {

    for (int i = 0; i < nodosAdj.size(); i++) {
        fila.push(nodosAdj[i]);
    }
}



void BFS(map<pair<int, int>, vector<pair<int, int>>>& grafo, pair<int, int> nodoInicial, map<pair<int, int>, bool>& celulasContaminadas) {

    queue<pair<int, int>> fila; //fila de células;
    adicionaArestasAdj(fila, grafo[nodoInicial]);

    while (!fila.empty()) {

        pair<int, int> nodoAtual = fila.front();
        fila.pop();

        if (!celulasContaminadas[nodoAtual]) {

            celulasContaminadas[nodoAtual] = true;

            adicionaArestasAdj(fila, grafo[nodoAtual]);
        }
    }
}

void printaGrafoFinal(const map<pair<int, int>, vector<pair<int, int>>>& grafo, map<pair<int, int>, bool> celulasContaminadas, vector<string> matriz) {

    for (int i = 0; i < matriz.size(); i++) {
        for (int j = 0; j < matriz[i].size(); j++) {

            if (matriz[i][j] == 'A') {

                //verifica se esta celula foi contaminada ou não;
                if (celulasContaminadas[make_pair(i, j)]) {
                    cout << 'T';
                }
                else {
                    cout << 'A';
                }
            }
            else if (matriz[i][j] == 'T') {
                cout << 'T';
            }
            else {
                cout << matriz[i][j];
            }

        }
        cout << "\n";
    }
}

int main()
{
    vector<string> vetorLinhas = {};

    map<pair<int, int>, bool> celulasContaminadas; //representa as células que foram contaminadas por estarem no mesmo componente conexo;
    vector<pair<int, int>> nodoContaminados; // representa as células já inicialmente contaminadas;
    map<pair<int, int>, vector<pair<int, int>>> grafo;
    //o grafo é um dicionário, em que a chave é a célula (pair<i, j>) e os valores são as células às quais a primeira se conecta;

    int linhas = 6;
    int colunas = 7;

    cin >> linhas >> colunas;
    cin.ignore();

    while (linhas != 0 && colunas != 0) {

        if (linhas > 50 || colunas > 50)
            continue;

        vetorLinhas.clear();
        grafo.clear();
        nodoContaminados.clear();
        celulasContaminadas.clear();


        for (int i = 0; i < linhas; i++) {

            string linha;

            if (getline(cin, linha))
                vetorLinhas.push_back(linha);

        }

        int numNodos = 0;
        int nodoIndex = 0;

        for (int i = 0; i < linhas; i++) {
            string linhaAtual = vetorLinhas.at(i);
            for (int j = 0; j < linhaAtual.size(); j++) {

                //cada célula é um pair<linha, coluna>;
                //cada célula é um nodo;
                if (linhaAtual.at(j) == 'A' || linhaAtual.at(j) == 'T') {

                    pair<int, int> celula = make_pair(i, j);
   
                    if (linhaAtual.at(j) == 'T') {
                        celulasContaminadas[celula] = true;
                        nodoContaminados.push_back(celula);
                    }
                    else
                    {
                        celulasContaminadas[celula] = false;
                    }


                    if (j - 1 >= 0 && (linhaAtual.at(j - 1) == 'A' || linhaAtual.at(j - 1) == 'T')) {

                        pair<int, int> nodo = make_pair(i, j - 1);
                        grafo[celula].push_back(nodo);
                        grafo[nodo].push_back(celula);

                    }

                    if (i - 1 >= 0 && (vetorLinhas.at(i - 1).at(j) == 'A' || vetorLinhas.at(i - 1).at(j) == 'T'))
                    {
                        //verifica se existe nodo à cima;
                        pair<int, int> nodo;
                        nodo.first = i - 1;
                        nodo.second = j;

                        grafo[celula].push_back(nodo);
                        grafo[nodo].push_back(celula);

                    }
                }
            }
        }

        for (int i = 0; i < nodoContaminados.size(); i++) {
            BFS(grafo, nodoContaminados[i], celulasContaminadas);
        }

        printaGrafoFinal(grafo, celulasContaminadas, vetorLinhas);
        cout << "\n";

        cin >> linhas >> colunas;
        cin.ignore();
    }


}
