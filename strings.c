 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct a {
    double cetnost;
    char *fraze;
} Text;

int porovnej(Text* a, Text* b) {
    double cA = a->cetnost;
    double cB = b->cetnost;
    if (fabs(cA - cB) < 1e-6 * cB)
        return 0;
    else if (cA < cB)
        return 1;

    return -1;
}

Text* nactiText(int * n) {
    Text * data = NULL;
    char d;
    double cetnost, konecVstupu = 0;
    *n = 0;
    char * radek = NULL;
    size_t velikost = 0;
    while (!konecVstupu) {
        if (getline(&radek, &velikost, stdin) <= 0) {
            if((*n)>0){
                    for (int f = 0; f < (*n); ++f) 
                        free(data[f].fraze); 
            }
            free(radek);
            free(data);
            return NULL;
        }
        radek[ strlen(radek) - 1 ] = '\0';
        if (sscanf(radek, "%lf %c", &cetnost, &d) == 2 && d == ':' && strcmp((strchr(radek, ':') + 1),"\0" ) ) { 
            data = (Text *) realloc(data, ((*n) + 1) * sizeof (*data));
            data[*n].cetnost = cetnost;            
            data[*n].fraze = strdup(strchr(radek, ':') + 1);            
            (*n)++;
        }
        else if (radek[0]=='\0') {          /*radek[0]=='\0'*/
            konecVstupu = 1;
        } else {
              if((*n)>0){
                  for (int a = 0; a < (*n); ++a) 
                      free(data[a].fraze); 
              }
              free(radek);
              free(data);
              return NULL;
          }
    }

    free(radek);
    return data;
}

int hledejDotaz(Text* text, int n) {
    char * r = NULL;
    size_t vel= 0;
    int pocet=0, pocet2=0;
    while (getline(&r, &vel, stdin) !=-1) {
        r[ strlen(r) - 1 ] = '\0';
        if(r[0]== '\0'){ 
            free(r); 
            return 0;
        }
          
        for ( int i = 0; i < n; ++i) {
          if (strcasestr(text[i].fraze, r) != NULL){
              ++pocet;
          }
        }
        printf("Nalezeno: %d\n", pocet);
        if(pocet>0){
            for (int b = 0; b < n; ++b) { 
                if (strcasestr(text[b].fraze, r) != NULL){ 
                    printf("> %s\n", text[b].fraze);
                    pocet2++ ;
                }
                if (pocet2==50)
                    break;   
          }
        }
        pocet2=0;
        pocet = 0;
   
   } 
    free(r);
    if (!feof(stdin)) 
        return 0;
         
    return 1;
}

int main(void) {
    int n;
    Text * data;
    printf("Casto hledane fraze:\n");
    data = nactiText(&n);
    
    if (!data) {
        printf("Nespravny vstup.\n");
        return 1;
    } 
    
    if (n > 1) {
        qsort((void*) data, n, sizeof (Text), (int(*)(const void *, const void *))porovnej);
    }
    printf("Hledani:\n");
    if (!hledejDotaz(data, n)) {
        for (int a = 0; a < n; ++a) 
          free(data[a].fraze); 
        free(data);
        printf("Nespravny vstup.\n");
        return 1;
    }
    for (int k = 0; k < n; ++k) 
        free(data[k].fraze); 
    free(data);
    return 0;
}
