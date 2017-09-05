/***
  ----------------------------- |
  Analog Value  Current reading |
  ------------ | -------------- |
  0.49-0.52    |    13.5-14.0   |
  1.01-1.10    |    27.8-28.0   |
  ------------------------------|
**/

long day = 86400000; // 86400000 milliseconds in a day
long hour = 3600000; // 3600000 milliseconds in an hour
long minute = 60000; // 60000 milliseconds in a minute
long second =  1000; // 1000 milliseconds in a second

double totalamps, ampSec, ampHour;


// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  ampSec = 0.0;
  ampHour = 0.0;
  Serial.begin(9600);
}

// the loop routine runs over and over again forever:
void loop() {
  long timeNow = millis(); // start grabbing the time
  int seconds = (((timeNow % day) % hour) % minute) / second;
  int minutes = ((timeNow % day) % hour) / minute ;
  int hours = (timeNow % day) / hour;   
  int days = timeNow / day ;                        

  float curSen = readcellvoltage(14); // current sensor reading, LEM connected to A0
  float cell = readcellvoltage(15); // cell voltage reading, Lifepo4 cell connected to A1
  // Calibration as per multimeter values
  float offSet = 0.06;
  cell = cell - 0.22;
  curSen = curSen + offSet;

  // calibration as per clampmeter current values
  float amps = curSen * 28; // calibration may vary as per your conditions
  
  totalamps += amps;
  ampSec = totalamps;
  ampHour = totalamps / 3600;

  Serial.print("Cur.Sen: ");
  Serial.print(curSen);
  Serial.print("\t");
  Serial.print("Amps drawn: ");
  Serial.print(amps);
  Serial.print("\t");
  Serial.print("Cell voltage: ");
  Serial.print(cell);
  Serial.print("\t");
  Serial.print("Amp-Sec: ");
  Serial.print(ampSec, 4);
  Serial.print("\t");
  Serial.print("Amp-Hour: ");
  Serial.print(ampHour, 6);
  Serial.print("\t");
  Serial.print(minutes);
  Serial.print(":");
  Serial.print(seconds);
  Serial.println();

  delay(1000);
}
float readcellvoltage(int a)
{
  float readVoltage = analogRead(a); 
  float val = (readVoltage * 5 ) / 1023; // 0-1023 TO 0-5v
  return val;
}
