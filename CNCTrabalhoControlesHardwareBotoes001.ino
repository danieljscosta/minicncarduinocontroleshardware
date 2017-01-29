// Programa :Controle CNC - Servo motor e Stepper Motor com o Shield L293D e arduino Mega
// Autor : Daniel de Jesus Silva Costa

// Carrega a biblioteca Servo
#include <Servo.h> 
#include <AFMotor.h>
 
//Cria objeto "ServoCaneta"
Servo ServoCaneta;

//Numero de passos para 1 rotacao total
double passos_total = 2048; 
 
// Define as portas (Pinos) para os motores (Fase A e Fase B)
// Valor 1 para motor em M1/M2 e 2 para motor em M3/M4
int porta_motor_1 = 1; 
int porta_motor_2 = 2;
 
// Armazena o numero de passos que o motor vai girar
double numero_de_passos = 1; 
 
// Define os parametros do motor 1
AF_Stepper motor_de_passo_1(passos_total, porta_motor_1); 
// Define os parametros do motor 2
AF_Stepper motor_de_passo_2(passos_total, porta_motor_2);

//Pinos (Portas) para botoes de controle
const int bPinoBotaoDirX = 50;     // botao motor X para direita
const int bPinoBotaoEsqX = 52;     // botao motor X para esquerda

const int bPinoBotaoDirY = 48;     // botao motor Y para direita
const int bPinoBotaoEsqY = 46;     // botao motor Y para esquerda

const int bPinoBotaoServo = 44;   // botao move servo


// Estado dos botoes de controle
int bEstadoBotaoMovDirX = 0;        // estado dos botoes que movimenta o motor
int bEstadoBotaoMovEsqX = 0;        // estado dos botoes que movimenta o motor
int bEstadoBotaoMovDirY = 0;        // estado dos botoes que movimenta o motor
int bEstadoBotaoMovEsqY = 0;        // estado dos botoes que movimenta o motor
int bEstadoBotaoServo = 0;          // estado do botão que movimenta o servo
int bServoEstavaAcionado = 0;       // flag de controle do acionamento do servo

void pl_Servo() {
    // -------------------   Controle do servo   ---------------------------
    bEstadoBotaoServo = digitalRead(bPinoBotaoServo);
    // Se pressionou botao do servo
    if (bEstadoBotaoServo == HIGH) {     
      
      //Se não estava acionado, aciona o servo e para
      if (bServoEstavaAcionado == 0) {
         // Abaixa o servo e para
         ServoCaneta.write(50);   // move servo 50 graus   
         bServoEstavaAcionado=1;  // muda estado da flag
         delay(500);              // delay para evitar repique do interruptor
            
       } else {
         
         // volta servo para posicao inicial
         ServoCaneta.write(10);   // move servo para o inicio (0 grau)  
         bServoEstavaAcionado=0; // muda estado da flag
         delay(500);             // delay para evitar repique do interruptor
       }
    }  
}

void pl_EixoX(){
    // -------------------   Controle do motor X  ---------------------------
    // verifica se botoes de comando do motor foram pressionadoso
    bEstadoBotaoMovDirX = digitalRead(bPinoBotaoDirX);
    bEstadoBotaoMovEsqX = digitalRead(bPinoBotaoEsqX);
    
    if (bEstadoBotaoMovDirX == HIGH) {     
         // Move motor para direita
           //Move o motor 1. Usando FORWARD para sentido horario,
            //BACKWARD para anti-horario
            motor_de_passo_1.step(numero_de_passos, FORWARD, SINGLE);
            motor_de_passo_1.release();
         delay(5); // delay para dar tempo de chavear as bobinas do motor
   } else {
        if (bEstadoBotaoMovEsqX == HIGH) {     
           // Move motor para esquerda
           motor_de_passo_1.step(numero_de_passos, BACKWARD, SINGLE);
           motor_de_passo_1.release();
           delay(5); // delay para dar tempo de chavear as bobinas do motor
        }      
    }  
}

void pl_EixoY(){
    // -------------------   Controle do motor X  ---------------------------
    // verifica se botoes de comando do motor foram pressionadoso
    bEstadoBotaoMovDirY = digitalRead(bPinoBotaoDirY);
    bEstadoBotaoMovEsqY = digitalRead(bPinoBotaoEsqY);
    
    if (bEstadoBotaoMovDirY == HIGH) {     
         // Move motor para direita
           //Move o motor 1. Use FORWARD para sentido horario,
            //BACKWARD para anti-horario
            motor_de_passo_2.step(numero_de_passos, FORWARD, SINGLE);
            motor_de_passo_2.release();
         delay(5); // delay para dar tempo de chavear as bobinas do motor
   } else {
        if (bEstadoBotaoMovEsqY == HIGH) {     
           // Move motor para esquerda
           motor_de_passo_2.step(numero_de_passos, BACKWARD, SINGLE);
           motor_de_passo_2.release();
           delay(5); // delay para dar tempo de chavear as bobinas do motor
        }      
    }  
}
 
void setup() 
{ 

  // Define a velocidade de rotacao do motor 1
  motor_de_passo_1.setSpeed(5);
  // Define a velocidade de rotacao do motor 2
  motor_de_passo_2.setSpeed(5);
  // Inicializa a serial
  // Indica que o ServoCaneta esta ligado ao pino 10
  ServoCaneta.attach(10);  
  Serial.begin(9600);
  
  pinMode(bPinoBotaoDirX, INPUT);
  pinMode(bPinoBotaoEsqX, INPUT);
  pinMode(bPinoBotaoDirY, INPUT);
  pinMode(bPinoBotaoEsqY, INPUT);
  pinMode(bPinoBotaoServo, INPUT);


           motor_de_passo_1.step(numero_de_passos, BACKWARD, SINGLE);
           motor_de_passo_1.release();
           delay(5); // delay para dar tempo de chavear as bobinas do motor
} 
 
void loop() 
{ 
  pl_EixoX();
  pl_EixoY();
  pl_Servo();

} 
