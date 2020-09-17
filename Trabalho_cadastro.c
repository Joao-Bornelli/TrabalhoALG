#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>

/*  Comentários:
1- Separar componentes por espaço
2- Conferir email (@ e .com)
3- Nome em caixa alta

*/
int menu();

int adiciona();
//int encontrar();
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

//int altera();

char busca(char* escolha, int opcao);



int linhas;

FILE *arquivo;
int *Ids;
char **nomes;
char **emails;
char **telefones;

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
        //opcao = 1;
        switch (opcao)
        {
        case 0:
            fecha_arquivo(0);
            return 0;
        case 1:
            adiciona();
            break;
        case 2:
            //altera();
            encontrar();
            break;
        case 3:
            //exclui();
            excluir_contato();
            break;
        case 4:
            lista();
            break;
        }
        libera_mem();
    }
}

void cria_abre()
{
    int i = 0;
    arquivo = fopen("Dados.txt", "a+");
    if (arquivo == NULL)
    {
        printf("\n\nerro na criação\n");
    }
}

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

    printf("O arquivo possui %d linhas.\n\n", linhas);
}

int aloca(int qnt)
{
    int i = 0;

    if(qnt > 0)
    {
        Ids = realloc(Ids,sizeof(int)*qnt);
        //Ids = malloc(sizeof(int)*index);
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
                //auxNome = nomes[i];
                strcpy(nomes[i],nomes[i+1]);
                //nomes[i] = nomes[i+1];
                strcpy(nomes[i+1],auxNome);
                //nomes[i+1] = auxNome;
                
                strcpy(auxEmail,emails[i]);
                //auxEmail = emails[i];
                strcpy(emails[i],emails[i+1]);
                strcpy(emails[i+1],auxEmail);
                
                strcpy(auxTel,telefones[i]);
                //auxTel = telefones[i];
                strcpy(telefones[i],telefones[i+1]);
                strcpy(telefones[i+1],auxTel);
            }
        }
    }
}


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
    conta_linhas();
    if(linhas > 0)
    {   
        aloca(linhas + 1);

        for(i = 1; i < linhas; i++)
        {
            if(Ids[i] > (Ids[i-1]+1))
            {
                //printf("----IDS I %d----\n", Ids[i]);
                x = i;
                break;
            }
        }
        if(x > 0)
        {
            Ids[x] = Ids[x-1] + 1;
            //printf("----IDS X %d----\n", Ids[x-1]+1);
            printf("Nome:\n");
            fflush(stdin);
            gets(auxNome);
            *auxNome = valida_nome(auxNome);
            strcpy(nomes[x], auxNome);
                        
            printf("E-mail:\n");
            fflush(stdin);
            gets(auxEmail);
            *auxEmail = valida_email(auxEmail);
            strcpy(emails[x], auxEmail);

            printf("Telefone:\n");
            fflush(stdin);
            gets(*telefones);
            strcpy(telefones[x], *telefones);

            fprintf(arquivo,"%d ", Ids[x]);
            //fprintf(arquivo,",");
            fprintf(arquivo,"%s ", nomes[x]);
            //fprintf(arquivo,",");
            fprintf(arquivo,"%s ", emails[x]);
            //fprintf(arquivo,",");
            fprintf(arquivo,"%s\n", telefones[x]);
        }
        else
        {
            index = linhas;
            Ids[index]= index+1;
            // printf("----IDS Linhas %d -- %d----\n", Ids[index],index);
            // strcpy(nomes[index],"leandro");
            printf("Nome:\n");
            fflush(stdin);
            gets(auxNome);
            printf("%s\n", auxNome);
            *auxNome = valida_nome(auxNome);
            strcpy(nomes[index],auxNome);

            printf("E-mail:\n");
            fflush(stdin);
            gets(auxEmail);
            *auxEmail = valida_email(auxEmail);
            strcpy(emails[index], auxEmail);

            printf("Telefone:\n");
            fflush(stdin);
            gets(*telefones);
            strcpy(telefones[index], *telefones);

            fprintf(arquivo,"%d ", Ids[index]);
            //fprintf(arquivo,",");
            fprintf(arquivo,"%s ", nomes[index]);
            //fprintf(arquivo,",");
            fprintf(arquivo,"%s ", emails[index]);
            //fprintf(arquivo,",");
            fprintf(arquivo,"%s\n", telefones[index]);
        }
    }
    else
    {       
        Ids[0] = 1;
        printf("Nome:\n");
        fflush(stdin);
        gets(auxNome);
        *auxNome = valida_nome(auxNome);
        strcpy(nomes[0],auxNome);
                        
        printf("E-mail:\n");
        fflush(stdin);
        gets(auxEmail);
        *auxEmail = valida_email(auxEmail);
        strcpy(emails[0], auxEmail);

        printf("Telefone:\n");
        fflush(stdin);
        gets(*telefones);
        strcpy(telefones[0],*telefones);        

        fprintf(arquivo,"%d ", Ids[0]);
        //fprintf(arquivo,",");
        fprintf(arquivo,"%s ", nomes[0]);
        //fprintf(arquivo,",");
        fprintf(arquivo,"%s ", emails[0]);
        //fprintf(arquivo,",");
        fprintf(arquivo,"%s\n", telefones[0]);
    }
    fecha_arquivo();
    printf("Contato adicionado com sucesso.\n");
}


int fecha_arquivo()
{
    fclose(arquivo);
}

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
    scanf("%d", &escolha);

    while(escolha < 0 || escolha > 5){
        printf("Número inválido, insira uma opção válida ou 0 para encerrar o programa.\n");
        fflush(stdin);
        scanf("%d", &escolha); 
    }
    return (escolha);
}



int encontrar()
{
    int escolha;
    printf("Digite o tipo de informação a ser buscada:\n");
    printf("1 - Id\n");
    printf("2 - Nome\n");
    printf("3 - Email\n");
    printf("4 - Telefone\n");
    printf("0 - Voltar\n");
    scanf("%d", &escolha);
    switch (escolha)
    {
    case 0:
      return 0;
    case 1:
        
        //busca();
        break;
    case 2:
        
        //busca();
        break;
    case 3:

        //busca();
        break;
    case 4:

        //busca();
        break;
    }
}

int lista()
{
    cria_abre();
    conta_linhas();
    if(linhas > 0)
    {
        int i;
        printf("Lista de clientes: \n");
        for(i = 0 ; i <linhas; i++)
        {
            printf("%d %s %s %s\n", Ids[i], nomes[i], emails[i], telefones[i]);
        }
        printf("\n");
        fecha_arquivo();
    }
    else
    {
        printf("\nNão existe nenhum cliente cadastrado!\n");
    }
    fecha_arquivo();
}

char busca(char* escolha, int opcao)
{
    cria_abre();

    printf("\n\n%s\n\n", escolha);
}


int excluir_contato() //esta funcao nao esta funcionando.
{
    char escolha[50];
    int i;
    printf("\nDigite o 0- Voltar\n1- nome\n2- email\n3- telefone do usuário para excluir:\n");
    fflush(stdin);
    scanf("%d", &i);
    switch (i)
    {
    case 0:
        return 0;
        break;
    case 1:
        fflush(stdin);
        gets(escolha);
        *escolha = valida_nome(escolha); 
        printf("escolha: %s\n", escolha);
        busca(escolha, i);   
        break;

    case 2:
        fflush(stdin);
        gets(escolha);
        *escolha = valida_email(escolha);
        printf("escolha: %s\n", escolha);
        busca(escolha, i);
        break;

    case 3:
        fflush(stdin);
        gets(escolha);
        busca(escolha, i);
        break;
    }
    fecha_arquivo();
}

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
        fflush(stdin);
        gets(escolha);
        valida_nome(escolha);
    }
}

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
        fflush(stdin);
        gets(escolha);
        valida_email(escolha);
    }
    else
    {
        return *escolha;
    }
}

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
    printf("x %d\n", sizeof(nomes));
    printf("x[0] %d\n\n", sizeof(nomes[0]));
}