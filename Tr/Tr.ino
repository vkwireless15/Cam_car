#define Up 0
#define Down 1

byte Work = 0, dir = 0, st = 0;
int SpeedValue = 0, RealSpeed = 0;

void fastpwm()
{

}

void ChangeDir()
{
  analogWrite(10, 0);
  fastpwm();
  if(dir == 0)
  {
    digitalWrite(8,LOW);
    digitalWrite(9,HIGH);
    dir = 1;
  }
  else
  {
    digitalWrite(8,HIGH);
    digitalWrite(9,LOW);
    dir = 0;
  }
}

void Speed(byte sp)
{
  if(sp == Up)
  {
    for(int i = 0; i<SpeedValue; i++)
    {
      analogWrite(10, i);
      fastpwm();
      delay(10);
    }
    RealSpeed = SpeedValue;
  }
  if(sp == Down)
  {
    for(int j = SpeedValue; j>0; j--)
    {
      analogWrite(10, j);
      fastpwm();
      delay(10);
    }
    RealSpeed = SpeedValue;
  }
}

void setup() {
  // put your setup code here, to run once:

  TCCR1A = 0b00000001;
  TCCR1B = 0b00001001;

  analogWrite(10, RealSpeed);
  fastpwm();

  pinMode(2,INPUT);
  pinMode(3,INPUT);
  pinMode(4,INPUT);

  pinMode(8,OUTPUT);
  pinMode(9,OUTPUT);

  digitalWrite(2,HIGH);
  digitalWrite(3,HIGH);
  digitalWrite(4,HIGH);

  digitalWrite(8,HIGH);
  digitalWrite(9,HIGH);
  delay(1000);
  digitalWrite(9,LOW);
  digitalWrite(8,LOW);

  delay(1000);
  
  if(digitalRead(4) != 0)
  {Work =1; digitalWrite(8,HIGH);}
}

void loop() {

 if(digitalRead(4) == 0 && st == 0)
 {
   Speed(Down);
   ChangeDir();
   Speed(Up);
   st = 1;
 }
 else
 {
  if(digitalRead(4) == 1)
  {
    if(st == 1)
    {
       delay(100); 
    }
    st = 0;
  }
 }
 if(Work == 1)
 {
    if(digitalRead(2) == 0)
    { 
      if(SpeedValue + 3 <= 255)
      {
        SpeedValue += 3;
      }
      else
      {
        SpeedValue = 255;
      }
      RealSpeed = SpeedValue;
      analogWrite(10, RealSpeed);
      fastpwm();
      delay(100);
    }

    if(digitalRead(3) == 0)
    { 
      if(SpeedValue - 3 >= 0)
      {
        SpeedValue -= 3;
      }
      else
      {
        SpeedValue = 0;
      }
      RealSpeed = SpeedValue;
      analogWrite(10, RealSpeed);
      fastpwm();
      delay(100);
    }
 }

}
