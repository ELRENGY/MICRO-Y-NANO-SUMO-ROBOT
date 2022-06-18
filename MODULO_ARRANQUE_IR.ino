#include <IRremote.h>
#include <EEPROM.h>

const int RECV_PIN = 10;
IRrecv irrecv(RECV_PIN);
decode_results results;
const int LED_ = 9;
int k=0;
int N;
int H=0;


int ARRAY_START[] = {4577, 4569, 4601, 4549, 4581, 4573, 4605, 4579, 4571, 4603, 4551, 4583, 4575, 4607};
int ARRAY_STOP[] = {4576, 4568, 4600, 4548, 4580, 4572, 4604, 4578, 4570, 4602, 4550, 4582, 4574, 4606};
int ARRAY_PROGRAMA1[] = {6880, 6872, 6904, 6852, 6884, 6876, 6908, 6882, 6874, 6906, 6854, 6886, 6878, 6910};
int ARRAY_PROGRAMA2[] = {4832, 4824, 4856, 4804, 4836, 4828, 4860, 4834, 4826, 4858, 4806, 4838, 4830, 4862};


//VARIABLES

int START;
int STOP;
int PROGRAMA;
int PROGRAMA2;
int VALOR=0;
int ACTIVACION = 0;

void setup(){
  
  
  
  Serial.begin(115200);
  irrecv.enableIRIn();
  pinMode(LED_, OUTPUT);

}

void loop(){
  if(H<5){
  Serial.println(EEPROM.read(0));
  N=int(EEPROM.read(0));
  START = ARRAY_START[N];
  STOP = ARRAY_STOP[N];
  PROGRAMA = ARRAY_PROGRAMA1[N];
  PROGRAMA2 = ARRAY_PROGRAMA2[N];
  delay(50);
  Serial.println(START);
  Serial.println(STOP);
  Serial.println(PROGRAMA);
  Serial.println(PROGRAMA2);
  H=H++;
  }
  

  if (irrecv.decode(&results)){
        VALOR= (results.value);
        Serial.println(VALOR);//HEX
        delay(10);
        
        for(int i=0; i<14; i++){
        if(ARRAY_PROGRAMA1[i] == VALOR || ARRAY_PROGRAMA2[i] == VALOR){
        ACTIVACION = 0;
        k=i;
        EEPROM.write(0, byte(k));
        Serial.println(EEPROM.read(0));
        digitalWrite(LED_, HIGH);
        delay(500);
        digitalWrite(LED_, LOW);
        delay(500);
        digitalWrite(LED_, HIGH);
        delay(500);
        digitalWrite(LED_, LOW);
        delay(500);
        }
        }
        
        if(ARRAY_STOP[N] == VALOR){
          STOP=VALOR;
          ACTIVACION = 0;
          k=N;
          for(int J = 0; J < 100; J++){
          digitalWrite(LED_, LOW);
          delay(1000);
          digitalWrite(LED_, HIGH);
          delay(1000);
          }

        }
        
        if(ARRAY_START[N] == VALOR){
          START=VALOR;
          ACTIVACION = 1;
          k=N;
          
          digitalWrite(LED_, HIGH);
        }  

        irrecv.resume();
        
  }
}
