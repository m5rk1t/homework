#include <stdio.h>
#include <stdlib.h>


typedef struct z
{
	unsigned int sila;
	unsigned int id;
} Zviratko;

typedef struct TList TLIST;
typedef struct heap
{
	Zviratko * root;
	TLIST * child;    // seznam pro potomky
} Heap;

typedef struct n
{
	Heap * frontaMax;
	Heap * frontaMin;
} Nakladak;
Nakladak nakladaky[10000];

typedef struct TItem  // seznam zdroj:edux. edit
{
  struct TItem  * m_Next;  
  struct TItem  * m_Prev;
  Heap * m_Val;   
} TITEM;

struct TList
{
  struct TItem  * m_First; 
	struct TItem * m_Last;
};


TLIST            * ListInit      ()
{
  TLIST * l;

  l = (TLIST*) malloc ( sizeof ( *l ) );
  l -> m_First = l->m_Last= NULL;    
  return l;
}

TLIST *  ListInsBefore  ( TLIST * l, Heap * val )
{
  TITEM * n = (TITEM *) malloc ( sizeof ( *n ) );
  if ( ! n ) return NULL;
  
  n -> m_Val  = val;
  n -> m_Prev = n -> m_Next = NULL;

  if ( ! l -> m_First )  /* prazdny seznam */
   {
     l -> m_First = l->m_Last = n;
     return l;
   }

  n -> m_Next = l -> m_First;     
  l -> m_First -> m_Prev = n;
	l->m_First = n ;
  return l;
}

Heap * HeapInit()
{
	Heap * h = (Heap*) malloc ( sizeof ( *h ) );
	h->root = NULL; 
	 h->child = ListInit();    
  return h;

}
Heap * Merge (Heap * staryStrom, Heap * dalsiStrom, char flag)
{
	if(!staryStrom)
		return dalsiStrom;
	if(!dalsiStrom)
		return staryStrom;

	if( flag == '2')
	{
		if( staryStrom->root->sila > dalsiStrom->root->sila )
		{
			dalsiStrom->child = ListInsBefore(dalsiStrom->child, staryStrom);  //koren s vetsi silou se stane ditetem druheho. Dite pridam na levy kraj
			return dalsiStrom;
		}
	
		else if (staryStrom->root->sila < dalsiStrom->root->sila )
		{
			staryStrom->child = ListInsBefore(staryStrom->child, dalsiStrom);
			return staryStrom;
		}
		else 
		{
			if( staryStrom->root->id > dalsiStrom->root->id )
			{
				dalsiStrom->child = ListInsBefore(dalsiStrom->child, staryStrom);
				return dalsiStrom;
			}
			else
			{
				staryStrom->child = ListInsBefore(staryStrom->child, dalsiStrom);
				return staryStrom;
			}

		}
	}
	else // max
	{
		if( staryStrom->root->sila < dalsiStrom->root->sila )
		{
			dalsiStrom->child = ListInsBefore(dalsiStrom->child, staryStrom);  //koren s vetsi silou se stane ditetem druheho. Dite pridam na levy kraj
			return dalsiStrom;
		}
	
		else if (staryStrom->root->sila > dalsiStrom->root->sila )
		{
			staryStrom->child = ListInsBefore(staryStrom->child, dalsiStrom);
			return staryStrom;
		}
		else 
		{
			if( staryStrom->root->id > dalsiStrom->root->id )
			{
				dalsiStrom->child = ListInsBefore(dalsiStrom->child, staryStrom);
				return dalsiStrom;
			}
			else
			{
				staryStrom->child = ListInsBefore(staryStrom->child, dalsiStrom);
				return staryStrom;
			}

		}
	}
}
Heap * Insert (Heap * staryStrom, Zviratko * zvir, char flag)
{
	Heap * dalsiStrom = HeapInit();
	dalsiStrom->root = zvir; 
	return Merge (staryStrom, dalsiStrom, flag);
}

Zviratko * Find(Heap * h)
{
	return h->root;
}

Heap * Extract(Heap * h, Zviratko * elem, char flag)
{
	Heap * pom =NULL; Heap * stara_pom =NULL; TITEM * pomocnaFree=NULL;
	if( (elem->sila== 0 && flag =='1') || (elem->sila == 4294967295 && flag =='2'))
	{
		free(elem);
	}
	else if(flag =='2')
	elem->sila = 0;
	else
	elem->sila = 4294967295;
	//free();
	h->root=NULL;
	TITEM * i = h->child->m_Last;
	free(h);

	for ( ; i ; i = i->m_Prev->m_Prev)
	{
		free(pomocnaFree);
		if(i->m_Prev)
		{
			pom = Merge (i->m_Prev->m_Val, i->m_Val, flag);
			if(stara_pom)
				pom = Merge (stara_pom, pom, flag);
			stara_pom=pom;
			pomocnaFree = i->m_Prev;
		}
		else
		{ 
			pomocnaFree=i;
			if ( pom)
				return Merge (pom, i->m_Val, flag);
			else return i->m_Val;
		}
	}

	return pom;
}
void NakladakInsert (int cislo_nakl, unsigned int id, unsigned int sila )
{
	Zviratko * zviratko = (Zviratko*) malloc (sizeof(*zviratko));
	zviratko->id =id; zviratko->sila = sila;
	nakladaky[cislo_nakl].frontaMin = Insert ( nakladaky [cislo_nakl].frontaMin, zviratko, '2');
	nakladaky[cislo_nakl].frontaMax = Insert ( nakladaky [cislo_nakl].frontaMax, zviratko, '1');
	
	
}
void volba0()
{
	int k; unsigned int id,s;
	scanf("%d %u %u", &k, &id, &s);
	--k;
	NakladakInsert( k, id, s);
}
void volba1()
{
	int k; Zviratko *z; 
	scanf("%d", &k);
	--k;
	if( ! nakladaky[k].frontaMax ){
		printf("empty\n");
		return;
	}
	z = Find (nakladaky[k].frontaMax);
	while (nakladaky[k].frontaMax && z->sila == 0)
	{
		nakladaky[k].frontaMax = Extract (nakladaky[k].frontaMax, z, '1');
		if(!nakladaky[k].frontaMax)
		{
			printf("empty\n");
				return;
		}
		z = Find (nakladaky[k].frontaMax);
		
	}
	printf("%u\n", z->id);
	nakladaky[k].frontaMax = Extract (nakladaky[k].frontaMax, z, '1');
}
void volba2 ()
{
	int k; Zviratko *z; 
	scanf("%d", &k);
	--k;
	if( ! nakladaky[k].frontaMin ){
		printf("empty\n");
		return;
	}
	z = Find (nakladaky[k].frontaMin);
	while( nakladaky[k].frontaMin && z->sila == 4294967295 )
	{
		nakladaky[k].frontaMin = Extract (nakladaky[k].frontaMin, z, '2');
		if(!nakladaky[k].frontaMin)
		{
			printf("empty\n");
				return;
		}
		z = Find (nakladaky[k].frontaMin);
	}
	printf("%u\n", z->id);
	nakladaky[k].frontaMin = Extract (nakladaky[k].frontaMin, z, '2');
}	
void volba3()
{
	int cil, zdroj; 
	scanf("%d %d", &cil, &zdroj);
	--cil; --zdroj;
	if( cil != zdroj)
	{
		nakladaky[cil].frontaMin =Merge(nakladaky[cil].frontaMin, nakladaky[zdroj].frontaMin, '2');
		nakladaky[zdroj].frontaMin=NULL;
		nakladaky[cil].frontaMax =Merge(nakladaky[cil].frontaMax, nakladaky[zdroj].frontaMax, '1');
		nakladaky[zdroj].frontaMax=NULL;
	}
}
int main()
{
	char prikaz;
	do{
		scanf(" %c", &prikaz);
		switch (prikaz)
		{
			case '0': volba0(); break;
			case '1': volba1(); break;
			case '2': volba2(); break;
			case '3': volba3(); break;
		}
	}
	while (prikaz != '4');


	return 0;
}
