
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Encomenda {
    char Codigo[9];
    char Destinatario[50];
    char Destino[50];
    char DatadeEnvio[11];
    char Transportadora[50];
};


void NovaEncomenda(Encomenda encomenda){
    File *arquivo = fopen("encomendas.txt", "a");
        if(arquivo==Null){
            printf("Erro ao abrir o arquivo. \n");
            return;
        }
        
        fprint(arquivo, "%s,%s,%s,%s,%s\n", encomenda.Codigo, encomenda.Destinatario, encomenda.Destino, encomenda.DatadeEnvio, encomenda.Transportadora);
        fclose(arquivo);
        printf("Pacote registrado!.\n");
}


int main(){



    return 0;
}  
