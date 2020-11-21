#ifndef PRODUTOS_H_INCLUDED
#define PRODUTOS_H_INCLUDED
#include <stdbool.h>
int quantidadeProdutos;

struct PRODUTOS{
    int codigo, quantidade, usuarioCadastrante;
    float valor, margemLucro;
    char nome[50];
};

struct PRODUTOS Produtos[1000];
int indice = 0;

void SELECT_ALL_FROM_PRODUTO(){
    FILE *PRODUTOS;
    int i,j, n,indice = 0;
    /*Variáveis da Funcionalidade*/
    char codigoFile[10], quantidadeFile[10], usuarioCadastranteFile[10], valorFile[15], margemLucroFile[15];

    /*Variáveis da consulta*/

    bool dado = false, var  = false, fim;
    char variavel[15];
    char dados[1000];


    PRODUTOS = fopen("Banco/Produto.csv", "r");
    while((fgets(dados, sizeof(dados), PRODUTOS))!=NULL){
        fim = false;

        memset(codigoFile, '\000', strlen(codigoFile) * sizeof(char));
        memset(quantidadeFile, '\000', strlen(quantidadeFile) * sizeof(char));
        memset(usuarioCadastranteFile, '\000', strlen(usuarioCadastranteFile) * sizeof(char));
        memset(valorFile, '\000', strlen(valorFile) * sizeof(char));
        memset(margemLucroFile, '\000', strlen(margemLucroFile) * sizeof(char));

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
                     if(strcmp(variavel, "codigo")     == 0){ codigoFile[n] = dados[i];}
                else if(strcmp(variavel, "nome") == 0){ Produtos[indice].nome[n] = dados[i]; }
                else if(strcmp(variavel, "quantidade") == 0){ quantidadeFile[n] = dados[i]; }
                else if(strcmp(variavel, "valor") == 0){ valorFile[n] = dados[i]; }
                else if(strcmp(variavel, "margemLucro") == 0){ margemLucroFile[n] = dados[i]; }
                else if(strcmp(variavel, "usuarioCadastrante") == 0){ usuarioCadastranteFile[n] = dados[i]; }
                n++;
            }
        }

        Produtos[indice].codigo = atoi(codigoFile);
        Produtos[indice].quantidade = atoi(quantidadeFile);

        sscanf(valorFile, "%f", &Produtos[indice].valor);
        sscanf(margemLucroFile, "%f", &Produtos[indice].margemLucro);

        Produtos[indice].usuarioCadastrante = atoi(usuarioCadastranteFile);
        indice++;

    }
    quantidadeProdutos = indice;
    fclose(PRODUTOS);

}

float PRODUTOS_valor(int idProduto){
    int i;
    double valor;
    SELECT_ALL_FROM_PRODUTO();
    for(i = 0; i < quantidadeProdutos; i++){
        if(idProduto == Produtos[i].codigo){
            return Produtos[i].valor;
        }
    }

}
void PRODUTOS_view(){
    int i,j;
    char usuario[100];
    SELECT_ALL_FROM_PRODUTO();
    system("cls");
    tituloTabela("Produtos");
    printf("\n\n");
    printf("             ################################################################################################################################\n");
    printf("             ##  CÓDIGO     #              NOME              #  QUANTIDADE #     VALOR      #  MARGEM DE LUCRO  #         USUARIO          ##\n");
    printf("             ################################################################################################################################\n");

    for(i = 0; i < quantidadeProdutos; i++){
        strcpy(usuario, getNomeVendedor(Produtos[i].usuarioCadastrante));
        printf("             ##  ");
        printf("%3d        #  ", Produtos[i].codigo);
        printf("%s ",Produtos[i].nome);
        for(j = strlen(Produtos[i].nome); j < 29; j++){
            printf(" ");
        }

        printf("#  %6d     #  R$ %9.2f  #     %5.1f %%       #" , Produtos[i].quantidade, Produtos[i].valor, Produtos[i].margemLucro);
        printf("  %s", usuario);
        for(j = strlen(usuario); j < 24; j++){
            printf(" ");
        }
        printf("##\n");
    }
    printf("             ##                                                                                                                            ##\n");
    printf("             ################################################################################################################################\n\n");
    optionViewProdutos();
}

void PRODUTOS_insert(){
    int i,j;
    char usuario[100];
    SELECT_ALL_FROM_PRODUTO();
    system("cls");
    tituloTabela("Produtos");
    printf("\n\n");
    printf("             ################################################################################################################################\n");
    printf("             ##  CÓDIGO     #              NOME              #  QUANTIDADE #     VALOR      #  MARGEM DE LUCRO  #         USUARIO          ##\n");
    printf("             ################################################################################################################################\n");

    for(i = 0; i < quantidadeProdutos; i++){
        strcpy(usuario, getNomeVendedor(Produtos[i].usuarioCadastrante));
        printf("             ##  ");
        printf("%3d        #  ", Produtos[i].codigo);
        printf("%s ",Produtos[i].nome);
        for(j = strlen(Produtos[i].nome); j < 29; j++){
            printf(" ");
        }

        printf("#  %6d     #  R$ %9.2f  #     %5.1f %%       #" , Produtos[i].quantidade, Produtos[i].valor, Produtos[i].margemLucro);
        printf("  %s", usuario);
        for(j = strlen(usuario); j < 24; j++){
            printf(" ");
        }
        printf("##\n");
    }
    printf("             ##                                                                                                                            ##\n");
    printf("             ################################################################################################################################\n\n");
}

void PRODUTOS_add(){
    FILE *PRODUTOS;
    int i, quantidade, codigo, res;
    float valor, taxaComissao;
    char nome[50];
    SELECT_ALL_FROM_PRODUTO();
    system("cls");
    printf("             INFORME O NOME DO PRODUTO\n");
    printf("             ");
    fflush(stdin);
    gets(nome);
    fflush(stdin);

    for(i = 0; i < quantidadeProdutos; i++){
        if(strcmp(nome, Produtos[i].nome) == 0){
            MessageBox(0,"PRODUTO JÁ CADASTRADO!\n", "CADASTRO DE PRODUTOS",0);
            PRODUTOS_view();
        }
    }
    printf("             INFORME A QUANTIDADE\n");
    printf("             ");
    receberValorInt(&quantidade);
    printf("             INFORME O VALOR\n");
    printf("             ");
    SERVICOS_receberValorFloat(&valor);

    printf("             INFORME A TAXA DE COMISSÃO\n");
    printf("             ");
    SERVICOS_receberValorFloat(&taxaComissao);

    codigo = PRODUTOS_gerarId();
    PRODUTOS = fopen("Banco/Produto.csv", "a");
        fprintf(PRODUTOS,
                "{ (codigo): <%d> ; (nome): <%s> ; (quantidade): <%d> ; (valor): <%.2f> ; (margemLucro): <%.2f> ; (usuarioCadastrante): <%d> ; }\n",
                codigo, nome, quantidade, valor, taxaComissao, getIdLogado());
        /*fprintf(PRODUTOS,"%d ; %s ; %d ; %.2f ; %.2f ; %d ;\n", codigo, nome, quantidade, valor, taxaComissao, getIdLogado());*/
        MessageBox(0,"PRODUTO CADASTRADO COM SUCESSO!\n", "CADASTRO DE PRODUTOS",0);
    fclose(PRODUTOS);

}
int PRODUTOS_gerarId(){
    int i, codigo;
    int maior = 0;
    for(i = 0; i < quantidadeProdutos; i++){
        if(Produtos[i].codigo > maior){
            maior = Produtos[i].codigo;
        }
    }
    codigo = maior + 1;
    return codigo;
}

int PRODUTOS_verificarEstoque(){
    int i, abaixo;
    abaixo = 0;
    SELECT_ALL_FROM_PRODUTO();
    for(i = 0; i < quantidadeProdutos; i++){
        if(Produtos[i].quantidade <= 5){
            abaixo++;
        }

    }
    return abaixo;

}
void PRODUTOS_baixoEstoque(){
    int i, op, j;
    char usuario[100];
    SELECT_ALL_FROM_PRODUTO();
    tituloTabela("Baixo Estoque");
    printf("\n\n");
    printf("             ################################################################################################################################\n");
    printf("             ##  CÓDIGO     #              NOME              #  QUANTIDADE #     VALOR      #  MARGEM DE LUCRO  #         USUARIO          ##\n");
    printf("             ################################################################################################################################\n");

    for(i = 0; i < quantidadeProdutos; i++){
        if(Produtos[i].quantidade <= 5){
            strcpy(usuario, getNomeVendedor(Produtos[i].usuarioCadastrante));
            printf("             ##  ");
            printf("%3d        #  ", Produtos[i].codigo);
            printf("%s ",Produtos[i].nome);
            for(j = strlen(Produtos[i].nome); j < 29; j++){
                printf(" ");
            }

            printf("#  %6d     #  R$ %9.2f  #     %5.1f %%       #" , Produtos[i].quantidade, Produtos[i].valor, Produtos[i].margemLucro);
            printf("  %s", usuario);
            for(j = strlen(usuario); j < 24; j++){
                printf(" ");
            }
            printf("##\n");
        }
    }
    printf("             ##                                                                                                                            ##\n");
    printf("             ################################################################################################################################\n\n");
    printf("             ####################\n");
    printf("             ##                ##\n");
    printf("             ## [ 1 ] VOLTAR   ##\n");
    printf("             ##                ##\n");
    printf("             ####################\n");
    printf("             ");
    receberValorInt(&op);
    switch(op){
        case 1:
            system("cls");
            return 1;
        break;
        default:
            system("color 4F");
            MessageBox(0,"OPÇÃO INVÁLIDA!\n", "BAIXO ESTOQUE",0);
            system("color 0F");
            system("cls");
            PRODUTOS_baixoEstoque();
        break;
    }
}
int PRODUTOS_verificarDisponibilidade(int idProduto, int quantidade){
    int i;
    SELECT_ALL_FROM_PRODUTO();
    for(i = 0; i <  quantidadeProdutos; i++){
        if(idProduto == Produtos[i].codigo){
            if(quantidade <= Produtos[i].quantidade){
                return 1;
            } else {
                return 2;
            }
        }
    }
    return 0;
}
void PRODUTOS_atualizarEstoqueProduto(){
    FILE *PRODUTOS;
    int codigo,quantidade, indice,i;
    char usuario[100];
    printf("             INFORME O CÓDIGO DO PRODUTO!\n");
    printf("             ");
    receberValorInt(&codigo);

    SELECT_ALL_FROM_PRODUTO();
    for(i = 0; i < quantidadeProdutos; i++){
        if(codigo == Produtos[i].codigo){
            indice = i;
            break;
        }
    }
    system("cls");
    tituloTabela("Dados do Produto");
    /*tituloTabelaAtualizarEstoque();*/
    printf("\n\n");
    strcpy(usuario, getNomeVendedor(Produtos[indice].usuarioCadastrante));
    printf("             ######################   ##########################################\n");
    printf("             ##                  ##   ##                                      ##\n");
    printf("             ## CÓDIGO : %3d     ##   ##  PRODUTO: %s", Produtos[indice].codigo, Produtos[indice].nome);
    for(i = strlen(Produtos[indice].nome); i < 27; i++){
        printf(" ");
    }
    printf("##\n");
    printf("             ##                  ##   ##                                      ##\n");
    printf("             ######################   ##########################################\n");
    printf("\n");
    printf("             ######################   #########################  ###################################\n");
    printf("             ##                  ##   ##                     ##  ##                               ##\n");
    printf("             ## QUANTIDADE : %3d ##   ##  VALOR: %7.2f     ##  ##  MARGEM DE LUCRO: %7.2f     ##\n" ,Produtos[indice].quantidade, Produtos[indice].valor, Produtos[indice].margemLucro);
    printf("             ##                  ##   ##                     ##  ##                               ##\n");
    printf("             ######################   #########################  ###################################\n");
    printf("\n");
    printf("             ################################################################\n");
    printf("             ##                                                            ##\n");
    printf("             ##  USUÁRIO: %s", usuario);
    for(i = strlen(usuario); i < 49; i++){
        printf(" ");
    }
    printf("##\n");
    printf("             ##                                                            ##\n");
    printf("             ################################################################\n");
    printf("\n");

    printf("             INFORME A NOVA QUANTIDADE\n");
    receberValorInt(&quantidade);
    Produtos[indice].quantidade = Produtos[indice].quantidade + quantidade;

    PRODUTOS = fopen("Banco/Produto.csv", "w");
    for(i = 0; i < quantidadeProdutos; i++){
        fprintf(PRODUTOS,
                "{ (codigo): <%d> ; (nome): <%s> ; (quantidade): <%d> ; (valor): <%.2f> ; (margemLucro): <%.2f> ; (usuarioCadastrante): <%d> ; }\n",
                Produtos[i].codigo, Produtos[i].nome, Produtos[i].quantidade, Produtos[i].valor, Produtos[i].margemLucro, Produtos[i].usuarioCadastrante);

    }
    fclose(PRODUTOS);

}
int PRODUTOS_SELECT_CODIGO_FROM_PRODUTOS_WHERE_CODIGO(int codigo){
    int i;
    SELECT_ALL_FROM_PRODUTO();
    for(i = 0; i < quantidadeProdutos; i++){
        if(Produtos[i].codigo == codigo){
            indice = i;
            return 1;
        }
    }
    return 0;
}
void PRODUTOS_alterar(){
    FILE *PRODUTOS;
    int codigo, i, res;
    char nome[100];
    float valor, margemLucro;

    printf("             INFORME O CÓDIGO DO PRODUTO\n");
    printf("             ");
    receberValorInt(&codigo);

    if(PRODUTOS_SELECT_CODIGO_FROM_PRODUTOS_WHERE_CODIGO(codigo) == 1){
        system("cls");
        printf("             NOME ATUAL: %s\n", Produtos[indice].nome);
        printf("             NOVO NOME: ");
        fflush(stdin);
        gets(nome);
        fflush(stdin);
        strcpy(Produtos[indice].nome,nome);

        printf("             VALOR ATUAL: %.2f\n",Produtos[indice].valor);
        printf("             NOVO VALOR: ");
        SERVICOS_receberValorFloat(&valor);
        Produtos[indice].valor = valor;

        printf("             MARGEM DE LUCRO ATUAL: %.2f\n",Produtos[indice].margemLucro);
        printf("             NOVO VALOR: ");
        SERVICOS_receberValorFloat(&margemLucro);
        Produtos[indice].margemLucro = margemLucro;

        PRODUTOS = fopen("Banco/Produto.csv", "w");
        for(i = 0; i < quantidadeProdutos; i++){
            fprintf(PRODUTOS,
                    "{ (codigo): <%d> ; (nome): <%s> ; (quantidade): <%d> ; (valor): <%.2f> ; (margemLucro): <%.2f> ; (usuarioCadastrante): <%d> ; }\n",
                    Produtos[i].codigo, Produtos[i].nome, Produtos[i].quantidade, Produtos[i].valor, Produtos[i].margemLucro, Produtos[i].usuarioCadastrante);

        }
        fclose(PRODUTOS);
        MessageBox(0,"PRODUTO ALTERADO COM SUCESSO!\n", "PRODUTOS",0);
    } else {
        MessageBox(0,"PRODUTO NÃO ENCONTRADO!\n", "PRODUTOS",0);
    }
    PRODUTOS_view();

}
void PRODUTOS_excluir(){
    FILE *PRODUTOS;
    int codigo, i, op;
    char senha[50];
    printf("             INFORME O CÓDIGO DO PRODUTO\n");
    printf("             ");
    receberValorInt(&codigo);


    int msgboxID = MessageBox(NULL, "EXCLUIR", "DESEJA REALMENTE EXCLUIR ESTE PRODUTO", MB_YESNO | MB_DEFBUTTON1);
        switch(msgboxID){
            case IDYES:
                op = 1;
            break;
            case IDNO:
                op = 2;
            break;
        }
    if(op == 1){
        printf("             CONFIRME SUA SENHA: \n             ");
        SERVICOS_receberSenha(&senha);
        SERVICOS_criptografar(senha);
        if(strcmp(getSenhaLogado(), senha)==0){
            if(PRODUTOS_SELECT_CODIGO_FROM_PRODUTOS_WHERE_CODIGO(codigo) == 1){
                PRODUTOS = fopen("Banco/Produto.csv", "w");
                for(i = 0; i < quantidadeProdutos; i++){
                    if(Produtos[i].codigo != codigo){
                        fprintf(PRODUTOS,
                            "{ (codigo): <%d> ; (nome): <%s> ; (quantidade): <%d> ; (valor): <%.2f> ; (margemLucro): <%.2f> ; (usuarioCadastrante): <%d> ; }\n",
                            Produtos[i].codigo, Produtos[i].nome, Produtos[i].quantidade, Produtos[i].valor, Produtos[i].margemLucro, Produtos[i].usuarioCadastrante);

                    }

                }
                fclose(PRODUTOS);
                MessageBox(0,"PRODUTO EXCLUÍDO COM SUCESSO!\n", "PRODUTOS",0);
            } else {
                MessageBox(0,"PRODUTO NÃO ENCONTRADO!\n", "PRODUTOS",0);
            }
        } else {
            MessageBox(0,"SENHA INVÁLIDA!\n", "PRODUTOS",0);
        }
    } else {
        MessageBox(0,"OPERAÇÃO CANCELADA!\n", "PRODUTOS",0);
    }

    PRODUTOS_view();

}
void optionViewProdutos(){
    int op;

    if(strcmp(getPerfilLogado(), "Gerente") == 0 || strcmp(getPerfilLogado(), "Estoquista") == 0){
        if(strcmp(getPerfilLogado(), "Estoquista") == 0){
            printf("\n\n");
            printf("             ####################   #######################   ##############################   #######################   #######################\n");
            printf("             ##                ##   ##                   ##   ##                          ##   ##                   ##   ##                   ##\n");
            printf("             ## [ 1 ] VOLTAR   ##   ## [ 2 ] CADASTRAR   ##   ## [ 3 ] ATUALIZAR ESTOQUE  ##   ##  [ 4 ]  ALTERAR   ##   ##   [ 5 ] EXCLUIR   ##\n");
            printf("             ##                ##   ##                   ##   ##                          ##   ##                   ##   ##                   ##\n");
            printf("             ####################   #######################   ##############################   #######################   #######################\n");
            printf("             ");
            receberValorInt(&op);
        switch(op){
            case 1:
                menu();
            break;
            case 2:
                PRODUTOS_add();
            break;
            case 3:
                PRODUTOS_atualizarEstoqueProduto();
            break;
            case 4:
                PRODUTOS_alterar();
                break;
            case 5:
                PRODUTOS_excluir();
                break;
            default:
                system("color 4F");
                MessageBox(0,"OPÇÃO INVÁLIDA!\n", "PRODUTOS",0);
                system("color 0F");
                PRODUTOS_view();
            }

        } else {
            printf("\n\n");
            printf("             ####################   #######################   #######################   #######################\n");
            printf("             ##                ##   ##                   ##   ##                   ##   ##                   ##\n");
            printf("             ## [ 1 ] VOLTAR   ##   ## [ 2 ] CADASTRAR   ##   ##  [ 3 ]  ALTERAR   ##   ##   [ 4 ] EXCLUIR   ##\n");
            printf("             ##                ##   ##                   ##   ##                   ##   ##                   ##\n");
            printf("             ####################   #######################   #######################   #######################\n");
            printf("             ");
            receberValorInt(&op);
            switch(op){
                case 1:
                    menu();
                break;
                case 2:
                    PRODUTOS_add();
                break;
                case 3:
                    PRODUTOS_alterar();
                break;
                case 4:
                    PRODUTOS_excluir();
                break;
                default:
                    system("color 4F");
                    MessageBox(0,"OPÇÃO INVÁLIDA!\n", "PRODUTOS",0);
                    system("color 0F");
                    PRODUTOS_view();
            }
        }

    } else if(strcmp(getPerfilLogado(), "Vendedor") == 0) {
        printf("             ####################\n");
        printf("             ##                ##\n");
        printf("             ## [ 1 ] VOLTAR   ##\n");
        printf("             ##                ##\n");
        printf("             ####################\n");
        printf("             ");
        receberValorInt(&op);
        switch(op){
            case 1:
                menu();
            break;
            /*case 2:
                printf("Outra Coisa!\n");
            break;*/
            default:
                MessageBox(0,"OPÇÃO INVÁLIDA!\n", "PRODUTOS",0);
        }
    }else{
        printf("             ####################\n");
        printf("             ##                ##\n");
        printf("             ## [ 1 ] VOLTAR   ##\n");
        printf("             ##                ##\n");
        printf("             ####################\n");
        printf("             ");
        receberValorInt(&op);
        switch(op){
            case 1:
                menu();
            break;
            default:
                MessageBox(0,"OPÇÃO INVÁLIDA!\n", "PRODUTOS",0);
        }
    }


}
void PRODUTOS_retirarDoEstoque(int quantidade, int idProduto){
    FILE *PRODUTOS;
    int i;
    SELECT_ALL_FROM_PRODUTO();
    for(i = 0; i < quantidadeProdutos; i++){
        if(Produtos[i].codigo == idProduto){
            Produtos[i].quantidade = Produtos[i].quantidade - quantidade;
        }
    }
    PRODUTOS = fopen("Banco/Produto.csv", "w");
    for(i = 0; i < quantidadeProdutos; i++){
        fprintf(PRODUTOS,
                "{ (codigo): <%d> ; (nome): <%s> ; (quantidade): <%d> ; (valor): <%.2f> ; (margemLucro): <%.2f> ; (usuarioCadastrante): <%d> ; }\n",
                Produtos[i].codigo, Produtos[i].nome, Produtos[i].quantidade, Produtos[i].valor, Produtos[i].margemLucro, Produtos[i].usuarioCadastrante);

    }
    fclose(PRODUTOS);

}
void PRODUTOS_retornarDoEstoque(int quantidade, int idProduto){
    FILE *PRODUTOS;
    int i;
    SELECT_ALL_FROM_PRODUTO();
    for(i = 0; i < quantidadeProdutos; i++){
        if(Produtos[i].codigo == idProduto){
            Produtos[i].quantidade = Produtos[i].quantidade + quantidade;
        }
    }
    PRODUTOS = fopen("Banco/Produto.csv", "w");
    for(i = 0; i < quantidadeProdutos; i++){

        fprintf(PRODUTOS,
                "{ (codigo): <%d> ; (nome): <%s> ; (quantidade): <%d> ; (valor): <%.2f> ; (margemLucro): <%.2f> ; (usuarioCadastrante): <%d> ; }\n",
                Produtos[i].codigo, Produtos[i].nome, Produtos[i].quantidade, Produtos[i].valor, Produtos[i].margemLucro, Produtos[i].usuarioCadastrante);
    }
    fclose(PRODUTOS);

}
char* getNomeProduto(int codigo){
    int i;
    SELECT_ALL_FROM_PRODUTO();
    for(i = 0; i <  quantidadeProdutos; i++){
        if(codigo == Produtos[i].codigo){
            return Produtos[i].nome;
        }
    }
}



#endif // PRODUTOS_H_INCLUDED
