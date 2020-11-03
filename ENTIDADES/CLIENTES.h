#ifndef CLIENTES_H_INCLUDED
#define CLIENTES_H_INCLUDED

struct CLIENTES{
    char cpf[20];
    char nome[155];
};
struct CLIENTES Clientes[1000];

struct RANKING{
    char cpf[20];
    float valoTotalCompras;
};
struct RANKING Ranking[1000];


int quantidadeClientes;

void SELECT_ALL_FROM_CLIENTES(){
    FILE *CLIENTES;
    int i,j, n,indice = 0, op;
    bool dado = false, var  = false, fim;
    char variavel[15];
    char dados[1000];


    CLIENTES = fopen("Banco/Clientes.csv", "r");
    while((fgets(dados, sizeof(dados), CLIENTES))!=NULL){
        fim = false;
        memset(Clientes[indice].cpf, '\000', strlen(Clientes[indice].cpf) * sizeof(char));
        memset(Clientes[indice].nome, '\000', strlen(Clientes[indice].nome) * sizeof(char));
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
                if(strcmp(variavel, "cpf")     == 0){ Clientes[indice].cpf[n] = dados[i];}
                else if(strcmp(variavel, "nome") == 0){ Clientes[indice].nome[n] = dados[i]; }
                n++;
            }
        }
        indice++;

    }
    quantidadeClientes = indice;
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
    printf("             DIGITE O NOME DO CLIENTE: \n");
    printf("             ");
    gets(nome);
    fflush(stdin);


    CLIENTES = fopen("Banco/Clientes.csv", "a");

        fprintf(CLIENTES,"{ (cpf): <%s> ; (nome): <%s> ; }\n", cpf, nome);

    fclose(CLIENTES);
}

#endif // CLIENTES_H_INCLUDED
