#include <bits/stdc++.h>

using namespace std;

void g(bitset<8> w_1, int round) {

    cout << endl << "--------------Função g-------------" << endl;


    bitset<4> n_0;
    bitset<4> n_1;

    // separando w_1 na metade
    for (int i = 3; i >= 0; i--){
        
        n_0[i] = w_1[i+4];
        n_1[i] = w_1[i];
    }

    cout << w_1 << endl;
    cout << n_0.to_ullong() << endl;
    cout << n_1.to_ullong() << endl;


    vector<bitset<4>> s_box = { 
        0b1001, 0b0100, 0b1010, 0b1011,
        0b1101, 0b0001, 0b1000, 0b0101, 
        0b0110, 0b0010, 0b0000, 0b0011,
        0b1100, 0b1110, 0b1111, 0b0111 
    };

    // aplicando s_box e invertendo as metades
    bitset<4> n_0_s_box(s_box[n_1.to_ullong()]); 
    bitset<4> n_1_s_box(s_box[n_0.to_ullong()]);

    // juntando as metades apos passar pela s-box
    bitset<8> n(n_0_s_box.to_string().append(n_1_s_box.to_string()));

    if (round == 1){

        
    }

}

void expand_key(bitset<16> chave, int round) {

        cout << endl << "--------------Expand Key-------------" << endl;


    bitset<8> w_0;
    bitset<8> w_1;
    
    for(int i = 7; i >= 0; i--){
        
        w_0[i] = chave[i + 8];
        w_1[i] = chave[i];
    }

    g(w_1, round);
}