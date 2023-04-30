#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//menu
#define CADASTRAR_PACIENTE 1
#define LISTAGEM_GERAL 2
#define RELATORIO_ESTATISTICO 3

//controle de execucao
#define OFF 0
#define ON 1

//especificacoes de regras de negocio
#define ESP_CLINICA_GERAL 1
#define ESP_CARDIOLOGISTA 2
#define ESP_OFTALMOLOGISTA 3
#define ESP_NEUROLOGISTA 4

#define CONVENIADO 1
#define NAO_CONVENIADO 0

#define MASCULINO 2
#define FEMININO 1

#define IDOSO_IDADE 60

#define VALOR_CLINICA_GERAL 250.00
#define VALOR_CARDIOLOGISTA 300.00
#define VALOR_OFTALMOLOGISTA 220.00
#define VALOR_NEUROLOGISTA 350.00

#define DESCONTO_CONVENIADO_A 50.00
#define DESCONTO_CONVENIADO_B 40.00

#define IDADE_MAX 125
#define IDADE_MIN 0

int validacao_idade(int idade)
{
    if ((idade >= IDADE_MIN) && (idade <= IDADE_MAX))
    {
        return idade;
    }
    else{
    while ((idade < IDADE_MIN) || (idade > IDADE_MAX))
    {
        printf("Idade invalida. Por favor, digite novamente: ");
        scanf("%d",&idade);
    }
    }
    return idade;
}

int validacao_sexo(int sexo)
{
    if ((sexo > 0) && (sexo < 3))
    {
        return sexo;
    }
    else{
    while ((sexo <= 0) || (sexo >= 3))
     {
        printf("Opcao invalida. Por favor, digite novamente: ");
        scanf("%d",&sexo);
    }
    }
    return sexo;
}

int validacao_convenio(int convenio)
{
    if ((convenio > -1) && (convenio < 2))
    {
        return convenio;
    }
    else{
    while ((convenio <= -1) || (convenio >= 2))
    {
        printf("Opcao invalida. Por favor, digite novamente: ");
        scanf("%d",&convenio);
    }
    }
    return convenio;
}

int validacao_status_exec(int status_execucao)
{
    if ((status_execucao > -1) && (status_execucao < 2))
    {
        return status_execucao;
    }
    else
    {
    while ((status_execucao <= -1) || (status_execucao >= 2))
        {
        printf("Opcao invalida. Por favor, digite novamente: ");
        scanf("%d",&status_execucao);
    }
    }
    return status_execucao;
}

int validacao_especialidade(int especialidade)
{
    
    if ((especialidade > 0) && (especialidade < 5))
    {
        return especialidade;
    }
    else{
    while ((especialidade <= 0) || (especialidade >= 5))
    {
        printf("Opcao invalida. Por favor, digite novamente: ");
        scanf("%d",&especialidade);
    }
    }
    return especialidade;
}

void criar_arquivo_csv()
{
    FILE *fp;

    fp = fopen("clinica_db.csv","w+");
    fprintf(fp,"Nome,Sexo,Idade,Especialidade,Conveniado,Valor tratamento");
    fclose(fp);
}

void escrever_dados_no_csv(char nome[200], int sexo, int idade, int especialidade, int conveniado, float valor_tratamento)
{
    FILE* fp = fopen("clinica_db.csv", "a");
    if (!fp) //se nao existir o arquivo
        criar_arquivo_csv();

    else {
        fprintf(fp,"%s,%d,%d,%d,%d,%.2f\n",nome,sexo,idade,especialidade,conveniado,valor_tratamento);
        fclose(fp);}
}

void printar_dados_do_csv()
{
    FILE* fp = fopen("clinica_db.csv", "r");
    if (!fp) //se nao existir o arquivo
        criar_arquivo_csv();

    else {
        char buffer[1024];
        int linha = 0;
        int coluna   = 0;

        while (fgets(buffer,1024,fp)){
            coluna = 0;
            linha++;

            char* value = strtok(buffer, ", ");

            while (value)
            {
                if (coluna == 1)
                {
                    printf(" \t\t");
                }
                
                if (coluna == 3 || coluna == 5 || coluna == 4  ||coluna == 2)
                {
                    printf("\t");
                }
                printf("\t%s", value);
                value = strtok(NULL, ", ");
                coluna++;
            }
            printf("\n");
        }
        fclose(fp);
     }
}

int encontrar_maior_valor(int vetor[4])
{
   int index_maior_valor = 0;
   int aux = 0;
  
   for(int i = 0; i ++; i < 4)
   {
       if (aux < vetor[i])
       {
           aux = 0;
           aux += vetor[i];
           index_maior_valor = i;
       }
       
   }
   return index_maior_valor;
}

void print_menu()
{
    printf("---------------------------------------------------------------------------------------------------------\n");
    printf("        Clinica Vida e Saude\n");
    printf("---------------------------------------------------------------------------------------------------------\n");
    printf("\n\nOpções:");
    printf("\n   1- Cadastrar Paciente");
    printf("\n   2- Listagem Geral");
    printf("\n   3- Relatório Estatístico");
    printf("\n   0- Sair \n");
}

float valor_a_pagar(int especialidade,int convenio, int idade)
{
    float valor = 0;
    //calcular desconto de idosos 10%
    switch (especialidade)
    {
        case ESP_CLINICA_GERAL:
            if (convenio == NAO_CONVENIADO)
            {
                valor = VALOR_CLINICA_GERAL;
            }
            else{
                valor = VALOR_CLINICA_GERAL-DESCONTO_CONVENIADO_A;
            }
            break;
        case ESP_CARDIOLOGISTA:
            if (convenio == NAO_CONVENIADO)
            {
                valor = VALOR_CARDIOLOGISTA;
            }
            else{
                valor = VALOR_CARDIOLOGISTA-DESCONTO_CONVENIADO_B;
            }
            break;
        case ESP_OFTALMOLOGISTA:
            if (convenio == NAO_CONVENIADO)
            {
                valor = VALOR_OFTALMOLOGISTA;
            }
            else{
                valor = VALOR_OFTALMOLOGISTA-DESCONTO_CONVENIADO_A;
            }
            break;
        case ESP_NEUROLOGISTA:
            if (convenio == NAO_CONVENIADO)
            {
                valor = VALOR_NEUROLOGISTA;
            }
            else{
                valor = VALOR_NEUROLOGISTA-DESCONTO_CONVENIADO_A;
            }
            break;
    }

    if (idade > IDOSO_IDADE)
    {
        valor = valor-(valor*0.1);
    }

   return valor;
}

int cadastro_paciente(int* qtd_homens_conveniados,int* qtd_idosas,float* qtd_mulheres_cardio,float* qtd_mulheres_total,int* qtd_homens_total,
                       int* idx_clin,int* idx_cardio,
                       int* idx_oft,int* idx_neuro, float* acm_valor_consulta)
{
    char nome[200];
    int sexo = 0;
    int idade = 0;
    int especialidade = 0;
    int convenio = 0;
    int status_execucao = 0;
    float valor_tratamento;

    printf("---------------------------------------------------------------------------------------------------------\n");
    printf("        Clínica Vida e Saúde\n");
    printf("---------------------------------------------------------------------------------------------------------\n");
    printf("\n\nCadastro de Paciente\n\n");
    printf("\n  Nome.............: ");
    scanf("%s",nome);
    printf("\n  Sexo(1-fem/2-mas): ");
    scanf("%d",&sexo);
    sexo = validacao_sexo(sexo);
    printf("\n  Idade.............: ");
    scanf("%d",&idade);
    idade = validacao_idade(idade);
    printf("\n  Especialidade(1-Clinica Geral/2-Cardiologista/3-Oftalmologista/4-Neurologista): ");
    scanf("%d",&especialidade);
    especialidade = validacao_especialidade(especialidade);
    printf("\n  Trabalha em empresa conveniada(1-sim/0-não)..........................: ");
    scanf("%d",&convenio);
    convenio = validacao_convenio(convenio);
    printf("\n\nPaciente cadastrado com sucesso!");
    printf("\n\n---------------------------------------------------------------------------------------------------------");
    printf("\n\nCadastrar outro(1-sim/0-não)?");
    scanf("%d",&status_execucao);
    status_execucao = validacao_status_exec(status_execucao);

    valor_tratamento = valor_a_pagar(especialidade,convenio,idade);

    escrever_dados_no_csv(nome,sexo,idade,especialidade,convenio,valor_tratamento);

    //qtd homens que trabalham em empresas conveniadas
    if ((convenio == CONVENIADO) && (sexo == MASCULINO))
    {
        (*qtd_homens_conveniados)++;
    }

    //qtd de idosas
    if ((sexo == FEMININO) && (idade >= IDOSO_IDADE))
    {
        (*qtd_idosas)++;
    }
    //percentual de mulheres que foram no cardio
    if (sexo == FEMININO)
    {
        (*qtd_mulheres_total)++;

        if (especialidade == ESP_CARDIOLOGISTA)
            {
                (*qtd_mulheres_cardio)++;
            }
    }
    //media de valor das consultas dos homens
    if (sexo == MASCULINO)
    {
        (*qtd_homens_total)++;
        (*acm_valor_consulta)+=valor_tratamento;
    }
    //especialidade que atendeu mais pacientes
    if (especialidade == ESP_CLINICA_GERAL)
    {
        (*idx_clin)++;
    }
    if (especialidade == ESP_CARDIOLOGISTA)
    {
        (*idx_cardio)++;
    }
    if (especialidade == ESP_OFTALMOLOGISTA)
    {
        (*idx_oft)++;
    }
    if (especialidade == ESP_NEUROLOGISTA)
    {
        (*idx_neuro)++;
    }
    
    return status_execucao;
}

void listagem_geral()
{
    printf("\n---------------------------------------------------------------------------------------------------------\n");
    printf("        Clinica Vida e Saude\n");
    printf("-----------------------------------------------------------------------------------------------------------\n");
    printf("\n\nListagem Geral");
    printf("\n\n-------------------------------------------------------------------------------------------------------");
    printf("\n\tNome\t\t\tSexo\t       Idade\tEspecialidade\tConveniado\tValor Tratamento");
    printf("\n---------------------------------------------------------------------------------------------------------\n");
    printar_dados_do_csv();
    printf("\n\nTecle enter para voltar ao menu...\n");
}


void relatorio(int qtd_homens_conveniados, int qtd_idosas, float pct_mulheres_cardio, float media_valor_consulta_homens, char especialidade_nome[200])
{
    printf("-----------------------------------------------------------------------------\n");
    printf("        Clínica Vida e Saúde\n");
    printf("-----------------------------------------------------------------------------\n");
    printf("\n\nRelatório Estatístico");
    printf("\n\n-------------------------------------------------------------------------");
    printf("\nQuantidade de homens que trabalham em empresas conveniadas: %d",qtd_homens_conveniados);
    printf("\nQuantidade de mulheres com mais de 60 anos................: %d",qtd_idosas);
    printf("\nPercentual de mulheres que foram ao cardiologista.........: %.2f  %%",pct_mulheres_cardio);
    printf("\nMédia de valor das consultas dos homens...................: R$ %.2f",media_valor_consulta_homens);
    printf("\nEspecialidade que atendeu mais pacientes..................: %s",especialidade_nome);
    printf("\n\n-----------------------------------------------------------------------------\n");
    printf("tecle enter para voltar ao menu principal...\n");
}

void main()
{
    int especialidade_mais_requisitada[4] = {0,0,0,0};
    int index_maior_valor = 0;
    int qtd_homens_conveniados = 0;
    int qtd_idosas             = 0;
    float qtd_mulheres_cardio    = 0;
    float qtd_mulheres_total     = 0;
    int qtd_homens_total       = 0;
    char especialidade_nome[200];
    
    int exec_cadatro           = 0;

    int acm_clin_geral         = 0;
    int acm_cardio             = 0;
    int acm_oftalmo            = 0;
    int acm_neuro              = 0;

    float pct_mulheres_cardio  = 0;
    float media_valor_consulta_homens = 0;
    float acm_valor_consulta   = 0;
    int status_execucao = ON;

    do{
    print_menu();
    scanf("%d",&status_execucao);

    switch(status_execucao)
    {
    case CADASTRAR_PACIENTE:
        //chama funcao de cadastro
        do
        {
        exec_cadatro = cadastro_paciente(&qtd_homens_conveniados,&qtd_idosas,&qtd_mulheres_cardio,&qtd_mulheres_total,&qtd_homens_total,
                             &especialidade_mais_requisitada[0],&especialidade_mais_requisitada[1],
                             &especialidade_mais_requisitada[2],&especialidade_mais_requisitada[3],&acm_valor_consulta);
        }
        while(exec_cadatro != OFF);
        break;
    case LISTAGEM_GERAL:
        //chama funcao de listagem geral
        listagem_geral();

        break;
    case RELATORIO_ESTATISTICO:
        //chama funcao de relatorio
        if (qtd_mulheres_total == 0)
        {
            pct_mulheres_cardio = 0;
        }
        else{
          pct_mulheres_cardio = qtd_mulheres_cardio/qtd_mulheres_total;  
        }
        
         //media valor consulta homem
        if (qtd_homens_total == 0)
        {
            media_valor_consulta_homens = 0;
        }
        else
        {
        media_valor_consulta_homens = acm_valor_consulta/qtd_homens_total;
        }
        
        
        //especialidade mais requisitada
        index_maior_valor = encontrar_maior_valor(especialidade_mais_requisitada);
        
        if (index_maior_valor == 0)
        {
            memcpy(especialidade_nome,"Clinica Geral",14);
        }
        
        else if (index_maior_valor == 1)
        {
            memcpy(especialidade_nome,"Cardiologista",14);
        }
        
        else if (index_maior_valor == 2)
        {
            memcpy(especialidade_nome,"Oftalmologista",15);
        }
        
        else if (index_maior_valor == 3)
        {
            memcpy(especialidade_nome,"Neurologista",13);
        }
        
        relatorio(qtd_homens_conveniados,qtd_idosas,pct_mulheres_cardio,media_valor_consulta_homens,especialidade_nome);
        break;
    case OFF:
        break;
    }
    }
    while(status_execucao != OFF);

}
