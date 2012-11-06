#include <stdlib.h>
#include <stdio.h>

void construire_sat(FILE * graph)
{
		FILE* result = NULL;
		result = fopen("resultat.txt", "w");
		if(result != NULL)
		{
				char chaine[10] = "";
				fgets(chaine, 10, graph);
				int nbsommet = atoi(&chaine[0]);
				int nbarrete = atoi(&chaine[2]);
				
				fprintf(result, "p cnf %d %d \n", 3*nbsommet, nbsommet+3*nbsommet+3*nbarrete);
				//initialisation termine
				int i;
				for(i=1;i<=nbsommet;++i)//P1 et P2
				{
						int var1 = 10*i +1;
						int var2 = var1+1;
						int var3 = var2+1;
						int negvar1 = 0-var1 ;
						int negvar2 = 0-var2;
						int negvar3 = 0-var3;
						fprintf(result,"%d %d %d 0 \n", var1, var2, var3);
						fprintf(result,"%d %d 0 \n", negvar1, negvar2);
						fprintf(result,"%d %d 0 \n", negvar1, negvar3);
						fprintf(result,"%d %d 0 \n", negvar2, negvar3);
				}
				while(fgets(chaine, 10, graph) != NULL)//P3
				{
						int sommet1 = atoi(&chaine[0]);
						int sommet2 = atoi(&chaine[2]);
						int negvar1 = 0-(10*sommet1+1);
						int negvar2 = 0-(10*sommet1+2);
						int negvar3 = 0-(10*sommet1+3);
						
						int negvar11 = 0-(10*sommet2+1);
						int negvar22 = 0-(10*sommet2+2);
						int negvar33 = 0-(10*sommet2+3);
						
						fprintf(result,"%d %d 0 \n", negvar1, negvar11);
						fprintf(result,"%d %d 0 \n", negvar2, negvar22);
						fprintf(result,"%d %d 0 \n", negvar3, negvar33);
				}
				fclose(result);
		}
		else
		{
				printf("lol noob \n");
		}
}
int main(int argc, char ** argv)
{
		FILE* graphe = NULL;
		graphe = fopen(argv[1] , "r");
		if (graphe != NULL)
		{
				construire_sat(graphe);
				fclose(graphe);
		}
		else
		{
				printf("lol noob \n");
		}
		
		return 0;
}