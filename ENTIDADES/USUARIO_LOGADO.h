#ifndef USUARIO_LOGADO_H_INCLUDED
#define USUARIO_LOGADO_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <locale.h>
#include <windows.h>
struct USUARIO_LOGADO{
    int idLogado;
    char nomeLogado[100];
    char usuarioLogado[50];
    char senhaLogado[20];
    char perfilLogado[50];
    bool isLogado;
};

struct USUARIO_LOGADO Usuario[1];

void USUARIO_LOGADO_login(){
    FILE *USUARIOS;
    int i,j,op, tam=0;
    bool userInvalid;
    char enter;
    char usuario[100] = " ", senha[20] = " ";
    char usuarioFile[100], senhaFile[20], nomeFile[100], perfilFile[50];
    int idFile;
    userInvalid = false;
    while(op != 1 || userInvalid){
        if(op == 2){
            strcpy(usuario, " ");
            strcpy(senha, " ");
        }
        if(userInvalid){
            strcpy(usuario, " ");
            strcpy(senha, " ");
            MessageBox(0,"USUÁRIO OU SENHA INVÁLIDOS!\n", "LOGIN",0);
        }

        for(i = 0; i < 3; i++){
            system("cls");
            printf("\n\n\n\n\n\n\n\n\n\n\n");
            printf("                                                             *******************************************************\n");
            printf("                                                             *******************************************************\n");
            printf("                                                             *******************************************************\n");
            printf("                                                             ******** USUÁRIO **************************************\n");
            printf("                                                             ********                                       ********\n");
            printf("                                                             ******** %s", usuario);
            for(j = strlen(usuario); j < 38; j++){
                printf(" ");
            }
            printf("********\n");
            printf("                                                             *******************************************************\n");
            printf("                                                             ******** SENHA   **************************************\n");
            printf("                                                             ********                                       ********\n");
            printf("                                                             ******** ");
            if(strlen(senha) <= 1){
                printf(" ");
            } else {
                for(j = 0; j < strlen(senha); j++){
                    printf("*");
                }
            }
            for(j = strlen(senha); j < 38; j++){
                printf(" ");
            }
            printf("********\n");
            printf("                                                             *******************************************************\n");
            printf("                                                             *******************************************************\n");
            printf("                                                             *******************************************************\n");

            if(i == 0){
                printf("\n\n\n                                                             DIGITE SEU USUÁRIO:    ");
                scanf("%s", &usuario);

            } else if(i == 1){

                printf("\n\n\n                                                             DIGITE SUA SENHA:   ");
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
            } else {
                int msgboxID = MessageBox(NULL, "ENTRAR", "CONFIRMAR LOGIN", MB_YESNO | MB_DEFBUTTON1);
				switch(msgboxID){
                    case IDYES:
                        op = 1;
                    break;
                    case IDNO:
                        op = 2;
                    break;
				}
            }

        }
        if(op == 1){
            USUARIOS = fopen("Banco/Usuario.csv", "r");
            SERVICOS_criptografar(senha);
            while(fscanf(USUARIOS,"%d ; %s ; %s ; %s ; %s ;\n", &idFile, &nomeFile, &usuarioFile ,&senhaFile, &perfilFile) != EOF){
                if(strcmp(usuario, usuarioFile) == 0 && strcmp(senha, senhaFile) == 0){
                    strcpy(Usuario[0].usuarioLogado, usuarioFile);
                    strcpy(Usuario[0].senhaLogado, senhaFile);
                    strcpy(Usuario[0].nomeLogado, nomeFile);
                    strcpy(Usuario[0].perfilLogado, perfilFile);
                    Usuario[0].idLogado = idFile;
                    Usuario[0].isLogado = true;
                    userInvalid = false;
                    return 1;
                } else {
                    Usuario[0].isLogado = false;
                    userInvalid = true;
                }
            }
            fclose(USUARIOS);
        }
        system("cls");

    }
    return 0;

}

bool isLogado(){
    return Usuario[0].isLogado;
}

char* getPerfilLogado(){
    return Usuario[0].perfilLogado;
}

void USUARIO_LOGADO_sair(){
    Usuario[0].isLogado = false;
}
int getIdLogado(){
    return Usuario[0].idLogado;
}


#endif // USUARIO_LOGADO_H_INCLUDED
