#include <stdio.h>
#include <stdlib.h>
#include "../include/queries.h"


void dealwithquerie (char **argv) {
    int q = atoi (argv[0]);
    switch (q)
    {
    case 1:
        break;
    
    default:
        break;
    }
    return;
}

/*
calculaIdade(char *str){
    int i;
    int d = atoi(strsep(&str, "/"));
    int m = atoi(strsep(&str, "/"));
    int a = atoi(strsep(&str, "/"));
    if(d >= 9 && m >= 10 && a <= 2022) i = 2022 - a;
    else if((d >= 9 && m < 10) || (d < 9 && m == 10)) i = (2022 - a) - 1;
    return i;
}
*/