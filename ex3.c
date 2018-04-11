/* ************************************************************************ *
 *    Calculadora Polonesa                                                  *
 *                                                                          *
 *    Copyright (C) 2018 by Douglas Azevedo Pereira Dantas                  *
 *                                                                          *
 *    This program is free software; you can redistribute it and/or modify  *
 *    it under the terms of the GNU General Public License as published by  *
 *    the Free Software Foundation; either version 2 of the License, or     *
 *    (at your option) any later version.                                   *
 *                                                                          *
 *    This program is distributed in the hope that it will be useful,       *
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *    GNU General Public License for more details.                          *
 *                                                                          *
 *    You should have received a copy of the GNU General Public License     *
 *    along with this program; if not, write to the                         *
 *    Free Software Foundation, Inc.,                                       *
 *    59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 *                                                                          *
 *    To contact the author, please write to:                               *
 *    Douglas Azevedo Pereira Dantas <douglasazevedo839@gmail.com>          *
 *    Webpage: https://github.com/DodoAz                                    *
 *    Phone: +55 (81) 99158-2473                                            *
 * ************************************************************************ *
 * 
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 256

typedef struct st_pilha 
{
    int c;                        //o item armazenado 
    struct st_pilha *prox;        //ponteiro para próximo
}pilha;

void push(pilha **, int);
int pop(pilha **);
void calculo(pilha **, char);
void imprimir(pilha *);
void limpar(pilha **);

int main (void)
{
    char str[MAX];
    char *pch;
    pilha *p1 = NULL;

    printf("Informe a expressao em notacao polonesa inversa a ser calculada:\n");
    fgets(str, MAX , stdin);
    //printf ("Particionando a string \"%s\" em tokens:\n", str);
    pch = strtok (str, " ");

    while (pch != NULL)
    {
        //if(!(strcmp(*pch,"-") || strcmp(*pch, "+") || strcmp(*pch, "/") || strcmp(*pch,"*")))
        if(*pch == '-' || *pch == '+' || *pch == '/' || *pch == '*')
            calculo(&p1, *pch);
        else
            push(&p1, atoi(pch));
    
        //imprimir(p1);

        pch = strtok (NULL, " ");
    }

    //printf("Caractere bugado: %c  -  %i\n", '▒', (int)'▒'); //

    printf("Resultado: %d\n", p1->c);
    limpar(&p1);

    return 0;
}

void push(pilha **cabeca, int x)
{
    pilha *pl;

    pl = malloc(sizeof(pilha));
    pl->c = x;
    pl->prox = *cabeca;

    *cabeca = pl;
}

int pop(pilha **cabeca)
{
    pilha *pl = *cabeca;
    int x;

    x = pl->c;
    *cabeca = pl->prox;

    free(pl);

    return x;
}

void calculo(pilha **cabeca, char op)
{
    int x, y, r;

    x = pop(cabeca);
    y = pop(cabeca);

    switch(op)
    {
        case '+':
            r = y + x;
            break;
        case '-':
            r = y - x;
            break;
        case '*':
            r = y * x;
            break;
        case '/':
            r = y / x;
            break;
    }

    printf("Calculo: %d %c %d = %d\n", y, op, x, r);
    push(cabeca, r);

    return;
}

void imprimir(pilha *cabeca)
{
    pilha *pl = cabeca;

    printf("Pilha: ");

    while(pl != NULL)
    {
        printf("%d ", pl->c);
        pl = pl->prox;
    }
    printf("\n");
}

void limpar(pilha **cabeca)
{
    pilha *pl = *cabeca;
    pilha *plant = NULL;

    while(pl != NULL)
    {
        plant = pl;
        pl = pl->prox;
        free(plant);
    }

    return;
}

