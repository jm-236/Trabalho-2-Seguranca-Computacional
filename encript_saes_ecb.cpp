#include <bits/stdc++.h>

using namespace std;

vector<bitset<16>> encript_saes_ecb(vector<bitset<16>> bloco, bitset<16> chave) {

    cout << endl << "--------------Executando cifragem em modo ECB-------------" << endl;

    vector<bitset<16>> bloco_encriptado;
    for(auto mensagem : bloco) {
        bitset<16> mensagem_encriptada = S_AES(mensagem, chave);
        bloco_encriptado.push_back(mensagem_encriptada);
    }

    cout << "Printando bloco encriptado: " << endl;
    for (auto i : bloco_encriptado) {
        cout << nibbleTo64(i) << endl;
    }

    return bloco_encriptado;
}

void comparar_blocos(vector<bitset<16>> bloco_1, vector<bitset<16>> bloco_2) {

    cout << endl << "--------------Comparando blocos-------------" << endl;

    vector<string> bloco_1_base_64, bloco_2_base_64;

    for(auto i: bloco_1){

        bloco_1_base_64.push_back(nibbleTo64(i));
    }

    for(auto i: bloco_2){

        bloco_2_base_64.push_back(nibbleTo64(i));
    }

    cout << "Comparando blocos cifrados em base 64:" << endl;
    cout << "bloco 1: ";
    for (auto i : bloco_1_base_64){
        cout << i;
    }
    cout << endl;
    cout << "bloco 2: ";
    for (auto i : bloco_2_base_64){
        cout << i;
    }
    cout << endl;
}