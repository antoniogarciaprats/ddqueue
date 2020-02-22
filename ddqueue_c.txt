
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#include "../include/ddqueue.h"

/* DESCRIPCION.-	

			La doble cola dinamica esta formada por una lista continua de nodos
			acabada en NULL; en principio est� construida como una lista de nodos
			dinamico tradicional. No obstante esta estructura de datos tiene una
			cabecera con dos punteros, los cuales, apuntan al primer nodo de cada
			cola ( izquierda y derecha, respectivamente ) manteniendo el siguiente
			orden: los primeros nodos pertenecen a la cola izquierda, y los �ltimos
			nodos pertenecen a la cola de la derecha.
			
			Las inserciones y borrados se realizan utilizando su propia primitiva
			o procedimiento, as� como el recorrido o la funcion booleana que com-
			prueba que la cola esta vacia. De �sta forma, el �nico c�digo que per-
			manece com�n a ambas colas es el construtor de la estructura y el des-
			tructor de la misma.
			
			Las operaciones que se realizan sobre �sta estructura de datos son las
			siguientes.-
				- Insercion de nodos en orden FIFO.
				- Borrado de nodos en orden FIFO.
				- Recorrido de cada una de las colas por separado ( derecha o
	                          izquierda ).
	   			- Comprobaci�n booleana de que la cola est� vacia.
	   			- Visualizacion del numero de nodos contenido en cada cola
	   		
	   		Las primitivas las agruparemos en la siguiente clasificaci�n.-
	   			- Constructores:	create.
	   			
	   			- Destructores:		erase.
	   			
	   			- Modificadores:	insertLeft
	   						insertRight
	   						deleteLeft
	   						deleteRight
	   						
	   			- Observadores:		acrossLeft
	   						acrossRight
	   						emptyLeft
	   						emptyRight
	   						nnQueueLeft
	   						nnQueueRight
	   		
	   		Este c�digo ha sido creado por.-	Antonio Garcia Prats.
	   		Version.-				1.0
	   		Sistema Operativo			SuSE Linux 7.0.
	   		
*/

// Definicion de un nodo de la cola ...
struct ddqueueNode {
	tGenData data;		    		//datos.
	struct ddqueueNode* next;              	//siguiente nodo.
};
// Definicion de la cabecera ...
struct ddqueueHead {
	struct ddqueueNode* leftQueue;   	//Cola de la izquierda.
	struct ddqueueNode* rightQueue;	 	//Cola de la derecha.
	unsigned int leftQueueNn; 		//Numero de nodos de la cola izquierda.
	unsigned int rightQueueNn; 		//Numero de nodos de la cola derecha.
};

//Procedimientos y Funciones Publicos del Tipo de Datos Abstracto DOBLE COLA DINAMICA.
/*	Constructor.- 	Construye la cabecera de la cola dinamica estableciendo los punteros
			al primero nodo de cada cola a NULL, e inicializando los contadores
			de cada cola a 0.
			
			Precondiciones:
			Ninguna.
			
			Postcondiciones:
			Devuelve una TAD doble cola dinamica vacio.
			En caso contrario devuelve NULL;
			
			Modifica:
			No tiene argumentos.
*/
DDQUEUE create ( void )
{
	struct ddqueueHead* ddq;
	
	ddq = ( struct ddqueueHead* ) malloc ( sizeof ( struct ddqueueHead ));
	if ( ddq == NULL ) return NULL;
	
	ddq->leftQueue = NULL;
	ddq->rightQueue = NULL;
	ddq->leftQueueNn = 0;
	ddq->rightQueueNn = 0;
	
	return ( ddq );
}

/*	Destructor.-	Destruye el tipo de dato abstracto doble cola dinamica devolviendo
			los recursos que utiliza al sistema. Para ello, utiliza la variable
			ddqindex como indice de la lista de nodos a borrar y ddqFreeNode co-
			mo la variable auxiliar que necesito para ir borrando cada nodo. Ade-
			m�s uso una variable booleana para acceder directamente al borrado de
			la cabecera si su valor es ED_FALSE o borrar los nodos si su valor es
			ED_TRUE.
			
			En caso de que ocurra alg�n error la funci�n devuelve ED_FALSE.
			
			Precondiciones:
			La cola debe existir.
			
			Postcondiciones:
			Libera la memoria ocupada por la cola.
			
			Modifica:
			*dDQueue
*/

int erase ( DDQUEUE* dDQueue )
{
	struct ddqueueNode* ddqIndex;
	struct ddqueueNode* ddqFreeNode;
	int auxFreeNode=0;
	
	if ( dDQueue == NULL ) return ED_FALSE;
	if ( emptyLeft ( *dDQueue ) == ED_TRUE )
		if ( emptyRight ( *dDQueue ) == ED_TRUE )
			ddqIndex = NULL;
		else {
			ddqIndex = (*dDQueue)->rightQueue;
			auxFreeNode = 1;
		}
	else {
		ddqIndex = (*dDQueue)->leftQueue;
		auxFreeNode = 1;
	}
	
	
	if ( auxFreeNode == ED_FALSE ) {
		while ( ddqIndex != NULL ) {
			ddqFreeNode = ddqIndex;
			ddqIndex = ddqFreeNode->next;
			free ( ddqFreeNode );
		}
	}
	
	free ( *dDQueue );
	return ED_TRUE;
}

/*	Modificador Insertar Izquierda.- Esta es quiz�s la forma de insertar que resulta m�s
			complicada, pero no demasiado, en �ste caso, creamos una variable cu-
			yo tama�o lo pasamos como argumento. Es cierto que esta variable la
			podr�amos haber pasado en el constructor como se hace habitualmente y
			nos ahorramos �ste argumento, pero por otro lado, el tama�o de la va-
			riable se puede definir como una constante en el programa principal o
			podemos usar distintas variables para cada nodo introduciendo m�s ver-
			satilidad, si cabe.
			
			Uso tres variables: ddqnn es la que utilizo para reservar la memoria del
			nuevo nodo y del nuevo dato respectivamente; la variable ddqIndex, como
			su nombre indica es un indice que utilizo para encontrar el �ltimo nodo
			de la cola izquierda; por ultimo, ddqEndNode me sirve para indicar cual
			es el primer nodo de la cola derecha o si, por el contrario, la cola de-
			recha est� actualmente vacia.
			
			El procedimiento es sencillo, compruebo las precondiciones; hago las re-
			servas de memoria oportunas y copio en el nuevo nodo el dato que quiero
			insertar y el puntero next lo actualio a NULL. A continuaci�n compruebo
			si la cola derecha esta vacia o no, de forma que actualizo el puntero
			auxiliar a NULL o a dDQueue->rightQueue. La insercion se realiza como en
			una cola normal. Por �ltimo, actualizo la direcci�n del nodo que acabo de
			insertar con la direcci�n del primer nodo de la cola derecha o a NULL si
			no hay; la ultima operaci�n es incrementar el contador.
			
			En caso de que ocurra un error la funcion devuelve ED_FALSE;
			
			Precondiciones:
			La doble cola dinamica debe estar creada.
			Haya memoria para el nodo.
			Haya memoria para el dato.
			
			Postcondiciones:
			Devuelve la doble cola dinamica con un nodo mas a�adido a la cola izq.
			Devuelve ED_FALSE en caso de algun problema, sino ED_TRUE.
			
			Modifica:
			dDQueue.
*/

int insertLeft ( tGenData data,
		 unsigned int size,
		 DDQUEUE dDQueue )
{
	struct ddqueueNode* ddqIndex;
	struct ddqueueNode* ddqEndNode;
	struct ddqueueNode* ddqnn;	
	
	if ( dDQueue == NULL ) return ED_FALSE;
	
	ddqnn = ( struct ddqueueNode* ) malloc ( sizeof ( struct ddqueueNode ));
	if ( ddqnn == NULL ) return ED_FALSE;
	
	ddqnn->data = ( void* ) malloc ( sizeof ( size ));
	if ( ddqnn->data == NULL ) return ED_FALSE;
		
	memcpy ( ddqnn->data, data, sizeof ( size ));
	ddqnn->next = NULL;
	
	if ( emptyRight ( dDQueue ) == ED_TRUE ) ddqEndNode = NULL;
	else ddqEndNode = dDQueue->rightQueue;
	
	if ( emptyLeft ( dDQueue ) == ED_TRUE )
		dDQueue->leftQueue = ddqnn;
	else {
		ddqIndex = dDQueue->leftQueue;
		while ( ddqIndex->next != ddqEndNode ) ddqIndex = ddqIndex->next;
	
		ddqIndex->next = ddqnn;
	}

	if ( ddqEndNode != NULL ) ddqnn->next = dDQueue->rightQueue;
	
	dDQueue->leftQueueNn++;
	return ED_TRUE;
}

/*	Modificador Insertar Derecha.- En este caso, al ser el orden de la cola FIFO, el nodo
			ser� insertado al final de la cola, en caso de que haya mas de un nodo
			o al principio de esta, en caso de que sea el primer nodo que introdu-
			cimos en la cola. Puesto que, seg�n nuestra estructura, la cola derecha
			esta situada en el segmento final de la lista, la inserci�n se reduce a
			una inserci�n tradicional: busco el final de la cola e inserto el nue-
			vo nodo.
			
			Hay que realizar, no obstante, una consideraci�n, y es que como la es-
			tructura de datos se ha concebido como una lista continua, en la que se
			distinguen dos colas de forma l�gica y no f�sica, se ha de poner especial
			cuidado en que el �ltimo nodo de la cola de la izquierda apunte al primer
			nodo de la cola de la derecha, y que esa referencia no se pierda.
			
			Las variables locales que utilizo aqui son: ddqnn que me sirve para la
			reserva de memoria del nuevo nodo, ddqIndex, que la utilizo como indice
			para localizar el �ltimo nodo de la cola a fin de realizar la inserci�n,
			y ddqAuxLeftNode que apunta al �ltimo nodo de la cola de la izquierda, de
			forma que se pueda realizar correctamente el enlace de �mbas colas.
			
			La funci�n devolver� ED_TRUE si todo va bien o ED_FALSE si ha ocurrido
			alg�n error.
			
			Precondiciones:
			La doble cola dinamica debe estar creada.
			Haya memoria para el nodo.
			Haya memoria para el dato.
			
			Postcondiciones:
			Devuelve estructura de datos con un nodo mas en la cola derecha.
			ED_TRUE si todo va bien.
			ED_FALSE si ha ocurrido alg�n problema.
			
			Modifica:
			*dDQueue.
*/

int insertRight ( tGenData data,
		  unsigned int size,
		  DDQUEUE dDQueue )
{
	struct ddqueueNode* ddqnn;
	struct ddqueueNode* ddqIndex;
	struct ddqueueNode* ddqAuxLeftNode;
	
	if ( dDQueue == NULL ) return ED_FALSE;
	
	ddqnn = ( struct ddqueueNode* ) malloc ( sizeof ( struct ddqueueNode ));
	if ( ddqnn == NULL ) return ED_FALSE;
	
	ddqnn->data = ( void* ) malloc ( sizeof ( size ));
	if ( ddqnn->data == NULL ) return ED_FALSE;
	
	memcpy ( ddqnn->data, data, sizeof ( size ));
	ddqnn->next = NULL;
	
	if ( emptyRight ( dDQueue ) == ED_TRUE ) {
		dDQueue->rightQueue = ddqnn;
 		if ( emptyLeft ( dDQueue ) == ED_FALSE )  {
			ddqAuxLeftNode = dDQueue->leftQueue;
			while ( ddqAuxLeftNode->next != NULL )
				ddqAuxLeftNode = ddqAuxLeftNode->next;
			ddqAuxLeftNode->next = dDQueue->rightQueue;
		}	
 	}
	else {
		ddqIndex = dDQueue->rightQueue;
		while ( ddqIndex->next != NULL ) ddqIndex = ddqIndex->next;
		ddqIndex->next = ddqnn;
	}
	
	dDQueue->rightQueueNn++;
	return ED_TRUE;
}

/*	Modificador Borrar Izquierda.-Esta rutina borra el primer nodo de la cola de la izquierda,
			esto es, borra el primer nodo de la lista que conforma la estructura de
			datos que hemos construido, por tanto, la eliminaci�n de dicho nodo no re-
			viste ning�n tipo de dificultad, pudiendo ser equivalente al borrado de un
			nodo en una cola tradicional.
			
			Las variables locales que aqu� utilizo son: auxDeleteNode que es la va-
			riable que apunta al nodo que voy a borrar y endLeftNode, que me indica
			cual es el primer nodo de la cola de la derecha o, si bien, en esta cola
			no hay ning�n nodo en cuyo caso su valor ser� NULL.
			
			Precondiciones:
			La cola debe existir.
			La cola de la izquierda no debe estar vacia.
			
			Postcondiciones:
			Elimina el primer nodo de la cola de la izquierda y devuelve los recursos
			al sistema. Si la operacion se verifica correctamente devolver� ED_TRUE.
			En caso de que ocurra alg�n error, devolver� ED_FALSE. Devuelve el valor
			del nodo borrado en la variable data.
			
			Modifica:
			dDQueue.
			data.
*/

int deleteLeft ( tGenData data,
		 DDQUEUE dDQueue )
{
	struct ddqueueNode* auxDeleteNode;
	struct ddqueueNode* endLeftNode;
	
	if ( dDQueue == NULL ) return ED_FALSE;
	
	if  ( emptyLeft ( dDQueue ) == ED_TRUE ) return ED_FALSE;
	
	auxDeleteNode = dDQueue->leftQueue;
	endLeftNode = dDQueue->rightQueue;
	
	if ( dDQueue->leftQueue->next == endLeftNode )	dDQueue->leftQueue = NULL;
	else dDQueue->leftQueue = dDQueue->leftQueue->next;

	memcpy ( data, auxDeleteNode->data, sizeof ( auxDeleteNode->data ));
	
	free ( auxDeleteNode->data );
	free ( auxDeleteNode );
	dDQueue->leftQueueNn--;
	
	return ED_TRUE;
}

/*	Modificador Borrar Derecha.- Esta operaci�n revistir�, quiz�s, alguna complicaci�n mas que
			la rutina anterior, puesto que, ahora, lo que estamos intentando borrar es
			el primer nodo de la cola de la derecha, esto es, un nodo que se encuentra
			dentro de la lista que conforma la estructura de datos; esto requerir�,
			por tanto, una serie de actualizaciones de punteros que deberemos reali-
			zar con cuidado no sea que perdamos alguna referencia, y, por tanto, co-
			rrompamos la estructura de datos.
			
			El primer nodo de la cola de la derecha lo encontramos de forma trivial,
			no obstante, es necesario encontrar una referencia al �ltimo nodo de la
			cola de la izquierda, y eso se realiza usando la variable local
			previousNode. El resto de la funci�n tiene un funcionamiento an�logo al
			de la funci�n anterior.
			
			Precondiciones:
			La cola debe estar creada.
			La cola derecha no puede estar vacia.
			
			Posconticiones:
			Elimina el nodo que ocupa la primera posici�n de la cola derecha y devuel-
			ve los recursos al sistema. En caso de que la operaci�n transcurra sin
			problemas devolveremos ED_TRUE. En caso contrario la funci�n devolver�
			ED_FALSE. Devuelve en el argumento data el valor contenido en �se nodo.
			
			Modifica:
			dDQueue.
			data.
*/

int deleteRight ( tGenData data,
                  DDQUEUE dDQueue )
{
	struct ddqueueNode* previousNode;
	struct ddqueueNode* auxdeleteNode;
	
	if ( dDQueue == NULL ) return ED_FALSE;
	
	if ( emptyRight ( dDQueue ) == ED_TRUE ) return ED_FALSE;
	
	previousNode = dDQueue->leftQueue;
	while ( previousNode->next != dDQueue->rightQueue ) previousNode = previousNode->next;
	
	auxdeleteNode = dDQueue->rightQueue;
	if ( dDQueue->rightQueue->next == NULL ) dDQueue->rightQueue = NULL;
	else dDQueue->rightQueue = dDQueue->rightQueue->next;
	
	previousNode->next = auxdeleteNode->next;

	memcpy ( data, auxdeleteNode->data, sizeof ( auxdeleteNode->data ));
	
	free ( auxdeleteNode->data );
	free ( auxdeleteNode );
	dDQueue->rightQueueNn--;
	
	return ED_TRUE;
}

/*	Observador Ver Cola Izquierda.- Este observador devuelve el valor del nodo cuya posicion
			se le indica como argumento. Por tanto habr� que indicar cu�l es la posi-
			ci�n que ocupa el nodo cuyo valor queremos visualizar en pantalla y que
			quedar� almacenado en la variable data que se le pasa como argumento. Los
			indices que utilizamos est�n comprendidos entre 1 y el n�mero total de no-
			dos de la cola.
			
			Precondiciones:
			La cola debe estar creada.
			La cola izquierda no estar� vacia.
			Se le indicar� el numero de nodo correcto.
			
			Postcondiciones:
			Devuelve el valor del nodo cuya posici�n le pasamos como argumento, en
			caso de que nos equivoquemos de numero, no devolver� nada, saldr� del
			procedimiento.
			
			Modifica:
			data.
*/

void acrossLeft ( tGenData data,
		  unsigned int ndata,		
		  DDQUEUE dDQueue )
{
	struct ddqueueNode* ddqIndex;
	register i;
	
	if ( dDQueue == NULL ) return;
	
	if ( emptyLeft ( dDQueue ) == ED_TRUE ) return;
	
	if ( dDQueue->leftQueueNn < ndata ) return;
	
	ddqIndex = dDQueue->leftQueue;
	for ( i=1; i<ndata; i++ ) ddqIndex = ddqIndex->next;
	memcpy ( data, ddqIndex->data, sizeof ( ddqIndex->data ));	
}

/*	Observador Ver Cola Derecha.- De la misma forma que en la rutina anterior, devolvemos el
			valor del nodo contenido en la cola de la derecha en la posicion indicada
			por ndata.
			
			Precondiciones:
			La cola debe estar creada.
			La cola derecha no estar� vac�a.
			
			Postcondiciones:
			Devuelve los valores contenidos en los nodos de la lista ademas del numero
			total de nodos.
			
			Modifica:
			data.
*/

void acrossRight ( tGenData data,
		   unsigned int ndata,
		   DDQUEUE dDQueue )
{
	struct ddqueueNode* ddqIndex;
	register i=1;
	
	if ( dDQueue == NULL ) return;
	
	if ( emptyRight ( dDQueue ) == ED_TRUE ) return;
	
	if ( dDQueue->rightQueueNn < ndata ) return;
	
	ddqIndex = dDQueue->rightQueue;
	
        while ( i < ndata ) {
        	ddqIndex = ddqIndex->next;
        	i++;
        }
        	
	memcpy ( data, ddqIndex->data, sizeof ( ddqIndex->data ));
}

/*	Observador Cola Izquierda Vacia.- Este observador comprueba si la cola izquierda tiene al-
			g�n nodo o por el contrario apunta a NULL, En el primer caso devolver�
			ED_TRUE, en caso contrario ED_FALSE.
			
			Precondiciones:
			La cola debe estar creada.
			
			Postcondiciones:
			Devuelve ED_TRUE si esta vacia o ED_FALSE en caso contrario. Tambien devol-
			vera ED_FALSE en caso de que la cola no exista.
			
			Modifica:
			Nada.
*/

int emptyLeft ( DDQUEUE dDQueue )
{
	if ( dDQueue == NULL ) return ED_FALSE;
	
	if ( dDQueue->leftQueue == NULL ) return ED_TRUE;
	else return ED_FALSE;
}


/*	Observador Cola Derecha Vacia.- Este observador comprueba si la cola derecha tiene al-
			g�n nodo o por el contrario el puntero de la cabecera correspondiente a-
			punta a NULL. Al igual que la rutina anterior, devolver� ED_TRUE en caso
			de que este vacia o devolvera ED_FALSE en caso de que la cola no exista o
			no este vacia.
			
			Precondiciones:
			La cola debe estar creada.
			
			Postcondiciones:
			Devuelve ED_TRUE si la cola esta vacia o ED_FALSE si no esta vacia o no
			esta creada.
			
			Modifica:
			Nada.
*/

int emptyRight ( DDQUEUE dDQueue )
{
	if ( dDQueue == NULL ) return ED_FALSE;
	
	if ( dDQueue->rightQueue == NULL ) return ED_TRUE;
	else return ED_FALSE;
}

/*	Observador Numero de Nodos Cola Izquierda.- Este observador es una funci�n que nos devuel-
			ve el numero de nodos que tiene actualmente la cola izquierda.
			
			Precondiciones:
			La cola debe estar creada.
			
			Postcondiciones:
			Devuelve el numero de nodos que tiene la cola izquierda. En caso de que la
			cola no exista o no este creada devuelve -1;
			
			Modifica:
			Nada
*/

int nnQueueLeft ( DDQUEUE dDQueue )
{
	if ( dDQueue == NULL ) return -1;
	
	return dDQueue->leftQueueNn;
}

/*	Observador Numero de Nodos Cola Derecha.- Este Observador es una funcion que nos devuel-
			ve el numero de nodos que tiene actualmente la cola derecha.
			
			Precondiciones:
			La cola debe estar creada.
			
			Postcondiciones:
			Devuelve el numero de nodos que tiene la cola derecha. En caso de que la
			cola no exista o no este creada devuelve -1.
			
			Modifica:
			Nada.
*/

int nnQueueRight ( DDQUEUE dDQueue )
{
	if ( dDQueue == NULL ) return -1;
	
	return dDQueue->rightQueueNn;
}