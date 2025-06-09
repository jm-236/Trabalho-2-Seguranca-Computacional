#include <bits/stdc++.h>

using namespace std;
using namespace std::chrono;

#define medirInc auto inicio = high_resolution_clock::now();
#define medirFim auto fim = high_resolution_clock::now(); auto duracao = duration_cast<microseconds>(fim-inicio);cout<<"Tempo de execucao: "<<duracao.count()<<" microssegundos (µs)"<<endl;


void aquecer_biblioteca_crypto() {
    cout << "--- Aquecendo a biblioteca para medições precisas ---" << endl;
    try {
        CryptoPP::byte dummy_key[CryptoPP::AES::DEFAULT_KEYLENGTH] = {0};
        CryptoPP::byte dummy_block[CryptoPP::AES::BLOCKSIZE] = {0};
        CryptoPP::byte dummy_output[CryptoPP::AES::BLOCKSIZE] = {0};
        CryptoPP::AES::Encryption aes_encryptor;

        //    Isso força o carregamento do código e dos dados para o cache da CPU.
        for (int i = 0; i < 5; ++i) {
            aes_encryptor.SetKey(dummy_key, sizeof(dummy_key));
            aes_encryptor.ProcessBlock(dummy_block, dummy_output);
        }

    } catch (const CryptoPP::Exception& e) {
        cerr << "Erro durante o aquecimento: " << e.what() << endl;
    }
    cout << "--- Aquecimento concluído. Iniciando medições. ---\n" << endl;
}

string cifrar_ECB (string mensagem, string chave_str) {

    cout << "--------------Modo ECB-------------" << endl << endl;
    cout << "Cifrando o texto \'" << mensagem << "\' em modo ECB..." << endl;
    medirInc;

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
    medirFim;
    return texto_cifrado;
}

string cifrar_CBC (string mensagem, string chave_str, string vi) {

    cout << "--------------Modo CBC-------------" << endl << endl;
    cout << "Cifrando o texto \'" << mensagem << "\' em modo CBC..." << endl;
    medirInc;
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
    medirFim;
    return texto_cifrado;
}

string cifrar_CFB (string mensagem, string chave_str, string vi) {
    
    cout << "--------------Modo CFB-------------" << endl << endl;
    cout << "Cifrando o texto \'" << mensagem << "\' em modo CFB..." << endl;
    medirInc;
    vi.resize(CryptoPP::AES::BLOCKSIZE);

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
   medirFim
   return texto_cifrado;
}

string cifrar_OFB(string mensagem, string chave_str, string vi)
{
    cout << "--------------Modo OFB-------------" << endl << endl;
    cout << "Cifrando o texto \'" << mensagem << "\' em modo OFB..." << endl;
    medirInc;
    vi.resize(CryptoPP::AES::BLOCKSIZE);
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
       vi = texto_cifrado;
   }
   medirFim;
   return texto_cifrado;
}

string cifrar_CTR(string mensagem, string chave_str)
{
    
    cout << "--------------Modo CTR-------------" << endl << endl;
    cout << "Cifrando o texto \'" << mensagem << "\' em modo CTR..." << endl;
    medirInc;
    int vi = 0;

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
        CryptoPP::byte counter[CryptoPP::AES::BLOCKSIZE] = {0};
        memcpy(counter, &vi, sizeof(vi));
        aes.ProcessBlock(
            counter,
            reinterpret_cast<CryptoPP::byte*>(&vi_cifrado[0])
        );

       // xor de vi cifrado com a mensagem
       for (int j = 0; j < CryptoPP::AES::BLOCKSIZE; j++){
            texto_cifrado[j + i] = mensagem[j + i] xor vi_cifrado[j];  
       }
       // vi =  proximo bloco
       vi++;
   }
   medirFim;
   return texto_cifrado;

}