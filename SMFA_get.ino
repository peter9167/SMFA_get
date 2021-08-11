#include <TimerOne.h> // TimeOne라이브러리 사용

//-------타이머 인터럽트를 위한 타이머 카운트------------
int time_count = 0;
int hum_count = 0;
int temp_count = 0;
int soil_count = 0;
int pump_count = 0;
int fan_count = 0;
//--------------------------------------------------

//Pump
#define pump 5

//Fan
#define fan 6 

void setup(){
  Serial.begin(9600); // 시리얼 모니터 통신속도 9600 설정
  pinMode(pump, OUTPUT);
  pinMode(fan, OUTPUT);
  
  Timer1.initialize(1000); //1000000μs = 1s, 1000us = 0.001s, 1000us = 1ms
  Timer1.attachInterrupt(timerIsr);
}
void loop() {
    int h = analogRead(A0);
    int t = analogRead(A1);
    int soil = analogRead(A2);
    int temp = analogRead(A3);
    
    int h_a, t_a;

    //------map함수를 이용한 온도 습도 아날로그 신호 값 변환----------
    h_a = map(h, 0, 1023, 20, 90); // 습도 값 아날로그 신호 값 변환
    t_a = map(t, 0, 1023, 0, 50); // 온도 값 아날로그 신호 값 변환

    //------습도 값 읽기 카운터---------------------------
    if(hum_count == 1000){
      Hum(h_a);
      hum_count = 0;
    }
    //------온도 값 읽기 카운터---------------------------
    if(temp_count == 1050){
      Temp(t_a);
      temp_count = 0;
    }
    //------토양 습도 값 읽기 카운터---------------------------
    if(soil_count == 1100){
      Soil(soil);
      soil_count = 0;
    }
    if(pump_count == 50){
      Pump(soil);
      pump_count = 0;
    }
    if(fan_count == 70){
      Fan(temp);
      fan_count = 0;
    }
}

//------------인터럽트를 위한 카운터 호출 함수----------------------
void timerIsr(){
  time_count += 1;
  hum_count += 1;
  temp_count += 1;
  soil_count += 1;
  pump_count += 1;
  fan_count += 1;
}



//------------습도 값 시리얼 출력 및 아날로그 값 전달 호출 함수----------------------
void Hum(int h){
    Serial.print("습도:");
    Serial.println(h); // 습도 값 출력
}

//------------온도 값 시리얼 출력 및 아날로그 값 전달 호출 함수----------------------
void Temp(int t){
    Serial.print("온도:");
    Serial.println(t); // 온도 값 출력
}
//------------토양 수분 값 호출 함수----------------------
void Soil(int soil){
    Serial.print("토양 수분:");
    Serial.println(soil); //토양 수분 값 출력
}
//------------Pump ON/OFF 함수----------------------
void Pump(int soil){
    //추후 토양 수분 센서에 비례한 값을 이용하여 PWM 출력을 하도록 한다.
    int soil_pwm;
    soil_pwm = map(soil, 0, 1023, 0, 12);
    if(soil > 600){
      digitalWrite(pump, HIGH);
    } else{
      digitalWrite(pump, LOW);
    }
    /*
    if(soil > 600){
      analogWrite(pump, soil_pwm);
    }
    */
}
//------------Fan 출력 함수----------------------
void Fan(int temp){
    //추후 조도 센서에 비례한 값을 이용하여 PWM 출력을 하도록 한다.
    int temp_pwm;
    temp_pwm = map(temp, 0, 1023, 0, 12);
    if(temp > 600){
      digitalWrite(temp, HIGH);
    } else{
      digitalWrite(temp, LOW);
    }
}
