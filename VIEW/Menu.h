#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED


void menu(){
    int op;
    system("cls");
    int res;
    if(strcmp(getPerfilLogado(), "Gerente") == 0){

        verificarEstoque();

        subMenu("Produtos",1);
        subMenu("Pedidos",2);
        subMenu("Clientes",3);
        subMenu("Sair",0);

        printf("\n                                 SELECIONE A OPÇÃO\n");
        printf("                                 ");
        receberValorInt(&op);

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
            case 3:

            break;


        }

    } else if(strcmp(getPerfilLogado(), "Vendedor") == 0){

        subMenu("Produtos",1);
        subMenu("Pedidos",2);
        subMenu("Clientes",3);
        subMenu("Sair",0);

        printf("\n                                 SELECIONE A OPÇÃO\n");
        printf("                                 ");
        receberValorInt(&op);
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

        subMenu("Produtos",1);
        subMenu("Sair",0);

        printf("\n                                 SELECIONE A OPÇÃO\n");
        printf("                                 ");
        receberValorInt(&op);
        switch(op){
            case 0:
                USUARIO_LOGADO_sair();
            break;
            case 1:
                PRODUTOS_view();
            break;

        }

    } else if(strcmp(getPerfilLogado(), "Administrador") == 0){
        subMenu("USUÁRIOS",1);
        subMenu("SAIR",0);
        printf("\n                                 SELECIONE A OPÇÃO\n");
        printf("                                 ");
        receberValorInt(&op);

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

subMenu(char titulo[], int opcao){
    int k,j,i;
    for(j = 1; j < 7; j++){
        espaco();
        espaco();
        espaco();
        espaco();
        numberOption(opcao, j);
        separador(j);
        for(i=0; i < strlen(titulo);i++ ){

            switch(tolower(titulo[i])){
                case 'a':
                    letraA(j);
                break;
                case 'b':
                    letraB(j);
                break;
                case 'c':
                    letraC(j);
                break;
                case 'd':
                    letraD(j);
                break;
                case 'e':
                    letraE(j);
                break;
                case 'f':
                    letraF(j);
                break;
                case 'g':
                    letraG(j);
                break;
                case 'h':
                    letraH(j);
                break;
                case 'i':
                    letraI(j);
                break;
                case 'j':
                    letraJ(j);
                break;
                case 'k':
                    letraK(j);
                break;
                case 'l':
                    letraL(j);
                break;
                case 'm':
                    letraM(j);
                break;
                case 'n':
                    letraN(j);
                break;
                case 'o':
                    letraO(j);
                break;
                case 'p':
                    letraP(j);
                break;
                case 'q':
                    letraQ(j);
                break;
                case 'r':
                    letraR(j);
                break;
                case 's':
                    letraS(j);
                break;
                case 't':
                    letraT(j);
                break;
                case 'u':
                    letraU(j);
                break;
                case 'v':
                    letraV(j);
                break;
                case 'x':
                    letraX(j);
                break;
                case 'w':
                    letraW(j);
                break;
                case 'y':
                    letraY(j);
                break;
                case 'z':
                    letraZ(j);
                break;
            }
        }

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
tituloTabela(char titulo[]){
    int k,j,i;
    for(j = 1; j < 7; j++){
        espaco();
        espaco();
        espaco();
        espaco();
        for(i=0; i < strlen(titulo);i++ ){

            switch(tolower(titulo[i])){
                case 'a':
                    letraA(j);
                break;
                case 'b':
                    letraB(j);
                break;
                case 'c':
                    letraC(j);
                break;
                case 'd':
                    letraD(j);
                break;
                case 'e':
                    letraE(j);
                break;
                case 'f':
                    letraF(j);
                break;
                case 'g':
                    letraG(j);
                break;
                case 'h':
                    letraH(j);
                break;
                case 'i':
                    letraI(j);
                break;
                case 'j':
                    letraJ(j);
                break;
                case 'k':
                    letraK(j);
                break;
                case 'l':
                    letraL(j);
                break;
                case 'm':
                    letraM(j);
                break;
                case 'n':
                    letraN(j);
                break;
                case 'o':
                    letraO(j);
                break;
                case 'p':
                    letraP(j);
                break;
                case 'q':
                    letraQ(j);
                break;
                case 'r':
                    letraR(j);
                break;
                case 's':
                    letraS(j);
                break;
                case 't':
                    letraT(j);
                break;
                case 'u':
                    letraU(j);
                break;
                case 'v':
                    letraV(j);
                break;
                case 'x':
                    letraX(j);
                break;
                case 'w':
                    letraW(j);
                break;
                case 'y':
                    letraY(j);
                break;
                case 'z':
                    letraZ(j);
                break;
                case ' ':
                    espaco();
                break;
            }
        }

        printf("\n");
    }
}


#endif // MENU_H_INCLUDED
