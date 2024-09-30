#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 300
FILE *pArquivo;


int escreverExercicio1(int pares, int impares, int negativos, int positivos, int zero) {
    FILE *arquivo = fopen("Estatisticas.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }
    fprintf(arquivo, "Números pares: %d\n", pares);
    fprintf(arquivo, "Números ímpares: %d\n", impares);
    fprintf(arquivo, "Números positivos: %d\n", positivos);
    fprintf(arquivo, "Números negativos: %d\n", negativos);
    fprintf(arquivo, "Números iguais a zero: %d\n", zero);
    fclose(arquivo);
    printf("Sucesso ao escrever no arquivo.\n");
}

void exercicio1(int vetor [], int tamanho) {
    int pares = 0;
    int impares = 0;
    int negativos = 0;
    int positivos = 0;
    int zero = 0;
  for(int i = 0; i < tamanho; i++) {
    /* Pares e Ímpares */
    if(vetor[i] % 2 == 0) {
      pares += 1;
    } else {
      impares += 1;
    }
    /* Positivos e Negativos */
    if (vetor[i] > 0) {
      positivos += 1;
    } else if (vetor[i] < 0) {
      negativos += 1;
    /* Iguais a zero */
    } else {
      zero += 1;
    }
  }
  escreverExercicio1(pares, impares, negativos, positivos, zero);
}


int exercicio2(int vetor[], int tamanho, int vetordistintos[]) {
  int tamanhodistintos = 0;
  for (int i = 0; i < tamanho; i++) {
      int repetido = 0;
      for (int j = 0; j < tamanhodistintos; j++) {
          if (vetor[i] == vetordistintos[j]) {
              repetido = 1;
              break;
          }
      }
      if (!repetido) {
          vetordistintos[tamanhodistintos] = vetor[i];
          tamanhodistintos++;
      }
  }
  return tamanhodistintos;
}

int escreverExercicio2(int vetordistintos[], int tamanhodistintos) {
    FILE *arquivo = fopen("Distintos.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }
    fprintf(arquivo, "Números distintos: ");
    for (int i = 0; i < tamanhodistintos; i++) {
        fprintf(arquivo, "%d ", vetordistintos[i]);
    }
    fprintf(arquivo, "\n");

    fclose(arquivo);
    printf("Sucesso ao escrever no arquivo.\n");
}


void exercicio3(int vetor[], int tamanho) {
    int aux;
    for (int i = 0; i < tamanho - 1; i++) {
        for (int j = 0; j < tamanho - i - 1; j++) {
            if (vetor[j] > vetor[j + 1]) {
                aux = vetor[j];
                vetor[j] = vetor[j + 1];
                vetor[j + 1] = aux;
            }
        }
    }
}

int escreverexercicio3(int vetorordenados[], int tamanhoordenados){
    FILE *arquivo = fopen("Ordenados.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }
    fprintf(arquivo, "Números em ordem não descrescente: ");
    for (int i = 0; i < tamanhoordenados; i++) {
        fprintf(arquivo, "%d ", vetorordenados[i]);
    }
    fprintf(arquivo, "\n");

    fclose(arquivo);
    printf("Sucesso ao escrever no arquivo.\n");
}

int escreverexercicio4(int vetordistintosordenados[], int tamanhodistintosordenados) {
    FILE *arquivo = fopen("Distintos_ordenados.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }
    fprintf(arquivo, "Números distintos em ordem crescente: ");
    for (int i = 0; i < tamanhodistintosordenados; i++) {
        fprintf(arquivo, "%d ", vetordistintosordenados[i]);
    }
    fprintf(arquivo, "\n");

    fclose(arquivo);
    printf("Sucesso ao escrever no arquivo.\n");
}


int *formatar(char array[], size_t *tamanho){
    short real_Size = 0; char *token; short capacidade = 3;
    int *novo_Vetor = (int *) malloc(capacidade * sizeof(int));
    //Separa a string em segmentos, separados por espaço
    token = strtok(array, " ");
    do{
        if (real_Size == capacidade){
            capacidade++;
            novo_Vetor = (int *) realloc(novo_Vetor, capacidade * sizeof(int));
            if(novo_Vetor == 0) {printf("Erro na alocação de memória"); exit(0);}
        }
        novo_Vetor[real_Size++] = atoi(token);
    } while (token = strtok(NULL, " "));

    *tamanho = real_Size; // Atualiza a variável que possuirá o novo tamanho do vetor
    return novo_Vetor;
}


int main(){

    //Vetor que guardará os números para fazer a operações, com o tamnho de caracteres que tem no arquivo
    char vetor[MAX];
    //Variável para guardar quantos números tem no arquivo, fornecido pelo arquivo
    int numero;
    //Abre o arquivo
    pArquivo = fopen("dados.txt", "r");

    if (pArquivo == NULL) { printf("Falha na leitura do arquivo."); return 1;} // Caso não consiga ler o arquivo

    //ler o arquivo
    fscanf(pArquivo, "%d\n", &numero);
    fscanf(pArquivo, "%[^\n]s", &vetor);

    //Fecha arquivo
    fclose(pArquivo);
    short contador = 0;
    for(int i = 0; vetor[i] != '\0'; vetor[i++]){
        contador++;
    }

    if(contador > MAX) { printf("O limite do vetor foi ultrapassado."); return 1;}
    
    size_t valor_Formatado;// tamanho do vetor formatado
    int *vetor_Formatado = formatar(vetor, &valor_Formatado); // Formata a string em um vetor tipo int
    
    //Caso o número informado não corresponda
    if(numero != valor_Formatado){
        printf("Valor informado no arquivo incorreto.\n");
        free(vetor_Formatado);
        return 1;
    }

    int vetordistintos[valor_Formatado];
    int tamanhodistintos = 0;
    int vetorordenados[valor_Formatado];
    int tamanhoordenados = valor_Formatado;
    int vetordistintosordenados[valor_Formatado];
    int tamanhodistintosordenados = 0;
   

    /* Chamando as funções */
    exercicio1(vetor_Formatado, valor_Formatado);

    tamanhodistintos = exercicio2(vetor_Formatado, valor_Formatado, vetordistintos);

    for (int i = 0; i < valor_Formatado; i++) {
        vetorordenados[i] = vetor_Formatado[i];
    }
    for (int i = 0; i < tamanhodistintos; i++) {
        vetordistintosordenados[i] = vetordistintos[i];
    }

    tamanhodistintosordenados = tamanhodistintos;

    exercicio3(vetorordenados, tamanhoordenados);
    exercicio3(vetordistintosordenados, tamanhodistintosordenados);

    escreverExercicio2(vetordistintos, tamanhodistintos);
    escreverexercicio3(vetorordenados, valor_Formatado);
    escreverexercicio4(vetordistintosordenados, tamanhodistintosordenados);

    // Libera a memória alocada
    free(vetor_Formatado);
    return 0;
}