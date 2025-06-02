#include <bits/stdc++.h>

using namespace std;

bitset<16> ler_mensagem() {
    
    string mensagem_str;

    while (true) {

        bool valida =  true;
        cout << "Digite a mensagem (16 bits): ";
        cin >> mensagem_str;
        
        if (mensagem_str.length() == 0 || mensagem_str.length() > 16) {
            cout << "Tamanho inválido!" << endl;
            valida = false;
            continue;
        }

        for (auto c : mensagem_str){
            
            if (c != '1' && c != '0'){
                cout << "Você só pode digitar 0 ou 1!" << endl;
                valida = false;
                break;
            }
        }

        if (valida) {
            break;
        }
    }

    return bitset<16>(mensagem_str);
}