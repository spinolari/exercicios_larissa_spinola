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
	cur1=SEARCH_CND("X",v[0]);
	v[1]= SEARCH_INST(cur1);
RESULT(v[1])

/*
EXERCÍCIO 2.1 - EXTRA
*/

/*
Variável do Setor
Essa variável deve fazer um CYCLE nas firmas e ESCREVER a posição da firma no ranking no respectivo parâmetro "firm_rank" de cada firma
*/

EQUATION("RANK")
v[0]=0;
CYCLE(cur2, "FIRM")
{
	v[1]=VS(cur2,"X_Share");
CYCLE(cur3, "FIRM")
{
	v[2]=VS(cur3,"X_Share");
			
			if(v[2]>v[1]) v[0]=v[0]+1;
			
}
v[3]=WRITES(cur2, "firm_rank", v[0]);
}
RESULT(v[3])
		
MODELEND

// do not add Equations in this area

void close_sim( void )
{
	// close simulation special commands go here
}
