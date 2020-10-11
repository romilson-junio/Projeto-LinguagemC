#ifndef PEDIDOS_H_INCLUDED
#define PEDIDOS_H_INCLUDED

int quantidadePedidos;

struct PEDIDO{
    int codigo, idVendedor;
    float valorTotal;
    char cpfCliente[12];
    int dia, mes, ano;
};

struct PEDIDO Pedidos[1000];

struct CARRINHO{
    int idProduto;
    int quantidade;
    float valor;
};
struct CARRINHO Carrinho[100];

void SELECT_ALL_FROM_PEDIDOS(){
    FILE *PEDIDOS;
    int codigoFILE, idVendedorFILE, i;
    float valorTotalFile;
    char cpfClienteFILE[100];
    int diaFILE, mesFILE, anoFILE, op;

    PEDIDOS = fopen("Banco/Pedido.csv", "r");
        i = 0;
        while(fscanf(PEDIDOS,"%d ; %d ; %f ; %s ; %d ; %d ; %d ;\n",
            &codigoFILE , &idVendedorFILE, &valorTotalFile, &cpfClienteFILE, &diaFILE, &mesFILE, &anoFILE) != EOF){
                Pedidos[i].codigo = codigoFILE;
                Pedidos[i].idVendedor = idVendedorFILE;
                Pedidos[i].valorTotal = valorTotalFile;
                strcpy(Pedidos[i].cpfCliente, cpfClienteFILE);
                Pedidos[i].dia = diaFILE;
                Pedidos[i].mes = mesFILE;
                Pedidos[i].ano = anoFILE;
                i++;
        }
        quantidadePedidos = i;
    fclose(PEDIDOS);

}

void PEDIDOS_view(){
    int i;
    char nomeVendedor[100], nomeProduto[100];
    SELECT_ALL_FROM_PEDIDOS();
    system("cls");
    printf("CODIGO VENDEDOR VALOR TOTAL CPF CLIENTE DATA\n");
    for(i = 0; i <quantidadePedidos; i++){
        printf("%d  ", Pedidos[i].codigo);
        strcpy(nomeVendedor, getNomeVendedor(Pedidos[i].idVendedor));
        printf("%s  ", nomeVendedor);
        printf("%.2f  ", Pedidos[i].valorTotal);
        printf("%s  ", Pedidos[i].cpfCliente);
        printf("%2d/", Pedidos[i].dia);
        printf("%2d/", Pedidos[i].mes);
        printf("%4d\n", Pedidos[i].ano);

    }
    optionViewPedidos();
}
void PEDIDOS_add(){
    FILE *PEDIDOS;
    SELECT_ALL_FROM_PEDIDOS();
    int result ,codigo, idVendedor, idProduto, quantidade, valido;
    float valor;
    float valorTotal;
    char cpf[20], nomeProduto[100];
    int dia, mes, ano, carrinho, i,j, itens;
    carrinho = 0;
    codigo = quantidadePedidos+1;
    idVendedor = getIdLogado();
    itens = 0;
    do{
        printf("INFORME O CPF DO CLIENTE\n");
        scanf("%s", &cpf);
        fflush(stdin);
        valido = SERVICOS_validarCPF(cpf);
    }while(valido == 0);
    CLIENTES_concultarCPF(cpf);
    system("cls");
    do{
        do{
            PRODUTOS_insert();
            if(itens != 0){
                printf("*********************************************\n");

                for(j=0; j < itens;j++){
                    strcpy(nomeProduto, getNomeProduto(Carrinho[j].idProduto));
                    printf("%s %d %.f\n", nomeProduto, Carrinho[j].quantidade, Carrinho[j].valor);
                }
                printf("*********************************************\n");
            }
            printf("INFORME O CÓDIGO DO PRODUTO                                                   Carrinho %d: \n", carrinho);
            scanf("%d", &idProduto);
            do{
                printf("INFORME A QUANTIDADE DO PRODUTO\n");
                scanf("%d", &quantidade);
            }while(quantidade == 0);

            result = PRODUTOS_verificarDisponibilidade(idProduto, quantidade);
            if(result == 0){
                MessageBox(0,"PRODUTO NÃO ENCONTRADO!\n", "PEDIDOS",0);
            }else if(result == 2){
                MessageBox(0,"PRODUTO SEM SALDO NO ESTOQUE!\n", "PEDIDOS",0);
            }else if(result == 1){
                carrinho += quantidade;
            }
            system("cls");
        }while(result == 0 || result == 2);

        printf("INFORME O VALOR\n");
        scanf("%f", &valor);

        Carrinho[itens].idProduto = idProduto;
        Carrinho[itens].quantidade = quantidade;
        Carrinho[itens].valor = valor;
        PRODUTOS_retirarDoEstoque(quantidade, idProduto);
        valorTotal = valorTotal + (quantidade * valor);
        itens++;
    } while(novoProduto() == 1);
    printf("*********************************************\n");
    for(j=0; j < itens;j++){
        strcpy(nomeProduto, getNomeProduto(Carrinho[j].idProduto));
        printf("%s %d %.f\n", nomeProduto, Carrinho[j].quantidade, Carrinho[j].valor);
    }
    printf("*********************************************\n");


    printf("INFORME O ANO\n");
    scanf("%d", &ano);

    printf("INFORME O MÊS\n");
    scanf("%d", &mes);

    printf("INFORME O DIA\n");
    scanf("%d", &dia);
    PEDIDOS = fopen("Banco/Pedido.csv", "a");

        fprintf(PEDIDOS, "%d ; %d ; %.2f ; %s ; %d ; %d ; %d ;\n",
            codigo, idVendedor, valorTotal, cpf , dia , mes , ano);

    fclose(PEDIDOS);
    for(i=0; i < itens;i++){
        ITENS_PEDIDO_add(codigo , Carrinho[i].idProduto ,Carrinho[i].valor , Carrinho[i].quantidade);
    }
    MessageBox(0,"PEDIDO CADASTRADO COM SUCESSO!\n", "PEDIDOS",0);
    PEDIDOS_view();

}
int novoProduto(){
    char opcao;
    bool opcaoValida;
    do{
        opcaoValida = true;
        printf("Deseja adicionar um novo produto! [ S ] [ N ]");
        scanf(" %c", &opcao);
        switch(opcao){
            case 'S':
            case 's':
                return 1;
                break;
            case 'N':
            case 'n':
                return 0;
                break;
            default:
                printf("OPÇÃO INVÁLIDA!");
                opcaoValida = false;
        }
    }while(!opcaoValida);

}
void optionViewPedidos(){
    int op, pedido;

    if(strcmp(getPerfilLogado(), "Gerente") == 0 || strcmp(getPerfilLogado(), "Vendedor") == 0){

    printf("\n\n");
    printf("             ####################   #######################   ######################\n");
    printf("             ##                ##   ##                   ##   ##                  ##\n");
    printf("             ## [ 1 ] VOLTAR   ##   ## [ 2 ] CADASTRAR   ##   ## [ 3 ] DETALHAR   ##\n");
    printf("             ##                ##   ##                   ##   ##                  ##\n");
    printf("             ####################   #######################   ######################\n");

    scanf("%d", &op);
    switch(op){
        case 1:
            menu();
        break;
        case 2:
            PEDIDOS_add();
        break;
        case 3:
            printf("INFORME O NÚMERO DO PEDIDO\n");
            scanf("%d", &pedido);
            ITENS_PEDIDO_view(pedido);
        break;
        default:
            MessageBox(0,"OPÇÃO INVÁLIDA!\n", "PRODUTOS",0);
            PEDIDOS_view();
        }
    } else if(strcmp(getPerfilLogado(), "Estoquista") == 0) {
        printf("             ####################\n");
        printf("             ##                ##\n");
        printf("             ## [ 1 ] VOLTAR   ##\n");
        printf("             ##                ##\n");
        printf("             ####################\n");
        scanf("%d", &op);
        switch(op){
            case 1:
                menu();
            break;
            default:
                MessageBox(0,"OPÇÃO INVÁLIDA!\n", "PRODUTOS",0);
        }
    }else{
        printf("             ####################\n");
        printf("             ##                ##\n");
        printf("             ## [ 1 ] VOLTAR   ##\n");
        printf("             ##                ##\n");
        printf("             ####################\n");
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
#endif // PEDIDOS_H_INCLUDED
