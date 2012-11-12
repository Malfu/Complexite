#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

extern char * __progname;

static void construire_sat(FILE * graph, FILE * result)
{
  int nbsommet, nbarrete, i;
  int var1, var2, var3, negvar1, negvar2, negvar3;
  int sommet1, sommet2;
  int negvar11, negvar22, negvar33;

  if(2 != fscanf(graph, "%d %d", &nbsommet, &nbarrete)){
    fprintf(stderr, "Cannot read header data\n");
    exit(1);
  }

  fprintf(result, "p cnf %d %d \n", 
      3 * nbsommet, 
      nbsommet + 3 * nbsommet + 3 * nbarrete);

  /* initialisation termine */
  for(i=1;i<=nbsommet;++i)/* P1 et P2 */
  {
    var1 = 10 * i + 1;
    var2 = var1 + 1;
    var3 = var2 + 1;

    negvar1 = -var1;
    negvar2 = -var2;
    negvar3 = -var3;

    fprintf(result,"%d %d %d 0 \n", var1, var2, var3);
    fprintf(result,"%d %d 0 \n", negvar1, negvar2);
    fprintf(result,"%d %d 0 \n", negvar1, negvar3);
    fprintf(result,"%d %d 0 \n", negvar2, negvar3);
  }

  i = 1;
  while(!feof(graph)) /* P3 */
  {
    if(2 != fscanf(graph, "%d %d", &sommet1, &sommet2))
    {
      fprintf(stderr, "Cannot read line %d\n", i);
      exit(1);
    }
    ++i;

    negvar1 = -(10 * sommet1 + 1);
    negvar2 = -(10 * sommet1 + 2);
    negvar3 = -(10 * sommet1 + 3);

    negvar11 = -(10 * sommet2 + 1);
    negvar22 = -(10 * sommet2 + 2);
    negvar33 = -(10 * sommet2 + 3);

    fprintf(result,"%d %d 0 \n", negvar1, negvar11);
    fprintf(result,"%d %d 0 \n", negvar2, negvar22);
    fprintf(result,"%d %d 0 \n", negvar3, negvar33);
  }
}


int main(int argc, char ** argv)
{
  FILE* graphe = NULL;
  FILE* output = NULL;

  if(argc == 3){
    graphe = fopen(argv[1], "r");
    output = fopen(argv[2], "w");

    if (graphe != NULL)
    {
      if (output != NULL)
      {
        construire_sat(graphe, output);
        fclose(graphe);
        fclose(output);
      }
      else
      {
        fprintf(stderr, "Error while opening output file %s\n", argv[2]);
        return 1;
      }
    }
    else
    {
      fprintf(stderr, "Error while opening input file %s\n", argv[1]);
      return 1;
    }
  }else{
    fprintf(stderr, "usage: %s <Input graph> <Output Dimacs file>\n", __progname);
    return 1;
  }

  return 0;
}
