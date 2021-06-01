// Including libraries
#include <SoftwareSerial.h>
#include <EmonLib.h>
#include <LiquidCrystal.h>

// Initialization of intances
EnergyMonitor emon1;
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// Global Variables
float powerFactor;
float powerFact;
float Voltages;
int count;

// Sensor pin defination
const int voltageSensor = A0;
const int currentSensor = A1;
const int tampSensor = A4;

// Initialization of variable
int mVperAmp = 100; 
int value = 0;
double sumWH = 0.00000;
float WH = 0;
double sumRupees = 0.00000;
float rupees = 0;
double Voltage = 0;
double vrms = 0;
double current = 0;
double irms = 0;
double power = 0;

// -------------------- Setup Funciton --------------------
void setup()
{
  pinMode(8, OUTPUT);     // Pin No. 8 defined as output
  Serial.begin(19200);    // Defining baud rate for bluetooth communication
  delay(500);
  
  emon1.voltage(voltageSensor, 230, 1.7);     // Voltage: input pin, calibration, phase_shift
  emon1.current(currentSensor, 58);           // Current: input pin, calibration.
  delay(100);
  
  lcd.begin(20, 4);     // Lcd defination (Total Cols, Total Rows)
  lcd.clear();
}


// -------------------- Looping Funciton --------------------

void loop()
{

  emon1.calcVI(20, 2000);         // Calculate all. No.of wavelengths, time-out
  emon1.serialprint();            // Print out all variables
  
  powerFact = emon1.powerFactor;
  Voltages = emon1.Vrms;
  powerFact= powerFact*1;
  
  if(irms<0.20)
  {
    powerFact=0;
  }

  // Energy Calculation and sending message after every 5 count
  energyCalculations();
  if (count == 5)
  {
    SendMessage();
    count = 0;
  }
  count = count +1;

  // Load Managment Body;
  if (power >= 250)
  {
    digitalWrite(8, HIGH);
    lcd.setCursor(1, 0); 
    lcd.print(" LOAD ABOVE LIMIT");
    SendMessage1();
    delay(60000);
    lcd.clear();     
  }
  else {
    digitalWrite(8, LOW);
    delay(500);
  }
  
  // Tampering Body
  value = analogRead(tampSensor);
  Serial.println(value);
  if (value == 1023)
  {
    digitalWrite(8, HIGH);
    Serial.println("Your Meter IS TEMPERED");
    lcd.setCursor(1, 0); 
    lcd.print(" METER IS TEMPERED");
    SendMessage2();
    delay(6000);
    lcd.clear();
  }
  else {
   digitalWrite(8,LOW);
   delay(500);
  }  
}


// -------------------- Energy Claculation Funciton --------------------

void energyCalculations()
{
  // Measured Voltage sending on terminal
  vrms = Voltages; 
  Serial.print("Voltage : ");
  Serial.print(vrms);
  Serial.println("Volt");

  // Measured Current sending on terminal
  current = getVPP(1);
  irms = (current / 2.0) * 0.707 * 1000 / mVperAmp;
  Serial.print("Current : ");
  Serial.print(irms);
  Serial.println("Amps");

  // Measured Power Factor sending on terminal
  power = (vrms * irms *powerFact );
  Serial.print("Power Factor : ");
  Serial.println(powerFact);

  // Measured Power sending on terminal
  Serial.print("Power : ");
  Serial.print(power);
  Serial.println("watt");

  // Measured Enegry Consumption sending on terminal
  WH = (power / 3600);
  Serial.print("Energy Consumed : ");
  Serial.print(WH);

  // Total Enegry Consumption sending on terminal
  Serial.println("Watt-Hour");
  sumWH = sumWH + WH;
  Serial.print("Total Energy Consumed : ");
  Serial.print(sumWH);
  Serial.println("Watt-Hour");

  // Counted Rupees sending on terminal
  rupees = getReading();
  Serial.print("Counted Rupees : ");
  Serial.print(rupees);
  Serial.println("Rs.");

  // Counted Total Rupees sending on terminal
  sumRupees = sumRupees + rupees ;
  Serial.print("Total Counted Rupees :");
  Serial.print(sumRupees);
  Serial.println("Rs.");
  Serial.println("");

  // Printing all values on LCD
  lcd.setCursor(1, 0);
  lcd.print(vrms);
  lcd.print("v");
  lcd.setCursor(12, 0);
  lcd.print(irms);
  lcd.print("A");
  lcd.setCursor(1, 1);
  lcd.print(power);
  lcd.print("W");
  lcd.setCursor(12, 1);
  lcd.print(WH);
  lcd.print("WH");
  lcd.setCursor(1, 2);
  lcd.print("Total WH : "); 
  lcd.print(sumWH);
  lcd.setCursor(1, 3); 
  lcd.print("PF. : ");
  lcd.print(powerFact);
  delay(5000);
  lcd.clear();
}

// -------------------- Current Measurement Funciton --------------------

float getVPP(int pinValue)
{
  float result;
  int readValue; 
  int maxValue = 0;        
  int minValue = 1024;        
  uint32_t start_time = millis();
  while ((millis() - start_time) < 1000)
  {
    if (pinValue == 0)
    {
      readValue = analogRead(voltageSensor);
    }
    else if (pinValue == 1)
    {
      readValue = analogRead(currentSensor);
    }
    if (readValue > maxValue)
    {
      maxValue = readValue;
    }
    if (readValue < minValue)
    {
      minValue = readValue;
    }
  }
  result = ((maxValue - minValue) * 5.0) / 1024.0;
  return result;
}

// -------------------- Rupees Claculation Funciton --------------------

float getReading()
{
  float solution;
  if (sumWH <= 50)
    solution = (WH * 3.15);
  if (( sumWH > 50 ) && ( sumWH <= 100 ))
    solution = ( WH * 3.60 );
  if (( sumWH > 100 ) && (sumWH <= 250))
    solution = (WH * 4.25);
  if (sumWH > 250)
    solution = (WH * 5.20);
  return solution;
}

// -------------------- Simple message sending Function --------------------

void SendMessage()
{
  Serial.println("Message from Smart Energy Meter");
  delay(500);
  Serial.print("Dear Customer, Your Energy Consumption is :");
  Serial.println(sumWH);
  Serial.print("Total Billing is Rs. ");
  Serial.println(sumRupees);
  delay(500);  
  Serial.println("Finish");
  Serial.println("");
}

// -------------------- Load Management message sending Function --------------------
// When consumer load exceeds the maximum demand, meter sheds the load and alert message is on the LCD as well as to the bluetooth terminal

void SendMessage1()
{
  Serial.println("Message from Smart Energy Meter");
  delay(500);
  Serial.println("Dear Customer, you are using load above the limit,kindly lower your load ");
  Serial.println("");
  delay(500);
  Serial.println ("Finish");
  Serial.println("");
}

// -------------------- Temper management message sending Funciton --------------------
// If meter casing is being lifted, tampering alert message is displayed on LCD and sent to the consumer and service provider.

void SendMessage2()
{
  Serial.println("Message from Smart Energy Meter");
  delay(500);
  Serial.print("Dear Customer, your meter has been tempered "); 
  delay(500);
  Serial.println ("Finish");
  Serial.println("");
}
