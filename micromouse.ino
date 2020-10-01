/* ALL RIGHT RESERVED FROM THE HALF RED SKULL*/
#include <EEPROM.h>

#define DISTANCE_AT_LEFT left
#define DISTANCE_AT_FRONT front
#define DISTANCE_AT_RIGHT right

#define LEFTFRONT 2
#define LEFTBACK 3 
#define RIGHTFRONT 4
#define RIGHTBACK 5

#define TRIG_F 6
#define ECHO_F 7
#define TRIG_L 8
#define ECHO_L 9
#define TRIG_R 10
#define ECHO_R 11

int addl=0,addf=257,addr=513;;
int min_d=30;
int l=0,f=0,r=0,left,front,right;
long duration_l=0,duration_f=0,duration_r=0;
boolean block[256][256][256];

void setup()
{ pinMode(LEFTFRONT,OUTPUT);
  pinMode(leftback,OUTPUT);
  pinMode(RIGHTFRONT,OUTPUT);
  pinMode(RIGHTBACK,OUTPUT);
  pinMode(TRIG_F,OUTPUT);
  pinMode(ECHO_F,INPUT);
  pinMode(TRIG_L,OUTPUT);
  pinMode(ECHO_L,INPUT);
  pinMode(TRIG_R,OUTPUT);
  pinMode(ECHO_R,INPUT);
  
  
  digitalWrite(2,LOW);
  digitalWrite(3,LOW);
  digitalWrite(4,LOW);
  digitalWrite(5,LOW);
  delay(1500);
}

void search()
{   {digitalWrite(TRIG_F,LOW);digitalWrite(TRIG_L,LOW);digitalWrite(TRIG_R,LOW);}
    delayMicroseconds(2);
    {digitalWrite(TRIG_F,HIGH);digitalWrite(TRIG_L,HIGH);digitalWrite(TRIG_R,HIGH);}
    delayMicroseconds(10);
    {digitalWrite(TRIG_F,LOW);digitalWrite(TRIG_L,LOW);digitalWrite(TRIG_R,LOW);}
    
    duration_l= pulseIn(ECHO_L, HIGH);
    // Calculating the distance
    left= duration_l*0.34/2;
    duration_r= pulseIn(ECHO_R, HIGH);
    // Calculating the distance
    right= duration_r*0.34/2;
    duration_f= pulseIn(ECHO_F, HIGH);
    // Calculating the distance
    front= duration_f*0.34/2;
    
    if(left>min_d)
    {
        while(left>min_d)
        {
            digitalWrite(2,LOW);
            digitalWrite(3,HIGH);
            digitalWrite(4,HIGH);            
            digitalWrite(5,LOW);
            delay(500);
        duration_l= pulseIn(ECHO_L, HIGH);
        // Calculating the distance
        left= duration_l*0.34/2;
        l++;
        distance[l][f][r]=0;
        EEPROM.write(addl,distance[l][f][r]);
        addl++;
        }
    }
    else 
    {
    if(left<min_d  &&  right>min_d)
    {
        while(right>min_d)
        {
            digitalWrite(2,HIGH);
            digitalWrite(3,LOW);
            digitalWrite(4,LOW);            
            digitalWrite(5,HIGH);
            delay(500);
        duration_r= pulseIn(ECHO_L, HIGH);
        // Calculating the distance
        right= duration_r*0.34/2;
        r++;
        distance[l][f][r]=0;
        EEPROM.write(addr,distance[l][f][r]);
        addr++;
        }
    }
    else
    {
        digitalWrite(2,HIGH);
        digitalWrite(3,LOW);
        digitalWrite(4,HIGH);            
        digitalWrite(5,LOW);
        f++;
        distance[l][f][r]=0;
        EEPROM.write(addf,distance[l][f][r]);
        addf++;
    }
    f++;
    distance[l][f][r]=0;
    EEPROM.write(addf,distance[l][f][r]);
    addf++; 
}
void running()
{ l=0;f=0;r=0;
  while(distance[l][f][r]={1,0,1})
  {
     digitalWrite(2,HIGH);//forward
     digitalWrite(3,LOW);
     digitalWrite(4,HIGH);            
     digitalWrite(5,LOW);
     f++;
  }
  while(distance[l][f][r]={0,1,1})
  {
     digitalWrite(2,LOW);//left
     digitalWrite(3,HIGH);
     digitalWrite(4,HIGH);            
     digitalWrite(5,LOW);
     delay(500);
     l++;
  }
  while(distance[l][f][r]={1,1,0})
  {
     digitalWrite(2,HIGH);//right
     digitalWrite(3,LOW);
     digitalWrite(5,HIGH);            
     digitalWrite(4,LOW);
     delay(500);
     r++;
  }
}
 
    


void loop()
{
    for(l=0;l<256;left++)
    {
        for(f=0;f<256;f++)
        {
            for(r=0;r<256;r++)
            {
                distance[l][f][r]=1;
            }
        }
    }
    search();
    running();/*this function is still under construction it is just initialised */
}
/*Avoid Recurrence*/
