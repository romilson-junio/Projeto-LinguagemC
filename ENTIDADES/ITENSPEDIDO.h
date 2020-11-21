#ifndef ITENSPEDIDO_H_INCLUDED
#define ITENSPEDIDO_H_INCLUDED
#include <stdbool.h>
struct ITENSPEDIDO{
    int idIten;
    int idPedido;
    int idProduto;
    char nomeProduto[100];
    int quantidade;
    float valor;
};

struct ITENSPEDIDO itens[1000];
int quantidadeItens;

void SELECT_ALL_FROM_ITENSPEDIDO(){
    FILE *ITENS;
    /*Variáveis da Funcionalidade*/
    char idItenFILE[10], idPedidoFILE[10], idProdutoFILE[10], quantidadeFILE[10], valorFILE[20];

    /*Variáveis da consulta*/
    int i,j, n,indice = 0;
    bool dado = false, var  = false, fim;
    char variavel[15];
    char dados[1000];


    ITENS = fopen("Banco/ItensPedido.csv", "r");
    while((fgets(dados, sizeof(dados), ITENS))!=NULL){
        fim = false;

        memset(idItenFILE, '\000', strlen(idItenFILE) * sizeof(char));
        memset(idPedidoFILE, '\000', strlen(idPedidoFILE) * sizeof(char));
        memset(idProdutoFILE, '\000', strlen(idProdutoFILE) * sizeof(char));
        memset(quantidadeFILE, '\000', strlen(quantidadeFILE) * sizeof(char));
        memset(valorFILE, '\000', strlen(valorFILE) * sizeof(char));

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
                     if(strcmp(variavel, "idItem")     == 0){ idItenFILE[n] = dados[i];}
                else if(strcmp(variavel, "nomeProduto") == 0){ itens[indice].nomeProduto[n] = dados[i]; }
                else if(strcmp(variavel, "idPedido") == 0){ idPedidoFILE[n] = dados[i]; }
                else if(strcmp(variavel, "idProduto") == 0){ idProdutoFILE[n] = dados[i]; }
                else if(strcmp(variavel, "quantidade") == 0){ quantidadeFILE[n] = dados[i]; }
                else if(strcmp(variavel, "valorProduto") == 0){ valorFILE[n] = dados[i]; }
                n++;
            }
        }

        itens[indice].idIten = atoi(idItenFILE);
        itens[indice].idPedido = atoi(idPedidoFILE);
        itens[indice].idProduto = atoi(idProdutoFILE);
        itens[indice].quantidade = atoi(quantidadeFILE);
        sscanf(valorFILE, "%f", &itens[indice].valor);
        indice++;

    }
    quantidadeItens = indice;
    fclose(ITENS);

}

void ITENS_PEDIDO_add(int idPedido, int idProduto , double valorUnitario, int quantidade){
    SELECT_ALL_FROM_ITENSPEDIDO();
    char nomeProduto[100];
    FILE *ITENS;
    int i;
    for(i = 0; i < quantidadeItens; i++){
        if(itens[i].idPedido == idPedido && itens[i].idProduto == idProduto && itens[i].valor == valorUnitario){
            itens[i].quantidade += quantidade;

            ITENS = fopen("Banco/ItensPedido.csv", "w");
                int j;
                for(j = 0; j < quantidadeItens; j++){
                    strcpy(nomeProduto, getNomeProduto(Carrinho[i].idProduto));
                    fprintf(ITENS,
                            "{ (idItem): <%d> ; (idPedido): <%d> ; (idProduto): <%d> ; (nomeProduto): <%s> 	; (quantidade): <%d> ; (valorProduto): <%.2f> ; }\n",
                            itens[j].idIten, itens[j].idPedido, itens[j].idProduto, nomeProduto, itens[j].quantidade, itens[j].valor);

                }
            fclose(ITENS);
            return 1;
        }
    }
    int idIten;
    idIten = quantidadeItens+1;
    strcpy(nomeProduto, getNomeProduto(idProduto));
    ITENS = fopen("Banco/ItensPedido.csv", "a");
        fprintf(ITENS,
            "{ (idItem): <%d> ; (idPedido): <%d> ; (idProduto): <%d> ; (nomeProduto): <%s> 	; (quantidade): <%d> ; (valorProduto): <%.2f> ; }\n",
            idIten, idPedido, idProduto, nomeProduto, quantidade, valorUnitario);

    fclose(ITENS);
}
int SELECT_ITENS_FROM_ITENSPEDIDO(int idPedido){
    int i, existe = 0;
    SELECT_ALL_FROM_ITENSPEDIDO();
    for(i = 0; i < quantidadeItens; i++){
        if(idPedido == itens[i].idPedido){
            existe += 1;
        }
    }

    return existe;
}
void PEDIDOS_excluir(int idPedido){
    char senha[50];
    int j,op;
    int msgboxID = MessageBox(NULL, "DESEJA REALMENTE EXCLUIR ESTE PEDIDO","EXCLUIR",  MB_YESNO | MB_DEFBUTTON1);
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
            FILE *ITENS;
            SELECT_ALL_FROM_ITENSPEDIDO();
            if(PEDIDOS_excluirPedido(idPedido) == 1){
                ITENS = fopen("Banco/ItensPedido.csv", "w");
                int j;
                for(j = 0; j < quantidadeItens; j++){
                    if(itens[j].idPedido != idPedido){
                        fprintf(ITENS,
                                "{ (idItem): <%d> ; (idPedido): <%d> ; (idProduto): <%d> ; (nomeProduto): <%s> 	; (quantidade): <%d> ; (valorProduto): <%.2f> ; }\n",
                                itens[j].idIten, itens[j].idPedido, itens[j].idProduto, itens[j].nomeProduto, itens[j].quantidade, itens[j].valor);

                    }

                }
                fclose(ITENS);
                MessageBox(0,"PEDIDO EXCLUÍDO COM SUCESSO!\n", "PEDIDOS",0);
            } else {
                MessageBox(0,"NÃO FOI POSSÍVEL REALIZAR ESTA OPERAÇÃO!\n", "PEDIDOS",0);
            }
        } else {
            MessageBox(0,"SENHA INVÁLIDA!\n", "PRODUTOS",0);
        }
    } else {
        MessageBox(0,"OPERAÇÃO CANCELADA!\n", "PRODUTOS",0);
    }

    PEDIDOS_view();
}
void ITENS_PEDIDO_view(int idPedido, int tipo){
    float valorTotal, valor,valorTotalPedido = 0;
    int i,j, op, idVendedor;
    char nome[255], usuario[100], cpf[20], cliente[155], data[15] = " ";

    if(SELECT_ITENS_FROM_ITENSPEDIDO(idPedido) > 0){

        system("cls");
        tituloTabela("Detalhes do Pedido");
        idVendedor = PEDIDOS_idVendedor(idPedido);
        strcpy(usuario, getNomeVendedor(idVendedor));
        valor = PEDIDOS_valorTotalPedido(idPedido);
        strcpy(cpf , PEDIDOS_cpfCliente(idPedido));
        getNomeCliente(cliente, cpf);
        getDataPedido(data, idPedido);
        printf("\n\n");
        printf("                          ######################   ##########################################   ###################################\n");
        printf("                          ##                  ##   ##                                      ##   ##                               ##\n");
        printf("                          ## CÓDIGO : %3d     ##   ##  VENDEDOR: %s",idPedido, usuario);
        for(i = strlen(usuario); i < 26; i++){
            printf(" ");
        }
        printf("##   ##   DATA PEDIDO : %s",data);
        for(i = strlen(data); i < 14; i++){
            printf(" ");
        }
        printf("##\n");
        printf("                          ##                  ##   ##                                      ##   ##                               ##\n");
        printf("                          ######################   ##########################################   ###################################\n");
        printf("\n");
        printf("                          #################################  ######################################################################\n");
        printf("                          ##                             ##  ##                                                                  ##\n");
        printf("                          ##  TOTAL: R$ %11.2f      ##  ##  CLIENTE: %s" ,valor, cliente);
        for(i = strlen(cliente); i < 55; i++){
            printf(" ");
        }
        printf("##\n");
        printf("                          ##                             ##  ##                                                                  ##\n");
        printf("                          #################################  ######################################################################\n");


        printf("\n");
        printf("                                    #######################################################################################\n");
        printf("                                    ##  PRODUTO                      #  QUANTIDADE  #      VALOR     #    VALOR TOTAL    ##\n");
        printf("                                    #######################################################################################\n");
        for(i = 0; i <quantidadeItens; i++){

            if(idPedido == itens[i].idPedido){
                valorTotal = itens[i].quantidade * itens[i].valor;
                /*valorTotalPedido += valorTotal;*/
                printf("                                    ##  %s  ", itens[i].nomeProduto);
                for(j = strlen(itens[i].nomeProduto); j < 27; j++){
                    printf(" ");
                }
                printf("#     %3d      #  R$ %10.2f #  R$ %12.2f  ##\n",itens[i].quantidade,itens[i].valor, valorTotal);
            }
        }
        printf("                                    ##_______________________________#______________#________________#___________________##\n");
        printf("                                    ##                                                    TOTAL      #  R$ %12.2f  ##\n", valor);
        printf("                                    #######################################################################################\n");

        printf("\n\n");
        printf("                          ####################   #######################\n");
        printf("                          ##                ##   ##                   ##\n");
        printf("                          ## [ 1 ] VOLTAR   ##   ##  [ 2 ] EXCLUIR    ##\n");
        printf("                          ##                ##   ##                   ##\n");
        printf("                          ####################   #######################\n");
        printf("\n                           ");
        receberValorInt(&op);
        switch(op){
            case 1:
                if(tipo == 1){
                    PEDIDOS_view();
                } else {
                    PEDIDOS_viewPedidosCliente(cpf);
                }
            break;
            case 2:
                PEDIDOS_excluir(idPedido);
            break;
            default:
                MessageBox(0,"OPÇÃO INVÁLIDA!\n", "PEDIDOS",0);
                ITENS_PEDIDO_view(idPedido, tipo);
        }
    } else {
        MessageBox(0,"PEDIDO NÃO ENCONTRADO!\n", "PEDIDOS",0);
        PEDIDOS_view();
    }


}

#endif // ITENSPEDIDO_H_INCLUDED
