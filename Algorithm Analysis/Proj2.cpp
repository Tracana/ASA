/*************************************
 *       Projeto ASA 2021/2022       *
 *       Carlota Tracana 99059       *
 *       Henrique Silva  99082       *
 *************************************/
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <algorithm>
#include "vector"
#include <set>

#define WHITE -1
#define GRAY 0
#define BLACK 1

using namespace std;

struct Node {
	int key;
	int parents;
	int colour;
 	int nchilds;
 	vector<int> childs; 
	bool ancestral1;
	bool ancestral2;
};

//Node* table;
int v1, v2, n_vertices, n_arcs = 0;
bool is_valid_tree = true;
set <int> ancestraisComuns;

void initialize_Graph(Node *table) {
	for (int i = 1; i <= n_vertices; i++) {
		table[i].key = i;
		table[i].parents = 0;
		table[i].colour = WHITE;
		table[i].nchilds = 0;
		table[i].ancestral1 = false;
		table[i].ancestral2 = false;
		if (table[i].key == v1) {
			table[i].ancestral1 = true;
		}
		else if (table[i].key == v2) {
			table[i].ancestral2 = true;
		}
	}
}

int insert_Connection(Node *table, int VerticeX, int VerticeY) {
	if (table[VerticeX].nchilds == 0) {
		// when Vertice x doesn't have children yet
		table[VerticeX].nchilds = 1;
		if (table[VerticeY].parents < 3) {
			table[VerticeY].parents++;
		}
		else {
			return -1;
		}
		table[VerticeX].childs.push_back(VerticeY);
	} 

    else {
		// will increase the number of children of vertice X and add vertice Y as one of its children
		table[VerticeX].nchilds++;
		if (table[VerticeY].parents < 3) {
			table[VerticeY].parents++;
		}
		else {
			return -1;
		}
		table[VerticeX].childs.push_back(VerticeY);
	}
	return 0;
}

int DFS_Visit(Node *table, int node) {
	// will visit every child of the node
	table[node].colour = GRAY;
	int size = table[node].nchilds;

	for (int i = 0; i < size; i++) {
		int index = table[node].childs[i];
		if (!index) {
			return -1;
		}
		if (table[index].colour == WHITE) {
			// when the node hasn´t been visited yet
			if (DFS_Visit(table, index) == -1) {
				return -1;
			}
		}
		else if (table[index].colour == GRAY) {
			// in case we have already visited this node which means that the graph is not acyclic 
			printf("0\n");
			exit(0);
		}
		if(table[index].ancestral1 == true){
			table[node].ancestral1 = true;
		}
		if(table[index].ancestral2 == true){
			table[node].ancestral2 = true;
		}
	}
	table[node].colour = BLACK;
	return 0;
}

int DFS(Node *table) {
	for (int i = 1; i <= n_vertices; i++) {
		if (table[i].colour == WHITE) {
			if(DFS_Visit(table, i) == -1) {
				return -1;
			}
		}
	}
	for (int j = 1; j <= n_vertices; j++) {
		if (table[j].ancestral1 == true && table[j].ancestral2 == true) {
			ancestraisComuns.insert(table[j].key);
		}
	}
	return 0;
}

int show_LCA(){
	if (ancestraisComuns.empty() == true) {
		return -1;
	}
	//sort(ancestraisComuns.begin(), ancestraisComuns.end());
	for (int ancestral : ancestraisComuns) {
		printf("%d ", ancestral);
	}
	printf("\n");
	return 0;
}

int main() {
    int id_read = scanf("%d %d", &v1, &v2);
	if (id_read != 2) {
		printf("0\n");
		return 0;
	}
    int integers_read = scanf("%d %d", &n_vertices, &n_arcs);
	if (integers_read != 2) {
		printf("0\n");
		return 0;
	}

	// In order for the keys to start at index 1
    n_vertices++;
	Node table[n_vertices];

    initialize_Graph(table);
    int verticeX, verticeY = 0;

    for (int i = 1; i <= n_arcs; i++) {
        int vertices_read = scanf("%d %d", &verticeX, &verticeY);
		if (vertices_read != 2) {
			printf("0\n");
			return 0;
		}
		if (verticeX == verticeY) {
			printf("%d\n", verticeX);
			return 0;
		}
        int error = insert_Connection(table, verticeX, verticeY);
		if (error != 0) {
			printf("0\n");
			return 0;
		}
    }

	if (DFS(table) == -1) {
		printf("0\n");
		return 0;
	}
	if(show_LCA() == -1){
		printf("-\n");
		return 0;
	}
    return 0;
}