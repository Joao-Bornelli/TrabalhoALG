/*
    EQUIPE: JOÃO LUÍS CORRÊA BORNELLI
            RAFAELA FERNANDA DA SILVA FERREIRA
            FRANTOR CESAR FAGUNDES DE OLIVEIRA JUNIOR
            LEANDRO FELIPE MOREIRA
*/


#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>


//Definição de funções
int menu();
int adiciona();
int alterar();
int excluir_contato();
int lista();
void cria_abre();
int conta_linhas();
int aloca(int qnt);
int ordena();
int fecha_arquivo();
char valida_nome(char* escolha);
char valida_email(char* escolha);
int limpa_email(int opcao);
void libera_mem();
int *busca(char* escolha, int opcao, int* tamanho);


//Definição de variáveis globais
int linhas;
FILE *arquivo;
FILE *arquivo_aux;
int *Ids;
char **nomes;
char **emails;
char **telefones;

//MAIN
int main()
{
    int opcao = 1;
    cria_abre();
    aloca(0);
    conta_linhas();
    aloca(linhas);
    fecha_arquivo();

    while(opcao != 0)
    {
        opcao = menu();
        switch (opcao)
        {
        case 0:
            libera_mem();
            fecha_arquivo();
            return 0;
        case 1:
            adiciona();
            break;
        case 2:
            alterar();
            break;
        case 3:
            excluir_contato();
            break;
        case 4:
            lista();
            break;
        }
    }
}

//Cria o arquivo caso não exista ou abre
void cria_abre()
{
    arquivo = fopen("Dados.txt", "a+");
    if (arquivo == NULL)
    {
        printf("\n\nerro na criação\n");
    }
}

//Conta a quantidade de linhas dentro do arquivo
int conta_linhas()
{   
    int caractere = 0;
    linhas = 0;
    do 
    {
        caractere = fgetc(arquivo);
        if(caractere == '\n') {
                linhas++;
        }
    }while(caractere != EOF);
}


//Copia os contatos para um array dinamicamente
int aloca(int qnt)
{
    int i = 0;

    if(qnt > 0)
    {
        Ids = realloc(Ids,sizeof(int)*qnt);
        nomes = realloc(nomes,sizeof(int)*qnt);
        emails = realloc(emails,sizeof(int)*qnt);
        telefones = realloc(telefones,sizeof(int)*qnt);
        
        for(i = 0 ; i < qnt; i++)
        {
            nomes[i]=  malloc(sizeof(char)*50);
            emails[i]= malloc(sizeof(char)*50);
            telefones[i]= malloc(sizeof(char)*50);
        }

        i = 0;
        if(linhas > 0)
        {
            fseek(arquivo,0,SEEK_SET);
            while(!feof(arquivo))
            {
                fscanf(arquivo,"%d %s %s %s", &Ids[i], nomes[i], emails[i], telefones[i]);    
                i++;      
            }
        }
        ordena();
    }
    else
    {
        Ids = malloc(sizeof(int)*1);
        nomes = malloc(sizeof(int)*1);
        emails = malloc(sizeof(int)*1);
        telefones = malloc(sizeof(int)*1);

        nomes[0] = (char*)malloc(sizeof(char)*50);
        emails[0] = (char*)malloc(sizeof(char)*50);
        telefones[0] = (char*)malloc(sizeof(char)*12);
    }
}


//Ordena os contatos pelo ID de forma crescente
int ordena()
{
    int i, j, auxIds;
    char auxNome[50];
    char auxEmail[50];
    char auxTel[20];

    for(j = 0; j < linhas; j++)
    {
        for(i = 0; i < (linhas - 1); i++)
        {
            if(Ids[i] > Ids[i+1])
            {
                auxIds = Ids[i];
                Ids[i] = Ids[i+1];
                Ids[i+1] = auxIds;

                strcpy(auxNome,nomes[i]);
                strcpy(nomes[i],nomes[i+1]);
                strcpy(nomes[i+1],auxNome);
                
                strcpy(auxEmail,emails[i]);
                strcpy(emails[i],emails[i+1]);
                strcpy(emails[i+1],auxEmail);
                
                strcpy(auxTel,telefones[i]);
                strcpy(telefones[i],telefones[i+1]);
                strcpy(telefones[i+1],auxTel);
            }
        }
    }
}


//Função para adicionar um novo contato
int adiciona()
{   
    int i = 0;
    int x = 0;
    int index = 0;
    int aux = 0;
    char auxNome[50];
    char auxEmail[50];

    printf("-----Adiciona-----\n");

    cria_abre();
    aloca(0);
    conta_linhas();
    aloca(linhas);

    if(linhas > 0)
    {   
        aloca(linhas + 1);

        for(i = 1; i < linhas; i++)
        {
            if(Ids[i] > (Ids[i-1]+1))
            {
                x = i;
                break;
            }
        }
        if(x > 0)
        {
            Ids[x] = Ids[x-1] + 1;
            printf("Nome:\n");
            __fpurge(stdin);
            fflush(stdin);
            gets(auxNome);
            *auxNome = valida_nome(auxNome);
            strcpy(nomes[x], auxNome);
                        
            printf("E-mail:\n");
            __fpurge(stdin);
            fflush(stdin);
            gets(auxEmail);
            *auxEmail = valida_email(auxEmail);
            strcpy(emails[x], auxEmail);

            printf("Telefone:\n");
            __fpurge(stdin);
            fflush(stdin);
            gets(*telefones);
            strcpy(telefones[x], *telefones);

            fprintf(arquivo,"%d ", Ids[x]);
            fprintf(arquivo,"%s ", nomes[x]);
            fprintf(arquivo,"%s ", emails[x]);
            fprintf(arquivo,"%s\n", telefones[x]);
        }
        else
        {
            index = linhas;
            Ids[index]= index+1;
            printf("Nome:\n");
            __fpurge(stdin);
            fflush(stdin);
            gets(auxNome);
            printf("%s\n", auxNome);
            *auxNome = valida_nome(auxNome);
            strcpy(nomes[index],auxNome);

            printf("E-mail:\n");
            __fpurge(stdin);
            fflush(stdin);
            gets(auxEmail);
            *auxEmail = valida_email(auxEmail);
            strcpy(emails[index], auxEmail);

            printf("Telefone:\n");
            __fpurge(stdin);
            fflush(stdin);
            gets(*telefones);
            strcpy(telefones[index], *telefones);

            fprintf(arquivo,"%d ", Ids[index]);
            fprintf(arquivo,"%s ", nomes[index]);
            fprintf(arquivo,"%s ", emails[index]);
            fprintf(arquivo,"%s\n", telefones[index]);
        }
    }
    else
    {       
        Ids[0] = 1;
        printf("Nome:\n");
        __fpurge(stdin);
        fflush(stdin);
        gets(auxNome);
        *auxNome = valida_nome(auxNome);
        strcpy(nomes[0],auxNome);
                        
        printf("E-mail:\n");
        __fpurge(stdin);
        fflush(stdin);
        gets(auxEmail);
        *auxEmail = valida_email(auxEmail);
        strcpy(emails[0], auxEmail);

        printf("Telefone:\n");
        __fpurge(stdin);
        fflush(stdin);
        gets(*telefones);
        strcpy(telefones[0],*telefones);        

        fprintf(arquivo,"%d ", Ids[0]);
        fprintf(arquivo,"%s ", nomes[0]);
        fprintf(arquivo,"%s ", emails[0]);
        fprintf(arquivo,"%s\n", telefones[0]);
    }
    libera_mem();
    fecha_arquivo();
    printf("Contato adicionado com sucesso.\n");
}

//Função para fechar o arquivo
int fecha_arquivo()
{
    fflush(stdin);
    fclose(arquivo);
    fclose(arquivo_aux);
}

//Menu principal
int menu ()
{
    int escolha;
    printf("\n                    Agenda\n");
    printf(" 1 - Adicionar contato\n");
    printf(" 2 - Alterar contato\n");
    printf(" 3 - Excluir contato\n");
    printf(" 4 - Exibir lista de contatos\n");
    printf(" 0 - Sair\n");
    printf("\nInsira o número da função desejada:\n");
    __fpurge(stdin);
    fflush(stdin);
    scanf("%d", &escolha);

    while(escolha < 0 || escolha > 5){
        printf("Número inválido, insira uma opção válida ou 0 para encerrar o programa.\n");
        __fpurge(stdin);
        fflush(stdin);
        scanf("%d", &escolha); 
    }
    return (escolha);
}


//Função para alterar alguma informação de um contato
int alterar()
{
    cria_abre();
    aloca(0);
    conta_linhas();
    aloca(linhas);
    int *resultado;
    char escolha[50],nova_info[50], c;
    int i, tamanho, j, info;
    tamanho = 0;

    printf("\nQual contato que deseja alterar?\nDigite:\n0- Voltar\n1- pesquisar por nome\n2- pesquisar por email\n3- pesquisar por telefone\n");
    __fpurge(stdin);
    fflush(stdin);
    scanf("%d", &i);
    switch (i)
    {
    case 0:
        return 0;
        break;
    case 1:
        printf("Insira o nome:\n");
        __fpurge(stdin);
        fflush(stdin);
        gets(escolha);
        *escolha = valida_nome(escolha); 
        printf("escolha: %s\n", escolha);
        resultado = busca(escolha, i, &tamanho);   
        break;

    case 2:
        printf("Insira o email:\n");
        __fpurge(stdin);
        fflush(stdin);
        gets(escolha);
        *escolha = valida_email(escolha);
        printf("escolha: %s\n", escolha);
        resultado = busca(escolha, i, &tamanho);
        break;

    case 3:
        printf("Insira o telefone:\n");
        __fpurge(stdin);
        fflush(stdin);
        gets(escolha);
        resultado = busca(escolha, i, &tamanho);
        break;
    }
    fecha_arquivo();
    if (tamanho == 1)
    {
        *escolha = resultado[0];
        for(i = 0; i < linhas; i++)
        {
            if(Ids[i] == *escolha)
            {
                printf("contato que sera alterado: %d %s %s %s\n", Ids[i], nomes[i], emails[i], telefones[i]);
                j = i;
                break;
            } 
        }
        printf("Qual informcao voce deseja alterar?\n");
        printf("0- Voltar\n1- Nome\n2- Email\n3- Telefone\n");
        fflush(stdin);
        scanf("%d",&info);
        while ((info < 0)||(info > 3))
        {
            printf("Opcao invalida, insira novamente\n");
            __fpurge(stdin);
            fflush(stdin);
            scanf("%d",&info);
        }
        switch (info)
        {
        case 0:
            break;
        case 1:
            printf("Insira o novo nome:\n");
            __fpurge(stdin);
            fflush(stdin);
            gets(nova_info);
            valida_nome(nova_info);
            strcpy(nomes[j], nova_info);
            break;
        case 2:
            printf("Insira o novo email:\n");
            __fpurge(stdin);
            fflush(stdin);
            gets(nova_info);
            valida_email(nova_info);
            strcpy(emails[j], nova_info);
            break;
        case 3:
            printf("Insira o novo telefone:\n");
            __fpurge(stdin);
            fflush(stdin);
            gets(nova_info);
            strcpy(telefones[j], nova_info);
            break;
        }
        arquivo = fopen("Dados.txt", "w+");
        if (arquivo == NULL)
        {
            printf("\n\nerro na criacao\n");
        }
        else
        {
            for(i = 0; i < linhas; i++)
            {                        
                fprintf(arquivo,"%d ", Ids[i]);
                        
                fprintf(arquivo,"%s ", nomes[i]);
                            
                fprintf(arquivo,"%s ", emails[i]);
                        
                fprintf(arquivo,"%s\n", telefones[i]);
            }
            fecha_arquivo();
            printf("contato alterado\n");                
        }
    }
    else if(tamanho > 1)
    {   
        printf("Foi encontrado mais de um contato com a mesma informacao.\n");
        for(i = 0; i < tamanho; i ++)
        {
            printf(" ID:%d - %s - %s - %s\n", Ids[resultado[i]-1], nomes[resultado[i]-1], emails[resultado[i]-1], telefones[resultado[i]-1]);
        }
        printf("Insira o ID do contato que deseja excluir?\n");
        __fpurge(stdin);
        fflush(stdin);
        scanf("%d",&escolha);
        
        for(i = 0; i < tamanho; i ++)
        {
            if(*escolha == Ids[resultado[i]-1])
            {
                j = 1;
            }
        }
        while(j != 1)
        {
            printf("Valor invalido, insira novamente:\n");
            __fpurge(stdin);
            fflush(stdin);
            scanf("%d",&escolha);
            for(i = 0; i < tamanho; i ++)
            {
                if(*escolha == Ids[resultado[i]-1])
                {
                    j = 1;
                }
            }
        }
        for(i = 0; i < linhas; i++)
        {
            if(Ids[i] == *escolha)
            {
                printf("contato que sera alterado: %d %s %s %s\n", Ids[i], nomes[i], emails[i], telefones[i]);
                j = i;
                break;
            } 
        }
        printf("Qual informcao voce deseja alterar?\n");
        printf("0- Voltar\n1- Nome\n2- Email\n3- Telefone\n");
        __fpurge(stdin);
        fflush(stdin);
        scanf("%d",&info);
        switch (info)
        {
        case 0:

            break;
        case 1:
            printf("Insira o novo nome:\n");
            __fpurge(stdin);
            fflush(stdin);
            gets(nova_info);
            valida_nome(nova_info);
            strcpy(nomes[j], nova_info);
            break;
        case 2:
            printf("Insira o novo email:\n");
            __fpurge(stdin);
            fflush(stdin);
            gets(nova_info);
            valida_email(nova_info);
            strcpy(emails[j], nova_info);
            break;
        case 3:
            printf("Insira o novo telefone:\n");
            __fpurge(stdin);
            fflush(stdin);
            gets(nova_info);
            strcpy(telefones[j], nova_info);
            break;
        }
        arquivo = fopen("Dados.txt", "w+");
        if (arquivo == NULL)
        {
            printf("\n\nerro na criacao\n");
        }
        else
        {
            for(i = 0; i < linhas; i++)
            {                        
                    
                fprintf(arquivo,"%d ", Ids[i]);
                        
                fprintf(arquivo,"%s ", nomes[i]);
                            
                fprintf(arquivo,"%s ", emails[i]);
                        
                fprintf(arquivo,"%s\n", telefones[i]);
            }
        }
        fecha_arquivo();   
        printf("contato alterado\n");              
    }   
    libera_mem();
    fecha_arquivo();
}


//Função para printar todos os contatos cadastrados
int lista()
{
    cria_abre();
    aloca(0);
    conta_linhas();
    aloca(linhas);
    if(linhas > 0)
    {
        int i;
        printf("Lista de contatos: \n");
        for(i = 0 ; i < linhas; i++)
        {
            printf("%d %s %s %s\n", Ids[i], nomes[i], emails[i], telefones[i]);
        }
        printf("\n");
        fecha_arquivo();
    }
    else
    {
        printf("\nNão existe nenhum contato cadastrado!\n");
    }
    libera_mem();
    fecha_arquivo();
}


//Função para buscar um contato no array
int *busca(char* escolha, int opcao, int* tamanho)
{
    int *vet_Ids;
    int i;
    int j = 0;

    switch (opcao)
    {
    case 1:
        for(i = 0; i < linhas; i++)
        {
            if(strcmp(escolha , nomes[i]) == 0)
            {    
                j++;
            }
        }
        if(j > 0)
        {
            vet_Ids =(int*) malloc(j);
            j = 0;
            for(i = 0; i < linhas; i++)
            {
                if(strcmp(escolha , nomes[i]) == 0)
                {    
                    vet_Ids[j] = Ids[i];
                    j++;
                }
            }
        }
        break;
    case 2:
        for(i = 0; i < linhas; i++)
        {
            if(strcmp(escolha , emails[i]) == 0)
            {    
                j++;
            }
        }
        if(j > 0)
        {
            vet_Ids = (int*) malloc(j);
            j = 0;
            for(i = 0; i < linhas; i++)
            {
                if(strcmp(escolha , emails[i]) == 0)
                {    
                    vet_Ids[j] = Ids[i];
                    j++;
                }
            }
        }
        break;
    case 3:
        for(i = 0; i < linhas; i++)
        {
            if(strcmp(escolha , telefones[i]) == 0)
            {    
                j++;
            }
        }
        if(j > 0)
        {
            vet_Ids = malloc(j);
            j = 0;
            for(i = 0; i < linhas; i++)
            {
                if(strcmp(escolha , telefones[i]) == 0)
                {    
                    vet_Ids[j] = Ids[i];
                    j++;
                }
            }
        }
        break;
    }
    *tamanho = j;
    if (j > 0)
    {
        for(i=0;i<j;i++)
        {
            printf("id %d\n", vet_Ids[i]);
        }
        return vet_Ids;
    }
    else
    {
        return 0;
    }
}


//Função para excluir um contato
int excluir_contato()
{
    cria_abre();
    aloca(0);
    conta_linhas();
    aloca(linhas);
    int *resultado;
    char escolha[50], c;
    int i, tamanho, j;
    tamanho = 0;

    printf("\nDigite:\n0- Voltar\n1- excluir por nome\n2- excluir por email\n3- excluir por telefone\n");
    __fpurge(stdin);
    fflush(stdin);
    scanf("%d", &i);
    switch (i)
    {
    case 0:
        return 0;
        break;
    case 1:
        printf("Insira o nome:\n");
        __fpurge(stdin);
        fflush(stdin);
        gets(escolha);
        *escolha = valida_nome(escolha); 
        printf("escolha: %s\n", escolha);
        resultado = busca(escolha, i, &tamanho);   
        break;
    case 2:
        printf("Insira o email:\n");
        __fpurge(stdin);
        fflush(stdin);
        gets(escolha);
        *escolha = valida_email(escolha);
        printf("escolha: %s\n", escolha);
        resultado = busca(escolha, i, &tamanho);
        break;
    case 3:
        printf("Insira o telefone:\n");
        __fpurge(stdin);
        fflush(stdin);
        gets(escolha);
        resultado = busca(escolha, i, &tamanho);
        break;
    }
    fecha_arquivo();
    if (tamanho == 1)
    {
        *escolha = resultado[0];
        for(i = 0; i < linhas; i++)
        {
            if(Ids[i] == *escolha)
            {
                printf("%d %s %s %s", Ids[i], nomes[i], emails[i], telefones[i]);
            } 
        } 
        arquivo_aux = fopen("Arq_auxiliar.txt", "w+");
        if (arquivo_aux == NULL)
        {
            printf("\n\nerro na criacao\n");
        }
        else
        {
            for(i = 0; i < linhas; i++)
            {                        
                if(Ids[i] != *escolha)
                {
                    fprintf(arquivo_aux,"%d ", Ids[i]);
                        
                    fprintf(arquivo_aux,"%s ", nomes[i]);
                            
                    fprintf(arquivo_aux,"%s ", emails[i]);
                        
                    fprintf(arquivo_aux,"%s\n", telefones[i]);
                    }
                }
                fecha_arquivo();
                arquivo_aux = fopen("Arq_auxiliar.txt", "r");
                if (arquivo_aux == NULL)
                {
                    printf("\n\nerro na criacao\n");
                }
                arquivo = fopen("Dados.txt", "w+");
                if (arquivo == NULL)
                {
                    printf("\n\nerro na criacao\n");
                }
                else
                {
                    c = fgetc(arquivo_aux); 
                    while (c != EOF) 
                { 
                fputc(c, arquivo); 
                c = fgetc(arquivo_aux); 
            }    
            printf("contato excluido\n");
            }                
        }
    }
    else if(tamanho > 1)
    {
        printf("Foi encontrado mais de um contato com a mesma informacao.\n Insira o ID do contato que deseja excluir?\n");
        for(i = 0; i < tamanho; i ++)
        {
            printf(" %d - %s - %s - %s\n", Ids[resultado[i]-1], nomes[resultado[i]-1], emails[resultado[i]-1], telefones[resultado[i]-1]);
        }
        __fpurge(stdin);
        fflush(stdin);
        scanf("%d",&escolha);

        for(i = 0; i < tamanho; i ++)
        {
            if(*escolha == Ids[resultado[i]-1])
            {
                j = 1;
            }
        }
        while(j != 1)
        {
            printf("Valor invalido, insira novamente:\n");
            __fpurge(stdin);
            fflush(stdin);
            scanf("%d",&escolha);
            for(i = 0; i < tamanho; i ++)
            {
                if(*escolha == Ids[resultado[i]-1])
                {
                    j = 1;
                }
            }
        }
        arquivo_aux = fopen("Arq_auxiliar.txt", "w+");
        if (arquivo_aux == NULL)
        {
            printf("\n\nerro na criacao\n");
        }
        else
        {
            for(i = 0; i < linhas; i++)
            {                        
                if(Ids[i] != *escolha)
                {
                    fprintf(arquivo_aux,"%d ", Ids[i]);
                    fprintf(arquivo_aux,"%s ", nomes[i]);
                    fprintf(arquivo_aux,"%s ", emails[i]);
                    fprintf(arquivo_aux,"%s\n", telefones[i]);
                }
            }
            fecha_arquivo();
            arquivo_aux = fopen("Arq_auxiliar.txt", "r");
            if (arquivo_aux == NULL)
            {
                printf("\n\nerro na criacao\n");
            }
            arquivo = fopen("Dados.txt", "w+");
            if (arquivo == NULL)
            {
                printf("\n\nerro na criacao\n");
            }
            else
            {
                c = fgetc(arquivo_aux); 
                while (c != EOF) 
                { 
                    fputc(c, arquivo); 
                    c = fgetc(arquivo_aux); 
                }    
                printf("contato excluido\n");
            }
        }
    }
    libera_mem();
    fecha_arquivo();
}


//Função para validar o nome inserido
char valida_nome(char* escolha)
{
    int i;
    int valida = 0; 
    for (i= 0; i < 50; i++)
    {
        if(escolha[i] == 0)
        {
            printf("\n%d\n",i);
            break;
        }
        if(((escolha[i] < 96) || (escolha[i] > 123)) && (escolha[i] != 32))   
        {
            printf("\ninvalido %d\n", escolha[i]);
            valida = 1;
        }    
    }
    if(valida != 1)
    {
        for(i = 0; i < 50; i++)
        {
            if(escolha[i] > 96 && escolha[i] < 123)   
            {
                escolha[i] = escolha[i] - 32;
            }   
            else if(escolha[i] == 32)
            {
                escolha[i] = escolha[i];
            }
            if(escolha[i] == 0)
            {
                break;
            }
        }
        printf("%s\n\n", escolha);
        return *escolha;   
    }
    else
    {
        printf("Nome com caractere invalido, por favor insira novamente:\n");
        __fpurge(stdin);
        fflush(stdin);
        gets(escolha);
        valida_nome(escolha);
    }
}


//Função para validar o email inserido
char valida_email(char* escolha)
{
    int i;
    int pos;
    int validador1 = 0;
    int validador2 = 0;

    for(i = 0; i < 50; i++)
    {
        if(escolha[i] == 64)   
        {
            validador1 = 1;
            pos = i;
            break;
        }
    } 
    for(i = pos; i < 50; i++)
    {
        if(escolha[i] == 46)   
        {
            if(escolha[i+1] == 99)
            {
                if(escolha[i+2] == 111)
                {
                    if(escolha[i+3] == 109)
                    {
                        validador2 = 1;
                        break;
                    }
                    break;
                }
                break;
            }
            break;
        }
    }
    if ((validador1 != 1) || (validador2 != 1))
    {
        printf("\nE-mail inválido. O e-mail deve ser digitado no formato exemplo@exemplo.com\n\n");
        printf("Insira um e-mail no formato exemplo@exemplo.com:\n");
        __fpurge(stdin);
        fflush(stdin);
        gets(escolha);
        valida_email(escolha);
    }
    else
    {
        return *escolha;
    }
}


//Função que libera memoria
void libera_mem()
{
    int i;
    free(Ids);
    
    for(i = 0; i < linhas; i++)
    {
        free(nomes[i]);
        free(emails[i]);
        free(telefones[i]);
    }
    free(nomes);
    free(emails);
    free(telefones);
}