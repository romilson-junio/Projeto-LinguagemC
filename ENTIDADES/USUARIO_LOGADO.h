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
bool USUARIO_LOGADO_validarUsuario(char *usuario, char *senha){
    char idFile[10], nomeFile[100] = " ", usuarioFile[50] = " ", senhaFile[20] = " ", perfilFile[50] = " ";
    int i,j, n, ultima;
    bool dado = false, var  = false, fim;
    char variavel[15];
    char dados[1000];
    SERVICOS_criptografar(senha);
    FILE *USUARIOS;

    USUARIOS = fopen("Banco/Usuario.csv", "r");
    while((fgets(dados, sizeof(dados), USUARIOS))!=NULL){
        fim = false;
        strcpy(idFile, "0");


        for(i = 0; i < 1000; i++){
            switch(dados[i]){
                case '<': n=0; dado = true; continue; break;
                case '>': dado = false; continue; break;
                case '(': j = 0; var = true; continue; break;
                case ')': variavel[j] = '\000'; var = false; continue; break;
                case '}': fim = true; break;
            }

            if(var && !fim){variavel[j] = dados[i]; j++;
            } else if(dado && !fim){
                     if(strcmp(variavel, "id")     == 0){ idFile[n] = dados[i];}
                else if(strcmp(variavel, "nome") == 0){ nomeFile[n] = dados[i]; }
                else if(strcmp(variavel, "senha") == 0){ senhaFile[n] = dados[i]; }
                else if(strcmp(variavel, "usuario") == 0){ usuarioFile[n] = dados[i]; }
                else if(strcmp(variavel, "perfil") == 0){ perfilFile[n] = dados[i]; }
                n++;
            }
        }
        if(strcmp(usuario, usuarioFile) == 0 && strcmp(senha, senhaFile) == 0){
            strcpy(Usuario[0].nomeLogado, nomeFile);
            strcpy(Usuario[0].senhaLogado, senhaFile);
            strcpy(Usuario[0].usuarioLogado, usuarioFile);
            strcpy(Usuario[0].perfilLogado, perfilFile);
            Usuario[0].idLogado = atoi(idFile);
            Usuario[0].isLogado = true;
            return true;
        } else{
            memset(nomeFile, '\000', strlen(nomeFile) * sizeof(char));
            memset(senhaFile, '\000', strlen(senhaFile) * sizeof(char));
            memset(usuarioFile, '\000', strlen(usuarioFile) * sizeof(char));
            memset(perfilFile, '\000', strlen(perfilFile) * sizeof(char));

        }

    }
    Usuario[0].isLogado = false;
    return false;
}
void USUARIO_LOGADO_login(){
    FILE *USUARIOS;
    int i,j,op, tam=0;
    bool userValid;
    char enter;
    char usuario[100] = " ", senha[20] = "";
    userValid = false;
    while(op == 2 || !userValid){
        if(op == 2){
            fflush(stdin);
            memset(usuario, '\000', strlen(usuario) * sizeof(char));
            memset(senha, '\000', strlen(senha) * sizeof(char));
            tam = 0;
        }
        for(i = 0; i < 3; i++){
            system("cls");
            printf("\n\n\n\n\n\n\n\n\n");
            printf("                                        ########################################################################################################\n");
            printf("                                      ##########################################################################################################\n");
            printf("                                    ############################################################################################################\n");
            printf("                                  ###############################################################                                          #####\n");
            printf("                                #################################################################     ..............    ..............     #####\n");
            printf("                              ###################################################################     ..............    ..............     #####\n");
            printf("                            #####################################################################     ..............    ..............     #####\n");
            printf("                            ############               ##                         ###############     ......                ......         #####\n");
            printf("                            ############     USUÁRIO   ##   %s", usuario);

            for(j = strlen(usuario); j < 22; j++){
                printf(" ");
            }
                                                                                              printf("###############     ......                ......         #####\n");
            printf("                            ############               ##                         ###############     ......                ......         #####\n");
            printf("                            #####################################################################     ..............        ......         #####\n");
            printf("                            #####################################################################     ..............        ......         #####\n");
            printf("                            #####################################################################             ......        ......         #####\n");
            printf("                            ############               ##                         ###############             ......        ......         #####\n");
            printf("                            ############    SENHA      ##   ");
            if(strlen(senha) > 1){
                for(j = 0; j < strlen(senha); j++){
                    printf("*");
                }
            }
            for(j = strlen(senha); j < 22; j++){
                printf(" ");
            }
                                                                                              printf("###############             ......        ......         #####\n");
            printf("                            ############               ##                         ###############     ..............        ......         #####\n");
            printf("                            #####################################################################     ..............        ......         #####\n");
            printf("                              ###################################################################     ..............        ......         #####\n");
            printf("                                #################################################################                                          #####\n");
            printf("                                  ###############################################################                                          #####\n");
            printf("                                    ############################################################################################################\n");
            printf("                                      ##########################################################################################################\n");
            printf("                                        ########################################################################################################\n");


            if(i == 0){

                printf("\n\n                                          DIGITE SEU USUÁRIO:  ");
                scanf("%s", &usuario);

            } else if(i == 1){

                printf("\n\n                                         DIGITE SUA SENHA: ");
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
            userValid = USUARIO_LOGADO_validarUsuario(usuario, senha);
            if(userValid){
                return 1;
            } else {
                fflush(stdin);
                memset(usuario, '\000', strlen(usuario) * sizeof(char));
                memset(senha, '\000', strlen(senha) * sizeof(char));
                tam = 0;
                MessageBox(0,"USUÁRIO OU SENHA INVÁLIDOS!\n", "LOGIN",0);
            }
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
char* getSenhaLogado(){
    return Usuario[0].senhaLogado;
}
int getIdLogado(){
    return Usuario[0].idLogado;
}


#endif // USUARIO_LOGADO_H_INCLUDED
