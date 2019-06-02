#include <OneWire.h>
#include <DallasTemperature.h>

// Pin donde se conecta el bus 1-Wire
const int pinDatosDQ = 2;
const int pinRele = 8;

// Instancia a las clases OneWire y DallasTemperature
OneWire oneWireObjeto(pinDatosDQ);
DallasTemperature sensorDS18B20(&oneWireObjeto);
 
void setup() {
  
    pinMode(pinRele, OUTPUT);
  
    // Iniciamos la comunicación serie
    Serial.begin(9600);
    // Iniciamos el bus 1-Wire
    sensorDS18B20.begin(); 
    // initialize digital pin LED_BUILTIN as an output.
    pinMode(LED_BUILTIN, OUTPUT);
}
 
void loop() {
    // Mandamos comandos para toma de temperatura a los sensores
    Serial.println("Mandando comandos a los sensores");
    sensorDS18B20.requestTemperatures();
 
    // Leemos y mostramos los datos de los sensores DS18B20
    Serial.print("Temperatura sensor 0: ");
    Serial.print(sensorDS18B20.getTempCByIndex(0));
    Serial.println(" C");
    /**Descomentar para usar 2 sensores
    Serial.print("Temperatura sensor 1: ");
    Serial.print(sensorDS18B20.getTempCByIndex(1));
    Serial.println(" C");*/
    
    /*Activar si la temperatura es mayor a 30 grados*/
    double temperatura = sensorDS18B20.getTempCByIndex(0);
    if(temperatura>30) {
      Serial.print("¡¡¡¡¡¡¡MAYOR A 30!!!!!!");
      digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
      digitalWrite(pinRele, HIGH);  //Accionar relé para encender ventilador
    } else {
      digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
      digitalWrite(pinRele, LOW);
    }

    delay(500); 
}
