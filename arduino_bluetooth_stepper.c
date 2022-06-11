using namespace std;
#define IN1 8
#define IN2 9
#define IN3 10
#define IN4 11

int koraci = 0;
boolean smjer = true;
unsigned long vrijemeZadnje = 0;   // biljeziti cemo vrijeme
unsigned long vrijemeTrenutno = 0; // koje je potrebno da se
unsigned long vrijeme = 0;         // se izvrsi zadani kut
int koraciPreostalo = 4095;        // ovaj koracni ukupno ima 4095 koraka
int BRZINA = 1000;

void setup()
{
  Serial.begin(9600);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
}

void loop()
{
  String value = Serial.readString();
  int i;
  if (value == "right")
  {
    smjer = true;
  }
  else if (value == "left")
  {
    smjer = false;
  }
  else
  {
    i = value.toInt();
    Serial.println(value);
    Serial.println(i);

    if (i > 1000)
    {
      BRZINA = i;
    }
    if (i == -1)
    { //SLATI -1 KAD NAM TREBA DA STOJI
      BRZINA = 0
    }
  }
  while (koraciPreostalo > 0)
  {
    vrijemeTrenutno = micros();
    if (vrijemeTrenutno - vrijemeZadnje >= BRZINA)
    {
      stepper(1); // pozovi funkciju stepper (vidi dolje void stepper)
      vrijeme = vrijeme + micros() - vrijemeZadnje;
      vrijemeZadnje = micros();
      koraciPreostalo--;
    }
  }

  Serial.println(vrijeme);
  delay(2000);
  koraciPreostalo = 4095; // resetiraj broj koraka
}

void stepper(int brojKoraka)
{
  for (int x = 0; x < brojKoraka; x++)
  {
    switch (koraci)
    {
    case 0:
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, HIGH);
      break;
    case 1:
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, HIGH);
      break;
    case 2:
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, LOW);
      break;
    case 3:
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, LOW);
      break;
    case 4:

      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, LOW);
      break;
    case 5:
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, HIGH);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, LOW);
      break;
    case 6:
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, LOW);
      break;
    case 7:
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, HIGH);
      break;
    default:
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, LOW);
      break;
    }
    postaviSmjer();
  }
}
void postaviSmjer()
{
  if (smjer == 1)
  {
    koraci++;
  }
  if (smjer == 0)
  {
    koraci--;
  }
  if (koraci > 7)
  {
    koraci = 0;
  }
  if (koraci < 0)
  {
    koraci = 7;
  }
}
