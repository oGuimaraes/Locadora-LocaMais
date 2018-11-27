#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <conio.h>
#include <time.h>

/*-----Registros------*/

//Registro do endereço
struct Tender
{
    char rua[100], bairro[100], complemento[100];
    int nro, cep;
};
typedef struct  Tender ender;

//Registro do Cliente
struct Tcliente
{
    int codigo, telefone;
    char nome[100];
    ender endereco;
};
typedef struct Tcliente cliente;

//Registro do Funcionário
struct Tfuncionario
{
    int codigo, telefone;
    char nome[100], cargo[50];
    float salario;
};
typedef struct  Tfuncionario funcionario;

//Registro do Veículo
struct Tveiculo
{
    int codigo, qOcup, intStatus;
    char descricao[500], cor[20], status[20];
    float vDiaria;
    char modelo[50], placa[10];
};
typedef struct Tveiculo veiculo;

//Registro da Locação
struct Tlocacao
{
    int codigo, codigoCliente, codigoVeiculo, qDias;
    int dataRetirada, dataDevolucao;
    float seguro;
};
typedef struct Tlocacao locacao;
/*-------------------*/

/*
int geraCodigo()
{
    srand(time(NULL));
    int resto;
    int cod = 1000 + rand() % 11000;
    cod = (1000 + rand() % 11000) * (1000 + rand() % 11000);
    cod = sqrt(cod);
    cod = pow(cod,2);
    cod = cod + 1000 + rand() % 11000;
    resto = cod % 1000;
    cod = (cod/1000) + resto;

    return cod;
}
*/

//Cadastro do Cliente
void cadastro_Cliente()
{
    cliente c;
    FILE *bdC;
    int maior;

    bdC= fopen("dadosCliente.txt","w+b");

    fseek(bdC,0,SEEK_SET);
    fread(&c,sizeof(c),1,bdC);
    if(sizeof(bdC) == 0) {
        maior = 99;
    } else
    {
        while (!feof(bdC))
        {
            maior=0;
            if(c.codigo >= maior)
                maior = c.codigo;
                printf("Código do cliente: %d",c.codigo);
        fread(&c,sizeof(c),1,bdC);

    }
}
c.codigo = maior+1;
printf("---CADASTRO DO CLIENTE---\n");
printf("Código do cliente: %d",c.codigo);
printf("\nDigite os dados do cliente:\n");
printf("Nome: ");
fflush (stdin);
gets(c.nome);

printf("Rua: ");
fflush (stdin);
gets(c.endereco.rua);
printf("Bairro: ");
fflush(stdin);
gets(c.endereco.bairro);
printf("Complemento: ");
fflush(stdin);
gets(c.endereco.complemento);
printf("Numero: ");
fflush(stdin);
scanf("%d",&c.endereco.nro);
printf("CEP: ");
fflush(stdin);
scanf("%d",&c.endereco.cep);

printf("Telefone: ");
fflush(stdin);
scanf("%d",&c.telefone);


fseek(bdC,0,SEEK_END);
fwrite(&c,sizeof(c),1,bdC);
fflush(bdC);
printf("\nCLIENTE CADASTRADO COM SUCESSO!!!");
}
void cadastro_funcionario()
{
    funcionario func;
    FILE *bdF;

    bdF= fopen("dadosFuncionario.txt","w+b");

    printf("--REGISTRO DO FUNCIONÁRIO--");
    printf("\nCódigo do funcionário: %d ",func.codigo);
    printf("\nDigite os dados do funcionário:\n");
    printf("Nome:\n");
    fflush(stdin);
    gets(func.nome);

    printf("Telefone:\n");
    fflush(stdin);
    scanf("%d",&func.telefone);

    printf("Cargo:\n");
    fflush(stdin);
    gets(func.cargo);

    printf("Salário:\n");
    fflush(stdin);
    scanf("%f",&func.salario);

    fseek(bdF,0,SEEK_END);
    fwrite(&func,sizeof(func),1,bdF);
    fflush(bdF);
    printf("\nFUNCIONÁRIO CADASTRADO COM SUCESSO!");
}
//funcão cadastro de locação
void cadastro_Locacao()
{
    locacao l;
    char nome[100];
    FILE *bdL,*bdC,*bdV;
    cliente c;

    bdL= fopen("dadosLocacao.txt","w+b");
    bdC= fopen("dadosCliente.txt","r+b");
    bdV= fopen("dadosVeiculo.txt","r+b");

    printf("--REGISTRO DE LOCAÇÃO--\n");
    printf("Código da Locação: \n",l.codigo);
    fflush(stdin);

    printf("\nInforme o nome do cliente: ");
    gets(nome);

    fseek(bdC,0,SEEK_SET);
    fread(&c,sizeof(c),1,bdC);
    while (!feof(bdC))
    {
        if(strcmp(nome,c.nome))
        {
            l.codigoCliente=c.codigo;
        }
        fread(&c,sizeof(c),1,bdC);
    }

    printf("\nData da retirada do veículo: ");
    fflush(stdin);
    gets(l.dataRetirada);

    printf("\nData da devolução do veículo: ");
    fflush(stdin);
    gets(l.dataDevolucao);

    printf("\nValor do Seguro: ");
    fflush(stdin);
    scanf("%f",&l.seguro);

    fseek(bdL,0,SEEK_END);
    fwrite(&l,sizeof(l),1,bdL);
    fflush(bdL);
}

//Cadastro Veículo
void cadastro_Veiculo()
{
    veiculo v;
    FILE * bdV;
    bdV= fopen("dadosVeiculo.txt","r+b");

    printf("--CADASTRO DO VEÍCULO--\n");
    printf("Código do veículo:\n");

    printf("Modelo:\n");
    fflush(stdin);
    gets(v.modelo);

    printf("Cor:\n");
    fflush(stdin);
    gets(v.cor);

    printf("Placa:\n");
    fflush(stdin);
    gets(v.placa);

    printf("Descrição do veículo:\n");
    fflush(stdin);
    gets(v.descricao);

    printf("Quantidade de ocupantes:\n");
    fflush(stdin);
    scanf("%d",&v.qOcup);

    printf("Valor da diária:\n");
    fflush(stdin);
    scanf("%f",&v.vDiaria);

    printf("DIGITE O Nº STATUS: 1-ALUGADO 2- DISPONÍVEL 3- MANUTENÇÃO \n");
    scanf("%d",&v.intStatus);

    switch(v.intStatus)
    {
    case 1:
        strcpy(v.status, "Alugado");
        break;
    case 2:
        strcpy(v.status, "Disponivel");
        break;
    case 3:
        strcpy(v.status, "Manutenção");
        break;
    }

    fseek(bdV,0,SEEK_END);
    fwrite(&v,sizeof(v),1,bdV);
    fflush(bdV);
    printf("\nVEÍCULO CADASTRADO COM SUCESSO!");

    return v;
}

int main()
{
    setlocale(LC_ALL,"portuguese");
    char opcao;
    int vC[1000];
    FILE *bdC,*bdF,*bdL,*bdV;

    /* Variáveis do FILE
    bdC= BANCO DE DADOS DO CLIENTE
    bdF= BANCO DE DADOS DO FUNCIONÁRIO
    bdL= BANCO DE DADOS DA LOCAÇÃO
    bdV= BANCO DE DADOS DO VEÍCULO*/

    if(bdC = fopen("dadosCliente.txt","r+b") == NULL)
    {
        bdC = fopen("dadosCliente.txt","w+b");
    }
    if(bdF = fopen("dadosFuncionario.txt","r+b") == NULL)
    {
        bdF = fopen("dadosFuncionario.txt","w+b");
    }
    if(bdL = fopen("dadosLocacao.txt","r+b") == NULL)
    {
        bdL = fopen("dadosLocacao.txt","w+b");
    }
    if(bdV = fopen("dadosVeiculo.txt","r+b") == NULL)
    {
        bdV = fopen("dadosVeiculo.txt","w+b");
    }



    //cadastro_Cliente();
    //cadastro_funcionario();
    //cadastro_Locacao();
    cadastro_Veiculo();

}


