#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED


void menu(){
    int op;
    system("cls");
    if(strcmp(getPerfilLogado(), "Gerente") == 0){

        verificarEstoque();

        subMenuProdutos(1);
        subMenuPedidos(2);
        subMenuClientes(3);
        subMenuSair(0);

        scanf("%d", &op);

        switch(op){
            case 0:
                USUARIO_LOGADO_sair();
            break;
            case 1:
                PRODUTOS_view();
            break;
            case 2:
                PEDIDOS_view();
            break;

        }

    } else if(strcmp(getPerfilLogado(), "Vendedor") == 0){

        subMenuProdutos(1);
        subMenuPedidos(2);
        subMenuClientes(3);
        subMenuSair(0);

        scanf("%d", &op);
        switch(op){
            case 0:
                USUARIO_LOGADO_sair();
            break;
            case 1:
                PRODUTOS_view();
            break;
            case 2:
                PEDIDOS_view();
            break;

        }
    }else if(strcmp(getPerfilLogado(), "Estoquista") == 0){

        verificarEstoque();

        subMenuProdutos(1);
        subMenuSair(0);

        scanf("%d", &op);
        switch(op){
            case 0:
                USUARIO_LOGADO_sair();
            break;
            case 1:
                PRODUTOS_view();
            break;

        }

    } else if(strcmp(getPerfilLogado(), "Administrador") == 0){

        subMenuUsuarios(1);
        subMenuSair(0);

        scanf("%d", &op);
        switch(op){
            case 0:
                USUARIO_LOGADO_sair();
            break;
            case 1:
                USUARIOS_novoUsuario();
            break;

        }
    }
}

void verificarEstoque(){
    int op;
    if(PRODUTOS_verificarEstoque() > 0){
        int msgboxID = MessageBox(NULL, "VISUALIZAR", "PRODUTOS COM BAIXO ESTOQUE", MB_YESNO | MB_DEFBUTTON1);
            switch(msgboxID){
                case IDYES:
                    op = 1;
                break;
                case IDNO:
                    op = 2;
                break;
            }
        }
        if(op == 1){
            PRODUTOS_baixoEstoque();
        }
}
void subMenuPedidos(opcao){
    int k,j;
    for(j = 1; j < 7; j++){
        espaco();
        espaco();
        espaco();
        espaco();
        numberOption(opcao, j);
        separador(j);
        letraP(j);
        letraE(j);
        letraD(j);
        letraI(j);
        letraD(j);
        letraO(j);
        letraS(j);
        printf("\n");
    }
}
void subMenuEncerrar(opcao){
    int j;
    espaco();
    espaco();
    espaco();
    espaco();
    numberOption(opcao, j);
    separador(j);
    letraE(j);
    letraN(j);
    letraC(j);
    letraE(j);
    letraR(j);
    letraR(j);
    letraA(j);
    letraR(j);
    printf("\n");
}

subMenuProdutos(opcao){
    int k,j;
    for(j = 1; j < 7; j++){
        espaco();
        espaco();
        espaco();
        espaco();
        numberOption(opcao, j);
        separador(j);
        letraP(j);
        letraR(j);
        letraO(j);
        letraD(j);
        letraU(j);
        letraT(j);
        letraO(j);
        letraS(j);
        printf("\n");
    }
}
subMenuClientes(opcao){
    int k,j;
    for(j = 1; j < 7; j++){
        espaco();
        espaco();
        espaco();
        espaco();
        numberOption(opcao, j);
        separador(j);
        letraC(j);
        letraL(j);
        letraI(j);
        letraE(j);
        letraN(j);
        letraT(j);
        letraE(j);
        letraS(j);
        printf("\n");
    }
}
subMenuUsuarios(opcao){
    int k,j;
    for(j = 1; j < 7; j++){
        espaco();
        espaco();
        espaco();
        espaco();
        numberOption(opcao, j);
        separador(j);
        letraU(j);
        letraS(j);
        letraU(j);
        letraA(j);
        letraR(j);
        letraI(j);
        letraO(j);
        letraS(j);
        printf("\n");
    }
}
subMenuSair(opcao){
    int k,j;
    for(j = 1; j < 7; j++){
        espaco();
        espaco();
        espaco();
        espaco();
        numberOption(opcao, j);
        separador(j);
        letraS(j);
        letraA(j);
        letraI(j);
        letraR(j);
        printf("\n");
    }
}
void numberOption(opcao, j){
    switch(opcao){
        case 1:
            numero1(j);
        break;
        case 2:
            numero2(j);
        break;
        case 3:
            numero3(j);
        break;
        case 4:
            numero4(j);
        break;
        case 5:
            numero5(j);
        break;
        case 6:
            numero6(j);
        break;
        case 7:
            numero7(j);
        break;
        case 8:
            numero8(j);
        break;
        case 9:
            numero9(j);
        break;
        case 0:
            numero0(j);
        break;
    }
}

#endif // MENU_H_INCLUDED
