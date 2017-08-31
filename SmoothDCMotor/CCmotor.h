////////////////////////////////
//        
//Definicion de la clase CCMotor
//
////////////////////////////////

class CCMotor{
  private:
    //Aceleracion
    int aceleracion;
    //Velocidad minima y maxima de 0-255
    int velini;
    int velact;
    int velmax;
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
    

   public:
   //Constructor, crea el objeto requiere los pines de control
   CCMotor(int pin1, int pin2);
   
   //Funciones Set, para establecer:
   //aceleracion
   void SetAcel(int acel);
   
   //Velocidad inicial
   void SetVini(int vini);
   
   //Velocidad final maxima
   void SetVmax(int vmax);
   
   //Todos los parametros
   void SetParams(int acel, int vini, int vmax); 

   //Solicita los parametros establecidos y los imprime por serial (115200)BAUDS
   void GetAllParams();

   void GetVelocidadActual();

    //Metodo privado que calcula la velocidad en funcion de la aceleracion
   void acelera();

   //Funcion para iniciar giro
   void Gira(char direccion);

   //Funcion Para parar el motor

   void parar();
  
};




