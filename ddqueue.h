
#ifndef _TAD_BICOLA_DINAMICA_PRACT_2000_01_EDI1_
#define _TAD_BICOLA_DINAMICA_PRACT_2000_01_EDI1_

#define ED_TRUE	1	// Definimos la constante Estructura de Datos Verdadero
#define ED_FALSE 0	// Definimos la constante Estructura de Datos Falso


//El dato que podr� almacenar la doble cola lo vamos a definir como void*
//para que sea lo mas generico posible ...
typedef void* tGenData;

//Definimos el tipo de dato doble cola dinamica de punteros a void.
typedef struct ddqueueHead* DDQUEUE;

//Operaciones definidas en el TAD doble cola dinamica ...
DDQUEUE create ( void );				// CONSTRUCTOR.
int erase (  DDQUEUE* dDQueue );                  	// DESTRUCTOR.
int insertLeft ( tGenData data,				// INSERTAR UN ELEMENTO A IZQUIERDA
		 unsigned int size,
		 DDQUEUE dDQueue );
int insertRight ( tGenData data,			// INSERTAR UN ELEMENTO A DERECHA
		  unsigned int size,
		  DDQUEUE dDQueue );
int deleteLeft ( tGenData data,				// BORRAR UN ELEMENTO A IZQUIERDA
	         DDQUEUE dDQueue );
int deleteRight ( tGenData data, 			// BORRAR UN ELEMENTO A DERECHA
		  DDQUEUE dDQueue );
void acrossLeft ( tGenData data,			// RECORRER LA COLA IZQUIERDA
		  unsigned int ndata,
		  DDQUEUE dDQueue );
void acrossRight ( tGenData data,			// RECORRER LA COLA DERECHA
		   unsigned int ndata,
		   DDQUEUE dDQueue );
int emptyLeft ( DDQUEUE dDQueue );			// �ESTA LA COLA IZQUIERDA VACIA?
int emptyRight ( DDQUEUE dDQueue );			// �ESTA LA COLA DERECHA VACIA?
int nnQueueLeft ( DDQUEUE dDQueue );            	// �CUANTOS NODOS TIENE LA COLA IZQUIERDA?
int nnQueueRight ( DDQUEUE dDQueue );			// �CUANTOS NODOS TIENE LA COLA DERECHA?

#endif