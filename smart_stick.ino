#include <TCS3200.h>
uint8_t RGBvalue[3];
TCS3200 colSens;

#define trigPin 13 
#define echoPin 12 //초음파
int tilt = 8;//기울기센서
int speakerPin = 10;//부저
int irSensor = 11;//적외선센서

int numTones = 2;
int tones[] = {7902,880,7040,220};

void setup() { 
    pinMode(trigPin, OUTPUT); 
    pinMode(echoPin, INPUT);
    pinMode(tilt, INPUT);
    pinMode(irSensor, INPUT);

    colSens.begin();

    tone(speakerPin,tones[2],200);
}

long microsecondsToCentimeters(long microseconds){
    return microseconds / 29 / 2;
}

void loop() { 
    long duration, cm;

    colSens.loop();
    colSens.getRGB (RGBvalue);

    digitalWrite(trigPin, LOW);
    delayMicroseconds(2); 
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10); 
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH); 
    
    cm = microsecondsToCentimeters(duration);

    if (cm < 100){
      tone(speakerPin,tones[0]);
      delay(100);
      noTone(speakerPin);
      delay(50);
    }
    else if(cm < 50){
      tone(speakerPin,tones[0]);
      delay(500);
      noTone(speakerPin);
      delay(100);
    }//초음파

    if(digitalRead(irSensor) == HIGH){
      tone(speakerPin,tones[2]);
      delay(300);
      noTone(speakerPin);
      delay(100);
    }//적외선센서

    if (digitalRead(tilt) == HIGH){
      int j = 0;
      while(digitalRead(tilt) == HIGH){
        delay(1000);
        j++;
        if(j>=15){
          for (int i = 0; i < sizeof(tones[i]-2); i++){
            tone(speakerPin,tones[i]);
            delay(300);
            noTone(speakerPin);
            delay(100);
          }//for
         }//if
          if(digitalRead(tilt) == LOW) {
            noTone(speakerPin);
            delay(100);
            j=0;
          }//if
      }//while
    }//if 기울기센서

    if(RGBvalue[0]>=160 and RGBvalue[0]<=200 and RGBvalue[1]<=140 and RGBvalue[2]<=115){
      tone(speakerPin,tones[3]);
      delay(200);
      noTone(speakerPin);
      delay(200);
    }
}
