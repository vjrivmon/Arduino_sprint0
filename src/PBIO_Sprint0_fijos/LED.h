// -*- mode: c++ -*-

#ifndef LED_H_INCLUIDO
#define LED_H_INCLUIDO

// ----------------------------------------------------------
// Jordi Bataller i Mascarell
// 2019-07-07
// ----------------------------------------------------------

// ----------------------------------------------------------
// ----------------------------------------------------------

// Z -> esperar -> 
// Esta función se encarga de hacer que el programa espere un tiempo determinado
void esperar (long tiempo) {
  delay (tiempo);
}

// ----------------------------------------------------------
// ----------------------------------------------------------

// La clase LED sirve para controlar un LED, encenderlo, apagarlo, hacerlo brillar...
class LED {
private:
  int numeroLED;  // número de pin del LED
  bool encendido; // indica si el LED está encendido o no
public:

  // .........................................................
  // .........................................................

  // Constructor
  LED (int numero)
	: numeroLED (numero), encendido(false)
  {
	pinMode(numeroLED, OUTPUT);
	apagar ();
  }

  // .........................................................
  // .........................................................

  // Encender el LED
  // -> encender() ->
  void encender () {
	digitalWrite(numeroLED, HIGH); 
	encendido = true;
  }

  // .........................................................
  // .........................................................

  // Apagar el LED
  // -> apagar() ->
  void apagar () {
	  digitalWrite(numeroLED, LOW);
	  encendido = false;
  }

  // .........................................................
  // .........................................................

  // Alternar el estado del LED
  // -> alternar() ->
  void alternar () {
	if (encendido) {
	  apagar();
	} else {
	  encender ();
	}
  } // ()

  // .........................................................
  // .........................................................

  // Hacer brillar el LED
  // Z -> brillar() ->
  void brillar (long tiempo) {
	encender ();
	esperar(tiempo); 
	apagar ();
  }
}; // class

// ----------------------------------------------------------
// ----------------------------------------------------------
// ----------------------------------------------------------
// ----------------------------------------------------------
#endif
