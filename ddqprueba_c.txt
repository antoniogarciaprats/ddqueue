
#include <stdio.h>
#include <stdlib.h>


#include "../include/ddqueue.h"

int main ( int argc, char** argv )
{
	DDQUEUE cola;
	int operacion;
	int contador, numero;
	
	//Llamar al constructor ...
	cola = create ( );         	
		
	//Probamos las funciones de insercion ...
	for ( contador=1; contador<=10; contador++ ) {
		insertLeft ( ( tGenData ) &contador, sizeof ( contador ), cola );
		acrossLeft ( ( tGenData ) &numero, contador, cola );
		printf ( "El valor del numero    izquierda es igual a ... %d\n", numero );
		insertRight ( ( tGenData )&contador, sizeof ( contador ), cola );
		acrossRight ( ( tGenData )&numero, contador, cola );
		printf ( "El valor del numero derecha es igual a ... %d\n", numero );
	}
	
	//Probamos la funcion de borrado de la cola izquierda ...
	for ( contador=1; contador<=5; contador++ ) {
		deleteLeft ( ( tGenData )&numero, cola );
		printf ( "El valor que saco es igual a %d\n", numero );
	}
	
	//Recorro la cola izquierda de nuevo ...
	for ( contador=1; contador<=5; contador++ ) {
		acrossLeft ( ( tGenData ) &numero, contador, cola );
		printf ( "El valor del numero izquierda es igual a ... %d\n", numero );
	}
	
	//Probamos la funcion de borrado de la cola derecha ...
	for ( contador=1; contador<=5; contador++ ) {
		deleteRight ( ( tGenData )&numero, cola );
		printf ( "El valor que saco es igual a %d\n", numero );
	}
	
	//Recorro la cola derecha de nuevo ...
	for ( contador=1; contador<=5; contador++ ) {
		acrossRight ( ( tGenData ) &numero, contador, cola );
		printf ( "El valor del numero derecha es igual a ... %d\n", numero );
	}
	
	//El numero de nodos que tiene la cola izquierda es ...
	printf ( "El numero de nodos que tiene la cola izquierda es %d\n", nnQueueLeft ( cola ));
	
	//El numero de nodos que tiene la cola derecha es ...
	printf ( "El numero de nodos que tiene la cola derecha es %d\n", nnQueueRight ( cola ));
	
	//Borramos el resto de nodos de la cola izquierda ...
	for ( contador=1; contador<=5; contador++ ) {
		deleteLeft ( ( tGenData )&numero, cola );
		printf ( "El numero que saco de la cola izquierda es igual a %d\n", numero );
	}
	
	//Compruebo si realmete la cola izquierda esta vacia ...
	if ( emptyLeft ( cola ) == ED_TRUE ) printf ( "La cola izquierda esta vacia..\n" );
	else printf ( "La cola izquierda no esta vacia.\n" );
	
	//Llamar al destructor ...
	operacion = erase ( &cola );
	if ( operacion == ED_TRUE )
		printf ( "\nLa cola ha sido destruida ...\n" );
	else printf ( "La cola no ha sido destruida correctamente ...\n" );
}
	
		