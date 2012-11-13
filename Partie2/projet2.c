#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <limits.h>
#include <string.h>


void construire_sat(FILE* graph, FILE* result)
{
	int nbsommet, nbarc;
	int source, destination;
	int i,j;
	int nbdestination = 0;
	
	if(2 != fscanf(graph, "%d %d", &nbsommet, &nbarc)){
    fprintf(stderr, "Cannot read header data\n");
    exit(1);
	}

	int adj[nbsommet][nbsommet];
	/* initialisation matrice */
	for(i=0; i<nbsommet;++i)
	{
		for(j=0;j<nbsommet;++j)
		{
			adj[i][j] = INT_MIN;
		}
	}
	/* remplissage de la matrice */
	for(;!feof(graph);)
	{
		fscanf(graph, "%d %d", &source, &destination);
		int i;
		for(i=0; i<nbsommet;++i)
		{
			if(destination == adj[i][0])/* match de la destination, ajout de la source a la liste des sources */
			{
				for(j=1;j<nbsommet;++j)
				{
					if(adj[i][j] == source) break;/* elimination des redondances */
					if(adj[i][j] == INT_MIN) adj[i][j] = source; /* ajout de la source a la liste des sources pour une destination */
				}
				continue;
			}
			else if (adj[i][0] == INT_MIN)/* nouvelle source */
			{
				++nbdestination;
				adj[i][0] = destination;
				adj[i][1] = source;
				break;
			}
		}
	}
	
	/* fin remplissage */
	fprintf(result, "p cnf %d %d \n", nbsommet, nbarc + nbdestination);
	for(i=0;i<nbsommet;++i)
	{
		if(adj[i][0] == INT_MIN) break;
		char clause[1024];/* si il y a plus d'arc fuck yourself */
		char buf[30]; 
		sprintf(buf,"%d",adj[i][0]);
		strcat(clause,buf);
		for(j=1;j<nbsommet;++j)
		{
			if(adj[i][j] == INT_MIN) break;
			sprintf(buf," %d",adj[i][j]);
			strcat(clause,buf);
			fprintf(result,"%d %d 0 \n", -adj[i][0], -adj[i][j]);/* P1 */
		}
		sprintf(buf," %d \n",0);
		strcat(clause,buf);
		fprintf(result,"%s",clause);/* P2 */
	}
	
}

int main(int arc, char ** argv)
{
	
	FILE* graphe = NULL;
	FILE* output = NULL;
	
	graphe = fopen(argv[1], "r");
    output = fopen(argv[2], "w");
	
	construire_sat(graphe, output);
    
	fclose(graphe);
    fclose(output);
	
	return 0;
}
