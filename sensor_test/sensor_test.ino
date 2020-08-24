int wheel_sensor = 0;

void setup() {
  pinMode(2,INPUT);
  Serial.begin(9600);
  Serial.print("START: ");
}

void loop() {
  wheel_sensor = digitalRead(2);
  if (wheel_sensor == HIGH){
    Serial.print("High ");
    while (wheel_sensor == HIGH){
      wheel_sensor = digitalRead(2);
    }
  }
  delay(1);
  if (wheel_sensor == LOW){
    Serial.print("Low ");
    while (wheel_sensor == LOW){
      wheel_sensor = digitalRead(2);
    }
  }
  delay(1);
  
}
