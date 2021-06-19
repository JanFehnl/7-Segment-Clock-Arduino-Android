#include <FastLED.h>

#define Num_Strip1 30
struct CRGB Strip1[Num_Strip1];

byte Red[5] = {255, 255, 255, 255};
byte Green[5] = {255, 255, 255, 255};
byte Blue[5] = {255, 255, 255, 255};
byte State;
byte Sekunde = 0;
byte MinuteUmspringen;
bool ValueIsComing = false;
unsigned long timeNow = 0;
unsigned long timeLast = 0;
int seconds = 0;
int minutes = 33;
int hours = 12;
int TimeCorrection = 1060;
int CaseNum;
char Case;

void setup()
{
  Serial.begin(9600);
  FastLED.addLeds<WS2811, 6, BRG>(Strip1, Num_Strip1);
}

void loop()
{
  timeNow = millis() / TimeCorrection;
  seconds = timeNow - timeLast;

  Sekunde = seconds;
  int ZeitInSekunden = Sekunde;
  int Minute = minutes;
  int Stunde = hours;

  if (MinuteUmspringen != Minute)
  {
    ShowDigit(0, Stunde / 10, 0);
    ShowDigit(7, Stunde % 10, 1);
    ShowDigit(16, Minute / 10, 2);
    ShowDigit(23, Minute % 10, 3);
    MinuteUmspringen = Minute;
  }
  if (ZeitInSekunden % 2 == 1)
  {
    Strip1[14] = CRGB(Red[4], Green[4], Blue[4]);
    Strip1[15] = CRGB(Red[4], Green[4], Blue[4]);
  }
  else
  {
    Strip1[14] = CRGB(Red[4] / 5, Green[4] / 5, Blue[4] / 5);
    Strip1[15] = CRGB(Red[4] / 5, Green[4] / 5, Blue[4] / 5);
  }

  if (seconds == 60)
  {
    timeLast = timeNow;
    minutes = minutes + 1;
  }

  if (minutes == 60)
  {
    minutes = 0;
    hours = hours + 1;
  }

  if (Serial.available())
  {
    if (ValueIsComing)
    {
      long int a = Serial.read();
      if (Case == 'a')
      {
        switch (CaseNum)
        {
        case 0:
          hours = a;
          CaseNum++;
          break;

        case 1:
          minutes = a;
          CaseNum++;
          break;

        case 2:
          timeLast = timeNow - a;
          ValueIsComing = false;
          break;

        default:
          break;
        }
      }
      else if (Case == 'b')
      {
        switch (CaseNum)
        {
        case 0:
          State = a;
          CaseNum++;
          break;

        case 1:
          if (State == 0 || State == 1 || State == 2 || State == 3)
          {
            Red[State] = a;
          }
          else if (State == 4)
          {
            Red[0] = a;
            Red[1] = a;
          }
          else if (State == 5)
          {
            Red[2] = a;
            Red[3] = a;
          }
          else if (State == 6)
          {
            Red[0] = a;
            Red[1] = a;
            Red[2] = a;
            Red[3] = a;
            Red[4] = a;
          }
          else if (State == 7)
          {
            Red[4] = a;
          }
          CaseNum++;
          break;

        case 2:
          if (State == 0 || State == 1 || State == 2 || State == 3)
          {
            Green[State] = a;
          }
          else if (State == 4)
          {
            Green[0] = a;
            Green[1] = a;
          }
          else if (State == 5)
          {
            Green[2] = a;
            Green[3] = a;
          }
          else if (State == 6)
          {
            Green[0] = a;
            Green[1] = a;
            Green[2] = a;
            Green[3] = a;
            Green[4] = a;
          }
          else if (State == 7)
          {
            Green[4] = a;
          }
          CaseNum++;
          break;

        case 3:
          if (State == 0 || State == 1 || State == 2 || State == 3)
          {
            Blue[State] = a;
          }
          else if (State == 4)
          {
            Blue[0] = a;
            Blue[1] = a;
          }
          else if (State == 5)
          {
            Blue[2] = a;
            Blue[3] = a;
          }
          else if (State == 6)
          {
            Blue[0] = a;
            Blue[1] = a;
            Blue[2] = a;
            Blue[3] = a;
            Blue[4] = a;
          }
          else if (State == 7)
          {
            Blue[4] = a;
          }
          MinuteUmspringen--;
          ValueIsComing = false;
          break;

        default:
          break;
        }
      }
    }
    else
    {
      char a = Serial.read();
      switch (a)
      {
      case 'a':
        Case = a;
        CaseNum = 0;
        ValueIsComing = true;
        break;

      case 'b':
        Case = a;
        CaseNum = 0;
        ValueIsComing = true;
        break;

      default:
        break;
      }
    }
  }
  FastLED.show();
}

void ShowDigit(int StartPosition, int Digit, int Num)
{
  FastLED.setBrightness(255);
  for (int a = StartPosition; a <= StartPosition + 7; a++)
  {
    Strip1[a] = CHSV(255, 255, 0);
  }
  if (Digit == 0)
  {
    Strip1[StartPosition + 1] = CRGB(Red[Num], Green[Num], Blue[Num]);
    Strip1[StartPosition + 2] = CRGB(Red[Num], Green[Num], Blue[Num]);
    Strip1[StartPosition + 3] = CRGB(Red[Num], Green[Num], Blue[Num]);
    Strip1[StartPosition + 4] = CRGB(Red[Num], Green[Num], Blue[Num]);
    Strip1[StartPosition + 5] = CRGB(Red[Num], Green[Num], Blue[Num]);
    Strip1[StartPosition + 6] = CRGB(Red[Num], Green[Num], Blue[Num]);
  }
  else if (Digit == 1)
  {
    Strip1[StartPosition + 1] = CRGB(Red[Num], Green[Num], Blue[Num]);
    Strip1[StartPosition + 6] = CRGB(Red[Num], Green[Num], Blue[Num]);
  }
  else if (Digit == 2)
  {
    Strip1[StartPosition] = CRGB(Red[Num], Green[Num], Blue[Num]);
    Strip1[StartPosition + 1] = CRGB(Red[Num], Green[Num], Blue[Num]);
    Strip1[StartPosition + 2] = CRGB(Red[Num], Green[Num], Blue[Num]);
    Strip1[StartPosition + 4] = CRGB(Red[Num], Green[Num], Blue[Num]);
    Strip1[StartPosition + 5] = CRGB(Red[Num], Green[Num], Blue[Num]);
  }
  else if (Digit == 3)
  {
    Strip1[StartPosition] = CRGB(Red[Num], Green[Num], Blue[Num]);
    Strip1[StartPosition + 1] = CRGB(Red[Num], Green[Num], Blue[Num]);
    Strip1[StartPosition + 2] = CRGB(Red[Num], Green[Num], Blue[Num]);
    Strip1[StartPosition + 5] = CRGB(Red[Num], Green[Num], Blue[Num]);
    Strip1[StartPosition + 6] = CRGB(Red[Num], Green[Num], Blue[Num]);
  }
  else if (Digit == 4)
  {
    Strip1[StartPosition] = CRGB(Red[Num], Green[Num], Blue[Num]);
    Strip1[StartPosition + 1] = CRGB(Red[Num], Green[Num], Blue[Num]);
    Strip1[StartPosition + 3] = CRGB(Red[Num], Green[Num], Blue[Num]);
    Strip1[StartPosition + 6] = CRGB(Red[Num], Green[Num], Blue[Num]);
  }
  else if (Digit == 5)
  {
    Strip1[StartPosition] = CRGB(Red[Num], Green[Num], Blue[Num]);
    Strip1[StartPosition + 2] = CRGB(Red[Num], Green[Num], Blue[Num]);
    Strip1[StartPosition + 3] = CRGB(Red[Num], Green[Num], Blue[Num]);
    Strip1[StartPosition + 5] = CRGB(Red[Num], Green[Num], Blue[Num]);
    Strip1[StartPosition + 6] = CRGB(Red[Num], Green[Num], Blue[Num]);
  }
  else if (Digit == 6)
  {
    Strip1[StartPosition] = CRGB(Red[Num], Green[Num], Blue[Num]);
    Strip1[StartPosition + 2] = CRGB(Red[Num], Green[Num], Blue[Num]);
    Strip1[StartPosition + 3] = CRGB(Red[Num], Green[Num], Blue[Num]);
    Strip1[StartPosition + 4] = CRGB(Red[Num], Green[Num], Blue[Num]);
    Strip1[StartPosition + 5] = CRGB(Red[Num], Green[Num], Blue[Num]);
    Strip1[StartPosition + 6] = CRGB(Red[Num], Green[Num], Blue[Num]);
  }
  else if (Digit == 7)
  {
    Strip1[StartPosition + 1] = CRGB(Red[Num], Green[Num], Blue[Num]);
    Strip1[StartPosition + 2] = CRGB(Red[Num], Green[Num], Blue[Num]);
    Strip1[StartPosition + 6] = CRGB(Red[Num], Green[Num], Blue[Num]);
  }
  else if (Digit == 8)
  {
    Strip1[StartPosition] = CRGB(Red[Num], Green[Num], Blue[Num]);
    Strip1[StartPosition + 1] = CRGB(Red[Num], Green[Num], Blue[Num]);
    Strip1[StartPosition + 2] = CRGB(Red[Num], Green[Num], Blue[Num]);
    Strip1[StartPosition + 3] = CRGB(Red[Num], Green[Num], Blue[Num]);
    Strip1[StartPosition + 4] = CRGB(Red[Num], Green[Num], Blue[Num]);
    Strip1[StartPosition + 5] = CRGB(Red[Num], Green[Num], Blue[Num]);
    Strip1[StartPosition + 6] = CRGB(Red[Num], Green[Num], Blue[Num]);
  }
  else if (Digit == 9)
  {
    Strip1[StartPosition] = CRGB(Red[Num], Green[Num], Blue[Num]);
    Strip1[StartPosition + 1] = CRGB(Red[Num], Green[Num], Blue[Num]);
    Strip1[StartPosition + 2] = CRGB(Red[Num], Green[Num], Blue[Num]);
    Strip1[StartPosition + 3] = CRGB(Red[Num], Green[Num], Blue[Num]);
    Strip1[StartPosition + 5] = CRGB(Red[Num], Green[Num], Blue[Num]);
    Strip1[StartPosition + 6] = CRGB(Red[Num], Green[Num], Blue[Num]);
  }
}
