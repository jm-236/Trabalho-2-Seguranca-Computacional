#include <bits/stdc++.h>

using namespace std;

bitset<16> add_round_key(bitset<16> mensagem, bitset<16> chave) {
    cout << endl << "--------------Add Round Key-------------" << endl;
    cout << "Mensagem no round key: " << hex << mensagem.to_ullong() << endl;
    cout << "Chave no round key: " << hex << chave.to_ullong() << endl;
    cout << "Mensagem após round key: " << hex << (mensagem xor chave).to_ullong() << endl;
    return mensagem xor chave;
}

bitset<16> s_nibbles(bitset<16> mensagem) {
    
    cout << endl << "--------------S-Nibbles-------------" << endl;

    vector<bitset<4>> s_box = { 
                                0b1001, 0b0100, 0b1010, 0b1011,
                                0b1101, 0b0001, 0b1000, 0b0101, 
                                0b0110, 0b0010, 0b0000, 0b0011,
                                0b1100, 0b1110, 0b1111, 0b0111 
                            };

    bitset<16> nova_mensagem;
    bitset<4> nibble;
    int cont = 1; // contador da nibble atual

    for(int i = 15; i >= 3; i -= 4){
        
        // pegando os bits de 4 em 4
        nibble[3] = mensagem[i];
        nibble[2] = mensagem[i - 1];
        nibble[1] = mensagem[i - 2];
        nibble[0] = mensagem[i - 3];

        bitset<4> correspondente_s_box = s_box[nibble.to_ullong()];

        cout << "Nibble " << cont << ": " << dec << nibble.to_ullong() << endl;
        cout << "Correspondente na s-box: " << correspondente_s_box << endl << endl;
        
        // inserindo os bits correspondentes na nova mensagem
        nova_mensagem[i] = correspondente_s_box[3];
        nova_mensagem[i - 1] = correspondente_s_box[2];
        nova_mensagem[i - 2] = correspondente_s_box[1];
        nova_mensagem[i - 3] = correspondente_s_box[0];

        cont++;
    }

    cout << "Mensagem após s-nibble: " << hex << nova_mensagem.to_ullong() << endl;

    return nova_mensagem;
}

bitset<16> shift_rows(bitset<16> mensagem) {

    cout << endl << "--------------Shift-Rows-------------" << endl;
    
    bitset<16> nova_mensagem;

    cout << "Trocando os dois elementos da segunda linha..." << endl;

    // bits que não mudarão
    for(int i = 15; i >= 12; i--){
        // bits que não trocam
        nova_mensagem[i] = mensagem[i];
        nova_mensagem[i - 8] = mensagem[i - 8];
        
        // bits que trocam de posição(2° com 4°)
        nova_mensagem[i - 4] = mensagem[i - 12];
        nova_mensagem[i - 12] = mensagem[i - 4];
    }

    cout << "Mensagem após shift-rows: " << hex << nova_mensagem.to_ullong() << endl;
    return 0;
}

bitset<16> S_AES(bitset<16> mensagem, bitset<16> chave) {
    
    bitset<16> mensagem_apos_round_key = add_round_key(mensagem, chave);
    

    bitset<16> mensagem_apos_s_nibble = s_nibbles(mensagem_apos_round_key);

    bitset<16> mensagem_apos_shift_rows = shift_rows(mensagem_apos_s_nibble);
    return 0;
}

