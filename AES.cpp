#include <bits/stdc++.h>

using namespace std;

string cifrar_ECB (string mensagem, string chave_str) {

    cout << "Cifrando o texto \'" << mensagem << "\' em modo ECB..." << endl;

    size_t original_length = mensagem.size();

    // padding
    int padding = CryptoPP::AES::BLOCKSIZE - (mensagem.size() % CryptoPP::AES::BLOCKSIZE);
    mensagem.append(padding, static_cast<char>(padding));

    string texto_cifrado;
    texto_cifrado.resize(mensagem.size()); // precisa reservar espaço

    // Chave
    CryptoPP::byte key[CryptoPP::AES::DEFAULT_KEYLENGTH] = {0}; // chave de 16 bytes
    memcpy(key, chave_str.data(), CryptoPP::AES::DEFAULT_KEYLENGTH);

    // AES puro
    CryptoPP::AES::Encryption aes;
    aes.SetKey(key, sizeof(key));

    // iterando os blocos
    for (size_t i = 0; i < mensagem.size(); i += CryptoPP::AES::BLOCKSIZE) {
        // realiza a cifragem do bloco aqui
        aes.ProcessBlock(
            reinterpret_cast<const CryptoPP::byte*>(&mensagem[i]),
            reinterpret_cast<CryptoPP::byte*>(&texto_cifrado[i])
        );
    }

    return texto_cifrado;
}

string cifrar_CBC (string mensagem, string chave_str, string vi) {

    cout << "Cifrando o texto \'" << mensagem << "\' em modo CBC..." << endl;

    // ajustando tamanho do vi
    vi.resize(CryptoPP::AES::BLOCKSIZE);
    
    // padding
    size_t original_length = mensagem.size();
    int padding = CryptoPP::AES::BLOCKSIZE - (mensagem.size() % CryptoPP::AES::BLOCKSIZE);
    mensagem.append(padding, static_cast<char>(padding));

    string texto_cifrado;
    texto_cifrado.resize(mensagem.size()); // precisa reservar espaço

    // Chave
    CryptoPP::byte key[CryptoPP::AES::DEFAULT_KEYLENGTH] = {0}; // chave de 16 bytes
    memcpy(key, chave_str.data(), CryptoPP::AES::DEFAULT_KEYLENGTH);

    // AES puro
    CryptoPP::AES::Encryption aes;
    aes.SetKey(key, sizeof(key));

    for (size_t i = 0; i < mensagem.size(); i += CryptoPP::AES::BLOCKSIZE) {
        
        // variavel pra armazenar resultado do xor 
        string bloco_apos_xor;
        bloco_apos_xor.resize(16);

        for(int j = 0; j < CryptoPP::AES::BLOCKSIZE; j++){
            // xor byte a byte da mensagem com o vetor de inicialização
            bloco_apos_xor[j] = mensagem[j + i] xor vi[j];
        }

        // cifrando bloco
        aes.ProcessBlock(
            reinterpret_cast<const CryptoPP::byte*>(&bloco_apos_xor[0]),
            reinterpret_cast<CryptoPP::byte*>(&texto_cifrado[i])
        );

        // atualizando vi
        vi = texto_cifrado.substr(i, CryptoPP::AES::BLOCKSIZE);
    }

    return texto_cifrado;
}

string cifrar_CFB (string mensagem, string chave_str, string vi) {

    vi.resize(CryptoPP::AES::BLOCKSIZE);
    cout << "Cifrando o texto \'" << mensagem << "\' em modo CFB..." << endl;

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
       
        string vi_cifrado;
        vi_cifrado.resize(CryptoPP::AES::BLOCKSIZE);   

       // cifrando vi 
       aes.ProcessBlock(
           reinterpret_cast<const CryptoPP::byte*>(&vi[0]),
           reinterpret_cast<CryptoPP::byte*>(&vi_cifrado[0])
       );
       // xor de vi cifrado com a mensagem
       for (int j = 0; j < CryptoPP::AES::BLOCKSIZE; j++){
            texto_cifrado[j + i] = mensagem[j + i] xor vi_cifrado[j];  
       }
       // vi =  proximo bloco
       vi = texto_cifrado.substr(i, CryptoPP::AES::BLOCKSIZE);
   }

   return texto_cifrado;
}