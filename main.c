#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

struct Cadastro
{
    unsigned int codigo_paciente;
    char nome[40];
    char telefone[20];
    char cidade[20];


}funcionarios;

FILE *Dados;
void menu(void);
void cadastrar(void);
void inserir(FILE *arquivo); // A funcao cadastrar chamar� essa fun��o
void exibir(FILE *arquivo);
void localizar(FILE *arquivo);
void editar();
void sobrescrever(FILE *arquivo);
void mensagemFIM(void);
void ArquivoResultados(FILE *arquivo);
void apagar();
void limparregistro(FILE *arquivo);
void main()
{
    menu();
}
void ArquivoResultados(FILE *arquivo)
{
    FILE *DadosImpressao;
    int resultado;
    struct Cadastro cad = {0,"","",""};
    if ((DadosImpressao = fopen("IMPRESSAO","wb"))==NULL)
    {
        printf("\nERRO 2355!\n");
        printf("\nERRO AO IMPRIMIR DADOS!\n");
    }
    else
    {
        rewind(Dados);
        fprintf(DadosImpressao,"%s\t%40s\t%20s\t%20s\n","Senha do paciente","Nome Completo","Telefone","Cidade");
        while(!feof(Dados))
        {
            resultado = fread(&Cadastro,sizeof(struct Cadastro),1,arquivo);
            if(resultado != 0 && Cadastro.codigo_paciente !=0)
            {
                fprintf(ArquivoImpressao,"%06d\t%40s\t%20s\t%20s\n",Cadastro.codigo_paciente,Cadastro.nome,Cadastro.telefone,Cadastro.cidade);
            }
        }
        fclose(ArquivoImpressao);
    }
}
void menu()
{
    int escolha;
    char opcao;
    printf("Menu");
    printf("\nDeseja Limpar os dados disponiveis?");
    printf("(s)sim?");
    printf("(n)nao?");
    opcao = tolower(getchar());
    if (opcao == 's')
    {
        if ((arquivo = fopen("Cadastro.txt","w+b"))==NULL)
            printf("\nERRO 404!\n");
            printf("\nNao foi possivel iniciar os dados!!!!!!\n");
        else
            printf("\nDados iniciados com Sucesso!\n");
        fclose(arquivo);
    }else if(opcao == 'n'){
       printf("\nArquivo Criado com Sucesso!!!!!!\n");
        fclose(arquivo);
    }
    if((arquivo = fopen("funcionarios.txt","r+b")) == NULL) // Abri o arquivo em modo escrita binaria
    {
        printf("Arquivo nao pode ser aberto para escrita binaria !!!\n");
        system("pause");
    }
    else
    {
    do{
            system("cls");
            printf("\n<---------- Menu --------------->\n");
            printf("1 -> Cadastrar \n2 -> Exibir todos os registros\n3 -> Localizar\n4 -> Editar registro\n5 -> Imprimir Resultados\n6 -> Apagar Registro\n0 -> Sair\n");
            printf("Digite um numero:\n");
            scanf("%d",&escolha);
            printf("\n<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>\n");
            fflush(stdin);
             // Realoca o indicador de posi��o do arquivo para o inicio
            switch(escolha)
            {
            case 1:
                cadastrar();
                break;
            case 2:
                exibir(arquivo);
                break;
            case 3:
                localizar(arquivo);
                break;
            case 4:
                editar();
                break;
            case 5:
                ArquivoResultados(arquivo);
                break;
            case 6:
                apagar();
            break;
            }
    }while(escolha != 0);
    }
    fclose(arquivo);
}
void cadastrar(void)
{
    char opcao = 's';
    while(opcao == 's')
    {
        system("cls");
        inserir(arquivo);
        printf("\nDeseja Continuar (s)im ou (n)ao (ou qualquer outra tecla diferente de s)?: ");
        opcao = tolower(getchar());
        fflush(stdin);
    }
}

void inserir(FILE *arquivo)
{
    int posicao;
    struct Funcionario funcionarios = {0,"","",""};
        printf("Entre com o identificador do Funcionario: ");
        scanf("%d",&posicao);
        fflush(stdin);
        fseek(arquivo,(posicao-1)*sizeof(struct Funcionario),SEEK_SET);
        fread(&funcionarios,sizeof(struct Funcionario),1,arquivo);
        if (funcionarios.identificador != 0)
        {
            printf("\nFuncionario ja cadastrado!!!!\n");
            printf("\n<> Funcionario %d: \n",funcionarios.identificador);
        }
        else
        {
            printf("\n****************** < Cadastro dos funcionarios > **********************\n");
            printf("Funcionario \n");
            printf("Nome: ");
            gets(funcionarios.nome);
            fflush(stdin);
            printf("Telefone : ");
            gets(funcionarios.telefone);
            fflush(stdin);
            printf("Cidade: ");
            gets(funcionarios.cidade);
            funcionarios.identificador = posicao;
            fseek(arquivo,(posicao-1)*sizeof(struct Funcionario),SEEK_SET);
            fwrite(&funcionarios,sizeof(struct Funcionario),1,arquivo); // Grava informa��es da struct no arquivo
        }
        mensagemFIM();
}
void exibir(FILE *arquivo)
{
    int resultado;
        rewind(arquivo);
        system("cls");
        printf("\n************** > Registros dos funcionarios < ********************\n\n");
        while(!feof(arquivo))
        {
            resultado = fread(&funcionarios,sizeof(struct Funcionario),1,arquivo);
            if(resultado != 0 && funcionarios.identificador !=0)
            {
                printf("\n<> Funcionario %d: \n",funcionarios.identificador);
                printf("Nome: %s\n",funcionarios.nome);
                printf("Telefone: %s\n",funcionarios.telefone);
                printf("Cidade: %s\n",funcionarios.cidade);
                printf("\n");
            }
        }
        mensagemFIM();
 }
void localizar(FILE *arquivo)
{
    unsigned int identificador,verificador;
    char opcao = 's';
    while(opcao == 's')
        {
            rewind(arquivo);
            system("cls");
            verificador = 0;
            printf("\n*************************** > Localizar Funcionarios > ***********************\n\n");
            printf("Digite o identificador do Funcionario: ");
            scanf("%d",&identificador);
            fflush(stdin);
            while(!feof(arquivo) && verificador != 1)
            {
                fread(&funcionarios,sizeof(struct Funcionario),1,arquivo);
                if(identificador == funcionarios.identificador)
                {
                    verificador = 1;
                    printf("\n************** > Funcionario Localizado < ********************\n");
                    printf("\n<> Funcionario %d: \n",funcionarios.identificador);
                    printf("Nome: %s\n",funcionarios.nome);
                    printf("Telefone: %s\n",funcionarios.telefone);
                    printf("Cidade: %s\n",funcionarios.cidade);
                }
            }
            if(verificador == 0)
                printf("\n\nIdentificador de Funcionario nao localizado\n\n");
            printf("\nDeseja Continuar (s)im ou (n)ao: ");
            opcao = tolower(getchar());
            fflush(stdin);
        }
    mensagemFIM();
 }
 void editar(void)
 {
     char opcao = 's';
     while(opcao == 's')
     {
        sobreescrever(arquivo);
        printf("\nDeseja Continuar (s)im ou (n)ao (ou qualquer outra tecla diferente de s)?: ");
        opcao = tolower(getchar());
        fflush(stdin);
     }
 }

void sobreescrever(FILE *arquivo)
{
    unsigned int posicao;
    struct Funcionario funcionarios = {0,"","",""};
    system("cls");
    printf("\n*************************** > Localizar Funcionarios Para Editar > ***********************\n\n");
    printf("Digite o identificador do Funcionario: ");
    scanf("%d",&posicao);
    fflush(stdin);
    fseek(arquivo,(posicao-1)*sizeof(struct Funcionario),SEEK_SET);
    fread(&funcionarios,sizeof(struct Funcionario),1,arquivo);
    if (funcionarios.identificador == 0)
    {
        printf("\n************** > Funcionario Nao Localizado para Ser Alterado< ********************\n");
    }
    else
    {
        printf("\n************** > Funcionario Localizado para Ser Alterado< ********************\n");
        printf("\n<> Funcionario %d: \n",funcionarios.identificador);
        printf("Nome: %s\n",funcionarios.nome);
        printf("Telefone: %s\n",funcionarios.telefone);
        printf("Cidade: %s\n",funcionarios.cidade);
        printf("\n");
        system("pause");
        printf("\n\nEntre com os novos Dados\n\n");
        printf("Nome: ");
        gets(funcionarios.nome);
        fflush(stdin);
        printf("Telefone : ");
        gets(funcionarios.telefone);
        fflush(stdin);
        printf("Cidade: ");
        gets(funcionarios.cidade);
        funcionarios.identificador = posicao;
        fseek(arquivo,(posicao-1)*sizeof(struct Funcionario),SEEK_SET);
        fwrite(&funcionarios,sizeof(struct Funcionario),1,arquivo);
    }
mensagemFIM();
}
void mensagemFIM(void)
{
    printf("\n");
    printf("\n()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()\n");
    system("pause");
}
void apagar(void)
 {
     char opcao = 's';
     while(opcao == 's')
     {
        limparregistro(arquivo);
        printf("\nDeseja Continuar (s)im ou (n)ao (ou qualquer outra tecla diferente de s)?: ");
        opcao = tolower(getchar());
        fflush(stdin);
     }
 }
void limparregistro(FILE *arquivo)
{
    unsigned int posicao;
    struct Funcionario funcionarios = {0,"","",""};
    struct Funcionario ressetar = {0,"","",""};
    system("cls");
    printf("\n*************************** > Localizar Funcionarios Para Editar > ***********************\n\n");
    printf("Digite o identificador do Funcionario: ");
    scanf("%d",&posicao);
    fflush(stdin);
    fseek(arquivo,(posicao-1)*sizeof(struct Funcionario),SEEK_SET);
    fread(&funcionarios,sizeof(struct Funcionario),1,arquivo);
    if (funcionarios.identificador == 0)
    {
        printf("\n************** > Funcionario Nao Localizado para Ser Alterado< ********************\n");
    }
    else
    {
        printf("\n************** > Funcionario Localizado para Ser Alterado< ********************\n");
        printf("\n<> Funcionario %d: \n",funcionarios.identificador);
        printf("Nome: %s\n",funcionarios.nome);
        printf("Telefone: %s\n",funcionarios.telefone);
        printf("Cidade: %s\n",funcionarios.cidade);
        printf("\n");
        system("pause");
        printf("\n\nLimpando\n\n");
        fseek(arquivo,(posicao-1)*sizeof(struct Funcionario),SEEK_SET);
        fwrite(&ressetar,sizeof(struct Funcionario),1,arquivo);
    }
mensagemFIM();
}

