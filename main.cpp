#include <bits/stdc++.h>
#include "ler_mensagem.cpp"
#include "s-aes.cpp"

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

    bitset<16> mensagem_criptografada = S_AES(mensagem, chave);
}