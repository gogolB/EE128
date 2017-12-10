//define pins
#define L_EN 10
#define R_EN 11
#define L_M1 9
#define L_M2 8
#define R_M1 12
#define R_M2 13
#define HORN 6
#define HEADLIGHT 5

//directions
#define FOR 1
#define BACK 2
#define CCW 3
#define CW 4
#define STOP 5
#define FL 6
#define FR 7
#define BL 8
#define BR 9

//BT
char bt_char = '0';
#define FOR_CHAR 'F'
#define BACK_CHAR 'B'
#define CCW_CHAR 'R'
#define CW_CHAR 'L'
#define STOP_CHAR 'S'
#define LIGHT_CHAR 'W'
#define HORN_CHAR 'V'
#define FW_LEFT 'G'
#define FW_RIGHT 'I'
#define BACK_LEFT 'H'
#define BACK_RIGHT 'J'

//globals
bool horn_stat = false;
bool light_stat = false;
int L_M_OFFSET = 25;
int BASE_SPEED = 150;
int DIAG_OFFSET = 80;

//function prototypes
void set_motor(int dir);
void toggle_horn();
void toggle_headlights();

void setup() 
{
  //pin modes
  pinMode(HORN, OUTPUT);
  pinMode(HEADLIGHT, OUTPUT);
  pinMode(L_EN, OUTPUT);
  pinMode(R_EN, OUTPUT);
  pinMode(L_M1, OUTPUT);
  pinMode(L_M2, OUTPUT);
  pinMode(R_M1, OUTPUT);
  pinMode(R_M2, OUTPUT);
  
  //setup BT
  Serial.begin(9600);
  
  //set initial motor dir to stop and set enables
  analogWrite(L_EN, BASE_SPEED + L_M_OFFSET);
  analogWrite(R_EN, BASE_SPEED);
  set_motor(STOP);
  toggle_headlights();
}

void loop() 
{
  //check for bt val
  if(Serial.available())
  {
    bt_char = Serial.read();
    Serial.println(bt_char);
    Serial.flush();
  }

  switch(bt_char)
  {
    case LIGHT_CHAR:
      toggle_headlights();
    break;

    case HORN_CHAR:
      toggle_horn();
    break;

    case FOR_CHAR:
      set_motor(FOR);
    break;

    case BACK_CHAR:
      set_motor(BACK);
    break;

    case CCW_CHAR:
      set_motor(CCW);
    break;

    case CW_CHAR:
      set_motor(CW);
    break;

    case STOP_CHAR:
      set_motor(STOP);
    break;

    case FW_LEFT:
      set_motor(FL);
    break;

    case FW_RIGHT:
      set_motor(FR);
    break;

    case BACK_LEFT:
      set_motor(BL);
    break;

    case BACK_RIGHT:
      set_motor(BR);
    break;

    default:
      set_motor(STOP);
    break;
  }
  delay(5); //200 ticks per second
}

void set_motor(int dir)
{
  switch(dir)
  {
    case STOP:
      //stop
      //Serial.println("Stop");
      analogWrite(L_EN, BASE_SPEED + L_M_OFFSET);
      analogWrite(R_EN, BASE_SPEED);
      digitalWrite(L_M1, LOW);
      digitalWrite(L_M2, LOW);
      digitalWrite(R_M1, LOW);
      digitalWrite(R_M2, LOW);
    break;
    
    case BACK:
      //backward
      //Serial.println("Back");
      analogWrite(L_EN, BASE_SPEED + L_M_OFFSET);
      analogWrite(R_EN, BASE_SPEED);
      digitalWrite(L_M1, HIGH);
      digitalWrite(L_M2, LOW);
      digitalWrite(R_M1, HIGH);
      digitalWrite(R_M2, LOW);
    break;

    case FOR:
      //forward
      //Serial.println("Forward");
      analogWrite(L_EN, BASE_SPEED + L_M_OFFSET);
      analogWrite(R_EN, BASE_SPEED);
      digitalWrite(L_M1, LOW);
      digitalWrite(L_M2, HIGH);
      digitalWrite(R_M1, LOW);
      digitalWrite(R_M2, HIGH);
    break;
    
    case CW:
      //rotate CW
      //Serial.println("CCW");
      analogWrite(L_EN, BASE_SPEED + L_M_OFFSET);
      analogWrite(R_EN, BASE_SPEED);
      digitalWrite(L_M1, HIGH);
      digitalWrite(L_M2, LOW);
      digitalWrite(R_M1, LOW);
      digitalWrite(R_M2, HIGH);
    break;

    case CCW:
      //rotate CCW
      //Serial.println("CW");
      analogWrite(L_EN, BASE_SPEED + L_M_OFFSET);
      analogWrite(R_EN, BASE_SPEED);
      digitalWrite(L_M1, LOW);
      digitalWrite(L_M2, HIGH);
      digitalWrite(R_M1, HIGH);
      digitalWrite(R_M2, LOW);
    break;

    case FL:
      analogWrite(L_EN, BASE_SPEED + L_M_OFFSET);
      analogWrite(R_EN, BASE_SPEED + DIAG_OFFSET);
      digitalWrite(L_M1, LOW);
      digitalWrite(L_M2, HIGH);
      digitalWrite(R_M1, LOW);
      digitalWrite(R_M2, HIGH);
    break;

    case FR:
      analogWrite(L_EN, BASE_SPEED + L_M_OFFSET + DIAG_OFFSET);
      analogWrite(R_EN, BASE_SPEED);
      digitalWrite(L_M1, LOW);
      digitalWrite(L_M2, HIGH);
      digitalWrite(R_M1, LOW);
      digitalWrite(R_M2, HIGH);
    break;

    case BL:
      analogWrite(L_EN, BASE_SPEED + L_M_OFFSET);
      analogWrite(R_EN, BASE_SPEED + DIAG_OFFSET);
      digitalWrite(L_M1, HIGH);
      digitalWrite(L_M2, LOW);
      digitalWrite(R_M1, HIGH);
      digitalWrite(R_M2, LOW);
    break;

    case BR:
      analogWrite(L_EN, BASE_SPEED + L_M_OFFSET + DIAG_OFFSET);
      analogWrite(R_EN, BASE_SPEED);
      digitalWrite(L_M1, HIGH);
      digitalWrite(L_M2, LOW);
      digitalWrite(R_M1, HIGH);
      digitalWrite(R_M2, LOW);
    break;

    default:
      //stop
      //Serial.println("Stop");
      digitalWrite(L_M1, LOW);
      digitalWrite(L_M2, LOW);
      digitalWrite(R_M1, LOW);
      digitalWrite(R_M2, LOW);
    break;
  }
}

void toggle_horn()
{
  //Serial.println("Horn");
  horn_stat = !(horn_stat);
  if(horn_stat)
  {
    //horn on
    analogWrite(HORN, 255/2);
  }
  else
  {
    //horn off
    digitalWrite(HORN, LOW);
  }
}

void toggle_headlights()
{
  //Serial.println("Headlights");
  light_stat = !(light_stat);
  if(light_stat)
  {
    //light on
    digitalWrite(HEADLIGHT, HIGH);
  }
  else
  {
    //light off
    digitalWrite(HEADLIGHT, LOW);
  }
}

