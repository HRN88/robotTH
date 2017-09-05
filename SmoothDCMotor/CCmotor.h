////////////////////////////////
//        
//Definicion de la clase CCMotor
//
////////////////////////////////

#ifndef CCMotor_h
#define CCMotor_h

class CCMotor{
  private:
    //Aceleracion
    int aceleracion;
	
    //*********Atributos relacionados a la velocidad*************
	
	//Velocidad con la que se desea que inicie el motor
    int velini;
	
	//Velocidad actual en un instante t
    int velact;
	
	//Velocidad maxima que se desea alcance el motor
    int velmax;
	
	//Variable temporal
    int timpo;
	
    //Pines de control para el motor
    int ctrla;
    int ctrlb;
	
    //Variable temporal
    int tiempo = 0;
    char anteriorMotor;
    char actualMotor;
    //tiempos para el timer
    unsigned long tiempoActual;
    unsigned long tiempoAnterior;
	
	
    //Metodo privado que calcula la velocidad en funcion de la aceleracion
    void acelera();
    

   public:
   //Constructor, crea el objeto, requiere los pines de control
   CCMotor(int pin1, int pin2);
   
   //*****************Metodos Set******************************
   //aceleracion
   void SetAcel(int acel);
   
   //Velocidad inicial
   void SetVini(int vini);
   
   //Velocidad final maxima
   void SetVmax(int vmax);
   
   //Todos los parametros
   void SetParams(int acel, int vini, int vmax); 

   //*****************Metodos Get********************************
   
   //Solicita todos los parametros establecidos y los imprime por serial (115200)BAUDS
   void GetAllParams();
	
   //Solicita la velocidad actual y la imprime por serial a (115200) BAUDS
   void GetVelocidadActual();

   //******************Metodos de funcionalidades****************************

   //Funcion para iniciar giro
   void Gira(char direccion);
   
   //Funcion Para parar el motor
   void parar();
   
  
};
#endif




