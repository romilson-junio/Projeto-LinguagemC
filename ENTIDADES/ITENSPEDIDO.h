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

int SELECT_ITENS_FROM_ITENSPEDIDO(int idPedido){
    FILE *ITENS;
    int idItenFILE, idPedidoFILE, idProdutoFILE, quantidadeFILE, i;
    float valorFILE;
    int existe = 0;
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
                existe = 1;
            }
        }
        quantidadeItens = i;
    fclose(ITENS);
    return existe;
}

void ITENS_PEDIDO_view(int idPedido){
    float valorTotal, valor;
    int i,j, op, idVendedor;
    char nome[255], usuario[100], cpf[20], cliente[255], data[15] = " ";
    if(SELECT_ITENS_FROM_ITENSPEDIDO(idPedido) == 1){
        system("cls");
        idVendedor = PEDIDOS_idVendedor(idPedido);
        strcpy(usuario, getNomeVendedor(idVendedor));
        valor = PEDIDOS_valorTotalPedido(idPedido);
        strcpy(cpf , PEDIDOS_cpfCliente(idPedido));
        getNomeCliente(cliente, cpf);
        getDataPedido(data, idPedido);
        printf("             ######################   ##########################################   ###################################\n");
        printf("             ##                  ##   ##                                      ##   ##                               ##\n");
        printf("             ## CÓDIGO : %3d     ##   ##  VENDEDOR: %s",idPedido, usuario);
        for(i = strlen(usuario); i < 26; i++){
            printf(" ");
        }
        printf("##   ##   DATA PEDIDO : %s",data);
        for(i = strlen(data); i < 14; i++){
            printf(" ");
        }
        printf("##\n");
        printf("             ##                  ##   ##                                      ##   ##                               ##\n");
        printf("             ######################   ##########################################   ###################################\n");
        printf("\n");
        printf("             #################################  ######################################################################\n");
        printf("             ##                             ##  ##                                                                  ##\n");
        printf("             ##  TOTAL: R$ %7.2f          ##  ##  CLIENTE: %s" ,valor, cliente);
        for(i = strlen(cliente); i < 55; i++){
            printf(" ");
        }
        printf("##\n");
        printf("             ##                             ##  ##                                                                  ##\n");
        printf("             #################################  ######################################################################\n");


        printf("\n");
        printf("                       #######################################################################################\n");
        printf("                       ##  PRODUTO                      #  QUANTIDADE  #  VALOR         #  VALOR TOTAL      ##\n");
        printf("                       #######################################################################################\n");
        for(i = 0; i <quantidadeItens; i++){
            valorTotal = itens[i].quantidade * itens[i].valor;
            strcpy(nome, getNomeProduto(itens[i].idProduto));
            printf("                       ##  %s  ", nome);
            for(j = strlen(nome); j < 27; j++){
                printf(" ");
            }
            printf("#     %3d      #  R$ %10.2f #  R$ %12.2f  ##\n",itens[i].quantidade,itens[i].valor, valorTotal);

        }
        printf("                       #######################################################################################\n");

        printf("\n\n");
        printf("             ####################   #######################\n");
        printf("             ##                ##   ##                   ##\n");
        printf("             ## [ 1 ] VOLTAR   ##   ##  [ 2 ] ALTERAR    ##\n");
        printf("             ##                ##   ##                   ##\n");
        printf("             ####################   #######################\n");

        scanf("%d", &op);
        switch(op){
            case 1:
                PEDIDOS_view();
            break;
            case 2:

            break;
            default:
                MessageBox(0,"OPÇÃO INVÁLIDA!\n", "PRODUTOS",0);
                PEDIDOS_view();
        }
    } else {
        MessageBox(0,"PEDIDO NÃO ENCONTRADO!\n", "PEDIDOS",0);
        PEDIDOS_view();
    }


}

#endif // ITENSPEDIDO_H_INCLUDED
