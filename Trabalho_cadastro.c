#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>

/*  Comentários:
1- Separar componentes por espaço
2- Conferir email (@ e .com)
3- Nome em caixa alta

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
int limpa_nome(int opcao);
int limpa_email(int opcao);
int excluir_contato();

//int altera();
//int pesquisa();
//int exclui();

//int limpa_nome();
//int verif_email();


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
            //pesquisa();
            break;
        case 4:
            //exclui();
            //excluir_contato();
            break;
        case 5:
            lista();
            break;
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
            gets(*nomes);
            strcpy(nomes[x], *nomes);
            limpa_nome(x);
                        
            printf("E-mail:\n");
            fflush(stdin);
            gets(*emails);
            strcpy(emails[x], *emails);
            limpa_email(x);
            
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
            gets(*nomes);
            printf("%s\n", *nomes);
            strcpy(nomes[index],*nomes);
            limpa_nome(index);
                        
            printf("E-mail:\n");
            fflush(stdin);
            gets(*emails);
            strcpy(emails[index],*emails);
            limpa_email(index);
            
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
            gets(*nomes);
            strcpy(nomes[0],*nomes);
            limpa_nome(0);
                        
            printf("E-mail:\n");
            fflush(stdin);
            gets(*emails);
            strcpy(emails[0],*emails);
            limpa_email(0);
            
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

        // fprintf(arquivo,"%d ",Ids[0]);        
        // strcpy(nomes[0],"leandro");
        // limpa_nome(0);
        
        // fprintf(arquivo,"%s ",nomes[0]);
        // strcpy(emails[0],"xxxxxxx@xxxx.com");
        // limpa_email(0);
        // fprintf(arquivo,"%s ",emails[0]);
        // strcpy(telefones[0], "01010101");
        // fprintf(arquivo,"%s\n",telefones[0]);
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
    printf(" 3 - Pesquisar contato\n");
    printf(" 4 - Excluir contato\n");
    printf(" 5 - Exibir lista de contatos\n");
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

int limpa_nome(int opcao)
{
    int i;
    int valida = 0; 
   for (i= 0; i < 50; i++)
    {
        if(nomes[opcao][i] == 0)
        {
            printf("\n%d\n",i);
            break;
        }
        if(((nomes[opcao][i] < 96) || (nomes[opcao][i] > 123))&&(nomes[opcao][i] != 32))   
        {
            printf("\ninvalido %d\n", nomes[opcao][i]);
            valida = 1;
        }
        
    }

    if(valida != 1)
    {
        for(i = 0; i < 50; i++)
        {
            if(nomes[opcao][i] > 96 && nomes[opcao][i] < 123)   
            {
                nomes[opcao][i] = nomes[opcao][i] - 32;
            }   
            else if(nomes[opcao][i] == 32)
            {
                nomes[opcao][i] = nomes[opcao][i];
            }
            if(nomes[opcao][i] == 0)
            {
                break;
            }
        }
        
    }
    else
    {
        printf("Nome com caractere invalido, por favor insira novamente:\n");
        fflush(stdin);
        gets(*nomes);
        strcpy(nomes[opcao],*nomes);
        limpa_nome(opcao);
    }
}

int limpa_email(int opcao)
{
    int i;
    int validador1 = 0;
    int validador2 = 0;

    for(i = 0; i < 50; i++)
    {
        if(emails[opcao][i] == 64)   
        {
            validador1 = 1;
            break;
        }
    }
    
    for(i = 0; i < 50; i++)
    {
        if(emails[opcao][i] == 46)   
        {

            if(emails[opcao][i+1] == 99)
            {
                if(emails[opcao][i+2] == 111)
                {
                    if(emails[opcao][i+3] == 109)
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
        printf("Validador 1 = %d, validador 2 = %d\n", validador1,validador2);
        printf("\nE-mail inválido. O e-mail deve ser digitado no formato exemplo@exemplo.com\n\n");
        printf("Insira um e-mail no formato exemplo@exemplo.com:\n");
        fflush(stdin);
        gets(*emails);
        strcpy(emails[opcao],*emails);
        limpa_email(opcao);
    }
}

/*
int excluir_contato() //esta funcao nao esta funcionando.
{
    int opcao;

    lista();
    printf("\nDigite o ID do usuário para excluir.\n");
    
    fflush(stdin);
    scanf("%d", &opcao);
    opcao -= 1;
    
    cria_abre();
    conta_linhas();
    aloca(linhas);
    
    nomes[opcao] = "";
    emails[opcao] = "";
    telefones[opcao] = "";
    //Ids[opcao] = 0;
    

    fecha_arquivo();
    conta_linhas();

    printf("Contato excluido com sucesso.\n");
    sleep(2);
    menu();
}
*/