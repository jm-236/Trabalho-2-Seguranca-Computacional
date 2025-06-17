#include <bits/stdc++.h>
#include <cryptopp/aes.h>
#include <cryptopp/modes.h>
#include <cryptopp/filters.h>
#include <cryptopp/base64.h>
#include <chrono>

// Arquivos do projeto
#include "ler_mensagem.cpp"
#include "s-aes.cpp"
#include "base64.cpp"
#include "encript_saes_ecb.cpp"
#include "AES.cpp"

using namespace std;

int main() {
    int parte;
    cout << "Qual parte deseja ver ? (1, 2 ou 3): ";
    if (!(cin >> parte)) {
        cerr << "Entrada inválida!" << endl;
        return 1;
    }

    switch (parte) {
        case 1: {
            cout << "--------------Algoritmo S-AES-------------\n\n";

            cout << "--------------Leitura da mensagem-------------\n";
            bitset<16> mensagem = 0b0110111101101011;
            cout << "Mensagem lida: " << mensagem << endl;

            cout << "\n--------------Leitura da chave-------------\n";
            bitset<16> chave = 0b1010011100111011;
            cout << "Chave lida: " << chave << endl;

            bitset<16> mensagem_criptografada = S_AES(mensagem, chave);
            string mensagem_base64 = nibbleTo64(mensagem_criptografada);
            cout << "Mensagem criptografada em base64: " << mensagem_base64 << endl;
            break;
        }

        case 2: {
            cout << "--------------Modo ECB (S-AES)-------------\n\n";

            vector<bitset<16>> bloco_ecb = {
                0b0110111101101011, 0b1010000011110001,
                0b0001110101000111, 0b0011100001010000
            };

            vector<bitset<16>> bloco_ecb_2 = {
                0b0001110101000111, 0b0011100001010000,
                0b0110111101101011, 0b1010000011110001
            };

            bitset<16> chave = 0b1010011100111011;

            auto bloco_encriptado = encript_saes_ecb(bloco_ecb, chave);
            auto bloco_encriptado_2 = encript_saes_ecb(bloco_ecb_2, chave);

            comparar_blocos(bloco_ecb, bloco_ecb_2);
            comparar_blocos(bloco_encriptado, bloco_encriptado_2);
            break;
        }

        case 3: {
            cout << "--------------Algoritmo AES real com vários modos de operação-------------\n\n";

            string mensagem_AES = "Bom dia, eu gostaria de receber nota 10 no trabalho, pois nos esforçamos muito e passamos muito tempo programando";
            string chave_str = "minha_chave_1234"; // deve ter 16 bytes

            aquecer_biblioteca_crypto();

            string texto_cifrado = cifrar_ECB(mensagem_AES, chave_str);
            cout << "Base64: " << converter_base64(texto_cifrado) << endl;

            string vi = "vetor de inicialização"; // deve ter 16 bytes no mínimo
            vi.resize(CryptoPP::AES::BLOCKSIZE);  // garante tamanho compatível

            texto_cifrado = cifrar_CBC(mensagem_AES, chave_str, vi);
            cout << "Base64: " << converter_base64(texto_cifrado) << endl;

            texto_cifrado = cifrar_CFB(mensagem_AES, chave_str, vi);
            cout << "Base64: " << converter_base64(texto_cifrado) << endl;

            texto_cifrado = cifrar_OFB(mensagem_AES, chave_str, vi);
            cout << "Base64: " << converter_base64(texto_cifrado) << endl;

            texto_cifrado = cifrar_CTR(mensagem_AES, chave_str);
            cout << "Base64: " << converter_base64(texto_cifrado) << endl;

            break;
        }

        default:
            cerr << "Parte inválida. Escolha 1, 2 ou 3." << endl;
            break;
    }

    return 0;
}
