#include <stdio.h>
//#include<conio.h>
#include <math.h>
long int power(int base, int exponent);
int hextodec(char *input);
int f;
int n;
long long int sctext[8];
int input;
int main()
{

    printf("how much char?\n");
    scanf("%x", &n);
    char tmp[20];
    /*sand box
    char textinput[20];
    scanf("%s",textinput);
    printf("%x",hextodec(textinput));
    return 0 ;
    ////////*/
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            scanf("%s", tmp);
            input = hextodec(tmp);
            printf("%d",input);
            sctext[j] =0xff& input;
            sctext[j] = sctext[j] << 8;
        }
    }

    // scanf("%d",&f);
    for (int i = 0; i < 8; i++)
        printf("0x%llx\n", sctext[i]);
    return 0;
}

int hextodec(char *input)
{
    int decnum = 0, rem, i = 0, len = 0;
    char hexdecnum[20];

    hexdecnum[0] = *input;
    while (hexdecnum[i] != '\0')
    {
        len++;
        i++;
    }
    len--;
    i = 0;
    while (len >= 0)
    {
        rem = hexdecnum[len];
        if (rem >= 48 && rem <= 57)
            rem = rem - 48;
        else if (rem >= 65 && rem <= 90)
            rem = rem - 55;
        else
        {
            //printf("\n Invalid Hexadecimal digit");
            //getchar();
            return 0;
        }
        decnum = decnum + (rem * power(16, i));
        len--;
        i++;
    }
    
    return decnum;
}

long int power(int base, int exponent) {
    long int result = 1;

    if (exponent >= 0) {
        for (int i = 0; i < exponent; i++) {
            result *= base;
        }
    } else {
        for (int i = 0; i > exponent; i--) {
            result /= base;
        }
    }

    return result;
}