#define PWM_MAX 2000
#define PWM_MIN 1000
#define MOTOR_L_1 5
#define MOTOR_L_2 6
#define MOTOR_R_1 7
#define MOTOR_R_2 8
#define enA 11
#define enB 10
#define pwm1 A0
#define pwm2 A1
float out1 =0;
float out2 =0;
float in1 =0;
float in2 =0;
float p1 =0;
float p2 =0;
int d1 =0;
int d2 =0;

void setup() {
  Serial.begin(9600);
  pinMode(pwm1, INPUT_PULLUP);
  pinMode(pwm2, INPUT_PULLUP);
  pinMode(MOTOR_L_1, OUTPUT);
  pinMode(MOTOR_L_2, OUTPUT);
  pinMode(MOTOR_R_1, OUTPUT);
  pinMode(MOTOR_R_2, OUTPUT);
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  while (1) {
      not_connect();
    p1 = pulseIn(pwm1, HIGH);
    p2 = pulseIn(pwm2, HIGH);
    if (( p1 > 1450) && (p1 < 1550)) {
      if ((p2 > 1450) && (p2 < 1550)) {
        break;
      }
    }
  }
}


void loop() {
  digitalWrite(LED_BUILTIN, HIGH);
  in1 = pulseIn(pwm1, HIGH);
  in2 = pulseIn(pwm2, HIGH);
  out1 = (2 * in1) / (PWM_MAX - PWM_MIN) + (1 - 2 * PWM_MAX / (PWM_MAX - PWM_MIN));
  out2 = (2 * in2) / (PWM_MAX - PWM_MIN) + (1 - 2 * PWM_MAX / (PWM_MAX - PWM_MIN));

    if (in1 < 100) {
    out1 = 0;
    out2 = 0;
    not_connect();
    Serial.println("not_connect_in1");
  } else if (in1 < PWM_MIN) {
    out1 = -1;
  } else if ((in1 > 1495) && (in1 < 1505)) {
    out1 = 0;
  } else if (in1 > PWM_MAX) {
    out1 = 1;
  }

    if (in2 < 100) {
    out1 = 0;
    out2 = 0;
    not_connect();
    Serial.println("not_connect_in2");
  }else if (in2 < PWM_MIN) {
    out2 = -1;
  } else if ((in2 > 1450) && (in2 < 1550)) {
    out2 = 0;
  } else if (in2 > PWM_MAX) {
    out2 = 1;
  }

  if (out1 > 0) {
    digitalWrite(MOTOR_L_1, LOW);
    digitalWrite(MOTOR_L_2, HIGH);
    analogWrite(enA, abs(out1) * 255);
  } else {
    digitalWrite(MOTOR_L_1, HIGH);
    digitalWrite(MOTOR_L_2, LOW);
    analogWrite(enA, abs(out1) * 255);
  }

  if (out2 > 0) {
   digitalWrite(MOTOR_R_1, LOW);
    digitalWrite(MOTOR_R_2, HIGH);
    analogWrite(enB, abs(out2) * 255);
  } else {
     digitalWrite(MOTOR_R_1, HIGH);
    digitalWrite(MOTOR_R_2, LOW);
    analogWrite(enB, abs(out2) * 255);
  }
  /*
  Serial.print("out1 :");
  Serial.println(out1);
  Serial.print("out2 :");
  Serial.println(out2);
  */
    Serial.print("in1 :");
  Serial.println(in1);
 // Serial.print("in2 :");
//  Serial.println(in2);
}

void not_connect() {
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(100);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(100);                       // wait for a second
} 
