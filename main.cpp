#include <bits/stdc++.h>
#include "ler_mensagem.cpp"
#include "s-aes.cpp"
#include "base64.cpp"
#include "encript_saes_ecb.cpp"

using namespace std;

int main() {

    cout << "--------------Algoritmo S-AES-------------" << endl << endl;

    cout << "--------------Leitura da mensagem-------------" << endl;
    // bitset<16> mensagem = ler_mensagem();
    bitset<16> mensagem = 0b0110111101101011;
    cout << "Mensagem lida: " << mensagem << endl;

    cout << endl << "--------------Leitura da chave-------------" << endl;
    // bitset<16> chave = ler_mensagem();
    bitset<16> chave = 0b1010011100111011;
    cout << "Chave lida: " << chave << endl;

    // Parte 1: implementação cifragem S-AES 
    bitset<16> mensagem_criptografada = S_AES(mensagem, chave);
    string mensagem_base64 = nibbleTo64(mensagem_criptografada);
    cout << "Mensagem criptografada em base 64: " << mensagem_base64 << endl;

    // Parte 2: Modo ECB
    vector<bitset<16>> bloco_ecb = {
    0b0110111101101011, 0b1010000011110001,
    0b0001110101000111, 0b0011100001010000
    };

    // mesmos bitsets do primeiro, o terceiro e o quarto viraram os dois primeiros 
    // enquanto os dois primeiros viraram os dois ultimos
    vector<bitset<16>> bloco_ecb_2 = {
    0b0001110101000111, 0b0011100001010000,
    0b0110111101101011, 0b1010000011110001,
    };

    vector<bitset<16>>bloco_encriptado = encript_saes_ecb(bloco_ecb, chave);
    vector<bitset<16>>bloco_encriptado_2 = encript_saes_ecb(bloco_ecb_2, chave);

    comparar_blocos(bloco_encriptado, bloco_encriptado_2);
}