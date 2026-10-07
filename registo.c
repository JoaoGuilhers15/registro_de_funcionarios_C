#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <windows.h>

#define TOTAL 50
#define MAX 15

typedef struct funcionario
{
    int id;
    char nome[TOTAL];
    float salario;
    int idade;
} Funcionario;


void criar_csv(Funcionario vet[], int quant, char *nome_arquivo){

    FILE *csv = fopen(nome_arquivo, "w");

    if (csv == NULL){
        printf("Erro ao criar arquivo");
        return;
    }

    fprintf("id,nome,salario,idade\n");




}




void adicionar_funcionario(Funcionario vet[], int *cadastro, int id, char nome[], int idade, float salario){
    if (*cadastro >= MAX){
        printf("Vetor cheio! Não é possível adicionar mais funcionários.\n");
        return;
    }
    vet[*cadastro].id = id;
    strcpy(vet[*cadastro].nome, nome);
    vet[*cadastro].idade = idade;
    vet[*cadastro].salario = salario;
    (*cadastro)++;
}

void buscar_funcionarioID(Funcionario vet[], int cadastrados, int id){
    int k = 0;
    while (k < cadastrados && vet[k].id != id){
        k++;
    }
    if (k == cadastrados) {
        printf("Funcionário com ID %d não encontrado.\n", id);
        return;
    }
    printf("---------------------FUNCIONÁRIO ID %d-----------------------\n", id);
    printf("NOME : %s\n", vet[k].nome);
    printf("IDADE : %d\n", vet[k].idade);
    printf("SALÁRIO : %.2f\n", vet[k].salario);
    printf("-------------------------------------------------------------");
}

void exibir_todos(Funcionario vet[], int cadastrados){
    if (cadastrados == 0){
        printf("Nenhum funcionário cadastrado.\n");
        return;
    }
    for (int i = 0; i < cadastrados; i++){
        printf("---------------------FUNCIONÁRIO ID %d-----------------------\n", vet[i].id);
        printf("NOME : %s\n", vet[i].nome);
        printf("IDADE : %d\n", vet[i].idade);
        printf("SALÁRIO : %.2f\n", vet[i].salario);
        printf("-------------------------------------------------------------");
    }
}

void zerar_vetor(int *total){
    *total = 0;
}

void remover_funcionario(Funcionario vet[], int *cadastro, int id) {
    int k = 0;

    while(k < *cadastro && vet[k].id != id){
        k++;
    }

    //caso não encontre funcionário
    if(k == *cadastro){
        printf("Funcionário com ID %d não encontrado\n", id);
        return;
    }
    //remoção do cadastro informado e "empurrando" os demais para o início da lista
    for(int i = k; i < *cadastro - 1; i++){
        vet[i] = vet[i + 1];
    }
    //subtrai 1 no número de cadastrados
    (*cadastro)--;
    printf("Funcionário com ID %d removido com sucesso\n", id);
}

int main(){

    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
    Funcionario vetor[MAX];
    int cadastrados;
    char action;

    int id_cad, idade_cad;
    char nome_cad[TOTAL];
    float salario_cad;

    zerar_vetor(&cadastrados);

    printf("----------Bem vindo----------\n\n");

    while(1){
        printf("\nDigite o número correspondente para qual operação deseja realizar:\n1 - Adicionar registro\n2 - Remover registro\n3 - Buscar registro\n4 - Exibir todos os registros\n5+ - Sair\n");
        scanf(" %c", &action);
        switch (action)
        {
        case '1':
            printf("\nDigite o ID do funcionário: ");
            scanf("%d", &id_cad);

            printf("Digite o Nome do funcionário: ");
            scanf(" %[^\n]", nome_cad);

            printf("Digite a idade do funcionário: ");
            scanf("%d", &idade_cad); 

            printf("Digite o salário do funcionário: ");
            scanf("%f", &salario_cad);

            adicionar_funcionario(vetor, &cadastrados, id_cad, nome_cad, idade_cad, salario_cad);
            break;

        case '2':
            printf("\nDigite o ID do funcionário que deseja remover: ");
            scanf("%d", &id_cad);
            remover_funcionario(vetor, &cadastrados, id_cad);
            
            break;

        case '3':
            printf("\nDigite o id do funcionário: ");
            scanf("%d", &id_cad);
            buscar_funcionarioID(vetor, cadastrados, id_cad);
            break;

        case '4':
            exibir_todos(vetor, cadastrados);
            break;

        default:
            printf("\nSaindo do programa...\n");
            return 0;
        }
    }
}