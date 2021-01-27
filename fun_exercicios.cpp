//#define EIGENLIB			// uncomment to use Eigen linear algebra library
//#define NO_POINTER_INIT	// uncomment to disable pointer checking

#include "fun_head_fast.h"

// do not add Equations in this area

MODELBEGIN

// insert your equations here, between the MODELBEGIN and MODELEND words

//EQUATION("X") ~~~TRANSFORMADO EM TEXTO PARA FAZER O EX 3~~~
/*
Vari�vel X (short form)
*/

//RESULT(VL("X",1)+V("c")) ~~~TRANSFORMADO EM TEXTO PARA FAZER O EX 3~~~


//EQUATION("c") ~~~TRANSFORMADO EM TEXTO PARA FAZER O EX 3~~~
/*
Random walk
*/

//v[0]=V("min"); ~~~TRANSFORMADO EM TEXTO PARA FAZER O EX 3~~~
//v[1]=V("max"); ~~~TRANSFORMADO EM TEXTO PARA FAZER O EX 3~~~
//v[2]=uniform(v[0], v[1]); ~~~TRANSFORMADO EM TEXTO PARA FAZER O EX 3~~~
//RESULT(v[2]) ~~~TRANSFORMADO EM TEXTO PARA FAZER O EX 3~~~

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


//EXERC�CIO 3

//X PASSA A SER AS VENDAS DE UMA FIRMA (MUDEI PARA TEXTO O COME�O DO SCRIPT QUE TINHA A DEFINI��O DE X, J� QUE AGORA USAREMOS UMA NOVA)

//AS VENDAR DEPENDEM DE DOIS FATORES AL�M DO FATOR ALEAT�RIO (RND): QUALIDADE E PRE�O

//DEFININDO A EQUA��O DA QUALIDADE
//VARI�VEL NO N�VEL DA FIRMA

EQUATION("Quality")

//A qualidade � cumulativa, aleat�ria e crescente. Caso a firma obtenha uma "qualidade" inferior � anterior, ela utiliza a anterior.

v[0]=VL("Quality",2);
v[1]=VL("Quality",1);
if(v[1]>=v[0]) v[0]=v[0]+v[1]+RND;
else v[0]=v[0];

RESULT (v[0])


//DEFININDO A EQUA��O DO PRE�O
//VARI�VEL NO N�VEL DA FIRMA

EQUATION("Price")

//O pre�o corresponde ao ganho de market share passado dela.

v[0]= VL("Price",1);
v[1]= VL("X_Share",2);
v[2]=VL("X_Share",1);
v[3]=V("a");
//Par�metro positivo que multiplica a varia��o de share que vai impactar o pre�o
if (v[2]>v[1]) v[4]=((v[2]-v[1])/v[1])*v[3]+v[0];
else v[4]=v[0];

RESULT(v[4])

//DEFININDO A EQUA��O DAS VENDAS
//VARI�VEL NO N�VEL DA FIRMA

EQUATION("X")

//As vendas v�o depender do pre�o, da qualidade e de um componente aleat�rio

v[0]=V("Price");
v[1]=V("b");
//Par�metro positivo entre 0 e 1 que multiplica o pre�o do produto e que vai impactar nas vendas
v[2]=V("Quality");
v[3]=V("c");
//Par�metro positivo entre 0 e 1 que multiplica a qualidade do produto e que vai impactar nas vendas
v[4]=v[1]*v[0]+v[3]*v[2]+RND;
RESULT(v[4])

MODELEND

// do not add Equations in this area

void close_sim( void )
{
	// close simulation special commands go here
}
