#include <TimerOne.h> // TimeOne라이브러리 사용

//-------타이머 인터럽트를 위한 타이머 카운트------------
int time_count = 0;
int hum_count = 0;
int temp_count = 0;
int soil_count = 0;
int light_count = 0;
int pump_count = 0;
int fan_count = 0;
int led_count = 0;
//--------------------------------------------------

//Pump
int pump = 5;

//Fan
int fan = 6;

//LED
int led = 9;

void setup() {
  Serial.begin(9600); // 시리얼 모니터 통신속도 9600 설정
  pinMode(pump, OUTPUT);
  pinMode(fan, OUTPUT);
  pinMode(LED, OUTPUT);

  Timer1.initialize(1000); //1000000μs = 1s, 1000us = 0.001s, 1000us = 1ms
  Timer1.attachInterrupt(timerIsr);
}
void loop() {
  int h = analogRead(A0); //습도 센서
  int t = analogRead(A1); //온도 센서
  int soil = analogRead(A2); //토양 수분 센서
  int light = analogRead(A3); //조도 센서

  int h_a, t_a; //아날로그 습도 값 변환 저장 변수, 아날로그 온도 값 변환 저장 변수

  //------map함수를 이용한 온도 습도 아날로그 신호 값 변환----------
  h_a = map(h, 0, 1023, 20, 90); // 습도 값 아날로그 신호 값 변환
  t_a = map(t, 0, 1023, 0, 50); // 온도 값 아날로그 신호 값 변환

  //------습도 값 읽기 카운터---------------------------
  if (hum_count == 700) {
    Hum(h_a);
    hum_count = 0;
  }
  //------온도 값 읽기 카운터---------------------------
  if (temp_count == 800) {
    Temp(t_a);
    temp_count = 0;
  }
  //------토양 습도 값 읽기 카운터---------------------------
  if (soil_count == 900) {
    Soil(soil);
    soil_count = 0;
  }
  //------조도 값 읽기 카운터---------------------------
  if (light_count == 1000) {
    Light(light);
    light_count = 0;
  }
  //------펌프 출력 카운터---------------------------
  if (pump_count == 50) {
    Pump(soil);
    pump_count = 0;
  }
  //------펜 출력 카운터---------------------------
  if (fan_count == 60) {
    Fan(t_a);
    fan_count = 0;
  }
  //------LED 출력 카운터---------------------------
  if (led_count == 70) {
    LED(light);
    led_count = 0;
  }
}

//------------인터럽트를 위한 카운터 호출 함수----------------------
void timerIsr() {
  //전체 코드 카운트
  time_count += 1;
  //습도 센서 카운트
  hum_count += 1;
  //온도 센서 카운트
  temp_count += 1;
  //토양 수분 센서 카운트
  soil_count += 1; 
  //조도 센서 카운트
  light_count += 1; 
  //펌프 카운트
  pump_count += 1;
  //펜 카운트
  fan_count += 1;
  //LED 카운트
  led_count += 1;
}



//------------습도 값 시리얼 출력 및 아날로그 값 전달 호출 함수----------------------
void Hum(int h) {
  Serial.print("습도:");
  Serial.println(h); // 습도 값 출력
}

//------------온도 값 시리얼 출력 및 아날로그 값 전달 호출 함수----------------------
void Temp(int t) {
  Serial.print("온도:");
  Serial.println(t); // 온도 값 출력
}
//------------토양 수분 값 호출 함수----------------------
void Soil(int soil) {
  Serial.print("토양 수분:");
  Serial.println(soil); //토양 수분 값 출력
}
//------------조도 값 호출 함수----------------------
void Light(int light) {
  Serial.print("조도:");
  Serial.println(light); //조도 값 출력
}
//------------Pump ON/OFF 함수----------------------
void Pump(int soil) {
  //추후 토양 수분 센서에 비례한 값을 이용하여 PWM 출력을 하도록 한다.
  int soil_pwm;
  soil_pwm = map(soil, 0, 1023, 0, 12); //펌프의 PWM 출력을 위한 
  if (soil > 750) {
    digitalWrite(pump, HIGH);
  } else {
    digitalWrite(pump, LOW);
  }
  /*
    if(soil > 600){
    analogWrite(pump, soil_pwm);
    }
  */
}
//------------Fan 출력 함수----------------------
void Fan(int temp) {
  //추후 조도 센서에 비례한 값을 이용하여 PWM 출력을 하도록 한다.
  int temp_pwm;
  temp_pwm = map(temp, 0, 50, 0, 12);
  if (temp > 30) {
    digitalWrite(temp, HIGH);
  } else {
    digitalWrite(temp, LOW);
  }
}
//------------LED 출력 함수----------------------
void LED(int light) {
  //추후 조도 센서에 비례한 값을 이용하여 PWM 출력을 하도록 한다.
  int light_pwm;
  if (light > 600) {
    digitalWrite(led, HIGH);
  } else {
    digitalWrite(led, LOW);
  }
}
