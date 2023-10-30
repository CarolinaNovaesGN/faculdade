#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>

#define MAX_VAGAS 10

#define OP_MARCAR 1
#define OP_DESMARCAR 2
#define OP_LISTAGEM 3

struct Usuario
{
    int rg;
    char nome[200];
    int idade;
    char email[200]
};

struct Usuario marcados[MAX_VAGAS];
struct Usuario filaDeEspera[MAX_VAGAS];

int vagas = MAX_VAGAS;
int usuariosFilaEspera = 0;

int validacaoIdade(int idade)
{
    while(idade < 0 || idade > 120)
    {
        printf("Idade invalia. Digite uma idade valida.");
        scanf("%d",&idade);
    }
    return idade;
}

void menu()
{
    printf("\nPosto de Vacinacao\n");
    printf("--------------------------------------------\n");
    printf("Opcoes:\n\n");
    printf("   1- Marcar vacina\n\n");
    printf("   2- Desmarcar vacina\n\n");
    printf("   3- Listagem geral\n\n");
    printf("   0- Sair do programa\n\n");
    printf("--------------------------------------------\n");
    printf("Informe a opcao desejada: ");


}

void cadastro()
{
    int entrada = 1;
    while (entrada == 1)
    {
        if(vagas>0)
        {
            struct Usuario novoUsuario;
            printf("\nPosto de Vacinacao\n");
            printf("--------------------------------------------\n");
            printf("Marcar Vacinacao:\n\n\n");
            printf("RG: ");
            scanf("%d",&novoUsuario.rg);
            printf("Nome: ");
            scanf("%s",&novoUsuario.nome);
            printf("Idade: ");
            scanf("%d",&novoUsuario.idade);
            novoUsuario.idade = validacaoIdade(novoUsuario.idade);
            printf("E-mail: ");
            scanf("%s",&novoUsuario.email);

            marcados[MAX_VAGAS - vagas] = novoUsuario;
            vagas--;

            printf("Vacinacao marcada com Sucesso!\n\n\n");
            printf("\n\nFazer outra marcacao(1-sim/0-nao)");
            scanf("%d",&entrada);
            while(entrada != 1 && entrada != 0)
            {
                printf("\n\nOpcao invalida. Digite um numero valido. ");
                scanf("%i",&entrada);
            }

        } else if (usuariosFilaEspera < MAX_VAGAS)
        {
            struct Usuario novoUsuario;
            printf("Nao ha mais vagas para vacinacao!\nDeseja ser inserido na fila de espera(1-sim/0-nao)?");
            scanf("%d", &entrada);
            if(entrada==1)
            {
                printf("\nPosto de Vacinacao\n");
                printf("--------------------------------------------\n");
                printf("Marcar Vacinacao:\n\n\n");
                printf("RG: ");
                scanf("%d",&novoUsuario.rg);
                printf("Nome: ");
                scanf("%s",&novoUsuario.nome);
                printf("Idade: ");
                scanf("%d",&novoUsuario.idade);
                novoUsuario.idade = validacaoIdade(novoUsuario.idade);
                printf("E-mail: ");
                scanf("%s",&novoUsuario.email);

                filaDeEspera[usuariosFilaEspera] = novoUsuario;
                usuariosFilaEspera++;
                printf("Voce foi inserido na fila de espera. Tem %d pessoas na sua frente! \n\n\n", usuariosFilaEspera-1);
                printf("\n\nFazer outra marcacao(1-sim/0-nao)");
                scanf("%d",&entrada);
                while(entrada != 1 && entrada != 0)
                {
                    printf("\n\nOpcao invalida. Digite um numero valido. ");
                    scanf("%d",&entrada);
                }
            }
            else{
                printf("Vacinacao nao foi marcada.\n\n");
            }

            } else{
            printf("Vacinacao nao foi marcada. Nao ha vagas para agendamento da vacinacao nem para fila de espera.\n");
        }
        printf("Pressione qualquer tecla para continuar.");
        getchar();
        system("cls");
    }
}

void desmarcacao()
{
    int entrada = 1;
    while(entrada == 1)
    {
        int rg;
        int entrada;
        char nome[200];
        int idade;
        char email[200];

        printf("\nPosto de Vacinacao\n");
        printf("--------------------------------------------\n");
        printf("Informe o RG do cancelamento:\n\n\n");
        scanf("%d", &rg);

        for(int i = 0; i< MAX_VAGAS; i++)
        {
            if(marcados[i].rg == rg)
            {
                vagas++;
                strcpy(nome, marcados[i].nome);
                idade = marcados[i].idade;
                strcpy(email, marcados[i].email);

                printf("RG     Nome                            Idade    e-mail\n");
                printf("-------------------------------------------------------------\n");
                printf("%d     %s                               %d       %s\n",rg,nome,idade,email);
                printf("-------------------------------------------------------------\n\n");
                printf("Confirmar desmarcacao (1-sim/0-nao)?\n\n");
                scanf("%d",&entrada);
                if(entrada==1)
                {
                    scanf("Desmarcacao realizada com sucesso!\n");
                    if(usuariosFilaEspera > 0)
                {
                    marcados[MAX_VAGAS - vagas] = filaDeEspera[0];
                    for(int j=0; j < usuariosFilaEspera - 1; j++)
                    {
                        filaDeEspera[j] = filaDeEspera[j+1];
                    }
                usuariosFilaEspera--;
                }
                }
                else{
                    printf("Nenhum paciente foi desmarcado.\n");
                    break;
                }
            }
        }
        printf("Desmarcar outro('1-sim/0-nao)?");
        scanf("%d",&entrada);
        while(entrada != 0 && entrada != 1)
        {
            printf("Opcao invalida. Digite um numero valido.");
            scanf("%d",&entrada);
        }

    }
    printf("Pressione qualquer tecla para continuar.");
    getchar();
    system("cls");
}

void listagemGeral() {
    printf("\nPosto de Vacinacao\n");
    printf("--------------------------------------------\n");
    printf("Listagem Geral:\n\n\n");
    printf("Relacao de pacientes confirmados:\n\n");
    printf("RG     Nome                            Idade    e-mail\n");
    printf("-------------------------------------------------------------\n");
    for (int i = 0; i < MAX_VAGAS - vagas; i++) {
        printf("%d     %s                            %d    %s\n", marcados[i].rg, marcados[i].nome, marcados[i].idade, marcados[i].email);
    }
    printf("\n");

    printf("Relacao dos pacientes na fila de espera:\n");
    printf("RG     Nome                            Idade    e-mail\n");
    printf("-------------------------------------------------------------\n");
    for (int i = 0; i < usuariosFilaEspera; i++) {
        printf("%d     %s                            %d    %s\n", filaDeEspera[i].rg, filaDeEspera[i].nome, filaDeEspera[i].idade, filaDeEspera[i].email);
    }
}

int main()
{
    int entrada = 11;
    while(entrada != 0)
    {
        menu();
        scanf("%d",&entrada);
        switch(entrada)
        {
            case OP_MARCAR:
                cadastro();
                break;
            case OP_DESMARCAR:
                desmarcacao();
                break;
            case OP_LISTAGEM:
                listagemGeral();
                break;
            case 0:
                break;
            default:
                printf("Opcao invalida. Digite um numero valido.\n");

        }
    }
    return 0;
}
