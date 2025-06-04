#include <bits/stdc++.h>

using namespace std;

bitset<8> g_function(bitset<8> w_1, int round) {

    //cout << endl << "--------------Função g-------------" << endl;


    bitset<4> n_0;
    bitset<4> n_1;
    bitset<4> temp;

    // separando w_1 na metade
    for (int i = 3; i >= 0; i--){
        
        n_0[i] = w_1[i+4];
        n_1[i] = w_1[i];
    }

    // troca
    n_0 = temp;
    n_0 = n_1;
    n_1 = temp;

    vector<bitset<4>> s_box = { 
        0b1001, 0b0100, 0b1010, 0b1011,
        0b1101, 0b0001, 0b1000, 0b0101, 
        0b0110, 0b0010, 0b0000, 0b0011,
        0b1100, 0b1110, 0b1111, 0b0111 
    };

    // aplicando s_box e invertendo as metades
    bitset<4> n_0_s_box(s_box[n_0.to_ullong()]); 
    bitset<4> n_1_s_box(s_box[n_1.to_ullong()]);

    // juntando as metades apos passar pela s-box
    bitset<8> n;
    for (int i = 3; i >= 0; i--){
        n[i + 4] = n_0_s_box[i];
        n[i] = n_1_s_box[i];
    }


    bitset<8> rconst;
    if (round == 1){
        rconst = 0b10000000;       
    }
    else
    {
        rconst = 0b00110000;
    }
    //Aplicação do xor entre a word e round
    n = n xor rconst;
    return n;

}

bitset<16> expand_key(bitset<16> chave, int round) {

        cout << endl << "--------------Expand Key-------------" << endl;


    bitset<8> w_0;
    bitset<8> w_1;
    
    for(int i = 7; i >= 0; i--){
        
        w_0[i] = chave[i + 8];
        w_1[i] = chave[i];
    }
    //dividimos a chave em duas words: w0 e w1

    bitset<8> w_2;
    bitset<8> w_3;
    //w2 é o resultado da g_function xor w0
    //w3 é o resultado do xor da w2 com w1

    w_2 = g_function(w_1, round) xor w_0;
    w_3 = w_1 xor w_2;
    
    //Juntar chaves
    bitset<16> result;
    if (round == 1){
        for(int i =0;i<8;i++)
        {
            result[i] = w_3[i];
            result[8+i] = w_2[i];
        }
        cout<< "chave " << round <<":" <<result<<endl;
        return result;
    }
    
    bitset<8> w_4;
    bitset<8> w_5;

    w_4 = g_function(w_3, round) xor w_2;
    w_5 = w_3 xor w_4;
    for(int i =0;i<8;i++)
    {
        result[i] = w_5[i];
        result[8+i] = w_4[i];
    }
    cout<< "chave " << round <<":" <<result<<endl;
    return result;

}