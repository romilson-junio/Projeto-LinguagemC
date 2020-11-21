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
    char cpfValidar[16];
    int digito[11];
    int D1, D2, i, j = 0;
    if(strlen(cpf) < 11 || strlen(cpf) > 14){
        MessageBox(0,"CPF INVÁLIDO!\n", "CPF",0);
        return 0;
    } else {
        for(i = 0; i < 15; i++){
            if(cpf[i] != '.' && cpf[i] != '-'){
                cpfValidar[j] = cpf[i];
                j++;
            }
        }
        strcpy(cpf, cpfValidar);
        if(strlen(cpf) != 11){
            MessageBox(0,"CPF INVÁLIDO!\n", "CPF",0);
            return 0;
        }

        if( strcmp(cpf, "00000000000") == 0 ||
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
                digito[i] = cpfValidar[i] - '0';
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

}
void receberValorInt(int *valor){
    int res, vl;
    do{
        res = scanf("%d", &vl);
        if(res == 0){
            MessageBox(0,"VALOR INVÁLIDO\n", "ERRO",0);
        }
        fflush(stdin);
    }while(res != 1);
    (*valor) = vl;
}

void SERVICOS_receberValorFloat(float *valor){
    int res;
    float vl = 00;
    do{
        res = scanf("%f", &vl);
        if(res == 0){
            MessageBox(0,"VALOR INVÁLIDO\n", "ERRO",0);
        }
        fflush(stdin);
    }while(res != 1);
    (*valor) = vl;
}
void SERVICOS_formatCpf(char* cpf){
    int i,j;
    j = 0;
    char cpfFormatado[16] = " ";
    for(i = 0; i < 14; i++){
        cpfFormatado[i] = cpf[j];
        if(i == 2 || i == 6 || i == 10){
            i++;
            if(i == 11){
                cpfFormatado[i] = '-';
            } else {
                cpfFormatado[i] = '.';
            }
        }

        j++;
    }
    strcpy(cpf, cpfFormatado);
}
void SERVICOS_receberSenha(char* senha){
    int tam = 0;
    do{
         senha[tam] = getch();
         if(senha[tam] == 0x08 && tam > 0){ /*Backspace*/
            printf("\b \b");
            senha[tam] = 0x00;
            tam--;
         }else if (senha[tam] == 13){ /*Enter*/
            senha[tam] = 0x00;
            break;
         }else if (senha[tam] != 0x08){
            putchar('*');
            tam++;
         }
    }while(tam < 8) ;
}
#endif // SERVICOS_H_INCLUDED
