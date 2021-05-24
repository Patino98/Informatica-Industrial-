// LCD y Teclado

#include <LiquidCrystal.h>
#include <Keypad.h>

int  contador = 1;    // cuenta el nivel del menu en el que se esta
int brillo=0, intencidad=5, led=6; //Variables tipo enteras para la funcion desvanecimiento.
unsigned long tiempo, tiempoA=0, retardo=10; //Variables tipo unsigned long para la funcion desvanecimiento.
char pulso;       // almacena la tecla pulsada
const byte ROWS = 4;  //Cuatro Filas
const byte COLS = 3;  //Cuatro Columnas 
char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};
byte rowPins[ROWS] = {13,12,11,10}; //Puntos de conexion del teclado al arduino FILAS
byte colPins[COLS] = {9,8,7}; //Puntos de conexion del teclado al arduino COLUMNAS
Keypad Teclado1 = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS ); //Configura el teclado
LiquidCrystal lcd(0,1,2,3,4,5); //Instruccion para asignar las terminales de salida para la pantalla lcd.

/* ----------------- Void Setup --------------------- */
void intro();
void menu1();
void seleccion1();
void parpadeo();
void desvanecimiento();

void setup () { 
  lcd.begin(16,2); //Enciende la pantalla lcd y se asigna el tamaño de la pantalla
  pinMode(6, OUTPUT); //Se asigna una terminal de salida en arduino
  intro();         // muestra el intro de  bienvenida
} 
/* ----------------- Void Loop ---------------------- */
void loop(){
 pulso = Teclado1.getKey() ;  // Lee la tecla pulsada
 if (pulso != 0) {      
    lcd.clear();
    delay(100);
 }  
if(contador == 1){ menu1();seleccion1();}
} /* -- Fin del void loop(), inician las Funciones -- */

/* ------------------  Intro ------------------------ */
void intro(){ 
 lcd.clear();  // Borra el  LCD
 lcd.setCursor(3,0);         // Se posiciona en la Columna 3, Fila 0
 lcd.print("BIENVENIDO ");
 lcd.setCursor(1,1);
 lcd.print("PRUEBA DE MENU");
 delay(4000);                // espera 4 segundos mostrando el intro
 lcd.clear();
}
/* ------------------ Menu 1 ------------------------ */
void menu1(){ 
   lcd.setCursor(0,0);
   lcd.print("ON    >1  ");
   lcd.setCursor(10,0);
   lcd.print("OFF >2");   
   lcd.setCursor(0,1);
   lcd.print("INTER >3  "); 
   lcd.setCursor(10,1);
   lcd.print("Desv>4");
  
}

/* ------------------ Seleccion 1 ------------------- */
void seleccion1(){ // Funcion seleccion1, mediante condiciones segun la seleccion en el menu1 se activa una accion.
  if(pulso == '1') digitalWrite(6,HIGH); //enciende el led
  if(pulso == '2') digitalWrite(6,LOW); // apaga el led
  if(pulso == '3') parpadeo(); //Llama a la funcion parpadeo
  if(pulso == '4') desvanecimiento(); //Llama a la funcion desvanecimiento 
}

/* ------------------   Parpadeo  ------------------- */
void parpadeo(){ //Funcion Parpadeo, Mediante una serie de instrucciones (digitalWrite y delay) se realiza un parpadeo del led.
 digitalWrite(6,HIGH);
  delay(300);
  digitalWrite(6,LOW);
  delay(300);
  digitalWrite(6,HIGH);
  delay(300);
  digitalWrite(6,LOW);
  delay(300);
  digitalWrite(6,HIGH);
  delay(300);
  digitalWrite(6,LOW);
  delay(300);
  digitalWrite(6,HIGH);
  delay(300);
  digitalWrite(6,LOW);
  delay(300);
}

/* ------------------   Desvanecimiento  ------------------- */
void desvanecimiento(){ //Funcion desvanecimiento, mediante retardos se hace un desvanecimiento del led.
 tiempo= millis ();

if (tiempo> tiempoA+retardo)
{
  tiempoA=tiempo;

  analogWrite(led, brillo);
  brillo+=intencidad;

  if(brillo==0 || brillo == 255)
  {
    intencidad = -intencidad;  
  }
  
}
}