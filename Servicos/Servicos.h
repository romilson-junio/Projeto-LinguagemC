#ifndef SERVICOS_H_INCLUDED
#define SERVICOS_H_INCLUDED

void SERVICOS_criptografar(char* senha){
    int i;
    for(i = 0; i < strlen(senha);i++){
        senha[i] = senha[i] + 5;
    }
    return 1;
}
void SERVICOS_descriptografar(char* senha){
    int i;
    for(i = 0; i < strlen(senha);i++){
        senha[i] = senha[i] - 5;
    }
    return 1;
}
int SERVICOS_validarCPF(char* cpf){
    int digito[11];
    int D1, D2, i;

    if(strcmp(cpf, "00000000000") == 0 ||
       strcmp(cpf, "11111111111") == 0 ||
       strcmp(cpf, "22222222222") == 0 ||
       strcmp(cpf, "33333333333") == 0 ||
       strcmp(cpf, "44444444444") == 0 ||
       strcmp(cpf, "55555555555") == 0 ||
       strcmp(cpf, "66666666666") == 0 ||
       strcmp(cpf, "77777777777") == 0 ||
       strcmp(cpf, "88888888888") == 0 ||
       strcmp(cpf, "99999999999") == 0){
            MessageBox(0,"CPF INVÁLIDO!\n", "CPF",0);
            return 0;

       } else {
           for(i = 0; i <= 11; i++){
                digito[i] = cpf[i] - '0';
           }

           D1 = digito[0]*10 + digito[1]*9 + digito[2]*8 + digito[3]*7 + digito[4]*6 + digito[5]*5 + digito[6]*4 + digito[7]*3 + digito[8]*2;
           D1 = (D1 * 10) % 11;
           if(digito[9] == D1){
                D2 = digito[0]*11 + digito[1]*10 + digito[2]*9 + digito[3]*8 + digito[4]*7 + digito[5]*6 + digito[6]*5 + digito[7]*4 + digito[8]*3 + digito[9]*2;
                D2 = (D2 * 10) % 11;
                if(digito[10] == D2){
                        return 1;
                } else {
                    MessageBox(0,"CPF INVÁLIDO!\n", "CPF",0);
                    return 0;
                }
           } else {
                MessageBox(0,"CPF INVÁLIDO!\n", "CPF",0);
                return 0;
           }

        }

}
#endif // SERVICOS_H_INCLUDED
