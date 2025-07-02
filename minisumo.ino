//Infrarrojos
const int sensorIzq = 4;
const int sensorDer = 5;
int valorSensorIzq=0;
int valorSensorDer=0;

//Ultrasónico
const int trig = 2;
const int echo = 3;
float duracion;
float distancia;
const float velocidadSonido = 0.0343;

//Motores
const int motorIzqA = 11; //IN1
const int motorIzqB = 12; //IN2
const int motorDerA = 8; //IN3
const int motorDerB = 7; //IN4
const int VelA=10; //ENA
const int VelB=9; //ENB
const int velMax = 200;


void setup() {
    pinMode(sensorIzq, INPUT);
    pinMode(sensorDer, INPUT);

    pinMode(trig, OUTPUT);
    pinMode(echo, INPUT);
    
    pinMode(motorIzqA, OUTPUT);
    pinMode(motorIzqB, OUTPUT);
    pinMode(motorDerA, OUTPUT);
    pinMode(motorDerB, OUTPUT);
    pinMode(VelA, OUTPUT);
    pinMode(VelB, OUTPUT);
    delay(5000);
}

void loop() {
    // Leer los valores de los sensores
    valorSensorIzq = digitalRead(sensorIzq);
    valorSensorDer = digitalRead(sensorDer);

    distancia = medirDistancia();

    // Si la distancia es menor a 15 cm, avanzar hacia el objeto detectado
    if (distancia < 15) {
        avanzarRecto();
    }
    // Si ambos sensores detectan el borde blanco, retrocede
    else if (valorSensorIzq == HIGH && valorSensorDer == HIGH) {
        retroceder();
    }
    // Si el sensor izquierdo detecta el dojo negro, girar hacia la derecha
    else if (valorSensorIzq == LOW) {
        girarDerecha();
    }
    // Si el sensor derecho detecta el dojo negro, girar hacia la izquierda
    else if (valorSensorDer == LOW) {
        girarIzquierda();
    }
    // Si ninguno de los sensores detecta el borde blanco ni el dojo negro ni hay objetos cercanos, girar a la izquierda
    else {
        girarIzquierda();
    }
}

float medirDistancia() {
    digitalWrite(trig, LOW);
    delayMicroseconds(2);
    digitalWrite(trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig, LOW);

    duracion = pulseIn(echo, HIGH);
    distancia = duracion * velocidadSonido / 2;
    return distancia;
}

void avanzarRecto() {
    analogWrite(VelA, velMax);
    analogWrite(VelB, velMax);
    digitalWrite(motorIzqA, HIGH);
    digitalWrite(motorIzqB, LOW);
    digitalWrite(motorDerA, HIGH);
    digitalWrite(motorDerB, LOW);
}

void girarIzquierda() {
    analogWrite(VelA, 5);
    analogWrite(VelB, 5);
    digitalWrite(motorIzqA, HIGH);
    digitalWrite(motorIzqB, LOW);
    digitalWrite(motorDerA, LOW);
    digitalWrite(motorDerB, HIGH);
}

void girarDerecha() {
    analogWrite(VelA, 5);
    analogWrite(VelB, 5);
    digitalWrite(motorIzqA, LOW);
    digitalWrite(motorIzqB, HIGH);
    digitalWrite(motorDerA, HIGH);
    digitalWrite(motorDerB, LOW);
}

void retroceder() {
    analogWrite(VelA, velMax); 
    analogWrite(VelB, velMax); 
    digitalWrite(motorIzqA, LOW);
    digitalWrite(motorIzqB, HIGH);
    digitalWrite(motorDerA, LOW);
    digitalWrite(motorDerB, HIGH);
}