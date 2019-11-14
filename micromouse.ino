/* ALL RIGHT RESERVED FROM THE HALF RED SKULL*/
#include <EEPROM.h>

#define distance_at_left left
#define distance_at_front front
#define distance_at_right right

#define leftfront 2
#define leftback 3 
#define rightfront 4
#define rightback 5

#define trig_f 6
#define echo_f 7
#define trig_l 8
#define echo_l 9
#define trig_r 10
#define echo_r 11

int addl=0,addf=257,addr=513;;
int min_d=30;
int l=0,f=0,r=0,left,front,right;
long duration_l=0,duration_f=0,duration_r=0;
boolean block[256][256][256];

void setup()
{ pinMode(leftfront,OUTPUT);
  pinMode(leftback,OUTPUT);
  pinMode(rightfront,OUTPUT);
  pinMode(rightback,OUTPUT);
  pinMode(trig_f,OUTPUT);
  pinMode(echo_f,INPUT);
  pinMode(trig_l,OUTPUT);
  pinMode(echo_l,INPUT);
  pinMode(trig_r,OUTPUT);
  pinMode(echo_r,INPUT);
  
  
  digitalWrite(2,LOW);
  digitalWrite(3,LOW);
  digitalWrite(4,LOW);
  digitalWrite(5,LOW);
  delay(1500);
}

void search()
{   {digitalWrite(trig_f,LOW);digitalWrite(trig_l,LOW);digitalWrite(trig_r,LOW);}
    delayMicroseconds(2);
    {digitalWrite(trig_f,HIGH);digitalWrite(trig_l,HIGH);digitalWrite(trig_r,HIGH);}
    delayMicroseconds(10);
    {digitalWrite(trig_f,LOW);digitalWrite(trig_l,LOW);digitalWrite(trig_r,LOW);}
    
    duration_l= pulseIn(echo_l, HIGH);
    // Calculating the distance
    left= duration_l*0.34/2;
    duration_r= pulseIn(echo_r, HIGH);
    // Calculating the distance
    right= duration_r*0.34/2;
    duration_f= pulseIn(echo_f, HIGH);
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
        duration_l= pulseIn(echo_l, HIGH);
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
        duration_r= pulseIn(echo_l, HIGH);
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
    running();
}