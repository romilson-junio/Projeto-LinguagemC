#ifndef ITENSPEDIDO_H_INCLUDED
#define ITENSPEDIDO_H_INCLUDED
#include <stdbool.h>
struct ITENSPEDIDO{
    int idIten;
    int idPedido;
    int idProduto;
    int quantidade;
    float valor;
};

struct ITENSPEDIDO itens[1000];
int quantidadeItens;

void SELECT_ALL_FROM_ITENSPEDIDO(){
    FILE *ITENS;
    int idItenFILE, idPedidoFILE, idProdutoFILE, quantidadeFILE, i;
    float valorFILE;
    ITENS = fopen("Banco/ItensPedido.csv", "r");
        i = 0;
        while(fscanf(ITENS,"%d ; %d ; %d ; %d ; %f ;\n", &idItenFILE, &idPedidoFILE, &idProdutoFILE, &quantidadeFILE, &valorFILE) != EOF){
                itens[i].idIten = idItenFILE;
                itens[i].idPedido = idPedidoFILE;
                itens[i].idProduto = idProdutoFILE;
                itens[i].quantidade = quantidadeFILE;
                itens[i].valor = valorFILE;
                i++;
        }
        quantidadeItens = i;
    fclose(ITENS);

}

void ITENS_PEDIDO_add(int idPedido, int idProduto, double valorUnitario, int quantidade){
    SELECT_ALL_FROM_ITENSPEDIDO();
    FILE *ITENS;
    int i;
    for(i = 0; i < quantidadeItens; i++){
        if(itens[i].idPedido == idPedido && itens[i].idProduto == idProduto && itens[i].valor == valorUnitario){
            itens[i].quantidade += quantidade;

            ITENS = fopen("Banco/ItensPedido.csv", "w");
                int j;
                for(j = 0; j < quantidadeItens; j++){
                    fprintf(ITENS, "%d ; %d ; %d ; %d ; %f ;\n",
                            itens[j].idIten, itens[j].idPedido, itens[j].idProduto, itens[j].quantidade, itens[j].valor);

                }
            fclose(ITENS);
            return 1;
        }
    }
    int idIten;
    idIten = quantidadeItens+1;
    ITENS = fopen("Banco/ItensPedido.csv", "a");
        fprintf(ITENS, "%d ; %d ; %d ; %d ; %f ;\n", idIten, idPedido, idProduto, quantidade, valorUnitario);

    fclose(ITENS);
}

void SELECT_ITENS_FROM_ITENSPEDIDO(int idPedido){
    FILE *ITENS;
    int idItenFILE, idPedidoFILE, idProdutoFILE, quantidadeFILE, i;
    float valorFILE;
    ITENS = fopen("Banco/ItensPedido.csv", "r");
        i = 0;
        while(fscanf(ITENS,"%d ; %d ; %d ; %d ; %f ;\n", &idItenFILE, &idPedidoFILE, &idProdutoFILE, &quantidadeFILE, &valorFILE) != EOF){

            if(idPedidoFILE == idPedido){
                itens[i].idIten = idItenFILE;
                itens[i].idPedido = idPedidoFILE;
                itens[i].idProduto = idProdutoFILE;
                itens[i].quantidade = quantidadeFILE;
                itens[i].valor = valorFILE;
                i++;
            }
        }
        quantidadeItens = i;
    fclose(ITENS);

}

void ITENS_PEDIDO_view(int idPedido){
    float valorTotal;
    int i, op;
    char nome[255];
    SELECT_ITENS_FROM_ITENSPEDIDO(idPedido);
    printf("ID\n", idPedido);
    printf("PRODUTO QUANTIDADE VALOR  VALOR TOTAL\n");
    for(i = 0; i < quantidadeItens; i++){
        valorTotal = itens[i].quantidade * itens[i].valor;
        strcpy(nome, getNomeProduto(itens[i].idProduto));
        printf("%s %d %.2f %.2f \n",nome ,itens[i].quantidade,itens[i].valor, valorTotal);
    }
}

#endif // ITENSPEDIDO_H_INCLUDED
