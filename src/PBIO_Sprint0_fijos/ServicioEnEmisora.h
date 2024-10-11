// -*- mode: c++ -*-

// ----------------------------------------------------------
// Jordi Bataller i Mascarell
// 2019-07-17
// 
// Pablo Meana Gonzalez
// 2024-10-10
//
// ----------------------------------------------------------
#ifndef SERVICIO_EMISORA_H_INCLUIDO
#define SERVICIO_EMISORA_H_INCLUIDO

// ----------------------------------------------------
// ----------------------------------------------------
#include <vector>

// ----------------------------------------------------
// alReves() utilidad
// pone al revés el contenido de una array en el mismo array
// ----------------------------------------------------
template< typename T >

// Esto es una plantilla, no una función. Sirve para poner al revés un array
T *  alReves( T * p, int n ) {
  T aux;

  for( int i=0; i < n/2; i++ ) {
	aux = p[i];
	p[i] = p[n-i-1];
	p[n-i-1] = aux;
  }
  return p;
} // ()

// ----------------------------------------------------
// ----------------------------------------------------

// Char, Z, Z -> stringAUint8AlReves() -> Z
// Sirve para poner al revés un string en un array
uint8_t * stringAUint8AlReves( const char * pString, uint8_t * pUint, int tamMax ) {

	int longitudString =  strlen( pString );
	int longitudCopiar = ( longitudString > tamMax ? tamMax : longitudString );  // copiar hasta tamMax
	// copio nombreServicio -> uuidServicio pero al revés
	for( int i=0; i<=longitudCopiar-1; i++ ) {
	  pUint[ tamMax-i-1 ] = pString[ i ];  // al revés
	} // for

	return pUint;
} // ()

// ----------------------------------------------------------
// ----------------------------------------------------------

// ServicioEnEmisora sirve para añadir servicios a la emisora
class ServicioEnEmisora {

public:


  // --------------------------------------------------------
  // --------------------------------------------------------

  // .........................................................
  // .........................................................

  // CallbackCaracteristicaEscrita es un puntero a función. Sus parametros son el conn_handle, la característica, los datos y la longitud de los datos
  using CallbackCaracteristicaEscrita = void ( uint16_t conn_handle,
											   BLECharacteristic * chr,
											   uint8_t * data, uint16_t len); 
  // .........................................................
  // .........................................................


  // La clase Caracteristica sirve para añadir características a un servicio, y para escribir y notificar datos en dichas características
  class Caracteristica {
  private:
	uint8_t uuidCaracteristica[16] = { // el uuid se copia aquí (al revés) a partir de un string-c
	  // least signficant byte, el primero
	  '0', '1', '2', '3', 
	  '4', '5', '6', '7', 
	  '8', '9', 'A', 'B', 
	  'C', 'D', 'E', 'F'
	};

	// 
	// 
	// 
	BLECharacteristic laCaracteristica;

  public:

	// .........................................................
	// .........................................................

	// Constructor
	Caracteristica( const char * nombreCaracteristica_ )
	  :
	  laCaracteristica( stringAUint8AlReves( nombreCaracteristica_, &uuidCaracteristica[0], 16 ) )  // el uuid se copia aquí (al revés) a partir de un string-c
	{
	  
	} // ()

	// .........................................................
	// .........................................................

	// Constructor
	Caracteristica( const char * nombreCaracteristica_ ,
					uint8_t props,
					SecureMode_t permisoRead,
					SecureMode_t permisoWrite, 
					uint8_t tam ) 
	  :
	  Caracteristica( nombreCaracteristica_ ) // llamada al otro constructor
	{
	  (*this).asignarPropiedadesPermisosYTamanyoDatos( props, permisoRead, permisoWrite, tam );   // esto no funciona si lo pongo en el constructor
	} // ()

  private:
	// .........................................................
	// CHR_PROPS_WRITE , CHR_PROPS_READ ,  CHR_PROPS_NOTIFY 
	// .........................................................

	// Z -> asignarPropiedades() -> 
	// Sirve para asignar propiedades a una característica
	void asignarPropiedades ( uint8_t props ) {
	  // no puedo escribir AUN si el constructor llama a esto: Serial.println( " laCaracteristica.setProperties( props ); ");
	  (*this).laCaracteristica.setProperties( props );
	} // ()

	// .........................................................
	// SecureMode_t::SECMODE_OPEN  , SecureMode_t::SECMODE_NO_ACCESS
	// .........................................................

	// SecureMode_t, SecureMode_t -> asignarPermisos() ->
	// Sirve para asignar permisos de lectura y escritura a una característica
	void asignarPermisos( SecureMode_t permisoRead, SecureMode_t permisoWrite ) {
	  // no puedo escribir AUN si el constructor llama a esto: Serial.println( "laCaracteristica.setPermission( permisoRead, permisoWrite ); " );
	  (*this).laCaracteristica.setPermission( permisoRead, permisoWrite );
	} // ()

	// .........................................................
	// .........................................................

	// Z -> asignarTamanyoDatos() ->
	// Sirve para asignar el tamaño de los datos de una característica
	void asignarTamanyoDatos( uint8_t tam ) {
	  // no puedo escribir AUN si el constructor llama a esto: Serial.print( " (*this).laCaracteristica.setFixedLen( tam = " );
	  // no puedo escribir AUN si el constructor llama a esto: Serial.println( tam );
	  // (*this).laCaracteristica.setFixedLen( tam );
	  (*this).laCaracteristica.setMaxLen( tam );
	} // ()

  public:
	// .........................................................
	// .........................................................

	// Z, SecureMode_t, SecureMode_t, Z -> asignarPropiedadesPermisosYTamanyoDatos() ->
	// Sirve para asignar propiedades, permisos y tamaño de datos a una característica
	void asignarPropiedadesPermisosYTamanyoDatos( uint8_t props,
												 SecureMode_t permisoRead,
												 SecureMode_t permisoWrite, 
												 uint8_t tam ) {
	  asignarPropiedades( props );
	  asignarPermisos( permisoRead, permisoWrite );
	  asignarTamanyoDatos( tam );
	} // ()
												 

	// .........................................................
	// .........................................................

	// Char -> escribirDatos() -> Z
	// Sirve para escribir datos en una característica y devuelve el número de bytes escritos
	uint16_t escribirDatos( const char * str ) {
	  // Serial.print( " return (*this).laCaracteristica.write( str  = " );
	  // Serial.println( str );

	  uint16_t r = (*this).laCaracteristica.write( str );

	  // Serial.print( ">>>Escritos " ); Serial.print( r ); Serial.println( " bytes con write() " );

	  return r;
	} // ()

	// .........................................................
	// .........................................................

	// Char -> notificarDatos() -> Z
	// Sirve para notificar datos en una característica y devuelve el número de bytes notificados
	uint16_t notificarDatos( const char * str ) {
	  
	  uint16_t r = laCaracteristica.notify( &str[0] );

	  return r;
	} //  ()

	// .........................................................
	// .........................................................
	// CallbackCaracteristicaEscrita --> instalarCallbackCaracteristicaEscrita() -->
	// Sirve para instalar un callback de escritura en una característica
	void instalarCallbackCaracteristicaEscrita( CallbackCaracteristicaEscrita cb ) {
	  (*this).laCaracteristica.setWriteCallback( cb );
	} // ()

	// .........................................................
	// .........................................................

	// -> activar() ->
	// Sirve para activar una característica
	void activar() {
	  err_t error = (*this).laCaracteristica.begin();
	  Globales::elPuerto.escribir(  " (*this).laCaracteristica.begin(); error = " ); 
	  Globales::elPuerto.escribir(  error ); 
	} // ()

  }; // class Caracteristica
  
  // --------------------------------------------------------
  // --------------------------------------------------------
private:
  
  uint8_t uuidServicio[16] = { // el uuid se copia aquí (al revés) a partir de un string-c
	// least signficant byte, el primero
	'0', '1', '2', '3', 
	'4', '5', '6', '7', 
	'8', '9', 'A', 'B', 
	'C', 'D', 'E', 'F'
  };

  //
  //
  //
  BLEService elServicio;

  //
  //
  //
  std::vector< Caracteristica * > lasCaracteristicas; // vector de punteros a características (Caracteristica)

public:
  
  // .........................................................
  // .........................................................

  // Constructor
  ServicioEnEmisora( const char * nombreServicio_ )
	:
	elServicio( stringAUint8AlReves( nombreServicio_, &uuidServicio[0], 16 ) ) // el uuid se copia aquí (al revés) a partir de un string-c
  {
	
  } // ()
  
  // .........................................................
  // .........................................................
  
  // -> escribirUUID() ->
  // Sirve para escribir el UUID de un servicio
  void escribeUUID() {
	Serial.println ( "**********" );
	for (int i=0; i<= 15; i++) {
	  Serial.print( (char) uuidServicio[i] );
	}
	Serial.println ( "\n**********" );
  } // ()

  // .........................................................
  // .........................................................

  // Caracteristica -> anyadirCaracteristica() ->
  // Sirve para añadir una característica a un servicio de la emisora
  void anyadirCaracteristica( Caracteristica & car ) {
	(*this).lasCaracteristicas.push_back( & car );
  } // ()

  // .........................................................
  // .........................................................

  // -> anyadirServicio() ->
  // Sirve para añadir un servicio a la emisora
  void activarServicio( ) {
	// entiendo que al llegar aquí ya ha sido configurado
	// todo: características y servicio

	err_t error = (*this).elServicio.begin();
	Serial.print( " (*this).elServicio.begin(); error = " );
	Serial.println( error );

	for( auto pCar : (*this).lasCaracteristicas ) {  // para cada característica en lasCaracteristicas 
	  (*pCar).activar();  // activar la característica
	} // for

  } // ()

  // .........................................................
  // .........................................................

  // Esto es una conversión de tipo. 
  operator BLEService&() {
	// "conversión de tipo": si pongo esta clase en un sitio donde necesitan un BLEService
	return elServicio;
  } // ()
	
}; // class

#endif

// ----------------------------------------------------------
// ----------------------------------------------------------
// ----------------------------------------------------------
// ----------------------------------------------------------

