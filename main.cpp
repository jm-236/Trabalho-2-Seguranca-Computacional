#include <bits/stdc++.h>
#include "ler_mensagem.cpp"

using namespace std;

int main() {

    cout << "--------------Algoritmo S-AES-------------" << endl << endl;

    cout << "--------------Leitura da mensagem-------------" << endl;
    bitset<16> mensagem = ler_mensagem();
    cout << "Mensagem lida: " << mensagem << endl;

    cout << endl << "--------------Leitura da chave-------------" << endl;
    bitset<16> chave = ler_mensagem();
    cout << "Chave lida: " << chave << endl;
}