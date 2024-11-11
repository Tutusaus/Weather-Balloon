char hola;
void setup() {
Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
hola = Serial.read();
 if (Serial.available()) {
    Serial.write(hola);
}
}
