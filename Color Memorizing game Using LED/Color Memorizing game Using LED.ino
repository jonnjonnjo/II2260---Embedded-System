#include <bits/stdc++.h>
#define ledYellow 3
#define ledRed 21
#define ledGreen 19
#define buttonYellow 23
#define buttonRed 22
#define buttonGreen 1

const int maxn = 3;
int pointer = 0;
int gameSequence[maxn];
int isInGame = 0;
int isShowedSequence = 0;
int stateRed,stateGreen,stateYellow;
int stateRedBefore = 1, stateGreenBefore = 1, stateYellowBefore = 1;

/*
  Code :
  Yellow  0 
  Red     1
  Green   2
*/

void blinkAll();
void lightAll();
void makeSequence();
void showSequence();
void showLed(int idx, int time);
void check();
void reset();


void reset()
{
  pointer = 0;
  isInGame = 0;
  isShowedSequence = 0;
  stateRedBefore = 1;
  stateGreenBefore = 1;
  stateYellowBefore = 1;
}


void check()
{
  if(stateGreen && stateYellow && stateRed) // no button is clicked
  {
    stateGreenBefore = 1;
    stateRedBefore = 1;
    stateYellowBefore = 1;
    return;
  }else if(stateGreen == stateGreenBefore && stateRed == stateRedBefore && stateYellow == stateYellowBefore) // still clicking the same button
  {
    return;
  }

  // here, there are definitely a button that is being clicked

  if(gameSequence[pointer] == 0)
  {
    if(!stateYellow && stateGreen && stateRed && stateGreenBefore && stateRedBefore && stateYellowBefore) pointer++;
    else
    {
      //.println("Here in yellow ");
      showLed(1,1000);
      reset();
      return;
    }
  }else if(gameSequence[pointer] == 1)
  {
    if(stateYellow && !stateRed && stateGreen  && stateGreenBefore && stateRedBefore && stateYellowBefore) pointer++;
    else
    {
      //.println("Here in G ");
      showLed(1,1000);
      reset();
      return;
    }
  }else
  {
    if(stateYellow && stateRed && !stateGreen && stateGreenBefore && stateRedBefore && stateYellowBefore) pointer++;
    else
    {
      showLed(1,1000);
      reset();
      return;
    }
  }


  stateRedBefore = stateRed;
  stateGreenBefore= stateGreen;
  stateYellowBefore = stateYellow;

  if(pointer == maxn)
  {
    showLed(2,1000);
    reset();
    return;
  }
}

void showLed(int idx, int time = 500)
{
  if(idx == 0)
  {
    digitalWrite(ledYellow,HIGH);
    delay(time);
    digitalWrite(ledYellow,LOW);
    delay(time);
  }else if(idx == 1)
  {
    digitalWrite(ledRed,HIGH);
    delay(time);
    digitalWrite(ledRed,LOW);
    delay(time);   
  }else
  {
    digitalWrite(ledGreen,HIGH);
    delay(time);
    digitalWrite(ledGreen,LOW);
    delay(time);
  }
}

void showSequence()
{
  for(int i = 0;i < maxn;i++) showLed(gameSequence[i]);
}

void makeSequence()
{
  for(int i = 0;i < maxn;i++) gameSequence[i] = rand()%3;
}

void lightAll()
{
  digitalWrite(ledYellow,HIGH);
  digitalWrite(ledRed,HIGH);
  digitalWrite(ledGreen,HIGH);
  delay(1000);
  digitalWrite(ledYellow,LOW);
  digitalWrite(ledRed,LOW);
  digitalWrite(ledGreen,LOW);
  delay(1000);
}

void blinkAll()
{
  digitalWrite(ledYellow,HIGH);
  delay(50);
  digitalWrite(ledYellow,LOW);
  delay(50);
  digitalWrite(ledRed,HIGH);
  delay(50);
  digitalWrite(ledRed,LOW);
  delay(50);
  digitalWrite(ledGreen,HIGH);
  delay(50);
  digitalWrite(ledGreen,LOW);
  delay(50);
}

void setup()
{
  pinMode(ledYellow,OUTPUT);
  pinMode(ledRed,OUTPUT);
  pinMode(ledGreen,OUTPUT);
  pinMode(buttonYellow,INPUT_PULLUP);
  pinMode(buttonRed,INPUT_PULLUP);
  pinMode(buttonGreen,INPUT_PULLUP);
  //.begin(9600);
}

void loop()
{
  if(!isInGame)
  {
      stateRed = digitalRead(buttonRed);
      stateGreen = digitalRead(buttonGreen);
      stateYellow = digitalRead(buttonYellow);

      if(!stateRed && !stateGreen && !stateYellow)
      {
          isInGame = 1;
          lightAll();
      }else
      {
          blinkAll();
      }
  }else
  {
    if(!isShowedSequence)
    {
      makeSequence();
      showSequence();
      isShowedSequence = 1;
    }else // get into play
    {
      stateRed = digitalRead(buttonRed);
      stateYellow = digitalRead(buttonYellow);
      stateGreen = digitalRead(buttonGreen);
      check();
    }

  }
}