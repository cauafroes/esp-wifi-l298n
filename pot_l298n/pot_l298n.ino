#define motor1a 3    //Associa "motor1a" ao pino D3 no Arduino
#define motor1b 4    //Associa "motor1b" ao pino D4 no Arduino
#define en1 5        //Associa "en1" ao pino D7 no Arduino

int j1pot_valor, potvalor = 0;   //Cria as variáveis que serão os valores recebidos pelo outro Arduino.
int velocidademotor1, velocidademotor2 = 0;
int potpin = A1;

void setup()
{
  pinMode(en1, OUTPUT);    //Determina os pinos como saída.
  pinMode(motor1a, OUTPUT);
  pinMode(motor1b, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  potvalor = analogRead(potpin);
  potvalor = map(potvalor,0, 1023, 0 ,255);

  if (potvalor < 117) {
    
    // Faz o motor 1 rodar para "trás"
    digitalWrite(motor1a, HIGH);
    digitalWrite(motor1b, LOW);
    
    //Aumenta a velocidade do motor
    velocidademotor1 = map(potvalor, 117, 0, 0, 255);
  }
  else if (potvalor > 137) {
    
    // Faz o motor 1 rodar para "frente"
    digitalWrite(motor1a, LOW);
    digitalWrite(motor1b, HIGH);
    
    // Aumenta a velocidade do motor
    velocidademotor1 = map(potvalor, 137, 255, 0, 255);
  }
    //Faz com que os motores fiquem parados caso o joystick esteje centrado
    else {
    velocidademotor1 = 0;
  }

    //Para testes
    Serial.print(potvalor);
    Serial.print("   ");
    Serial.println(velocidademotor1);

  analogWrite(en1, velocidademotor1); // Envia um sinal PWM para o motor1
  
}
