#ifndef PRODUTOS_H_INCLUDED
#define PRODUTOS_H_INCLUDED
#include <stdbool.h>
int quantidadeProdutos;

struct PRODUTOS{
    int codigo, quantidade, usuarioCadastrante;
    float valor, taxaComissao;
    char nome[50];
};

struct PRODUTOS Produtos[1000];

void SELECT_ALL_FROM_PRODUTO(){
    FILE *PRODUTOS;
    int i, codigoFile, quantidadeFile, usuarioCadastranteFile;
    float valorFile, taxaComissaoFile;
    char nomeFile[50];
    PRODUTOS = fopen("Banco/Produto.csv", "r");
    i = 0;
    while(fscanf(PRODUTOS, "%d ; %s ; %d ; %f ; %f ; %d ;\n", &codigoFile, &nomeFile, &quantidadeFile, &valorFile, &taxaComissaoFile, &usuarioCadastranteFile) != EOF){
        Produtos[i].codigo = codigoFile;
        strcpy(Produtos[i].nome, nomeFile);
        Produtos[i].quantidade = quantidadeFile;
        Produtos[i].valor = valorFile;
        Produtos[i].taxaComissao = taxaComissaoFile;
        Produtos[i].usuarioCadastrante = usuarioCadastranteFile;
        i++;
    }
    quantidadeProdutos = i;
    fclose(PRODUTOS);
}

void PRODUTOS_view(){
    int j;
    SELECT_ALL_FROM_PRODUTO();
    system("cls");
    printf("CÓDIGO    NOME   QUANTIDADE  VALOR  TAXA COMISSAO  USUARIO\n");
    for(j = 0; j < quantidadeProdutos; j++){
        printf("%d       %s     %d     %.2f  %.2f  %d \n", Produtos[j].codigo, Produtos[j].nome, Produtos[j].quantidade, Produtos[j].valor, Produtos[j].taxaComissao, Produtos[j].usuarioCadastrante);
    }
    optionViewProdutos();
}

void PRODUTOS_insert(){
    int j;
    SELECT_ALL_FROM_PRODUTO();
    system("cls");
    printf("CÓDIGO    NOME   QUANTIDADE  VALOR  TAXA COMISSAO  USUARIO\n");
    for(j = 0; j < quantidadeProdutos; j++){
        printf("%d       %s     %d     %.2f  %.2f  %d \n", Produtos[j].codigo, Produtos[j].nome, Produtos[j].quantidade, Produtos[j].valor, Produtos[j].taxaComissao, Produtos[j].usuarioCadastrante);
    }
}

void PRODUTOS_add(){
    FILE *PRODUTOS;
    int i, quantidade, codigo;
    float valor, taxaComissao;
    char nome[50];
    SELECT_ALL_FROM_PRODUTO();
    system("cls");
    printf("INFORME O NOME DO PRODUTO\n");
    fflush(stdin);
    gets(nome);
    fflush(stdin);

    for(i = 0; i < quantidadeProdutos; i++){
        if(strcmp(nome, Produtos[i].nome) == 0){
            MessageBox(0,"PRODUTO JÁ CADASTRADO!\n", "CADASTRO DE PRODUTOS",0);
            PRODUTOS_view();
        }
    }
    printf("INFORME A QUANTIDADE\n");
    scanf("%d", &quantidade);
    printf("INFORME O VALOR\n");
    scanf("%f", &valor);
    printf("INFORME A TAXA DE COMISSÃO\n");
    scanf("%f", &taxaComissao);
    codigo = quantidadeProdutos+1;
    PRODUTOS = fopen("Banco/Produto.csv", "a");

        fprintf(PRODUTOS,"%d ; %s ; %d ; %.2f ; %.2f ; %d ;\n", codigo, nome, quantidade, valor, taxaComissao, getIdLogado());
        MessageBox(0,"PRODUTO CADASTRADO COM SUCESSO!\n", "CADASTRO DE PRODUTOS",0);
    fclose(PRODUTOS);
    return 1;

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
    int i;
    SELECT_ALL_FROM_PRODUTO();
    printf("CÓDIGO    NOME   QUANTIDADE  VALOR  TAXA COMISSAO  USUARIO\n");
    for(i = 0; i < quantidadeProdutos; i++){
        if(Produtos[i].quantidade <= 5){
            printf("%d       %s     %d     %.2f  %.2f  %d \n", Produtos[i].codigo, Produtos[i].nome, Produtos[i].quantidade, Produtos[i].valor, Produtos[i].taxaComissao, Produtos[i].usuarioCadastrante);
        }
    }
    getchar();
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
void optionViewProdutos(){
    int op;

    if(strcmp(getPerfilLogado(), "Gerente") == 0 || strcmp(getPerfilLogado(), "Estoquista") == 0){
    printf("\n\n");
    printf("####################   #######################\n");
    printf("##                ##   ##                   ##\n");
    printf("## [ 1 ] VOLTAR   ##   ## [ 2 ] CADASTRAR   ##\n");
    printf("##                ##   ##                   ##\n");
    printf("####################   #######################\n");

    scanf("%d", &op);
    switch(op){
        case 1:
            menu();
        break;
        case 2:
            PRODUTOS_add();
        break;
        default:
            system("color 4F");
            MessageBox(0,"OPÇÃO INVÁLIDA!\n", "PRODUTOS",0);
            system("color 0F");
            PRODUTOS_view();
        }
    } else if(strcmp(getPerfilLogado(), "Vendedor") == 0) {
        printf("\n\n\ [ 1 ] VOLTAR  [ 2 ] OUTRA COISA\n\n");
        scanf("%d", &op);
        switch(op){
            case 1:
                menu();
            break;
            case 2:
                printf("Outra Coisa!\n");
            break;
            default:
                MessageBox(0,"OPÇÃO INVÁLIDA!\n", "PRODUTOS",0);
        }
    }else{
        printf("\n\n\ [ 1 ] VOLTAR\n\n");
        scanf("%d", &op);
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
        fprintf(PRODUTOS,"%d ; %s ; %d ; %.2f ; %.2f ; %d ;\n",
                Produtos[i].codigo, Produtos[i].nome, Produtos[i].quantidade, Produtos[i].valor, Produtos[i].taxaComissao, Produtos[i].usuarioCadastrante);

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
