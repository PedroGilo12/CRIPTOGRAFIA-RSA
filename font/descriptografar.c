#include <stdio.h>
#include <math.h>

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

double mdc(double a, double d) {
    double q = floor(a/d);
    double r = fmod(a,d);

    if(r == 0) {
        return d;
    }
    double a2 = mdc(d, r);

    return a2;
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

int main()
{
    double p, q, e;
    scanf("%lf %lf %lf", &p, &q, &e);
    
    double n = (p * q);

    double phi_n = ((p-1) * (q-1));
    printf("O phi(N) é %lf\n", phi_n);

    double res = mdc(phi_n, e);
    printf("O mdc(%lf,%lf) = %lf\n",phi_n, e, res);
    
    double d;

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

    FILE * cript = fopen("InputFile.tmp", "r");
    FILE * arquivo_descript = fopen("OutputFile.tmp", "w");
 
    char c2[20];

    while(fgets(c2, 20, cript) != NULL) {
        double c = atof(c2);

        c = modPow(c, d, n);

        c = c + 63;

        if(c != -1){
            printf("%d ", (int)c);
            fprintf(arquivo_descript, "%c", (char)c);
        } else {
            fprintf(arquivo_descript, "\n");
        }
        

    }

    fclose(arquivo_descript);

    return 0;
}