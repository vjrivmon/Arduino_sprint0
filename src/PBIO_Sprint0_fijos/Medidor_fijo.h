// -*- mode: c++ -*-

#ifndef MEDIDOR_H_INCLUIDO
#define MEDIDOR_H_INCLUIDO
#define pin_gas 28
#define pin_vref 5
#define TIAGain 499
float sensitivityCode = -41.26;

// la clase Medidor sirve para medir el CO2 en el aire y devolver el valor en ppm. De momento solo lo utilizaremos para pasar datos fijos
class Medidor {
  private:

  public:
  // .....................................................
  // constructor
  // .....................................................
  Medidor(  ) {
  } // ()

  // .....................................................
  // .....................................................
  // -> iniciarMedidor() ->
  void iniciarMedidor() {
	// las cosas que no se puedan hacer en el constructor, if any
  } // ()
  
  // -> medirCO2() -> Z
  float medirCO2() {
    return 1909;  // ----------------- CAMBIAR ESTE NÚMERO POR OTRO CUALQUIERA
  } // ()

  // .....................................................
  // .....................................................
 
  
  
}; // class

// ------------------------------------------------------
// ------------------------------------------------------
// ------------------------------------------------------
// ------------------------------------------------------
#endif
