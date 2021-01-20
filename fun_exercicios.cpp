//#define EIGENLIB			// uncomment to use Eigen linear algebra library
//#define NO_POINTER_INIT	// uncomment to disable pointer checking

#include "fun_head_fast.h"

// do not add Equations in this area

MODELBEGIN

// insert your equations here, between the MODELBEGIN and MODELEND words

EQUATION("X")
/*
Vari�vel X (short form)
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
Vari�vel do Setor
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
Vari�vel do Setor
M�DIA
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
Vari�vel do Setor
M�XIMO
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
Vari�vel da Firma
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
Vari�vel do Setor
SOMA DAS PARCELAS DE TODAS AS FIRMAS
*/

RESULT(SUM("X_Share"))

/*
Vari�vel do Setor (a posi��o da firma no setor)
DESAFIO: POSI��O DA FIRMA COM MAIOR X A CADA PER�ODO DE TEMPO
*/

EQUATION("X_Pos")
	v[0]=V("X_Max");
	cur1=SEARCH_CND("X",v[0]);
	v[1]= SEARCH_INST(cur1);
RESULT(v[1])

/*
EXERC�CIO 2.1 - EXTRA
*/

/*
Vari�vel do Setor
Essa vari�vel deve fazer um CYCLE nas firmas e ESCREVER a posi��o da firma no ranking no respectivo par�metro "firm_rank" de cada firma
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
WRITES(cur2, "firm_rank", v[0]);
}
RESULT(0)


/* ~~~~FORMA DA AULA~~~~

EQUATION("RANK")
SORT("FIRM", "X", "DOWN");

Organizar as firmas por ordem decrescente

v[0]=0;
CYCLE(cur, "FIRM")

O cur est� me dizendo para passar por todas as firmas e a cada firma apontar para aquele endere�o (o cur)

O ciclo � um definidor de ponteiro (cur) em looping

{
	v[0]=v[0]+1;

Pegue o valor anterior e some um na sua contagem (pode ser v[0]++)

	WRITES(cur, "firm_rank", v[0]);

Escrever especificamente o valor do meu ponteiro (n�mero da firma), lembrando que cur armazena objeto, o ranking dela, dado o n�vel de produ��o dessa firma "v[0]"
ou seja
Escreva a cada valor espec�fico apontado no cur o ranking da firma 

}
RESULT(0)
*/

EQUATION("EntryExit")
	v[0]=V("switch_entry");
	if(v[0]==1)
	{
			cur=SEARCH_CND("firm_rank",10);
			DELETE(cur);
			cur1=SEARCH_CND("firm_rank",5);
			
//meu modelo tem 10 firmas, quero deletar a de �ltimo ranking e colocar uma replica da firma de ranking 5 no lugar
			cur2=ADDOBJ_EX("FIRM", cur1);
//Estou salvando a replica e adicionando na amostra de firmas (que volta a ter 10), chamei de cur2 para ser um atalho e n�o ter que escrev�-la sempre, salvei um ponteiro para o objeto, mas n�o precisava, poderia colocar direto, mas sempre que eu fosse usar, teria que colocar o nome todo de novo.
			}
RESULT(0)


MODELEND

// do not add Equations in this area

void close_sim( void )
{
	// close simulation special commands go here
}
