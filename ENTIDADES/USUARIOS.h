#ifndef USUARIOS_H_INCLUDED
#define USUARIOS_H_INCLUDED

int quantidadeUsuarios;

struct Usuarios{
    int id;
    char nome[100], usuario[50], perfil[50];

};

struct Usuarios BD_Usuarios[100];

void SELECT_ALL_FROM_USUARIOS(){
    char idFile[10];
    int i,j, n,indice = 0;
    bool dado = false, var  = false, fim;
    char variavel[15];
    char dados[1000];

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
                else if(strcmp(variavel, "nome") == 0){ BD_Usuarios[indice].nome[n] = dados[i]; }
                else if(strcmp(variavel, "usuario") == 0){ BD_Usuarios[indice].usuario[n] = dados[i]; }
                else if(strcmp(variavel, "perfil") == 0){ BD_Usuarios[indice].perfil[n] = dados[i]; }
                n++;
            }
        }
        BD_Usuarios[indice].id = atoi(idFile);
        indice++;

    }
    quantidadeUsuarios = indice;
    fclose(USUARIOS);


}

void USUARIOS_novoUsuario(){
    SELECT_ALL_FROM_USUARIOS();
    FILE *USUARIOS;
    int i, id, j, op;
    char nome[100], usuario[50], senha[20], perfil[50], cpf[20];
    int valido = 1;
    id = quantidadeUsuarios+1;
    system("cls");
    fflush(stdin);
    printf("             INFORME O USUARIO: \n");
    printf("             ");
    gets(usuario);
    fflush(stdin);

    for(i = 0; i < quantidadeUsuarios; i++){
        if(strcmp(usuario,BD_Usuarios[i].usuario) == 0){
            MessageBox(0,"USUARIO J� CADASTRADO!\n", "CADASTRO DE USU�RIOS",0);
            return 0;
        }
    }
    system("cls");
    printf("             INFORME O NOME: \n");
    printf("             ");
    gets(nome);
    fflush(stdin);
    system("cls");
    do{
        system("cls");
        printf("             INFORME O CPF DO USU�RIO\n");
        printf("             ");
        scanf("%s", &cpf);
        fflush(stdin);
        valido = SERVICOS_validarCPF(cpf);

    }while(valido == 0);

    for(j = 0 ; j < 6 ; j++){
        senha[j] = cpf[j];
    }
    system("cls");
    do{
        printf("\n             SELECIONE O PERFIL\n");
        printf("             [ 1 ] GERENTE\n");
        printf("             [ 2 ] VENDEDOR\n");
        printf("             [ 3 ] ADMINISTRADOR\n");
        printf("             [ 4 ] ESTOQUISTA\n");
        printf("             ");
        receberValorInt(&op);
        if(op != 1 && op != 2 && op != 3 && op != 4){
            system("cls");
        }
    } while(op != 1 && op != 2 && op != 3 && op != 4);
    switch(op){
        case 1:
            strcpy(perfil, "Gerente");
        break;
        case 2:
            strcpy(perfil, "Vendedor");
        break;
        case 3:
            strcpy(perfil, "Administrador");
        break;
        case 4:
            strcpy(perfil, "Estoquista");
        break;
    }
    SERVICOS_criptografar(senha);
    system("cls");
    tituloTabela("DADOS DO USUARIO");
    printf("\n\n");
    printf("           #####################   ************************                            #####################   *****************************\n");
    printf("           ##                 ##   **                    **                            ##                 ##   **                         **\n");
    printf("           ##     USU�RIO     ##   **   %s ", usuario);
    for(i = strlen(usuario); i < 16 ; i++){
        printf(" ");
    }
    printf("**                            ##     CPF         ##   **   %s ",SERVICOS_formatCpf(cpf));
    for(i = strlen(cpf); i < 21;i++){
        printf(" ");
    }
    printf("**\n");
    printf("           ##                 ##   **                    **                            ##                 ##   **                         **\n");
    printf("           #####################   ************************                            #####################   *****************************\n\n\n");
    printf("           #################   **********************************************************   #####################   ************************\n");
    printf("           ##             ##   **                                                      **   ##                 ##   **                    **\n");
    printf("           ##     NOME    ##   **   %s ", nome);
    for(i = strlen(nome); i < 50;i++){
        printf(" ");
    }
    printf("**   ##     PERFIL      ##   **   %s ", perfil);
    for(i = strlen(perfil); i < 16 ; i++){
        printf(" ");
    }
    printf("**\n");
    printf("           ##             ##   **                                                      **   ##                 ##   **                    **\n");
    printf("           #################   **********************************************************   #####################   ************************\n");


    int msgboxID = MessageBox(NULL, "CONFIRMAR CADASTRO", "CADASTRO DE USUARIO", MB_YESNO | MB_DEFBUTTON1);
        switch(msgboxID){
            case IDYES:
                op = 1;
            break;
            case IDNO:
                op = 0;
            break;
        }
    if(op == 1){
        USUARIOS = fopen("Banco/Usuario.csv", "a");

            fprintf(USUARIOS,
                    "{ (id): <%d> ; (nome): <%s> 	; (usuario): <%s>		; (senha): <%s> ; (perfil): <%s> ;\n}",
                    id, nome, usuario ,senha , perfil);
            MessageBox(0,"USUARIO CADASTRADO COM SUCESSO!\n", "CADASTRO DE USU�RIOS",0);
        fclose(USUARIOS);
    } else {
        MessageBox(0,"OPERA��O CANCELADA!\n", "CADASTRO DE USU�RIOS",0);
    }


}

char* getNomeVendedor(int id){
    int i;
    SELECT_ALL_FROM_USUARIOS();
    for(i = 0; i < quantidadeUsuarios; i++){
        if(id == BD_Usuarios[i].id){
            return BD_Usuarios[i].nome;
        }
    }
}

#endif // USUARIOS_H_INCLUDED
