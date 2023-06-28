/*************************************
 *       Projeto ASA 2021/2022       *
 *       Carlota Tracana 99059       *
 *       Henrique Silva  99082       *
 *************************************/
#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <chrono>
using namespace std::chrono;
using namespace std;

/* Problem 1 - Given a sequence of integers, it calculates the length of the longest subsequence 
strictly increasing and the number of subsequences strictly increasing with the maximum length */
void problem1(vector<int> seq) {
    int size = seq.size();
    vector<int> len(size, 1), cnt(size, 1);

    for(int i = 0; i < size; i++){
        for(int j = 0; j < i; j++){
            if(seq[j] < seq[i] && len[i] < len[j] + 1){ //Se anteriores forem menores, adiciona se outro elemento 
                len[i] =  len[j] + 1;
                cnt[i] = cnt[j];
            }
            
            else if(seq[j] < seq[i] && len[i] == len[j] + 1){
                cnt[i] += cnt[j];
            }
        }
    }

    int lis = 0;
    for(int i = 0; i < size; i++){
        lis = max(lis, len[i]);       
    }
    
    int n_subseq = 0;
    for(int i = 0; i < size; i++){
        if(lis == len[i]){
            n_subseq += cnt[i];
        }   
    }
    cout << lis << ' ' << n_subseq << endl;
}
/* Problem 2 - Given two sequences of integers, it calculates the length of the longest common 
subsequence strictly increasing between them */
void problem2(vector<int> seq1, vector<int> seq2) {
    int size1 = seq1.size();
    int size2 = seq2.size();
    int aux[size2];

    for(int i = 0; i < size2; i++) //Reset everything (prevent wrong values in answer)
        aux[i] = 0;

    for(int i = 0; i < size1; i++){
        int lineVal = 0;
        for(int j = 0; j < size2; j++){
            if(seq1[i] == seq2[j])
                aux[j] = max(lineVal + 1, aux[j]);

            else if(seq1[i] > seq2[j])
                lineVal = max(lineVal, aux[j]);
        }
    }
    int len_Max = 0;
    for(int i = 0; i < size2; i++)
        len_Max = max(len_Max, aux[i]);

    cout << len_Max << endl;
}

/* it puts the sequence of integers from the input into a vector */
vector<int> obtainSequence() {
    int n;
    char c = ' ';
    vector<int> sequence;

    while(c != '\n' && cin.eof() == 0){
        cin >> n;
        c = getchar();
        sequence.push_back(n);
    }
    return sequence;
}

/* Main code */
int main() {
    int op;
    vector<int> seq1;
    vector<int> seq2;
	cin >> op;

    switch(op){
        case 1:
         seq1 = obtainSequence();
         problem1(seq1);
        break;

        default:
         seq1 = obtainSequence();
         seq2 = obtainSequence();
         problem2(seq1, seq2);
    }
	return 0;
}