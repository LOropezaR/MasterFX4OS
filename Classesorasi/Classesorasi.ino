//Codigo con clase (OOP)
//Codigo desarrollado por OpenSource UPIITA
/*Desarrolladores\
 *Abarca Robles Diego
 *Cruz Alvarez Fernando
 *Huang Rojas Armando Mao Li
 *Oropeza Rangel Luis
*/


//Definimos que pines se van a usar y los nombramos con respecto
//a su funcion

//Entradas
#define entrada1 2
#define entrada2 3
#define entrada3 4
//salidas
#define sal1 5
#define sal2 6
#define sal3 7
#define clk 8 //salida de reloj
const unsigned long bounce = 50;

//Creamos una clase para, posteriormente, leer
//las instrucciones que le demos de manera externa
class Bank
{
  private:
  int set[3]; //aquí se guardarán los pines que se usarán
  public:
  Bank(int p1, int p2, int p3){//con este podremos construir y guardar los bancos
    setBnk(p1, p2, p3)
  }
  void setBnk(int p1, int p2, int p3){
    this->set[0] = p1;
    this->set[1] = p2;
    this->set[2] = p3;
  }
  void begin() //configuramos pines de salida
  {
    pinMode(sal1, OUTPUT);
    pinMode(sal2, OUTPUT);
    pinMode(sal3, OUTPUT);
  }
  
  void sett() //instrucción que permite modificar las salidas con respecto al contenido
              //del banco
  { 
    for(int i=0; i<3; i++)
    {
      int pinOutput = sal1 + i;
      digitalWrite(pinOutput, this->set[i] ? HIGH : LOW);
      delayMicroseconds(10);
      digitalWrite(clk, HIGH);
      delayMicroseconds(10);
      digitalWrite(clk, LOW);
      delayMicroseconds(10);
    }
  }
};

Bank bnk[3] = { //Este es un banco donde configuramos los pines que queremos prender
  Bank(1,1,1),
  Bank(0,1,1),
  Bank(0,0,1),
};

int idbnk = 0;

bool estadoAnterior1 = LOW;
bool estadoAnterior2 = LOW;

unsigned long tiempoRebote = 0;

void setup() //declaramos que pines queremos como entradas y salidas
{
  Serial.begin(9600);
  pinMode(entrada1, INPUT);
  pinMode(entrada2, INPUT);
  pinMode(entrada3, INPUT);
  pinMode(clk, OUTPUT);

  for(int i = 0; i < 3; i++) //inicializamos los objetos que usaremos 
  {
    bnk[i].begin();
  }
  
  bnk[idbnk].sett();        //iniciamos en el banco cero aunque en un futuro se cambiará
                            //para poder iniciar en el ultimo usado
}

void loop() 
{
  //analizamos si hay entradas en los botones
  bool lectura1 = digitalRead(entrada1);
  bool lectura2 = digitalRead(entrada2);
  
  unsigned long tiempoActual = millis();
  
  if((tiempoActual - tiempoRebote) > bounce) // verifica que no hayan rebotes en el push button
  {
    if(lectura1 == HIGH && estadoAnterior1 == LOW)    //
    {
      idbnk++;
      if(idbnk >= 3) idbnk = 0;                       //Crea un loop para que no suba a un banco inexistente 
      bnk[idbnk].sett();                              //indicamos en que banco se ubica y hacemos el seteo de pines
      tiempoRebote = tiempoActual;
    }

    if(lectura2 == HIGH && estadoAnterior2 == LOW)    //resta o baja el banco en el que se encuentre
    {
      idbnk--;
      if(idbnk < 0) idbnk = 2;                       //Crea un loop para que no baje a un banco inexistente 
      bnk[idbnk].sett();                             //indicamos en que banco se ubica y hacemos el seteo de pines
      tiempoRebote = tiempoActual;
    }
  }
  estadoAnterior1 = lectura1;
  estadoAnterior2 = lectura2;

  if(Serial.available() > 0){
    char dato = Serial.read();
    
  }
}
