#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <windows.h>

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
        return;
    }
    novo->id = id;
    strcpy(novo->nome, nome);
    novo->idade = idade;
    novo->salario = salario;

    return novo;
} 



//Recebe as informações para o campo Funcionário e adiciona na lista;
void adicionar_na_lista(Funcionario **cabeça, int id, char nome[], int idade, float salario){

    //chama função para criação do registro com os dados recebidos
    Funcionario *func = cadastrar_funcionario(id, nome, idade, salario);
    
    if (func == NULL) return; 

    Funcionario *atual = *cabeça;

    while (atual->proximo != NULL){
        atual = atual->proximo;
    }

    atual->proximo = func;
    
}



void buscar_funcionarioID(Funcionario **cabeça, int id){
    
    if (cabeça == NULL){
        printf("Nenhum funcionário cadastrado.\n");
        return;
    }

    Funcionario *atual = *cabeça;
    while(atual->id != id){
        atual = atual->proximo;
    }

    if(atual == NULL){
        printf("Funcionário com ID %d não encontrado.\n", id);
        return;
    }

    //seria interessante criar uma função só pra exibir essas informações não é??
    printf("\n---------------------FUNCIONÁRIO ID %d-----------------------\n", id);
    printf("NOME : %s\n", atual->nome);
    printf("IDADE : %d\n", atual->idade);
    printf("SALÁRIO : %.2f\n", atual->salario);
    printf("-------------------------------------------------------------\n");
}



void exibir_todos(Funcionario **cabeça){
    if (cabeça == NULL){
        printf("Nenhum funcionário cadastrado.\n");
        return;
    }

    Funcionario *atual = *cabeça;

    //Aqui é usado o "for", mas também poderia ser um "while"

    for (atual; atual != NULL; atual = atual->proximo){
        printf("---------------------FUNCIONÁRIO ID %d-----------------------\n", atual->id);
        printf("NOME : %s\n", atual->nome);
        printf("IDADE : %d\n", atual->idade);
        printf("SALÁRIO : %.2f\n", atual->salario);
        printf("-------------------------------------------------------------\n");
    }
}


//Limpa a lista e libera as memórias que estavam alocadas
void limpar_lista(int **cabeça){
    Funcionario *atual = *cabeça;

    while(atual != NULL){
        Funcionario *limpar = atual;
        atual = atual->proximo;
        free(limpar);
    }
}


void remover_funcionario(Funcionario **cabeça, int id) {
    Funcionario *atual = *cabeça;
    Funcionario *anterior = NULL;
    
    while(atual->id != id){
        anterior = atual;
        atual = atual->proximo;
    }

    //caso não encontre funcionário
    if(atual == NULL){
        printf("Funcionário com ID %d não encontrado\n", id);
        return;
    }

    anterior->proximo = atual->proximo;



    free(atual);
}


// Criação do arquivo CSV
void criar_csv(Funcionario vet[], int quant, char *nome_arquivo){
    int k;

    FILE *csv = fopen(nome_arquivo, "w");

    if (csv == NULL){   //Caso dê erro ao criar arquivo
        printf("Erro ao criar arquivo");
        return;
    }

    fprintf(csv, "id,nome,salario,idade\n");  //cabeçalho do CSV

    for(k = 0; k < quant; k++){  //Preenchimento do arquivo
        fprintf(csv, "%d,%s,%.2f,%d\n", vet[k].id, vet[k].nome, vet[k].salario, vet[k].idade);
    }

    fclose(csv);
    printf("Arquivo criado com sucesso\n");
}



int main(){

    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
    Funcionario vetor;
    char action, arquivo_csv[100] = "registros_funcionarios.csv";

    int id_cad, idade_cad;
    char nome_cad[TOTAL];
    float salario_cad;

    limpar_lista(&cadastrados);

    printf("----------Bem vindo----------\n\n");

    while(1){
        printf("\nDigite o número correspondente para qual operação deseja realizar:\n1 - Adicionar registro\n2 - Remover registro\n3 - Buscar registro\n4 - Exibir todos os registros\n5 - Criar arquivo CSV\n6+ - Sair do programa\n");
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

            adicionar_na_lista(vetor, &cadastrados, id_cad, nome_cad, idade_cad, salario_cad);
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

        case '5':
            criar_csv(vetor, cadastrados, &arquivo_csv);
            break;

        default:
            printf("\nSaindo do programa...\n");
            return 0;
        }
    }
}