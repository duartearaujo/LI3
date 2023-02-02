#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../include/parse.h"
#include "../include/users.h"
#include "../include/rides.h"
#include "../include/queries.h"
#include "../include/drivers.h"
#include "../include/cidades.h"
#include "../include/query1.h"
#include "../include/query2.h"
#include "../include/query3.h"
#include "../include/query4.h"
#include "../include/query5.h"
#include "../include/query6.h"
#include "../include/query7.h"
#include "../include/query8.h"
#include "../include/query9.h"

/* Função usada para responder às queries, ou chamar as funções que resolvem as queries */
int queryHandler(char **argv, int n_querie, int modo) {  
    FILE *res = NULL;
    int q = atoi (argv[0]);
    int r = 1; 
    if(modo == 0){  /*Modo Batch.*/
        char filename [29 + n_querie];
        sprintf(filename, "Resultados/command%d_output.txt", n_querie);
        res = fopen(filename, "a");
    }
    else {
        if (!copia (strdup ("Resultado:")));
    }
    switch (q)  /*q == nº da query que queremos responder*/
    {
    case 1: {
        clock_t t = clock();
        r= query1Exe(res,modo,argv[1]);
        t = clock () -t;
        if (modo == 0) printf ("Query1: %f\n", ((float)t)/CLOCKS_PER_SEC);
        break;
    }
    case 2: {
        clock_t t = clock();
        r = query2Exe(res,modo,argv[1]);
        t = clock () -t;
        if (modo == 0) printf ("Query2: %f\n", ((float)t)/CLOCKS_PER_SEC);
        break;
    }
    case 3: {
        clock_t t = clock();
        r = query3Exe(res,modo,argv[1]);
        t = clock () -t;
        if (modo == 0) printf ("Query3: %f\n", ((float)t)/CLOCKS_PER_SEC);
        break;
    }
    case 4: {
        clock_t t = clock();
        r = exec_Q4 (argv[1], res, modo);
        t = clock () -t;
        if (modo == 0) printf ("Query4: %f\n", ((float)t)/CLOCKS_PER_SEC);
        break;
    }
    case 5: {
        clock_t t = clock();
        r = query5Exe(res,modo,argv);
        t = clock () -t;
        if (modo == 0) printf ("Query5: %f\n", ((float)t)/CLOCKS_PER_SEC);
        break;
    }
    case 6: {
        clock_t t = clock();
        r = query6Exe(res,modo,argv);
        t = clock () -t;
        if (modo == 0) printf ("Query6: %f\n", ((float)t)/CLOCKS_PER_SEC);
        break;
    }
    case 7:{
        clock_t t = clock();
        r = exec_Q7 (argv [2], atoi (argv[1]), res, modo);
        t = clock () -t;
        if (modo == 0) printf ("Query7: %f\n", ((float)t)/CLOCKS_PER_SEC);
        break;
    }
    case 8: {
        clock_t t = clock();
        r = query8Exe(res,modo,argv);
        t = clock () -t;
        if (modo == 0) printf ("Query8: %f\n", ((float)t)/CLOCKS_PER_SEC);
        break;
    }
    case 9: {
        clock_t t = clock();
        r = query9Exe(res,modo,argv);
        t = clock () -t;
        if (modo == 0) printf ("Query9: %f\n", ((float)t)/CLOCKS_PER_SEC);
        break;
    }
    default:
        break;
    }
    if (res) fclose (res);
    return r;
}