#include <bits/stdc++.h>

using namespace std;

bitset<16> add_round_key(bitset<16> mensagem, bitset<16> chave) {
    cout << endl << "--------------Add Round Key-------------" << endl;
    cout << "Mensagem no round key: " << hex << mensagem.to_ullong() << endl;
    cout << "Chave no round key: " << hex << chave.to_ullong() << endl;
    return mensagem xor chave;
}

bitset<16> S_AES(bitset<16> mensagem, bitset<16> chave) {
    
    bitset<16> mensagem_apos_round_key = add_round_key(mensagem, chave);
    cout << "Mensagem após round key: " << hex << mensagem_apos_round_key.to_ullong() << endl;

    return 0;
}

