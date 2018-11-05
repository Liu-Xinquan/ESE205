int light = A1;
int temp = A2;
int lightRead = 0; 
int tempRead = 0; 
float vLight = 0; 
float vTemp = 0; 

void setup() {
  Serial.begin(9600);
  pinMode(lightRead, INPUT);
  pinMode(tempRead, INPUT);

}

void loop() {
  lightRead = analogRead(light);
  delay(10);
  lightRead = analogRead(light);
  delay(10);

  vLight = (lightRead * 5.0)/1024.0;

  Serial.print(lightRead); 
  Serial.print(' ');
  
  tempRead = analogRead(temp);
  delay(10);
  tempRead = analogRead(temp);
  delay(10);

  vTemp = (tempRead * 5.0)/1024.0;

  Serial.println(tempRead);
}
