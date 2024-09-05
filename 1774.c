#include <stdio.h>
#include <stdlib.h>


void heapfyUp(int** minHeap, int* heapSize) {

	int index = *heapSize - 1;
	int indexPai = (index - 1) / 2;
	int* arestaTemp = NULL;

	while ((index > 0) && minHeap[indexPai][2] > minHeap[index][2]) {

		arestaTemp = minHeap[indexPai];
		minHeap[indexPai] = minHeap[index];
		minHeap[index] = arestaTemp;

		index = indexPai;
		indexPai = (index - 1) / 2;
	}
}

int** heappush(int** minHeap, int* aresta, int* heapSize, int* capacity) {

	*heapSize = *heapSize + 1;

	if (*heapSize > *capacity) {
		int** temp = (int**)realloc(minHeap, (*heapSize) * sizeof(int*));
		*capacity = *capacity + 1;
		if (temp != NULL) {
			minHeap = temp;
		}
	}

	minHeap[*heapSize - 1] = (int*)aresta;


	heapfyUp(minHeap, heapSize);

	return minHeap;
}

void heapfyDown(int** minHeap, int* heapSize) {

	int* ultimaArestaInserida = NULL;

	if (*heapSize <= 0)
		return;

	int index = 0;
	int indexFilhoEsq = 0;
	int indexFilhoDir = 0;
	int indexProcurado = 0;

	int* filhoEsq = NULL;
	int* filhoDir = NULL;
	int* temp = NULL;
	int indexSmallerChild = 0;

	while (1) {

		indexFilhoEsq = (index * 2) + 1;
		indexFilhoDir = (index * 2) + 2;

		filhoEsq = minHeap[indexFilhoEsq];
		filhoDir = minHeap[indexFilhoDir];


		if (indexFilhoEsq < *heapSize && filhoEsq[2] < filhoDir[2]) {
			indexSmallerChild = indexFilhoEsq;
		}
		else if (indexFilhoDir < *heapSize)
		{
			indexSmallerChild = indexFilhoDir;
		}
		else {
			break;
		}

		if (indexSmallerChild < *heapSize && minHeap[index][2] < minHeap[indexSmallerChild][2])
			break;


		temp = minHeap[indexSmallerChild];
		minHeap[indexSmallerChild] = minHeap[index];
		minHeap[index] = temp;

		index = indexSmallerChild;

	}


}

int* heappop(int** minHeap, int* heapSize, int* capacity) {

	if (*heapSize == 0)
		return NULL;

	int* arestaMin = minHeap[0];

	*heapSize = *heapSize - 1;
	minHeap[0] = minHeap[*heapSize];

	heapfyDown(minHeap, heapSize);

	return arestaMin;
}


int** colocaArestasAdjacentesNaHeap(int** minHeap, int** edges, int numEdges, int partida, int* heapSize, int* capacity) {

	for (int i = 0; i < numEdges; i++) {
		if (edges[i][0] == partida) {
			minHeap = heappush(minHeap, edges[i], heapSize, capacity);
		}
	}

	return minHeap;
}


int main() {


	int** edges;
	int* nodes;


	int v, e = 0; //nodos e arestas;
	scanf("%d %d", &v, &e);

	int n1, n2, value = 0;
	int arestasTotais = e * 2;

	edges = (int**)malloc(arestasTotais * sizeof(int*));
	nodes = (int*)calloc(v, sizeof(int));

	int heapSize = 0;
	int capacity = 0;
	int** minHeap = NULL;

	int counter = 0;

	for (int i = 0; i < e; i++) {

		int* edge = (int*)malloc(3 * sizeof(int));
		int* edge2 = (int*)malloc(3 * sizeof(int));

		scanf("%d %d %d", &n1, &n2, &value);

		if (edge != NULL) {
			edge[0] = n1;
			edge[1] = n2;
			edge[2] = value;
		}
		if (edge2 != NULL) {
			edge2[0] = n2;
			edge2[1] = n1;
			edge2[2] = value;
		}
		edges[counter] = edge;
		counter++;
		edges[counter] = edge2;
		counter++;
	}

	int custoTotal = 0;
	int arestasMin = 0;
	int verticeChegada = -1;
	int verticePartida = -1;

	int* arestaAtual = NULL;
	verticePartida = edges[0][0];

	nodes[verticePartida - 1] = 1;

	minHeap = colocaArestasAdjacentesNaHeap(minHeap, edges, arestasTotais, verticePartida, &heapSize, &capacity);


	while (heapSize > 0 && arestasMin != e - 1) {

		arestaAtual = heappop(minHeap, &heapSize, &capacity);

		if (arestaAtual == NULL)
			break;

		verticeChegada = arestaAtual[1];

		if (nodes[verticeChegada - 1])
			continue;

		nodes[verticeChegada - 1] = 1;

		custoTotal += arestaAtual[2];
		arestasMin++;

		minHeap = colocaArestasAdjacentesNaHeap(minHeap, edges, arestasTotais, verticeChegada, &heapSize, &capacity);

	}

	printf("%d\n", custoTotal);

	return 0;
}