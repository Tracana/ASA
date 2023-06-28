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

#define WHITE 0
#define GRAY 1
#define BLACK 2

using namespace std;

struct Node {
	int parents = 0;
	int colour = WHITE;
 	int nchilds = 0;
 	vector<int> childs; 
	bool ancestral1 = false;
	bool ancestral2 = false;
};

int v1, v2, n_vertices, n_arcs = 0;
set <int> ancestraisComuns;

int insert_Connection(Node *table, int VerticeX, int VerticeY) {
	// will increase the number of children of vertice X and add vertice Y as one of its children
	table[VerticeX].nchilds++;
	if (table[VerticeY].parents < 2) {
		table[VerticeY].parents++;
	}
	else {
		return -1;
	}
	table[VerticeX].childs.push_back(VerticeY);

	return 0;
}

bool any_child(Node *table, Node parent){
	int n_child = parent.nchilds;
	for(int i = 0; i < n_child; i++){
		if(table[parent.childs[i]].ancestral1 == true && table[parent.childs[i]].ancestral2 == true){
			return false;
		}
	}
	return true;
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

	for(int x = 1; x <= n_vertices; x++){
		if (table[x].ancestral1 == true && table[x].ancestral2 == true && any_child(table, table[x])) {
			ancestraisComuns.insert(x);
		}
	}
	return 0;
}

int show_LCA(){
	if (ancestraisComuns.empty() == true) {
		return -1;
	}
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
	if(v1 == v2){
		printf("%d \n", v1);
		return 0;
	}
    int integers_read = scanf("%d %d", &n_vertices, &n_arcs);
	if (integers_read != 2) {
		printf("0\n");
		return 0;
	}

	Node *table = (Node*) malloc(sizeof(Node) * (n_vertices + 1));
	table[v1].ancestral1 = true;
	table[v2].ancestral2 = true;

    int verticeX, verticeY;

    for (int i = 0; i < n_arcs; i++) {
        int vertices_read = scanf("%d %d", &verticeX, &verticeY);
		if (vertices_read != 2) {
			printf("0\n");
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