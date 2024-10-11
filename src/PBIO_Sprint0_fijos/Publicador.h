// -*- mode: c++ -*-

// --------------------------------------------------------------
// Jordi Bataller i Mascarell
//
// Pablo Meana Gonzalez
// 2024-10-10
//
// --------------------------------------------------------------

#ifndef PUBLICADOR_H_INCLUIDO
#define PUBLICADOR_H_INCLUIDO

// --------------------------------------------------------------
// --------------------------------------------------------------

// La clase Publicador sirve para publicar valores de CO2 en la emisora BLE
class Publicador {

  // ............................................................
  // ............................................................
private:

  /*uint8_t beaconUUID[16] = { //UUID del Beacon // --------------------------------------------- CAMBIAR
	'E', 'P', 'S', 'G', '-', 'G', 'T', 'I', 
	'-', 'P', 'R', 'O', 'Y', '-', '3', 'A'
	};*/

uint8_t beaconUUID[16] = { //UUID del Beacon // --------------------------------------------- ESTE ES EL NOMBRE QUE TE PIDE QUE MUESTRE EN LA WEB
  'M', 'A', 'T', 'X', 'O', '-', 'L', 'L', 
  'E', 'V', 'A', 'N', 'T',  '-', 'U', 'D'
  };
  

  // ............................................................
  // ............................................................
public:
  EmisoraBLE laEmisora {
	"Manolito", //  nombre emisora   //Nombre que aparece como dispositivo en nRFConnect ----------- CAMBIAR
	  0x004c, // fabricanteID (Apple)
	  4 // txPower
	  };
  
  const int RSSI = -53;

  // ............................................................
  // ............................................................
public:

  // ............................................................
  // ............................................................
  enum MedicionesID  {  // --------------------------------------------- CAMBIAR
	CO2 = 11,
	};

  // ............................................................
  // ............................................................
  // constructor
  Publicador( ) {
	// ATENCION: no hacerlo aquí. (*this).laEmisora.encenderEmisora();
	// Pondremos un método para llamarlo desde el setup() más tarde
  } // ()

  // ............................................................
  // ............................................................
  // --> encenderEmisora() --> 
  // Sirve para encender la emisora
  void encenderEmisora() {
	(*this).laEmisora.encenderEmisora();
  } // ()

  // ............................................................
  // ............................................................
  // Z, Z, Z --> publicarCO2() -->
  // Sirve para publicar el valor de CO2 en la emisora 
  void publicarCO2( int16_t valorCO2, uint8_t contador, long tiempoEspera ) {

	//
	// 1. empezamos anuncio
	//
	uint16_t major = (MedicionesID::CO2 << 8) + contador;
	(*this).laEmisora.emitirAnuncioIBeacon( (*this).beaconUUID, 
											major,
											valorCO2, // minor
											(*this).RSSI // rssi
									);

	/*
	Globales::elPuerto.escribir( "   publicarCO2(): valor=" );
	Globales::elPuerto.escribir( valorCO2 );
	Globales::elPuerto.escribir( "   contador=" );
	Globales::elPuerto.escribir( contador );
	Globales::elPuerto.escribir( "   todo="  );
	Globales::elPuerto.escribir( major );
	Globales::elPuerto.escribir( "\n" );
	*/

	//
	// 2. esperamos el tiempo que nos digan
	//
	esperar( tiempoEspera );

	//
	// 3. paramos anuncio
	//
	(*this).laEmisora.detenerAnuncio();
  } // ()

 
}; // class

// --------------------------------------------------------------
// --------------------------------------------------------------
// --------------------------------------------------------------
// --------------------------------------------------------------
#endif
