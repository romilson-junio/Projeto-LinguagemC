#ifndef PEDIDOS_H_INCLUDED
#define PEDIDOS_H_INCLUDED

#define CODIGO "codigo"

int quantidadePedidos;
int tipoConsulta;
char* cpfConsulta[15];
struct PEDIDO{
    int codigo, idVendedor;
    float valorTotal;
    char cpfCliente[15];
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
    int i,j, n,indice = 0;

    bool dado = false, var  = false, fim;
    char variavel[15];
    char dados[1000];
    char codigoOld[5], idVendedorOld[5], valorOld[15], diaOld[4], mesOld[4], anoOld[6];

    PEDIDOS = fopen("Banco/Pedido.csv", "r");
    while((fgets(dados, sizeof(dados), PEDIDOS))!=NULL){
        fim = false;
        strcpy(codigoOld, "0");
        strcpy(idVendedorOld, "0");
        strcpy(diaOld, "0");
        strcpy(mesOld, "0");
        strcpy(anoOld, "0");

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
                     if(strcmp(variavel, CODIGO)     == 0){ codigoOld[n] = dados[i];}
                else if(strcmp(variavel, "idVendedor") == 0){ idVendedorOld[n] = dados[i]; }
                else if(strcmp(variavel, "valorTotal") == 0){ valorOld[n] = dados[i]; }
                else if(strcmp(variavel, "cpfCliente") == 0){ Pedidos[indice].cpfCliente[n] = dados[i]; }
                else if(strcmp(variavel, "dia")   == 0){ diaOld[n] = dados[i]; }
                else if(strcmp(variavel, "mes")   == 0){ mesOld[n] = dados[i]; }
                else if(strcmp(variavel, "ano")   == 0){ anoOld[n] = dados[i]; }

                n++;
            }
        }
        Pedidos[indice].codigo = atoi(codigoOld);
        Pedidos[indice].idVendedor = atoi(idVendedorOld);
        sscanf(valorOld, "%f", &Pedidos[indice].valorTotal);
        Pedidos[indice].dia = atoi(diaOld);
        Pedidos[indice].mes = atoi(mesOld);
        Pedidos[indice].ano = atoi(anoOld);
        indice++;

    }
    quantidadePedidos = indice;
    fclose(PEDIDOS);

}

float PEDIDOS_valorTotalPedido(int idPedido){
    int i;
    SELECT_ALL_FROM_PEDIDOS();
    for(i = 0; i < quantidadePedidos; i++){
        if(Pedidos[i].codigo == idPedido){
            return Pedidos[i].valorTotal;
        }
    }
}

char* PEDIDOS_cpfCliente(int idPedido){
    int i;
    SELECT_ALL_FROM_PEDIDOS();
    for(i = 0; i < quantidadePedidos; i++){
        if(Pedidos[i].codigo == idPedido){
            return Pedidos[i].cpfCliente;
        }
    }
}

int PEDIDOS_idVendedor(int idPedido){
    int i;
    SELECT_ALL_FROM_PEDIDOS();
    for(i = 0; i < quantidadePedidos; i++){
        if(Pedidos[i].codigo == idPedido){
            return Pedidos[i].idVendedor;
        }
    }
}
void getDataPedido(char* data, int idPedido){
    int i;
    char buffer[6];
    SELECT_ALL_FROM_PEDIDOS();
    for(i = 0; i < quantidadePedidos; i++){
        if(Pedidos[i].codigo == idPedido){
            strcat(data, itoa(Pedidos[i].dia, buffer, 10));
            strcat(data, "/");
            strcat(data, itoa(Pedidos[i].mes, buffer, 10));
            strcat(data, "/");
            strcat(data, itoa(Pedidos[i].ano, buffer, 10));
        }
    }
}
void PEDIDOS_view(){
    int i,j;
    char nomeVendedor[100], nomeProduto[100], cpf[16], data[16] = " ";
    tipoConsulta = 1;
    SELECT_ALL_FROM_PEDIDOS();
    system("cls");
    tituloTabela("  Pedidos");
    printf("\n\n");
    printf("             ###################################################################################################################\n");
    printf("             ##  CODIGO  #  VENDEDOR                              #  VALOR TOTAL      #    CPF CLIENTE   #        DATA        ##\n");
    printf("             ###################################################################################################################\n");
    for(i = 0; i <quantidadePedidos; i++){
        memset(data, '\000', strlen(data) * sizeof(char));
        printf("             ##  %3d     #", Pedidos[i].codigo);
        strcpy(nomeVendedor, getNomeVendedor(Pedidos[i].idVendedor));
        printf("  %s  ", nomeVendedor);
        for(j = strlen(nomeVendedor); j < 36; j++){
            printf(" ");
        }
        printf("#");
        printf("  R$ %10.2f    #", Pedidos[i].valorTotal);
        strcpy(cpf,Pedidos[i].cpfCliente);

        printf("  %s", SERVICOS_formatCpf(cpf));
        for(j = strlen(cpf); j < 16; j++){
            printf(" ");
        }

        getDataPedido(data, Pedidos[i].codigo);
        printf("#   %s", data);
        for(j = strlen(data); j < 17; j++){
            printf(" ");
        }
        printf("##\n");


    }
    printf("             ###################################################################################################################");
    optionViewPedidos();
}
void PEDIDOS_viewPedidosCliente(char* cpfCliente){
    int i,j;
    char nomeVendedor[100], nomeProduto[100], cpf[16], data[16] = " ";
    tipoConsulta = 2;
    strcpy(cpfConsulta, cpfCliente);

    SELECT_ALL_FROM_PEDIDOS();
    system("cls");
    tituloTabela("  Pedidos");
    printf("\n\n");
    printf("             ###################################################################################################################\n");
    printf("             ##  CODIGO  #  VENDEDOR                              #  VALOR TOTAL      #    CPF CLIENTE   #        DATA        ##\n");
    printf("             ###################################################################################################################\n");
    for(i = 0; i <quantidadePedidos; i++){
        if(strcmp(cpfCliente,Pedidos[i].cpfCliente )== 0){
            memset(data, '\000', strlen(data) * sizeof(char));
            printf("             ##  %3d     #", Pedidos[i].codigo);
            strcpy(nomeVendedor, getNomeVendedor(Pedidos[i].idVendedor));
            printf("  %s  ", nomeVendedor);
            for(j = strlen(nomeVendedor); j < 36; j++){
                printf(" ");
            }
            printf("#");
            printf("  R$ %10.2f    #", Pedidos[i].valorTotal);
            strcpy(cpf,Pedidos[i].cpfCliente);

            printf("  %s", SERVICOS_formatCpf(cpf));
            for(j = strlen(cpf); j < 16; j++){
                printf(" ");
            }

            getDataPedido(data, Pedidos[i].codigo);
            printf("#   %s", data);
            for(j = strlen(data); j < 17; j++){
                printf(" ");
            }
            printf("##\n");
        }
    }
    printf("             ###################################################################################################################");
    optionViewPedidos();
}
float PEDIDOS_consultarTotalPorCpf(char* cpf){
    int i;
    double valor = 0;
    SELECT_ALL_FROM_PEDIDOS();
    for(i = 0; i < quantidadePedidos; i++){
        if(strcmp(Pedidos[i].cpfCliente, cpf) == 0){
            valor += Pedidos[i].valorTotal;
        }
    }
    return valor;
}
void PEDIDOS_add(){
    FILE *PEDIDOS;
    SELECT_ALL_FROM_PEDIDOS();
    int result ,codigo, idVendedor, idProduto, quantidade, valido;
    float valor,valorTotalPedido;
    bool desconto = false;
    float valorTotal, valorComprasRealizadas;
    char cpf[20], nomeProduto[100] = " ";
    int dia, mes, ano, carrinho, i,j, itens, op;
    carrinho = 0;
    codigo = PEDIDOS_gerarId();
    idVendedor = getIdLogado();
    itens = 0;
    newDate();
    dia = getDia();
    mes = getMes();
    ano = getAno();
    do{
        printf("             INFORME O CPF DO CLIENTE\n");
        printf("             ");
        scanf("%s", &cpf);
        fflush(stdin);
        valido = SERVICOS_validarCPF(cpf);
    }while(valido == 0);

    CLIENTES_concultarCPF(cpf);
    valorComprasRealizadas = PEDIDOS_consultarTotalPorCpf(cpf);
    if(valorComprasRealizadas > 5000){
        desconto = true;
    }
    system("cls");
    do{
        do{
            PRODUTOS_insert();
            if(itens != 0){
                valorTotalPedido = 0;
                for(j=0; j < itens;j++){
                    valorTotalPedido += Carrinho[j].valor * Carrinho[j].quantidade;
                    PEDIDOS_tabelaCarrinho(j, Carrinho[j].idProduto, Carrinho[j].quantidade, &Carrinho[j].valor);
                }
                printf("                                     ##_______________________________________#________________#___________________##\n");
                printf("                                     ##                                             TOTAL      #  R$ %11.2f   ##\n", valorTotalPedido);
                printf("                                     ################################################################################\n");
            }
            printf("\n                                     INFORME O CÓDIGO DO PRODUTO                                          Carrinho %d: \n", carrinho);
            printf("                                     ");
            receberValorInt(&idProduto);
            do{
                printf("                                     INFORME A QUANTIDADE DO PRODUTO\n");
                printf("                                     ");
                receberValorInt(&quantidade);
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

        valor = PRODUTOS_valor(idProduto);
        printf("                                     VALOR DO PRODUTO SEM DESCONTO: %.2f \n", valor);
        printf("                                     ");
        if(desconto){
            valor = valor - (valor * 0.10);
            printf("                                     VALOR DO PRODUTO COM DESCONTO: %.2f \n", valor);
            printf("                                     ");
        }

        Carrinho[itens].idProduto = idProduto;
        Carrinho[itens].quantidade = quantidade;
        Carrinho[itens].valor = valor;
        PRODUTOS_retirarDoEstoque(quantidade, idProduto);
        valorTotal = valorTotal + (quantidade * valor);
        itens++;
    } while(novoProduto() == 1);
    valorTotalPedido = 0;
    for(j=0; j < itens;j++){
        valorTotalPedido += Carrinho[j].valor * Carrinho[j].quantidade;
        PEDIDOS_tabelaCarrinho(j, Carrinho[j].idProduto, Carrinho[j].quantidade, &Carrinho[j].valor);

    }
    printf("                                     ##_______________________________________#________________#___________________##\n");
    printf("                                     ##                                             TOTAL      #  R$ %11.2f   ##\n", valorTotalPedido);
    printf("                                     ################################################################################\n");
    int msgboxID = MessageBox(NULL, "DESEJA CONFIRMAR O PEDIDO", "PEDIDO", MB_YESNO | MB_DEFBUTTON1);

    switch(msgboxID){
        case IDYES:

            PEDIDOS = fopen("Banco/Pedido.csv", "a");
            fprintf(PEDIDOS,
                    "{ (codigo): <%d> ; (idVendedor): <%d> ; (valorTotal): <%.2f> ; (cpfCliente): <%s> ; (dia): <%d> ; (mes): <%d> ; (ano): <%d> ;}\n",
                    codigo, idVendedor, valorTotal, cpf , dia , mes , ano);

            fclose(PEDIDOS);
            for(i=0; i < itens;i++){
                ITENS_PEDIDO_add(codigo , Carrinho[i].idProduto ,Carrinho[i].valor , Carrinho[i].quantidade);
            }
            MessageBox(0, "PEDIDO CADASTRADO COM SUCESSO!\n", "PEDIDO",0);
            PEDIDOS_view();
        break;
        case IDNO:
            for(i=0; i < itens;i++){
                PRODUTOS_retornarDoEstoque(Carrinho[i].quantidade, Carrinho[i].idProduto);
            }

            PEDIDOS_view();
        break;
    }

}
int PEDIDOS_gerarId(){
    int i, codigo;
    int maior = 0;
    for(i = 0; i < quantidadePedidos; i++){
        if(Pedidos[i].codigo > maior){
            maior = Pedidos[i].codigo;
        }
    }
    codigo = maior + 1;
    return codigo;

}
int PEDIDOS_excluirPedido(int idPedido){
    int excluido = 0, i;
    FILE *PEDIDOS;
    SELECT_ALL_FROM_PEDIDOS();
    PEDIDOS = fopen("Banco/Pedido.csv", "w");
        for(i = 0; i < quantidadePedidos; i++){
            if(Pedidos[i].codigo == idPedido){
                excluido = 1;
            } else {
                fprintf(PEDIDOS,
                    "{ (codigo): <%d> ; (idVendedor): <%d> ; (valorTotal): <%.2f> ; (cpfCliente): <%s> ; (dia): <%d> ; (mes): <%d> ; (ano): <%d> ;}\n",
                    Pedidos[i].codigo, Pedidos[i].idVendedor, Pedidos[i].valorTotal, Pedidos[i].cpfCliente , Pedidos[i].dia , Pedidos[i].mes , Pedidos[i].ano);

            }

        }
        fclose(PEDIDOS);
        return excluido;
}
int novoProduto(){
    int opcaoValida;
    int msgboxID = MessageBox(NULL, "DESEJA ADICIONAR UM NOVO PRODUTO", "ADICIONAR PRODUTO", MB_YESNO | MB_DEFBUTTON1);
    switch(msgboxID){
        case IDYES:
            opcaoValida = 1;
        break;
        case IDNO:
            opcaoValida = 0;
        break;
    }
    return opcaoValida;

}
void PEDIDOS_tabelaCarrinho(int j,int idProduto, int qtd, float *valor){
    int i;
    char nome[100] = " ";

    if(j == 0){
        printf("\n");
        printf("                                     ################################################################################\n");
        printf("                                     ##  PRODUTO                              #   QUANTIDADE   #  VALOR            ##\n");
        printf("                                     ################################################################################\n");
    }
    strcpy(nome, getNomeProduto(idProduto));
    printf("                                     ##  %s", nome);
    for(i = strlen(nome); i < 37; i++){
        printf(" ");
    }
    printf("#");
    printf("   %3d          #",qtd);
    printf("  R$ %11.2f   ##\n",(*valor));

}
int PEDIDOS_verificarPedidoComCPF(int idPedido, char* cpf){
    int i;
    SELECT_ALL_FROM_PEDIDOS();
    for(i = 0 ; i < quantidadePedidos; i++){
        if(idPedido == Pedidos[i].codigo && strcmp(cpf, Pedidos[i].cpfCliente)== 0){
            return 1;
        }
    }
    return 0;
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
    printf("\n              ");
    receberValorInt(&op);
    switch(op){
        case 1:
            if(tipoConsulta == 1){
                menu();
            } else {
                CLIENTES_view();
            }

        break;
        case 2:
            PEDIDOS_add();
        break;
        case 3:
            printf("             INFORME O NÚMERO DO PEDIDO\n");
            printf("             ");
            receberValorInt(&pedido);
            if(tipoConsulta == 2){
                while(PEDIDOS_verificarPedidoComCPF(pedido, cpfConsulta) == 0){
                    MessageBox(0,"ERRO!\n", "MEUS PEDIDOS",0);
                    printf("             INFORME O NÚMERO DO PEDIDO\n");
                    printf("             ");
                    receberValorInt(&pedido);
                }

            }
            ITENS_PEDIDO_view(pedido, tipoConsulta);
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
        printf("\n              ");
        receberValorInt(&op);
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
        printf("\n              ");
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

#endif // PEDIDOS_H_INCLUDED
