#ifndef query9
#define query9

typedef struct Q9_aux Q9_aux;

gint desempate_Q9(gconstpointer p1, gconstpointer p2);

gboolean Q9Print_Aux(gpointer key, gpointer value, gpointer user_data);

void Q9Print(FILE *res, int t1, int t2, int modo);

#endif