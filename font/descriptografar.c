#include <stdio.h>
#include <math.h>

// Algoritmo de euclides extendido
double ocl(double phi_n, double b, double *x, double *y) 
{
    if (phi_n == 0) 
    {
        *x = 0;
        *y = 1;
        return b;
    }
 
    double x1, y1;
    double cl = ocl(fmod(b, phi_n), phi_n, &x1, &y1);
 
    *x = y1 - floor(b / phi_n) * x1;
    *y = x1;
 
    return cl;
}

// Calcula o inverso modular de dois numeros (D*E)mod(N)
double inversoMod(double phi_n, double e) // inversoMod = inverso modular
{
    double x, y;
    double cl = ocl(phi_n, e, &x, &y); // cl = congruencia linear && ocl = operação da congruencia linear

    if (cl != 1) 
    {
        return -1;
    }
    else 
    {
        double res = fmod(x, e) + e;
        return fmod(res, e);
    }
}

// Calcula o MDC entre dois numeros
double mdc(double a, double d) {
    double q = floor(a/d);
    double r = fmod(a,d);

    if(r == 0) {
        return d;
    }
    double a2 = mdc(d, r);

    return a2;
}

// Função que implementa a exponênciação modular
double modPow(double base, double expoent, double modulo) {
    double result = 1;
    while (expoent > 0) {
        if (fmod(expoent, 2) == 1) {
            result = fmod(result * base, modulo);
        }
        base = fmod(base * base, modulo);
        expoent = floor(expoent / 2);
    }
    return result;
}

int main()
{
    // Recebe as entradas de p q e e
    double p, q, e;
    scanf("%lf %lf %lf", &p, &q, &e);
    
    // Calcula o N
    double n = (p * q);

    // Calcula o phi(N)
    double phi_n = ((p-1) * (q-1));
    printf("O phi(N) é %lf\n", phi_n);

    // Verifica se e é coprimo de phi(N)
    double res = mdc(phi_n, e);
    printf("O mdc(%lf,%lf) = %lf\n",phi_n, e, res);
    
    double d;

    // Se for coprimo, calcula o d como o inverso modular de emod(phi(N))
    if (res == 1)
    {
        d = inversoMod(e,phi_n);
        printf("A chave privada é %lf\n", d);
    }
    else
    {
        printf("Não existe chave privada do número %lf [phi(n)] em relação a %lf (E)\n", phi_n, e);
        printf("por favor escolha outro numero cujo mdc dos dois numeros seja igual a 1\n");
    } 


    // Abre o arquivo para ser descriptografado
    FILE * cript = fopen("InputFile.tmp", "r");
    FILE * arquivo_descript = fopen("OutputFile.tmp", "w");
 
    char c2[20];

    while(fgets(c2, 20, cript) != NULL) {
        double c = atof(c2);

        c = modPow(c, d, n);

        printf("Caracter: %.lf\n", c);

        if(c != 28) {
            c = c + 63;
        } else {
            c = c + 4;
        }

        if(c != 63){
            printf("%d ", (int)c);
            fprintf(arquivo_descript, "%c", (char)c);
        } else {
            fprintf(arquivo_descript, "\n");
        }
        

    }

    fclose(arquivo_descript);

    return 0;
}