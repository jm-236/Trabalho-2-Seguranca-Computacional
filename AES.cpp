#include <bits/stdc++.h>

using namespace std;

string cifrar_ECB (string mensagem, string chave_str) {

    cout << "Cifrando o texto \'" << mensagem << "\' em modo ECB..." << endl;

    size_t original_length = mensagem.size();
    int padding = CryptoPP::AES::BLOCKSIZE - (mensagem.size() % CryptoPP::AES::BLOCKSIZE);
    mensagem.append(padding, static_cast<char>(padding));

    string texto_cifrado;
    texto_cifrado.resize(mensagem.size()); // precisa reservar espaço

    // Chave
    CryptoPP::byte key[CryptoPP::AES::DEFAULT_KEYLENGTH] = {0}; // chave de 16 bytes zerada
    memcpy(key, chave_str.data(), CryptoPP::AES::DEFAULT_KEYLENGTH);

    // AES puro
    CryptoPP::AES::Encryption aes;
    aes.SetKey(key, sizeof(key));

    for (size_t i = 0; i < mensagem.size(); i += CryptoPP::AES::BLOCKSIZE) {
        aes.ProcessBlock(
            reinterpret_cast<const CryptoPP::byte*>(&mensagem[i]),
            reinterpret_cast<CryptoPP::byte*>(&texto_cifrado[i])
        );
    }

    return texto_cifrado;
}