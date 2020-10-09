#ifndef USUARIOS_H_INCLUDED
#define USUARIOS_H_INCLUDED

int quantidadeUsuarios;

struct Usuarios{
    int id;
    char nome[100], usuario[50], perfil[50];
};

struct Usuarios BD_Usuarios[100];

void SELECT_ALL_FROM_USUARIOS(){
    int idFile,i;
    char nomeFile[100], usuarioFile[50], senhaFile[20], perfilFile[50];
    FILE *USUARIOS;
    USUARIOS = fopen("Banco/Usuario.csv", "r");
    i = 0;
    while(fscanf(USUARIOS,"%d ; %s ; %s ; %s ; %s ;\n", &idFile, &nomeFile, &usuarioFile ,&senhaFile, &perfilFile) != EOF){
        strcpy(BD_Usuarios[i].usuario, usuarioFile);
        strcpy(BD_Usuarios[i].nome, nomeFile);
        strcpy(BD_Usuarios[i].perfil, perfilFile);
        BD_Usuarios[i].id = idFile;
        i++;
    }
    quantidadeUsuarios = i;
    fclose(USUARIOS);

}

void USUARIOS_novoUsuario(){
    SELECT_ALL_FROM_USUARIOS();
    FILE *USUARIOS;
    int i, id;
    char nome[100], usuario[50], senha[20], perfil[50];
    id = quantidadeUsuarios+1;
    fflush(stdin);
    printf("INFORME O USUARIO: \n");
    gets(usuario);
    fflush(stdin);

    for(i = 0; i < quantidadeUsuarios; i++){
        if(strcmp(usuario,BD_Usuarios[i].usuario) == 0){
            MessageBox(0,"USUARIO JÁ CADASTRADO!\n", "CADASTRO DE USUÁRIOS",0);
            return 0;
        }
    }

    fflush(stdin);
    printf("INFORME O NOME: \n");
    gets(nome);
    fflush(stdin);

    fflush(stdin);
    printf("INFORME A SENHA: \n");
    gets(senha);
    fflush(stdin);

    fflush(stdin);
    printf("INFORME O PERFIL: \n");
    gets(perfil);
    fflush(stdin);

    SERVICOS_criptografar(senha);

    USUARIOS = fopen("Banco/Usuario.csv", "a");
        fprintf(USUARIOS,"%d ; %s ; %s ; %s ; %s ;\n", id, nome, usuario ,senha , perfil);
        MessageBox(0,"USUARIO CADASTRADO COM SUCESSO!\n", "CADASTRO DE USUÁRIOS",0);
    fclose(USUARIOS);

}

char* getNomeVendedor(int id){
    int i;
    SELECT_ALL_FROM_USUARIOS();
    for(i = 0; i < quantidadeUsuarios; i++){
        if(id == BD_Usuarios[i].id){
            return BD_Usuarios[i].nome;
        }
    }
}

#endif // USUARIOS_H_INCLUDED
