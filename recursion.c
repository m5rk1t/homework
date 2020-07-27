#include <stdio.h>
#include <stdlib.h>  
/* Problem deleni koristi. Mame n emisi a 3 vyfuky.
 * Chceme emise rozdelit mezi vyfuky tak, aby maximum namerene pres jednotlive vyfuky bylo co nejnizsí.
 */

 int max=1000000;
 /** Funkce pro deleni emisi. .
 *
 * @param values [in] pole s hodnotami rozdelovanych predmetu.
 * @param valuesNr [in] pocet predmetu v poli
 * pole - cisla prirazenych ventilu pro kazdou emisi, stopy
 */ 
int tryDivide ( int * values, int valuesNr, int x1, int x2, int x3, int * pole)
 {
 	int maximum, max1, max2, max3;
   	if ( ! valuesNr)   { 
		    /****idealni pripad na bonus if(x1==x2 && x2==x3) ukonceni***/

   		
		   if(x1==x2 && x2==x3) {
		   			max=x1; 
		   			return 2;
		   	}
			if(x1>=x2){
					if(x1>=x3)  maximum=x1 ;
					else        maximum=x3 ;
			} 
		    else if(x2>=x3) 
		           maximum= x2 ;
		         else  
		           maximum= x3;
		         
		    if(max>maximum){
		            max=maximum; 
		            return 1;
		    } 
		    else return 0; 
	}
      
    max1= tryDivide ( values + 1, valuesNr - 1, x1 + *values, x2, x3, pole); 
    if(max1) {
	       pole[valuesNr-1]=1 ;
	        if(max1==2) return max1;
    }
    max2= tryDivide ( values + 1, valuesNr - 1, x1, x2 + *values, x3, pole ) ; 
    if(max2){
		    pole[valuesNr-1]=2;
		    if(max2==2) return max2;
    }
    max3= tryDivide ( values + 1, valuesNr - 1, x1, x2, x3 + *values, pole);
    if( max3){
	        pole[valuesNr-1]=3;
	        if(max3==2) return max3;
    }
    return max1||max2|| max3;   
 
 }
/*---------------------------------------------------------------------------*/
/** Funkce pro vypis rozdelenych emisi. 
 *
 * @param values [in] pole s hodnotami rozdelovanych predmetu.
 * @param valuesNr [in] pocet predmetu v poli
 * pole - cisla prirazenych ventilu pro kazdou emisi, stopy
 */

void canDivide3 ( int * values, int valuesNr, int * pole )
 {  
 	int delka=valuesNr, pocet1=0, pocet2=0, pocet3=0;
   	tryDivide ( values, valuesNr, 0, 0, 0 , pole);
   	printf("Nejvyssi emise: %d\n",  max);

   	
   	//(while pocet1!=3){ printf ( "%c, %dvojt",'A'+ pocet1, ':') ...
   	printf ( "A:");
    for(int i=0; i<delka; i++){         
        if( pole[i]==1 ){
		         ++pocet1;
		         printf ( "%s%d ", (pocet1==1)? " " : ",", values[delka-1-i]);
         }
    }
    printf ( "\n");
           
    printf ( "B:");
    for(int i=0; i<delka; i++){         
         if( pole[i]==2 ){
	         ++pocet2;
	         printf ( "%s%d ", (pocet2==1)? " " : ",", values[delka-1-i]);
         }
    }
    printf ( "\n");
    printf ( "C:");
    for(int i=0; i<delka; i++){         
         if( pole[i]==3 ){
	         ++pocet3;
	         printf ( "%s%d ", (pocet3==1)? " " : ",", values[delka-1-i]);
         }
    }
    printf ( "\n");
   
  
 }
/*---------------------------------------------------------------------------*/
int main ( int argc, char * argv [] )
 {
 	int res, emise, pocet=0; int * data=NULL; int * pole=NULL; 
   	printf("Emise ventilu:\n"); 
  	while ( (res = scanf ( "%d", &emise ) ) == 1 && emise>0 ){
		 	++pocet;
		 	data = (int *) realloc ( data, pocet * sizeof ( *data ) );
		 	data[pocet-1]=emise;
  
  	}
  	if ( res != EOF || pocet ==0) 
    {  
		    printf("Nespravny vstup.\n"); 
		    free ( data );
      		return 1;
    } 
  	pole = (int *) calloc( pocet , sizeof (*pole)); 
	canDivide3 ( data, pocet, pole);
    free(pole);
    free ( data );
    
   	return  0 ;
 }
