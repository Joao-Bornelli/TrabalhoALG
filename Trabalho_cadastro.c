#include<stdio.h>
#include<string.h>
#include<stdlib.h>

/*  Comentários:
1- Separar componentes por espaço
*/

int adiciona();
int acessa();
int ordena();
int escreve();
int lista();
int menu();
void cria_abre();
int conta_linhas();
int aloca(int qnt);
int fecha_arquivo();

//int altera();
//int pesquisa();

//int exclui();
//int confere();

//int fechar_prog();
//int limpa_nome();
//int limpa_email();
//int limpa_telefone();


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
            return 0;
        case 1:
            adiciona();
            break;
        case 2:
      //  altera();
            encontrar();
            break;
        case 3:
      //  pesquisa();
            break;
        case 4:
      //exclui();
            break;
        case 5:
            lista();
            break;
        }
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
        
        for(i = 0 ;i < qnt; i++)
        {
            nomes[i]=  malloc(sizeof(char)*50);
            emails[i]= malloc(sizeof(char)*50);
            telefones[i]= malloc(sizeof(char)*12);
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
        nomes[0]= (char*)malloc(sizeof(char)*50);
        emails[0]= (char*)malloc(sizeof(char)*50);
        telefones[0]= (char*)malloc(sizeof(char)*12);
    }
}


int adiciona()
{   
    int i = 0;
    int x = 0;
    int index = 0;
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
                printf("----IDS I %d----\n", Ids[i]);
                x = i;
                break;
            }
        }
        if(x > 0)
        {
            Ids[x] = Ids[x-1] + 1;
            printf("----IDS X %d----\n", Ids[x-1]+1);
            strcpy(nomes[x],"leandro");
            strcpy(emails[x],"xxxxxxx@xxxx.com");
            strcpy(telefones[x], "01010101");

            fprintf(arquivo,"%d ",Ids[x]);
            //fprintf(arquivo,",");
            fprintf(arquivo,"%s ",nomes[x]);
            //fprintf(arquivo,",");
            fprintf(arquivo,"%s ",emails[x]);
            //fprintf(arquivo,",");
            fprintf(arquivo,"%s\n",telefones[x]);
        }
        else
        {
            index = linhas;
            Ids[index]= index+1;
            printf("----IDS Linhas %d -- %d----\n", Ids[index],index);
            strcpy(nomes[index],"leandro");
            strcpy(emails[index],"xxxxxxx@xxxx.com");
            strcpy(telefones[index], "01010101");

            fprintf(arquivo,"%d ",Ids[index]);
            //fprintf(arquivo,",");
            fprintf(arquivo,"%s ",nomes[index]);
            //fprintf(arquivo,",");
            fprintf(arquivo,"%s ",emails[index]);
            //fprintf(arquivo,",");
            fprintf(arquivo,"%s\n",telefones[index]);
        }
    }
    else
    {   
        printf("---%d---\n",linhas);
    
        Ids[0] = 1;
        fprintf(arquivo,"%d ",Ids[0]);        
        strcpy(nomes[0],"leandro");
        fprintf(arquivo,"%s ",nomes[0]);
        strcpy(emails[0],"xxxxxxx@xxxx.com");
        fprintf(arquivo,"%s ",emails[0]);
        strcpy(telefones[0], "01010101");
        fprintf(arquivo,"%s\n",telefones[0]);
    }
    fecha_arquivo();
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
    printf(" 3 - Pesquisar contato\n");
    printf(" 4 - Excluir contato\n");
    printf(" 5 - Exibir lista de contatos\n");
    printf(" 0 - Sair\n");
    printf("\nInsira o número da função desejada:\n");
    scanf("%d", &escolha);

    while(escolha < 0 || escolha > 5){
        printf("Número inválido, insira uma opção válida ou 0 para encerrar o programa.\n");
        scanf("%d", &escolha);   
    }
    return (escolha);
}



int encontrar()
{

    int escolha_2;
    printf("Digite o tipo de informação a ser buscada:\n");
    printf("1 - Id\n");
    printf("2 - Nome\n");
    printf("3 - Email\n");
    printf("4 - Telefone\n");
    printf("0 - Voltar\n");
    scanf("%d", &escolha_2);

    switch (escolha_2)
    {
    case 0:
      return 0;
    case 1:
        
        break;
    case 2:
      //  altera();
        
        break;
    case 3:
      //  pesquisa();
        break;
    case 4:
      //exclui();
        break;
    }
}

int lista()
{
    cria_abre();
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
