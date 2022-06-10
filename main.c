#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int find(char letras[], char str[], int n, int j, int i)
{
    if (str[i] == letras[j])
    {
        return j;
    }
    else
    {
        j++;
        return find(letras, str, n, j, i);
    }
    return find(letras, str, n, j, i);
}

void cripto(char letras[], int tabela[], char str[], unsigned long int new[], int n, int i)
{
    if (i == n)
    {
        return;
    }
    else
    {
        int pos;
        pos = find(letras, str, n, 0, i);
        new[i] = tabela[pos];
    }
    cripto(letras, tabela, str, new, n, i + 1);
}

unsigned long int pow_and_mod(long c, unsigned long int d, long long int n)
{
    unsigned long int value = 1;
    while (d > 0)
    {
        value *= c;
        value %= n;
        d--;
    }
    return value;
}

int finding(int tabela[], long long new[], int n, int j, int i)
{
    if (new[i] == tabela[j])
    {
        return j;
    }
    else
    {
        j++;
        return finding(tabela, new, n, j, i);
    }
    return finding(tabela, new, n, j, i);
}

void decifrar(char letra[], int tabela[], long long new[], char crip[], int n, int i)
{
    if (i == n)
    {
        crip[i] = '\0';
        return;
    }
    else
    {
        long pos;
        pos = finding(tabela, new, n, 0, i);
        crip[i] = letra[pos];
    }
    decifrar(letra, tabela, new, crip, n, i + 1);
}

long long gcdExtended(long long a, long long b, int *x, int *y)
{
    if (a == 0)
    {
        *x = 0;
        *y = 1;
        return b;
    }

    int x1, y1;
    int gcd = gcdExtended(b % a, a, &x1, &y1);
    *x = y1 - (b / a) * x1;
    *y = x1;

    return gcd;
}

int main()
{
    while (1)
    {
        int opcao;

        system("clear");
        printf("\n\tPROJETO DE MATEMATICA DISCRETA CRIPTOGRAFIA");
        printf("\n\n |1| - Gerar chave publica");
        printf("\n\n |2| - Encriptar");
        printf("\n\n |3| - Desencriptar");
        printf("\n\n |4| - Sair");
        printf("\n\n Escolha : ");
        scanf("%d", &opcao);

        if (opcao == 1)
        {
            FILE *pont_arq;
            long long int p, q, e, n, z;
            system("clear");
            printf("Digite o 'p', o 'q' e o 'e' \n");
            scanf("%lld %lld %lld", &p, &q, &e);
            n = p * q;
            z = (p - 1) * (q - 1);
            pont_arq = fopen("chaves.txt", "w");
            fprintf(pont_arq, "n = %lld e = %lld", n, e);
            fclose(pont_arq);
            system("clear");
            system("read -p 'Chaves criadas com sucesso!' var");
        }
        else if (opcao == 2)
        {
            system("clear");
            long long int e, n;
            FILE *arq;
            arq = fopen("cifrado.txt", "w");
            char letras[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', ' '};
            int tabela[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28};

            char str[999];
            printf("Digite a mensagem a ser encriptografada: \n");
            scanf(" %[^\n]", str);
            system("clear");
            printf("Digite as chaves publicas('n' e 'e'): \n");
            scanf(" %lld %lld", &n, &e);
            system("clear");

            int tam = strlen(str);
            unsigned long int new[tam], crip[tam];
            unsigned long int val[tam];
            for (int i = 0; i < tam; i++)
            {
                str[i] = toupper(str[i]);
            }
            cripto(letras, tabela, str, new, tam, 0);

            for (int i = 0; i < tam; i++)
            {
                crip[i] = pow_and_mod(new[i], e, n);
            }

            for (int i = 0; i < tam; i++)
            {
                fprintf(arq, "%lu ", crip[i]);
            }
            fclose(arq);
            system("read -p 'Arquivo txt criptografado criado com sucesso!' var");
        }
        else if (opcao == 3)
        {
            FILE *file;
            FILE *arq;

            long long value[999];
            char letras[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', ' '};
            int tabela[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28};
            file = fopen("cifrado.txt", "r");

            if (file == NULL)
            {
                printf("[ERRO] Arquivo txt não encontrado!\n");
                getchar();
                exit(0);
            }
            long long d, z, e, p, q, n;
            int x, y;
            system("clear");
            printf("Digite 'p', 'q' e 'e'\n");
            scanf(" %lld %lld %lld", &p, &q, &e);
            system("clear");
            n = p * q;
            z = (p - 1) * (q - 1);
            int g = gcdExtended(e, z, &x, &y);

            d = x;

            int tam = 0;
            int numero;

            while (fscanf(file, "%lld", &value[tam]) != EOF)
            {
                tam++;
            }
            long long new[tam];
            char crip[tam];

            for (int c = 0; c < tam; c++)
            {
                new[c] = pow_and_mod(value[c], d, n);
            }
            arq = fopen("decifrado.txt", "w");

            decifrar(letras, tabela, new, crip, tam, 0);

            fprintf(arq, "%s", crip);
            printf("txt decifrado!\n");

            fclose(file);
            fclose(arq);
            system("clear");
            system("read -p 'Txt decifrado!' var");
        }
        else if (opcao == 4)
        {
            printf("sAINDO...\n");
            system("read -p 'Obrigado!' var");
            exit(0);
        }
        else
        {
            printf("[ERRO] Opção invalída!\n");
            system("read -p 'Digite outro valor!' var");
        }
    }

    return 0;
}