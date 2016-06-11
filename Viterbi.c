/*

Autores: 
Compilar:
gcc HMM.c -Wall -Wextra -pedantic -o hmm
-Wall
ativa vários avisos que não são ativados normalmente. Pode dar alguns conselhos úteis.
-pedantic
ativa alguns avisos que existem de acordo com o padrão C mas que são desativados normalmente por extensões do gcc.
 */

#include <stdio.h>
#include <stdlib.h>

void criarMatrizDinamica();
void liberaMatrizDinamica();
void viterbi();

/*Problema 2 - Problema de decodificação significa buscar pela sequencia de estados ocultos que possui a maior probabilidade de ter gerado uam determinada sequencia de observador

*/

int main()
{
	viterbi();
	return 0;
}


void viterbi()
{
	//psi armazena qual estado tem maior probabilidade
	int psi, pergunta[4];
	register int i, t, j;
	float a[7][7], b[7][7], pi[7];
	float respostas_parciais[7], teste,maior, teste2;

	printf("\n\n\t VITERBI");	//inicialização estatica - dados referente a um modelo de clima/tempo
	printf("\n 1 para seco - 2 para molhado");

	/* matriz de transição entre estados(oculto)*/
	a[0][0] = 0.01; a[0][1] = 0.37; a[0][2] = 0.37; a[0][3] = 0.06; a[0][4] = 0.07; a[0][5] = 0.07; a[0][6] = 0.05;	
	a[1][0] = 0.37; a[1][1] = 0.01; a[1][2] = 0.37; a[1][3] = 0.06; a[1][4] = 0.07; a[1][5] = 0.07; a[1][6] = 0.05;
	a[2][0] = 0.37; a[2][1] = 0.37; a[2][2] = 0.01; a[2][3] = 0.06; a[2][4] = 0.07; a[2][5] = 0.07; a[2][6] = 0.05;
	a[3][0] = 0.07; a[3][1] = 0.07; a[3][2] = 0.06; a[3][3] = 0.01; a[3][4] = 0.37; a[3][5] = 0.37; a[3][6] = 0.05;
	a[4][0] = 0.07; a[4][1] = 0.07; a[4][2] = 0.06; a[4][3] = 0.37; a[4][4] = 0.01; a[4][5] = 0.37; a[4][6] = 0.05;
	a[5][0] = 0.07; a[5][1] = 0.07; a[5][2] = 0.06; a[5][3] = 0.37; a[5][4] = 0.37; a[5][5] = 0.01; a[5][6] = 0.05;
	a[6][0] = 0.07; a[6][1] = 0.07; a[6][2] = 0.06; a[6][3] = 0.37; a[6][4] = 0.37; a[6][5] = 0.05; a[6][6] = 0.01;
	
	/* matriz de probabilidade de emmissao(observaveis)*/
	b[0][0] = 0.6; b[0][1] = 0.4;
	b[1][0] = 0.6; b[1][1] = 0.4;
	b[2][0] = 0.6; b[2][1] = 0.4;
	b[3][0] = 0.3; b[3][1] = 0.7;
	b[4][0] = 0.3; b[4][1] = 0.7;
	b[5][0] = 0.3; b[5][1] = 0.7;
	b[6][0] = 0.2; b[6][1] = 0.2;
	
	/* vetor com probabilidades iniciais*/
	pi[0] = 0.07;
	pi[1] = 0.42;
	pi[2] = 0.32;
	pi[3] = 0.08;
	pi[4] = 0.04;
	pi[5] = 0.04;
	pi[6] = 0.03;

	/*soma do pi tem que ser  igual a 1*/
	printf("\n\t PROBABILIDADE DE TRANSICAO ENTRE ESTADOS");
	for(i = 0; i < 7; i++)
		for(j = 0; j < 7; j++)
			printf("\n[%d][%d] = [%.2f]", i, j, a[i][j]);		

	printf("\n\t PROBABILIDADE DE EMISSAO");
	for(i = 0; i < 7; i++)
		for(j = 0; j < 2; j++)
			printf("\n[%d][%d] = [%.2f]", i, j, b[i][j]);		


	/*primeiro passo do algoritmo de viterbi - inicialização, probabilidade parcial no tempo 1
	i = 3, que é a quantidade de estados [ensolarado, nublado e chuvoso]
	t é igual a 1.
	respostas_parciais recebe a resposta parcial de cada i
	b[][0] corresponde à observação do tempo que é seco
	pergunta, dada a sequencia de observação  o= seco, molhado, molhado,seco, estados maximiza*/

	for(i = 0; i < 7; i++)
	{
		respostas_parciais[i] = pi[i] * b[i][0];
		printf("\n resposta parcial[%.2f]", respostas_parciais[i]);
	}

	printf("\n\n");
	/*segundo passo do algoritmo de viterbi - recursão*/
	for(t = 0; t < 7; t++)
	{
		maior = 0;
		for(i = 0; i < 7; i++)
		{/*esse i é refente a pergunta, que contem 4 observaveis
			printf("\n\t %.4f X %.4f",respostas_parciais[i],b[i][0]);*/
			teste = respostas_parciais[i] * a[i][t];
			printf("\n\t recursao passo: %.4f", teste);
			//procura qual valor de teste eh maior
			if(maior < teste)
			{
				maior = teste;
				psi = i;//grava o estado em que ocorreu?
				printf("\n\t Maior = %.4f\n", maior);
				printf("\n\t\t\t %.4f",b[0][t+1]);
				teste2 = maior * b[0][t+1];
				printf("\n\t maior * observavel=[%.4f][%.4f]",maior,b[0][t+1]);
				printf("\n\t teste2 = %.4f", teste2);

			}

		

		}
			// 0.3 é a porcentagem do observavel ser seco,como o proximo[2estado] é molhado eh 0.3
			printf("\n psi = %d",psi);
			//o valor da observavel esta errado! 

	printf("\n\n\n");

	}//fim laco do t

}

