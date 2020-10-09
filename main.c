#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <locale.h>
#include <windows.h>
#include <ctype.h>

#include "ENTIDADES/USUARIO_LOGADO.h"
#include "ENTIDADES/USUARIOS.h"
#include "ENTIDADES/PRODUTOS.h"
#include "ENTIDADES/PEDIDOS.h"
#include "ENTIDADES/ITENSPEDIDO.h"
#include "ENTIDADES/CLIENTES.h"
#include "VIEW/Menu.h"
#include "Servicos/Servicos.h"
#include "Servicos/Alfabeto.h"

int main(){

    int i = 1;
    setlocale(LC_ALL, "Portuguese");
    do{
        if(!isLogado()) {
            USUARIO_LOGADO_login();
        }
        menu();
    } while(i < 3);
    return 0;
}

