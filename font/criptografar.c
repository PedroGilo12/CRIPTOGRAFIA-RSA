#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define DEBUG 1

void Debug(char msg[]) {
    if(DEBUG) {
        printf("%s\n", msg);
    }

    return;
}

int chave_publica(char nome_arquivo[], unsigned long int key[]) {

    Debug("Abrindo arquivo da chave publica...");

    FILE * arquivo = fopen(nome_arquivo, "r");

    if(arquivo != NULL) {

        Debug("Arquivo aberto com sucesso!!");

        char key1[1000];
        char key2[1000];

        fgets(key1, 1000, arquivo);
        fgets(key2, 1000, arquivo);

        key[0] = atoi(key1);
        key[1] = atoi(key2);

        fclose(arquivo);

        return 1;
    } else {

        Debug("Não foi possível abrir o arquivo!!\n");
        return 0;
    }
}

double modPow(double base, double exponent, double modulus) {
    double result = 1;
    while (exponent > 0) {
        if (fmod(exponent, 2) == 1) {
            result = fmod(result * base, modulus);
        }
        base = fmod(base * base, modulus);
        exponent = floor(exponent / 2);
    }
    return result;
}

int criptografar_arquivo(char arquivo_origem[], char arquivo_destino[],unsigned long int key[]) {

    Debug("Abrindo arquivo para ser criptografado...");

    FILE * arquivo = fopen(arquivo_origem, "r");
    FILE * arquivo_cript = fopen(arquivo_destino, "w");
    char c;

    if(arquivo != NULL) {

        Debug("Arquivo criptografado com sucesso!!");

        while(c != EOF) {
            c = fgetc(arquivo);
            if(c != -1) {
                printf("Caracter: %d\n", c);
                double c_int = c;

                if(c != 32){
                    c_int = c - 63;      
                } else {
                    c_int = c - 4;
                }

                int caracter_criptografado = modPow(c_int, key[0], key[1]);

                fprintf(arquivo_cript, "%d ", caracter_criptografado);
            }
        }

        fclose(arquivo_cript);

        return 1;
    } else {

        Debug("Não foi possível abrir o arquivo!!\n");
        return 0;
    } 

}

int main() {

    char debug[100];
    unsigned long int key[2];
    chave_publica("key_pub.txt", key);

    sprintf(debug, "Chave publica: %ld %ld ", key[0], key[1]);
    Debug(debug);

    criptografar_arquivo("InputFile.tmp", "OutputFile.tmp",key);

}