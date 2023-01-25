#include <stdio.h>
#include <stdlib.h>
#include <glib.h>
#include "../include/parse.h"
#include "../include/users.h"
#include "../include/rides.h"
#include "../include/queries.h"
#include "../include/drivers.h"
#include "../include/query9.h"

gint desempate_Q9(gconstpointer p1, gconstpointer p2){
    RIDES const*dados_1 = p1;
    RIDES const*dados_2 = p2;
    int result = 1;
    int distance = getdistanceR_Q9 (dados_1);
    int PDistance = getdistanceR_Q9 (dados_2);
    if(distance > PDistance) result = -1;
    if(distance == PDistance){ 
        int Date = getIdadeViagem_Q9 (dados_1);
        int PDate = getIdadeViagem_Q9 (dados_2);
        if(Date == PDate){
            char *id = getIdR_Q9 (dados_1);
            char *Pid = getIdR_Q9 (dados_2);
            if(strcmp(id, Pid) > 0) result = -1;
            free (id);
            free (Pid);
        }
        else if(Date < PDate) result = -1;
    }
    return result;
}

struct Q9_aux {
    FILE *res;
    int t1,t2,modo;
};

gboolean Q9Print_Aux(gpointer key, gpointer value, gpointer user_data) {
    Q9_aux *print = user_data;
    RIDES *ride = value;
    int t = getIdadeViagem (ride);
    if(t <= print->t1 && print->t2 <= t){
        char *id = getIdR (ride);
        char *date = getDateR (ride);
        int distance = getdistanceR (ride);
        char *city = getcityR (ride);
        double tip = getTip (ride);
        if(print->modo == 0) 
            fprintf(print->res, "%s;%s;%d;%s;%.3f\n", id, date, distance, city, tip);
        else
            printf("\t%s;%s;%d;%s;%.3f\n", id, date, distance, city, tip);
        free (id);
        free (date);
        free (city);
    }
    return FALSE;
}

void Q9Print (FILE *res, int t1, int t2, int modo) {
    Q9_aux *print = malloc(sizeof (Q9_aux));
    print -> res = res;
    print->t1 = t1; 
    print->t2 = t2; 
    print->modo = modo;
    foreach_print_Q9 (print);
    free (print); 
}