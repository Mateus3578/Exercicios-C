/* Implemente um procedimento que receba uma palavra como entrada e 
verifique se essa palavra é um palíndromo. Palíndromos são palavras 
que podem ser lida da mesma forma independentemente de direção. 
Por exemplo: asa, arara, etc. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void verificaPalindromo(char string[100])
{
    int i, j;
    char string2[100];

    //Remove espaços para comparar frases
    for(i=0, j=0; string[i] != '\0'; i++)
    {
        if (string[i] != ' ')
        {
            string[j] = string[i];
            j++;
        }
    }
    //Coloca o novo final da string, retirado os espaços
    string[j] = '\0';
    //Função que copia uma string
    strcpy(string2, string);
    //Função que inverte uma string
    strrev(string2);
    //Função que compara duas strings e retorna um valor. 0 significa que são iguais
    if(strcmp(string, string2) == 0)
    {printf("A palavra e um palindromo \n\n");}
    else
    {printf("A palavra nao e um palindromo \n\n");}
}

int main() 
{
    char s[100];
	
    printf("Digite sua string: ");
    gets(s);
    verificaPalindromo(s);

    system("pause");
	return 0;
}