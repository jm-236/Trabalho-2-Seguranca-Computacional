#include <bits/stdc++.h>
#include "expand_key.cpp"

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

    for(int i = 15; i >= 12; i--){
        // bits que não trocam
        nova_mensagem[i] = mensagem[i];
        nova_mensagem[i - 8] = mensagem[i - 8];
        
        // bits que trocam de posição(2° com 4°)
        nova_mensagem[i - 4] = mensagem[i - 12];
        nova_mensagem[i - 12] = mensagem[i - 4];
    }

    cout << "Mensagem após shift-rows: " << hex << nova_mensagem.to_ullong() << endl;
    return nova_mensagem;
}

bitset<16> mix_columns(bitset<16> mensagem) {

    cout << endl << "--------------Mix Columns-------------" << endl;

    // Tabela de multiplicação em GF(16) com polinômio x^4 + x + 1
    vector<vector<int>> gf16_mult = {
    // * | 0 1 2 3 4 5 6 7 8 9 A B C D E F
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, // 0
    { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15}, // 1
    { 0,2,4,6,8,10,12,14,3,1,7,5,11,9,15,13}, // 2
    { 0,3,6,5,12,15,10,9,11,8,13,14,7,4,1,2}, // 3
    { 0,4,8,12,3,7,11,15,6,2,14,10,5,1,13,9}, // 4
    { 0,5,10,15,7,2,13,8,14,11,4,1,9,12,3,6}, // 5
    { 0,6,12,10,11,13,7,1,5,3,9,15,14,8,2,4}, // 6
    { 0,7,14,9,15,8,1,6,13,10,3,4,2,5,12,11}, // 7
    { 0,8,3,11,6,14,5,13,12,4,15,7,10,2,9,1}, // 8
    { 0,9,1,8,2,11,3,10,4,13,5,12,6,15,7,14}, // 9
    { 0,10,7,13,14,4,9,3,15,5,0,10,1,11,6,12}, // A
    { 0,11,5,14,10,1,15,4,7,12,10,1,9,2,8,13}, // B
    { 0,12,11,7,5,9,14,2,10,6,1,9,15,3,4,8}, // C
    { 0,13,9,4,1,12,8,5,2,15,11,2,3,14,10,7}, // D
    { 0,14,15,1,13,3,2,12,9,7,6,8,4,10,5,11}, // E
    { 0,15,13,2,9,6,4,11,1,14,12,13,8,7,11,10}, // F
    };

    bitset<4> primeira_coluna;
    bitset<4> segunda_coluna;
    bitset<4> terceira_coluna;
    bitset<4> quarta_coluna;

    // definindo as colunas
    for(int i = 15; i >= 11; i--){
        primeira_coluna[i - 12] = mensagem[i];
        segunda_coluna[i - 12] = mensagem[i - 4];
        terceira_coluna[i - 12] = mensagem[i - 8];
        quarta_coluna[i - 12] = mensagem[i- 12];
    }

    // realizando a operação para cada uma das colunas
    bitset<4> nova_primeira_coluna(
        gf16_mult[primeira_coluna.to_ullong()][1] 
        xor 
        gf16_mult[segunda_coluna.to_ullong()][4]);

    bitset<4> nova_segunda_coluna(
        gf16_mult[primeira_coluna.to_ullong()][4]
        xor 
        gf16_mult[segunda_coluna.to_ullong()][1]);
    
    bitset<4> nova_terceira_coluna(
        gf16_mult[terceira_coluna.to_ullong()][1] 
        xor 
        gf16_mult[quarta_coluna.to_ullong()][4]);

    bitset<4> nova_quarta_coluna(
        gf16_mult[terceira_coluna.to_ullong()][4]
        xor 
        gf16_mult[quarta_coluna.to_ullong()][1]);

    cout << "Primeira coluna após transformação: " << nova_primeira_coluna << endl;
    cout << "Segunda coluna após transformação: " << nova_segunda_coluna << endl;
    cout << "Terceira coluna após transformação: " << nova_terceira_coluna << endl;
    cout << "Quarta coluna após transformação: " << nova_quarta_coluna << endl;

    bitset<16> nova_mensagem; 

    for(int i = 15; i > 11; i--){
        
        nova_mensagem[i] = nova_primeira_coluna[i - 12];
        nova_mensagem[i - 4] = nova_segunda_coluna[i - 12];
        nova_mensagem[i - 8] = nova_terceira_coluna[i - 12];
        nova_mensagem[i - 12] = nova_quarta_coluna[i - 12];
    }

    cout << "Mensagem após mix_columns: " << hex << nova_mensagem.to_ullong() << endl;

    return nova_mensagem;
}

bitset<16> S_AES(bitset<16> mensagem, bitset<16> chave) {
    
    bitset<16> mensagem_apos_round_key = add_round_key(mensagem, chave);

    bitset<16> mensagem_apos_s_nibble = s_nibbles(mensagem_apos_round_key);

    bitset<16> mensagem_apos_shift_rows = shift_rows(mensagem_apos_s_nibble);

    bitset<16> mensagem_apos_mix_columns = mix_columns(mensagem_apos_shift_rows);

    bitset<16> chave_1,chave_2;
    chave_1 = expand_key(chave, 1);
    chave_2 = expand_key(chave, 2);

    bitset<16> mensagem_apos_add_key_1 = add_round_key(mensagem_apos_mix_columns, chave_1);
    bitset<16> mensagem_apos_snibbles_2 = s_nibbles(mensagem_apos_add_key_1);
    bitset<16> mensagem_apos_shift_rows_2 = shift_rows(mensagem_apos_snibbles_2);

    bitset<16> mensagem_apos_add_key_2 = add_round_key(mensagem_apos_shift_rows_2, chave_2);

    cout << "Texto cifrado: " << mensagem_apos_add_key_2 << endl;
    return mensagem_apos_add_key_2;
}

