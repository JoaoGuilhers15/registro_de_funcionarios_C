#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <stdlib.h>

#define TOTAL 50

typedef struct Funcionario
{
    int id;
    char nome[TOTAL];
    float salario;
    int idade;
    struct Funcionario *proximo;
    
} Funcionario;



//Aloca a memória a ser utilzada pelo struct, e preenche os campos do Funcionario
Funcionario* cadastrar_funcionario(int id, char nome[], int idade, float salario){

    Funcionario* novo = malloc(sizeof(Funcionario));
    if (novo == NULL){
        printf("Sem espaço na memória!");
        return NULL;
    }
    novo -> proximo = NULL;
    novo->id = id;
    strcpy(novo->nome, nome);
    novo->idade = idade;
    novo->salario = salario;

    return novo;
} 

void exibir_funcionario(Funcionario *achado){

    printf("\n---------------------FUNCIONÁRIO ID %d-----------------------\n", achado -> id);
    printf("NOME : %s\n", achado->nome);
    printf("IDADE : %d\n", achado->idade);
    printf("SALÁRIO : %.2f\n", achado->salario);
    printf("-------------------------------------------------------------\n");

}

//Recebe as informações para o campo Funcionário e adiciona na lista;
void adicionar_na_lista(Funcionario **cabeca, int id, char nome[], int idade, float salario){

    //chama função para criação do registro com os dados recebidos
    Funcionario *func = cadastrar_funcionario(id, nome, idade, salario);
    
    if (func == NULL) return; 

    if(*cabeca == NULL){
        *cabeca = func;

    }
    else{

        Funcionario *atual = *cabeca;

        while (atual->proximo != NULL){
            atual = atual->proximo;
        }

        atual->proximo = func;
    }
    exibir_funcionario(func);
}

void buscar_funcionarioID(Funcionario **cabeca, int id){
    
    if (*cabeca == NULL){
        printf("Nenhum funcionário cadastrado.\n");
        return;
    }

    Funcionario *atual = *cabeca;
    while(atual != NULL && atual->id != id){
        atual = atual->proximo;
    }

    if(atual == NULL){
        printf("Funcionário com ID %d não encontrado.\n", id);
        return;
    }

    exibir_funcionario(atual);
}



void exibir_todos(Funcionario **cabeca){
    if (*cabeca == NULL){
        printf("Nenhum funcionário cadastrado.\n");
        return;
    }

    Funcionario *atual = *cabeca;

    //Aqui é usado o "for", mas também poderia ser um "while"

    for (atual; atual != NULL; atual = atual->proximo){
        exibir_funcionario(atual);
    }
}


//Limpa a lista e libera as memórias que estavam alocadas
void limpar_lista(Funcionario **cabeca){
    Funcionario *atual = *cabeca;

    while(atual != NULL){
        Funcionario *limpar = atual;
        atual = atual->proximo;
        free(limpar);
    }

    *cabeca = NULL;

    printf("Lista excluida com sucesso!");
}


void remover_funcionario(Funcionario **cabeca, int id) {
    if (*cabeca == NULL){
        printf("Nenhum funcionário cadastrado.\n");
        return;
    }
    
    
    Funcionario *atual = *cabeca;
    Funcionario *anterior = NULL;
    
    while(atual != NULL && atual->id != id){
        anterior = atual;
        atual = atual->proximo;
    }

    //caso não encontre funcionário
    if(atual == NULL){
        printf("Funcionário com ID %d não encontrado\n", id);
        return;
    }
    if(anterior == NULL){
        *cabeca = atual -> proximo;
    }
    else{
        anterior->proximo = atual->proximo;
    }

    free(atual);

    printf("O funcionario de id %d, foi retirado com sucesso!", id);
}


// Criação do arquivo CSV
void criar_csv(Funcionario *cabeca, char *nome_arquivo){
    FILE *csv = fopen(nome_arquivo, "w");

    if (csv == NULL){   //Caso dê erro ao criar arquivo
        printf("Erro ao criar arquivo");
        return;
    }

    fprintf(csv, "id,nome,salario,idade\n");  //cabecalho do CSV

    for(Funcionario *atual = cabeca; atual != NULL; atual = atual -> proximo){  //Preenchimento do arquivo
        fprintf(csv, "%d,%s,%.2f,%d\n", atual -> id, atual -> nome, atual -> salario, atual -> idade);
    }

    fclose(csv);
    printf("Arquivo criado com sucesso\n");
}



int main(){

    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
    Funcionario *cadastro = NULL;
    char action, arquivo_csv[100] = "registros_funcionarios.csv";

    int id_cad, idade_cad;
    char nome_cad[TOTAL];
    float salario_cad;

    printf("-----------------------Bem vindo-----------------------\n\n");

    while(1){
        printf("\nDigite o número correspondente para qual operação deseja realizar:\n1 - Adicionar registro\n2 - Remover registro\n3 - Buscar registro\n4 - Exibir todos os registros\n5 - Criar arquivo CSV\n6 - Limpar lista\n7+ - Sair do programa\n");
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

            adicionar_na_lista(&cadastro, id_cad, nome_cad, idade_cad, salario_cad);
            break;

        case '2':
            printf("\nDigite o ID do funcionário que deseja remover: ");
            scanf("%d", &id_cad);
            remover_funcionario(&cadastro, id_cad);
            
            break;

        case '3':
            printf("\nDigite o id do funcionário: ");
            scanf("%d", &id_cad);
            buscar_funcionarioID(&cadastro, id_cad);
            break;

        case '4':
            exibir_todos(&cadastro);
            break;

        case '5':
            criar_csv(cadastro, arquivo_csv);
            break;

        case '6':
            limpar_lista(&cadastro);
            break;
        default:
            printf("\nSaindo do programa...\n");

            limpar_lista(&cadastro);

            return 0;
        }
    }
}