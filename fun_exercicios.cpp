//#define EIGENLIB			// uncomment to use Eigen linear algebra library
//#define NO_POINTER_INIT	// uncomment to disable pointer checking

#include "fun_head_fast.h"

// do not add Equations in this area

MODELBEGIN

// insert your equations here, between the MODELBEGIN and MODELEND words

EQUATION("X")
/*
Variável X (short form)
*/

RESULT(VL("X",1)+V("c"))


EQUATION("c")
/*
Random walk
*/

v[0]=V("min");
v[1]=V("max");
v[2]=uniform(v[0], v[1]);
RESULT(v[2])

EQUATION("X_Sum")
/*
Variável do Setor
SOMA
*/
v[0]=0;
CYCLE(cur, "FIRM")
{
	v[1]=VS(cur,"X");
	v[0]=v[0]+v[1];
}

RESULT(v[0])

EQUATION("X_Ave")
/*
Variável do Setor
MÉDIA
*/

v[0]=0;
CYCLE(cur, "FIRM")
{
	v[1]=VS(cur,"X");
	v[0]=(v[0]+v[1]);
	v[2]=COUNT("FIRM");
	v[3]=v[0]/v[2];
}

RESULT(v[3])

EQUATION("X_Max")
/*
Variável do Setor
MÁXIMO
*/

v[0]=0;
CYCLE(cur, "FIRM")
{
	v[1]=VS(cur, "X");
	if(v[1]>v[0])
		v[0]=v[1];
	else 
		v[0]=v[0];
}
RESULT(v[0])

EQUATION("X_Share")
/*
Variável da Firma
PARCELA DE CADA FIRMA
*/
	v[0]=V("X");
	v[1]=V("X_Sum");
	if(v[1]!=0)
		v[2]=v[0]/v[1];
	else 
		v[2]=0;

RESULT(v[2])

EQUATION("X_Share_Sum")
/*
Variável do Setor
SOMA DAS PARCELAS DE TODAS AS FIRMAS
*/

RESULT(SUM("X_Share"))

/*
Variável do Setor (a posição da firma no setor)
DESAFIO: POSIÇÃO DA FIRMA COM MAIOR X A CADA PERÍODO DE TEMPO
*/

EQUATION("X_Pos")
	v[0]=V("X_Max");
	cur=SEARCH_CND("X",v[0]);
	v[1]= SEARCH_INST(cur);
RESULT(v[1])

/*
EXERCÍCIO 2.1 - EXTRA
*/

/*
Variável do Setor
Essa variável deve fazer um CYCLE nas firmas e ESCREVER a posição da firma no ranking no respectivo parâmetro "firm_rank" de cada firma
*/

EQUATION("RANK")
SORT("FIRM", "X", "DOWN");
/*
Organizar as firmas por ordem decrescente
*/
v[0]=0;
CYCLE(cur, "FIRM")
/*
O cur está me dizendo para passar por todas as firmas e a cada firma apontar para aquele endereço (o cur)

O ciclo é um definidor de ponteiro (cur) em looping
*/
{
	v[0]=v[0]+1;
/*
Pegue o valor anterior e some um na sua contagem (pode ser v[0]++)
*/
	WRITES(cur, "firm_rank", v[0]);
/*
Escrever especificamente o valor do meu ponteiro (número da firma), lembrando que cur armazena objeto, o ranking dela, dado o nível de produção dessa firma "v[0]"
ou seja
Escreva a cada valor específico apontado no cur o ranking da firma 
*/
}
RESULT(0)
		
MODELEND

// do not add Equations in this area

void close_sim( void )
{
	// close simulation special commands go here
}
