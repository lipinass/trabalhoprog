#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct Encomenda {
    char Codigo[20];
    char Destinatario[120];
    char Destino[50];
    char DatadeEnvio[11];
    char Transportadora[50];
};

struct Status {
    char Codigo[20];
    char localidade[50];
    char Status[50];
    char data_hora[30];
    char previsao[11]; 
};

void NovaEncomenda(struct Encomenda encomenda) {
    FILE *arquivo = fopen("encomendas.txt", "a");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de encomendas.\n");
        return;
    }

    fprintf(arquivo, "%s,%s,%s,%s,%s\n", encomenda.Codigo, encomenda.Destinatario, encomenda.Destino, encomenda.DatadeEnvio, encomenda.Transportadora);
    fclose(arquivo);
    printf("Pacote registrado!\n");
}

void atualizar_status(struct Status status) {
    FILE *arquivo = fopen("logs.txt", "a");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de log.\n");
        return;
    }

    fprintf(arquivo, "%s,%s,%s,%s,%s\n", status.Codigo, status.localidade, status.Status, status.data_hora, status.previsao);
    fclose(arquivo);
    printf("Status atualizado com sucesso.\n");
}

void buscar_status(char *codigo_rastreamento) {
    FILE *arquivo = fopen("logs.txt", "r");
    if (arquivo == NULL) {
        printf("Erro: O arquivo de logs não foi encontrado. Registre um status antes de realizar uma busca.\n");
        return;
    }

    struct Status status;
    int encontrado = 0;
    while (fscanf(arquivo, "%[^,],%[^,],%[^,],%[^,],%[^\n]\n", status.Codigo, status.localidade, status.Status, status.data_hora, status.previsao) != EOF) {
        if (strcmp(status.Codigo, codigo_rastreamento) == 0) {
            printf("\n-------------------------------------");
            printf("\nData e Hora: %s\n", status.data_hora);
            printf("-------------------------------------");
            printf("\nCodigo de rastreamento: %s\n", status.Codigo);
            printf("Localizacao: %s\n", status.localidade);
            printf("Status: %s\n", status.Status);
            printf("Previsao de entrega: %s\n\n", status.previsao);
            
            encontrado = 1;
        }
    }

    if (!encontrado) {
        printf("Encomenda com o código de rastreamento %s nao encontrada.\n", codigo_rastreamento);
    }

    fclose(arquivo);
}

int main() {
    int opcao;
    struct Encomenda encomenda;
    struct Status status;
    char Codigo[20];

    while (1) {
        printf("\n/------- Sistema de Rastreamento -------/\n");
        printf("1. Registrar novo pacote.\n");
        printf("2. Atualizar status do pacote.\n");
        printf("3. Rastrear pacote.\n");
        printf("4. Sair.\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar(); 

        switch (opcao) {
            case 1:
                printf("\nDigite o codigo de rastreamento do pacote: \n");
                fgets(encomenda.Codigo, 20, stdin);
                encomenda.Codigo[strcspn(encomenda.Codigo, "\n")] = '\0';

                printf("\nDigite o destinatario: \n");
                fgets(encomenda.Destinatario, 50, stdin);
                encomenda.Destinatario[strcspn(encomenda.Destinatario, "\n")] = '\0';

                printf("\nDigite o destino: \n");
                fgets(encomenda.Destino, 120, stdin);
                encomenda.Destino[strcspn(encomenda.Destino, "\n")] = '\0';

                printf("\nDigite a data de envio (ddmmaaaa): \n");
                fgets(encomenda.DatadeEnvio, 20, stdin);
                encomenda.DatadeEnvio[strcspn(encomenda.DatadeEnvio, "\n")] = '\0';

                printf("\nDigite o nome da transportadora: \n");
                fgets(encomenda.Transportadora, 50, stdin);
                encomenda.Transportadora[strcspn(encomenda.Transportadora, "\n")] = '\0';

                NovaEncomenda(encomenda);
                break;

case 2:
    printf("\nDigite o codigo de rastreamento do pacote: \n");
    fgets(status.Codigo, 20, stdin);
    status.Codigo[strcspn(status.Codigo, "\n")] = '\0';

    printf("\nDigite a localizacao atual do pacote: \n");
    fgets(status.localidade, 50, stdin);
    status.localidade[strcspn(status.localidade, "\n")] = '\0';

    printf("\nEscolha o status do pacote:\n");
    printf("1. Em separacao\n");
    printf("2. Enviado\n");
    printf("3. Em rota de entrega\n");
    printf("4. Entregue\n");
    int escolha_status;
    scanf("%d", &escolha_status);
    getchar(); 


    if (escolha_status == 1) {
        sprintf(status.Status, "Em separacao");
    } else if (escolha_status == 2) {
        sprintf(status.Status, "Enviado");
    } else if (escolha_status == 3) {
        sprintf(status.Status, "Em rota de entrega");
    } else if (escolha_status == 4) {
        sprintf(status.Status, "Entregue");
    } else {
        printf("Opção inválida. Status definido como 'Indefinido'.\n");
        sprintf(status.Status, "Indefinido");
    }

    printf("\nDigite a data e hora do status (dd/mm/aaaa hhmm): \n");
    fgets(status.data_hora, 20, stdin);
    status.data_hora[strcspn(status.data_hora, "\n")] = '\0';

    printf("\nDigite a previsao de entrega (dd/mm/aaaa): \n");
    fgets(status.previsao, 20, stdin);
    status.previsao[strcspn(status.previsao, "\n")] = '\0';

    atualizar_status(status);
    break;

    printf("\nDigite a data e hora do status (ddmmaaaa hhmm): \n");
    fgets(status.data_hora, 20, stdin);
    status.data_hora[strcspn(status.data_hora, "\n")] = '\0';

    printf("\nDigite a previsao de entrega (dd/mm/aaaa): \n");
    fgets(status.previsao, 20, stdin);
    status.previsao[strcspn(status.previsao, "\n")] = '\0';

    atualizar_status(status);
    break;
            case 3:
                printf("\nDigite o codigo de rastreamento da sua encomenda: \n");
                fgets(Codigo, 24, stdin);
                Codigo[strcspn(Codigo, "\n")] = '\0';

                buscar_status(Codigo);
                break;

            case 4:
                printf("\nSaindo do sistema.\n");
                exit(0);

            default:
                printf("\nOpcao invalida, tente novamente.\n");
        }
    }

    return 0;
}
