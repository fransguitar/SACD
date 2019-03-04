int mot1[4]={11,10,9,8};
int mot2[4]={26,27,28,29};
int mot3[4]={30,31,32,33};
int mot4[4]={34,35,36,37};
int mot5[4]={38,39,40,41};
int final_cr[5]={51,43,44,45,46};
int b1;
int b2;
int b3;
int b4;
int retardo=2;
String select;
String motor;
int door=0;
int r;
int r2=0;
int state=0;            //estado de el final de carrera 
int psc;              // Valor en mm donde se encuentra el motor
int compueta=0;
int fin_c;
String leeCadena;       // Almacena la cadena de datos recibida
int d_mv;             // valor recibido en mm


void setup() {
  Serial.begin(9600);
  //pines de prueba 
  pinMode(11,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(8,OUTPUT);
  pinMode(51,INPUT);

  //fin de pines de prueba 
  pinMode(22,OUTPUT);
  pinMode(23,OUTPUT);
  pinMode(24,OUTPUT);
  pinMode(25,OUTPUT);
  pinMode(26,OUTPUT);
  pinMode(27,OUTPUT);
  pinMode(28,OUTPUT);
  pinMode(29,OUTPUT);
  pinMode(30,OUTPUT);
  pinMode(31,OUTPUT);
  pinMode(32,OUTPUT);
  pinMode(33,OUTPUT);
  pinMode(34,OUTPUT);
  pinMode(35,OUTPUT);
  pinMode(36,OUTPUT);
  pinMode(37,OUTPUT);
  pinMode(38,OUTPUT);
  pinMode(39,OUTPUT);
  pinMode(40,OUTPUT);
  pinMode(41,OUTPUT);
  pinMode(42,INPUT);
  pinMode(43,INPUT);
  pinMode(44,INPUT);
  pinMode(45,INPUT);
  pinMode(46,INPUT);
}

void loop() {
 while(door==0){
  Serial.println("estoy en el door==0"); 
  while (Serial.available()) {    // Leer el valor enviado por el Puerto serial
      delay(retardo);
      char c  = Serial.read();     // Lee los caracteres
      select += c;              // Convierte Caracteres a cadena de caracteres
    }
  if(select.length()>0){
     r2=select.toInt();
  }
  
    if (r2==2180){
      Serial.println("estoy en el if r2=2181");
      while (Serial.available()) {    // Leer el valor enviado por el Puerto serial
      delay(retardo);
      char c  = Serial.read();     // Lee los caracteres
      motor += c;              // Convierte Caracteres a cadena de caracteres
    }
    Serial.println(motor);
    if(motor.length()>0){
    r =motor.toInt();
    }
    switch(r){
    case 1:
    b1=mot1[0];
    b2=mot1[1];
    b3=mot1[2];
    b4=mot1[3];
    fin_c=final_cr[0];
    door=1;
    
    
    Serial.println("seteo"); 
    
    break;
    case 2:
    b1=mot2[0];
    b2=mot2[1];
    b3=mot2[2];
    b4=mot2[3];
    fin_c=final_cr[1];
    door=1;
    break;
    case 3:
    b1=mot3[0];
    b2=mot3[1];
    b3=mot3[2];
    b4=mot3[3];
    fin_c=final_cr[2];
    door=1;
    
    break;
    case 4:
    b1=mot4[0];
    b2=mot4[1];
    b3=mot4[2];
    b4=mot4[3];
    fin_c=final_cr[3];
    door=1;
    break;
    case 5:
    b1=mot5[1];
    b2=mot5[2];
    b3=mot5[3];
    b4=mot5[4];
    fin_c=final_cr[4];
    door=1;
    break;
    }
    
      }
    
    }
   
  //homig inicial 
  if(compueta==0){ 
    homing(fin_c);
    compueta=1;      
    }
  //comprobacion del homing 
  if(compueta==1){
  
    while (Serial.available()) {    // Leer el valor enviado por el Puerto serial
      delay(retardo);
      char c  = Serial.read();     // Lee los caracteres
      leeCadena += c;              // Convierte Caracteres a cadena de caracteres
    }
    
    if(leeCadena.length()>0){
    int r =leeCadena.toInt();
    delay(5);
    d_mv=(r*4.591928251);
    } 
   
    
    while((psc<d_mv)&&(d_mv!=0)){
      paso_izq();
      psc++;
      ;
          
      } 
      
    if((psc==d_mv)&&(d_mv!=0)){
      state=0;
      apagado();         // Apagado del Motor para que no se caliente  
      delay(1000);
      homing(fin_c);
      d_mv=0;
      door=0; 
      select=""; 
      r2=0;
      motor="";
      r=0;
     
      
       
          
               
      }  
     
                    
    
        
    leeCadena = "";   // Inicializamos la cadena de caracteres recibidos 
    apagado();         // Apagado del Motor para que no se caliente
     
    }
  
  
 

  

}
void paso_der(){         // Pasos a la derecha
 digitalWrite(b1, LOW); 
 digitalWrite(b2, LOW);  
 digitalWrite(b3, HIGH);  
 digitalWrite(b4, HIGH);  
   delay(retardo); 
 digitalWrite(b1, LOW); 
 digitalWrite(b2, HIGH);  
 digitalWrite(b3, HIGH);  
 digitalWrite(b4, LOW);  
   delay(retardo); 
 digitalWrite(b1, HIGH); 
 digitalWrite(b2, HIGH);  
 digitalWrite(b3, LOW);  
 digitalWrite(b4, LOW);  
  delay(retardo); 
 digitalWrite(b1, HIGH); 
 digitalWrite(b2, LOW);  
 digitalWrite(b3, LOW);  
 digitalWrite(b4, HIGH);  
  delay(retardo);  
}

void paso_izq() {        // Pasos a la izquierda
 digitalWrite(b1, HIGH); 
 digitalWrite(b2, HIGH);  
 digitalWrite(b3, LOW);  
 digitalWrite(b4, LOW);  
  delay(retardo); 
 digitalWrite(b1, LOW); 
 digitalWrite(b2, HIGH);  
 digitalWrite(b3, HIGH);  
 digitalWrite(b4, LOW);  
  delay(retardo); 
 digitalWrite(b1, LOW); 
 digitalWrite(b2, LOW);  
 digitalWrite(b3, HIGH);  
 digitalWrite(b4, HIGH);  
  delay(retardo); 
 digitalWrite(b1, HIGH); 
 digitalWrite(b2, LOW);  
 digitalWrite(b3, LOW);  
 digitalWrite(b4, HIGH);  
  delay(retardo); 
}
void apagado() {         // Apagado del Motor
 digitalWrite(b1, LOW); 
 digitalWrite(b2, LOW);  
 digitalWrite(b3, LOW);  
 digitalWrite(b4, LOW);  
 }
int homing(int fin){
    while(state==0){
      paso_der();
      state=digitalRead(fin) ;
      }
    psc=0;
    apagado();
    
  
  }
