#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

// Função para salvar o arquivo com a chave pública
int salvar(unsigned int n, unsigned int e, char arquivo[])
{
    FILE * numeros = fopen(arquivo, "w");
    fprintf(numeros, "%d\n%d\n", e, n);
    fclose(numeros);
}

// Função para calcular o MDC entre dois numeros
unsigned int mod(unsigned int a, unsigned int d) {
    unsigned int q = a/d;
    unsigned int r = a%d;

    if(r == 0) {
        return d;
    }
    unsigned int mdc = mod(d, r);

    return mdc;
}

// Função para checar se um numero é primo
int eprimo(unsigned int p) {
    if (p == 2) {
        return 1;
    }
    if (p < 2 || p % 2 == 0) {
        return 0;
    }
    for (int i = 3; i <= sqrt(p); i += 2) {
        if (p % i == 0) {
            return 0;
        }
    }
    return 1;
}

// Função para checar se o numero "e" é coprimo de phi(N)
double gerare(unsigned int p, unsigned int q, unsigned int e) {
    unsigned int phin = (p-1)*(q-1);
    
    printf("mdc entre '%d' e '%d': %d\n", e, phin, mod(e, phin));

    if(eprimo(e) && (mod(e, phin) == 1)) {
        return e;
    } else {
        return 0;
    }
}

// Função para gerar o N = p*q
unsigned int gerarn(unsigned int p, unsigned int q) //gerando o primeiro numero da chave publica.
{
    unsigned int n = (p) * (q);

    return n;
}

int main () //funcao que recebe as entradas e as envia para teste, se aprovadas o codigo continua.
{

    unsigned int p, q, e;

    scanf("%d%d%d", &p, &q, &e);

    printf("Gerando chave publica...\n p: %d, q: %d, e: %d\n", p, q, e);

    // Cadeia de decisão que verifica se os numeros  p, q e e são válidos
    if(eprimo(p))
    {

        if(eprimo(q))
        {

            int resultn = gerarn(p, q);

            unsigned int casoe = gerare(p, q, e);

            if(casoe == 0)
            {
                salvar(-1, -1, "key_pub.txt");
                printf("Erro\n");

            }
            else
            {
                salvar(resultn, casoe, "key_pub.txt");

                printf("Chave publica: n: %d e: %d\n", resultn, casoe);
            }

        }

        else
        {
            salvar(-1, -1, "key_pub.txt");
            printf("Erro\n");
        }


    } 
    else
    {
        salvar(-1, -1, "key_pub.txt");
        printf("Erro\n");
    }

    printf("O Codigo terminou\n");

    return 0;
}