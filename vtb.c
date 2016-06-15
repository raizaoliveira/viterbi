#include <stdio.h>
#include <stdlib.h>


#define N_STAT 3
#define t 4 
#define N_S_OBS 2



float max(int col, int stat_now, int t_now, float T[][t], float A[][N_STAT], float B[][N_S_OBS], int stat_obs)
{
	register int i;
	double max;
	double var = 0;
	max = 0;
	for(i = 0; i < N_STAT; i++)//*N_Stat -> equivale a quantide de estados nao observaveis
	{
		printf("B[%d][%d]: %.3f\n\n", i, stat_obs, B[i][stat_obs]);
		var = T[i][col] * A[i][stat_now] * B[i][stat_obs];
		if(max < var)
		{
			
			max = var;
			printf("max: %.5f    var: %.5f\n", max, var);
		}
	} 
	return max;

}


float max_stat(int col, int stat_now, int t_now, float T[][t], float A[][N_STAT], float B[][N_S_OBS])
{
	register int i;
	double m;

	for(i = 1; i < N_S_OBS; i++)
		m = max(col, stat_now, t_now, T, A, B, i);

	printf("retornando ->-> %.3f\n\n", m);
	return m;


}


void viterbi()
{
	float T1 [N_STAT][t];
	float T2 [N_STAT][t];
	float m;
	int flag;
	register int i;
	register int j;
	float array_pi[N_STAT] = {0.5, 0.3, 0.2};

	float A[N_STAT][N_STAT] = {{0.5, 0.3, 0.2},
							{0.2, 0.3, 0.5},
							{0.1, 0.2, 0.7}};

	float B[N_STAT][N_S_OBS] = {{0.7, 0.3},
								{0.5, 0.5},
								{0.1, 0.9}};
	/*
	Inicialização  -> calculo de todos os estados delta_1(i) = pi_i * b_i (O_1)
				->-> calculo de Psi_1(i) = 0

	recursão-> calculado todas as probabilidades parciais do instante t_2 ate t_N

	*/
	//propabilidade inicial no tempo 1

	for(i = 0; i < N_STAT; i++)
	{
		T1[i][0] = array_pi[i] * B[i][0];
		T2[i][0] = 0;
		printf("T1 %.2f\n T2 %.1f\n", T1[i][0], T2[i][0]);
		printf("PI[%d] * B[%d][0] :: %.3f * %.3f\n->  %.4f\n", i, i, array_pi[i], B[i][0], array_pi[i] * B[i][0]);
	}

	/*/max score no tempo anterior 
	for(i = 0; i < N_STAT; i++)
	{
		for(j = 0; j < N_STAT; j++)
		{
			printf("%.2f * %.2f: %.3f\n", delta[j], A[j][i], delta[j] *  A[j][i]);
			score[i][j] = delta[i] *  A[i][j];
			
		}
	}

	/multiplica o maximo score pela array_pi do proximo estado*/

	for(i = 1; i < t; i++)
	{
		for(j = 0; j < N_STAT; j++)
		{
			T1[j][i] = max_stat(i-1, j, i, T1, A, B);
		}
		printf("Continua :" );
		scanf(" %d", &flag);
	}
			

	for(i = 1; i < t; i++)
		for(j = 0; j < N_STAT; j++)
			printf("T1[%d][%d]: %.5f\n", j, i, T1[j][i]);
		

}









int main()
{


	viterbi();

	return 0;
}

















