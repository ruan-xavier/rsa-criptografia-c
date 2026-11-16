#include <stdio.h>
#include <ctype.h>

int mdc(int a, int b)
{
    if (b == 0)
        return a;

    return mdc(b, a % b);
}

long long int pM(long long int b, long long int e, long long int n)
{
    long long int r = 1;
    b = b % n;

    while (e > 0)
    {
        if (e % 2 != 0)
            r = (r * b) % n;
        b = (b * b) % n;
        e = e / 2;
    }
    return r;
}

long long int iM(long long int e, long long int t)
{
    long long int t0 = t;
    long long int d = 1, sub = 0;

    while (t > 0)
    {
        long long int q = e / t;
        long long int resto = e % t;

        e = t;
        t = resto;

        long long int proximo_sub = d - q * sub;
        d = sub;
        sub = proximo_sub;
    }

    if (e > 1)
        return -1;

    return (d % t0 + t0) % t0;
}

int cLetra(char letra)
{
    if (letra >= 'A' && letra <= 'Z')
        return letra - 'A' + 2;

    if (letra == ' ')
        return 28;

    return -1;
}

char dLetra(int m)
{
    if (m >= 2 && m <= 27)
        return 'A' + (m - 2);

    if (m == 28)
        return ' ';

    return '?';
}
int chavePublica(int p, int q, int e)
{
    if (mdc(e, ((p - 1) * (q - 1))) == 1)
    {
        FILE *arquivo = fopen("ChavePublica.txt", "w");
        fprintf(arquivo, "Chave Publica: (%d:%d)", e, (p * q));
        fclose(arquivo);
        return 1;
    }
    else
    {
        printf("Expoente invalido escolha outro expoente");
        scanf("%d", &e);
        chavePublica(p, q, e);
    }
    return 0;
}

int chavePrivada(int p, int q, int e)
{
    if (mdc(e, ((p - 1) * (q - 1))) == 1)
    {
        long long int d = iM(e, ((p - 1) * (q - 1)));
        return d;
    }
    else
    {
        printf("Expoente invalido escolha outro expoente");
        scanf("%d", &e);
        chavePrivada(p, q, e);
    }
    return 0;
}
int criptografar(char mensagem[], int e, int n)
{
    FILE *arquivo = fopen("criptografia.txt", "w");

    for (int i = 0; mensagem[i] != '\0'; i++)
    {

        int m = cLetra(mensagem[i]);

        if (m == -1)
            continue;

        int c = pM(m, e, n);

        fprintf(arquivo, "%d ", c);
    }

    fclose(arquivo);
    return 1;
}

int descriptografar(long long int p, long long int q, long long int e)
{
    long long int c;
    char proximo;

    FILE *arquivo = fopen("descriptografia.txt", "w");

    printf("Digite a mensagem criptografada:");

    while (scanf("%lld", &c) == 1)
    {
        long long int m = pM(c, chavePrivada(p, q, e), (p * q));
        fputc((char)dLetra((int)m), arquivo);

        proximo = getchar();
        if (proximo == '\n' || proximo == EOF)
            break;
    }

    fclose(arquivo);
    return 1;
}

int main()
{
    int p, q, e, n;
    char mensagem[9999];
    printf("Escolha uma opção:\n1-Gerar chave publia\n2-Criptografar\n3-descriptografar");
    switch (getchar())
    {
    case '1':
        printf("Digite 'p' e 'q' e um expoente");
        scanf("%d%d%d", &p, &q, &e);

        if (chavePublica(p, q, e) == 1)
            printf("Chave Publica gerada");

        break;
    case '2':
        printf("Digite a mensagem: ");
        getchar();
        fgets(mensagem, sizeof(mensagem), stdin);

        for (int i = 0; mensagem[i] != '\0'; i++)
        {
            mensagem[i] = toupper((unsigned char)mensagem[i]);
        }

        printf("Digite a chave publica (e n): ");
        scanf("%d %d", &e, &n);

        if (criptografar(mensagem, e, n) == 1)
            printf("Mensagem criptografada");
        break;
    case '3':
        printf("Digite 'p' e 'q' e um expoente");
        scanf("%d%d%d", &p, &q, &e);

        if (descriptografar(p, q, e) == 1)
            printf("Mensagem descriptografada no arquivo");
        break;

    default:
        printf("Entrada invalida");
        break;
    }
    return 0;
}
