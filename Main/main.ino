bool state_current = true;
bool state_previous = false;

int illumi = 56; // 조도센서
int humidAnalog = 55; // 습도 센서 
int waterlvPin = 54; //수위센서
int led0 = 6;
int led1 = 2;
int led2 = 3;
int btn = 4;
//BT 18,19


int onoff = 0;


int bright;
int humidity;
int waterlv;
int humidDegree = 0; // 정도는 조절할 것, 건조도에 따라 모터 작동을 위한 변수
int motorD = 5;
int motorS = 150;
int waterperiod = 2000;

char cmd;
int intro = 1;



void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);
  pinMode(led0, OUTPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(btn, INPUT);


}


void led1Onoff(){
  //버튼 2 값 읽어오기 (led1 on/off)
  //state 구분해서 값 저장
  //led1는 관상용 라이트

  state_current = digitalRead(btn); 
  // 버튼 상태 읽기 
  if (state_current) { 
    // 버튼을 누른 경우 
    if (state_previous == false) {
      // 이전 상태와 비교 
      state_previous = true; 
      onoff = !onoff;
      } 
      delay(50); // 디바운싱 
  }
       
    else { 
      state_previous = false; 
        
    }

    if(onoff){
      digitalWrite(led1,HIGH);
      }
    else{
      digitalWrite(led1,LOW);
      }
  
}


  


void watering(){

    //analogWrite(motorD, motorS);
    //D포트에 S만큼의 급수를 시작함
    
    
    delay(waterperiod);
    analogWrite(7, 10);

    
    
  }  

void led2Onoff() { 
  // 조도 센서를 읽고 라이트 켬
  int reading = analogRead(illumi); 
  bright = map(reading, 0, 1023, 0, 3);
  if(bright < 2){
    digitalWrite(led2,HIGH);
    }
   else {
    digitalWrite(led2,LOW);
    }

  //led2는 식물 생장용. 조도 값에 따라서 자동 ON/OFF

}

void waterLevel() { 
  // 수위 센서 읽기 
  //digitalWrite(waterPower, HIGH);
  //delay(10);  
  int reading = analogRead(waterlvPin); 
  //digitalWrite(waterPower, LOW);
  waterlv = map(reading, 0, 680, 0, 7);
  // 수위는 8단계로 구분  
  if(waterlv < 2){
    digitalWrite(led0, HIGH);
    }
  else {
    digitalWrite(led0, LOW);
    }
  if(humidity < humidDegree){
    watering();
    }

    
}

void humid(){
  //토양 습도 센서값 읽기
  int reading = analogRead(humidAnalog); 
  humidity = map(reading, 0, 1023, 0, 3);
  //습함 정도를 4개로 나눔 
  
}





void loop() {
  //모든 함수 
  //bt 명령어 처리

  led1Onoff();
  led2Onoff();
  //watering();
  waterLevel();
  humid();
  

  
  // "Enter the number to do action.
  // "1 : LED On / Off
  // "2 : Check the Water Level -> Water Level is XX now.
  // "3 : Watering
  
  if (intro){
    Serial1.println("Enter the number to do action.");
    Serial1.println("1 : LED On / Off");
    Serial1.println("2 : Check the Water Level");
    Serial1.println("3 : Watering");
    delay(1000);
    intro--;
    }


  
  if(Serial1.available()){
    cmd = Serial1.read();
    }

  if (cmd == '1'){
    onoff = !onoff;
    Serial1.println("Done");
    delay(1000);
    }
  else if (cmd == '2'){
    Serial1.print("Water Level is ");
    Serial1.print(waterlv);
    Serial1.println(" Now.");
    delay(1000);
    }
  else if (cmd == '3'){
    watering();
    Serial1.println("Watering Now.");
    delay(1000);
    }

    cmd = '0';
    
    

}
