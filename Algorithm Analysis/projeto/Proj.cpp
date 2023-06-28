/*************************************
 *       Projeto ASA 2021/2022       *
 *       Carlota Tracana 99059       *
 *       Henrique Silva  99082       *
 *************************************/
#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;


/* Problem 1 - Given a sequence of integers, it calculates the length of the longest subsequence 
strictly increasing and the number of subsequences strictly increasing with the maximum length */
void problem1(vector<int> &seq) {
    int size = seq.size();
    vector<int> len(size, 1), cnt(size, 1);
    int len_max = 1;
    // reset everything to 1 bc the sequence can have at least 1 subsequence with size 1
    // len[i] will keep track of the max length and cnt[i] of how many longest subsequences at the index i
    for(int i = 0; i < size; i++){
        for(int j = 0; j < i; j++){
            if(seq[j] < seq[i]){
                if(len[i] <= len[j]){
                    // means it was found a longer subsequence then the previous one so len[i] will increase and cnt will stay the same
                    len[i] = len[j] + 1;
                    cnt[i] = cnt[j];
                    if(len_max < len[i]){
                        len_max = len[i];
                    }
                }
            
                else if(len[i] == len[j] + 1){
                    // means it was found one more subsquence with the longest length so far
                    cnt[i] += cnt[j];
                }
            }
        }
    }

    int n_subseq = 0;
    /*
    auto it = find(len.begin(), len.end(), len_max);
    while(it != len.end()){
        n_subseq += cnt[it - len.begin()];
        it = find(it + 1, len.end(), len_max);
    }*/
    for(size_t i = 0; i <= len.size(); i++){
        if(len_max == len[i]){
            n_subseq += cnt[i];
        }
    }
    cout << len_max << ' ' << n_subseq << endl;
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<nanoseconds>(stop - start);
    cout << duration.count() << endl;
}

/* Problem 2 - Given two sequences of integers, it calculates the length of the longest common 
subsequence strictly increasing between them */
void problem2(vector<int> &seq1, vector<int> &seq2) {
    int size1 = seq1.size();
    int size2 = seq2.size();
    // reset everything to 0 bc the sequences can at least have 0 in common
    vector<int> aux(size2, 0);

    for(int i = 0; i <= size1; i++){
        // where the values will be stored temporarely
        int lineVal = 0; 
        for(int j = 0; j <= size2; j++){
            // means it founds a common value
            if(seq1[i] == seq2[j] && aux[j] < lineVal + 1){
                aux[j] = lineVal + 1;
            }

            else if(seq1[i] > seq2[j] && lineVal < aux[j]){
                lineVal =  aux[j];
            }
        }
    }
    cout << *max_element(aux.begin(), aux.end()) << endl;
}

void setCommon(vector<int> seq1, vector<int> seq2, vector<int> &common){
    sort(seq1.begin(), seq1.end());
    sort(seq2.begin(), seq2.end());
    set_intersection(seq1.begin(), seq1.end(), seq2.begin(), seq2.end(), back_inserter(common));
}

/* it puts the sequence of integers from the input into a vector */
void obtainSequence(vector <int> &seq1) {
    int n;
    char c = ' ';

    while( c != '\n' && !cin.eof() ){
        cin >> n;
        c = getchar();
        seq1.push_back(n);
    }
}



vector<int> filterElementsFromSeq(vector<int> &seq, vector<int> common){
    vector<int> sequence;
    for(size_t i = 0; i <= seq.size(); i++){
        if(std::find(common.begin(), common.end(), seq[i]) != common.end()){
            sequence.push_back(seq[i]);
        }
    }
    return sequence;
}

/* Main code */
int main() {
    int op;
    vector<int> seq1;
    vector<int> seq2;
    vector<int> common;
	cin >> op;

    switch(op){
        case 1:
         obtainSequence(seq1);
         problem1(seq1);
        break;

        default:
         obtainSequence(seq1);
         obtainSequence(seq2);
         setCommon(seq1, seq2, common);
         seq1 = filterElementsFromSeq(seq1, common);
         seq2 = filterElementsFromSeq(seq2,  common);
         problem2(seq2, seq1);
    }
	return 0;
}