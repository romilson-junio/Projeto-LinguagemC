#ifndef CLIENTES_H_INCLUDED
#define CLIENTES_H_INCLUDED

struct CLIENTES{
    char cpf[12];
    char* nome[255];
};
struct CLIENTES Clientes[1000];

struct RANKING{
    char cpf[12];
    float valoTotalCompras;
};
struct RANKING Ranking[1000];


int quantidadeClientes;

void SELECT_ALL_FROM_CLIENTES(){
    FILE *CLIENTES;
    int i;
    char cpf[12], nome[255];
    CLIENTES = fopen("Banco/Clientes.csv", "r");
        i = 0;
        while(fscanf(CLIENTES,"%s ; %s ;\n", &cpf, &nome) != EOF){
                strcpy(Clientes[i].cpf, cpf);
                strcpy(Clientes[i].nome, nome);

                i++;
        }
        quantidadeClientes = i;
    fclose(CLIENTES);
}

void CLIENTES_concultarCPF(char *cpf){
    int i;
    SELECT_ALL_FROM_CLIENTES();
    for(i = 0; i < quantidadeClientes; i++){
        if(strcmp(cpf, Clientes[i].cpf) == 0){
            return 1;
        }
    }
    CLIENTES_cadastrarCliente(cpf);
    return 1;
}

void getNomeCliente(char* cliente, char* cpf){
    int i;
    SELECT_ALL_FROM_CLIENTES();
    for(i = 0; i < quantidadeClientes; i++){
        if(strcmp(cpf, Clientes[i].cpf) == 0){
            strcpy(cliente, Clientes[i].nome);
        }
    }
}
/*
    Ideia inicial era gerar Ranking mais foi descontinuada por estar fora do escopo da aplicação!
*/
/*void CLIENTES_gerarRankingClientes(char* cpf){
    int i,op;
    SELECT_ALL_FROM_CLIENTES();

    for(i = 0; i < quantidadeClientes; i++){
        strcpy(Ranking[i].cpf, Clientes[i].cpf);
        Ranking[i].valoTotalCompras = PEDIDOS_consultarTotalDosPedidos(Ranking[i].cpf);
    }

    for(i = 0; i < quantidadeClientes; i++){
        if(Ranking[i].valoTotalCompras < Ranking[i+1].valoTotalCompras){
            strcpy(cpfAulixar, Ranking[i].cpf);
            valorAuxiliar = Ranking[i].valoTotalCompras;
            strcpy(Ranking[i+1].cpf, Ranking[i].cpf);
            Ranking[i+1].valoTotalCompras = Ranking[i].valoTotalCompras;
        }
    }

    printf("CPF             VALOR TOTAL");
    printf("%s          %.2f\n", Ranking[i].cpf,Ranking[i].valoTotalCompras);

}
*/
void CLIENTES_cadastrarCliente(char *cpf){
    FILE *CLIENTES;
    char nome[255];

    fflush(stdin);
    printf("DIGITE O NOME DO CLIENTE: \n");
    gets(nome);
    fflush(stdin);


    CLIENTES = fopen("Banco/Clientes.csv", "a");

        fprintf(CLIENTES,"%s ; %s ;\n", cpf, nome);

    fclose(CLIENTES);
}

#endif // CLIENTES_H_INCLUDED
