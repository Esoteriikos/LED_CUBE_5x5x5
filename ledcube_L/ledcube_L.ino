
#define SIZE 5
#define COLS (SIZE*SIZE)

byte colPins[COLS] = {22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46};
byte levelPins[SIZE] = {49,50,51,52,53};

int frame[] = {};
int frameSize;
int frame_nacl[] = {0,0, 0,2, 0,4, 0,10, 0,12, 0,14, 0,20, 0,22, 0,24, 2,0, 2,2, 2,4, 2,10, 2,12, 2,14, 2,20, 2,22, 2,24, 4,0, 4,2, 4,4, 4,10, 4,12, 4,14, 4,20, 4,22, 4,24};
int frameSize_nacl = sizeof( frame_nacl ) / sizeof( int );
 
int frame_diamond[] = {0,0, 0,4, 0,12, 0,20, 0,24, 1,6, 1,16, 2,2, 2,10, 2,14, 2,22, 3,8, 3,18, 4,0, 4,4, 4,12, 4,20, 4,24};
int frameSize_diamond = sizeof( frame_diamond ) / sizeof( int );
int pat;

void setup ()
{
  Serial.begin(230400);
  for(int i=0;i<25;i++){
    pinMode(colPins[i],OUTPUT);
    digitalWrite(colPins[i],LOW);
  }
  for(int i=0;i<5;i++){
    pinMode(levelPins[i],OUTPUT);
    digitalWrite(levelPins[i],HIGH);
  }
  Serial.print("Setup complete !\n\n");
}

void display_clear_pattern()
{
  Serial.print("Transistion pattern\n\n");
  for(int i=0;i<25;i++){
    digitalWrite(colPins[i],HIGH);
  }
  for (int j=1 ; j>=0; j--){
    for(int i=0;i<5;i++){
        digitalWrite(levelPins[i], !digitalRead(levelPins[i]));
        delay(50);
      }
    delay(100);
    for(int i=0;i<5;i++){
        digitalWrite(levelPins[i], !digitalRead(levelPins[i]));
        delay(100);
      }
  }
}

void flush_pins()
{
  Serial.print("Flushing\n");
      for(int i=0;i<25;i++){
    digitalWrite(colPins[i],LOW);
  }
  for(int i=0;i<5;i++){
    digitalWrite(levelPins[i],HIGH);
  }
  Serial.print("Flush Complete\n\n");
}

void display_pattern(int del)
{ 
  unsigned long x;
  int i;
  if (pat ==1)
    {
      Serial.print("Displaying pattern NaCl\n");
      x = millis();
      while(millis() - x < del){
        for(int i=0;i<frameSize_nacl;i++){
          digitalWrite(levelPins[frame_nacl[i]],LOW);
          i++;
          digitalWrite(colPins[frame_nacl[i]],HIGH);
          for(int m=0;m<10;m++)
          {}
          i=i-1;
          digitalWrite(levelPins[frame_nacl[i]],HIGH);
          i++;
        }
      }
      Serial.print("NaCl Complete\n\n");
    }
  if (pat == 2)
    {
      Serial.print("Displaying pattern Diamond\n");
      x = millis();
      while(millis() - x < del){
        for(int i=0;i<frameSize_diamond;i++){
          digitalWrite(levelPins[frame_diamond[i]],LOW);
          i++;
          digitalWrite(colPins[frame_diamond[i]],HIGH);
          for(int m=0;m<10;m++)
          {
            }
          i=i-1;
          digitalWrite(levelPins[frame_diamond[i]],HIGH);
          i++;
          digitalWrite(colPins[frame_diamond[i]],LOW);
        }
      }
      Serial.print("Diamond Complete\n\n");
    }

}

void loop ()
{
    flush_pins();
    display_clear_pattern();
    flush_pins();
    pat = 1;
    display_pattern(4000);    // 1=nacl, 2=diamond,
    flush_pins();
    display_clear_pattern();
    flush_pins();
    pat = 2;
    display_pattern(4000);
   
}
