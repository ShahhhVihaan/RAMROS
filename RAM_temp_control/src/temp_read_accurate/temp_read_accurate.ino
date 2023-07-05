// Define the pin connected to the thermistor
#define THERMISTORPIN A0

// Thermistor parameters
#define THERMISTORNOMINAL 10000      // Nominal resistance at 25 degrees Celsius
#define TEMPERATURENOMINAL 25        // Nominal temperature in degrees Celsius
#define BCOEFFICIENT 3950            // Beta coefficient of the thermistor
#define SERIESRESISTOR 10000         // Known resistance value connected in series with the thermistor

// Number of samples to take
#define NUMSAMPLES 5

int samples[NUMSAMPLES];  // Array to store the analog readings

void setup(void) {
  Serial.begin(9600);  // Initialize serial communication
}

void loop(void) {
  uint8_t i;
  float average;

  // Take N samples with a small delay
  for (i = 0; i < NUMSAMPLES; i++) {
    samples[i] = analogRead(THERMISTORPIN);  // Read analog value from the thermistor pin
    delay(5);  // Small delay between readings
  }

  // Calculate the average of the samples
  average = 0;
  for (i = 0; i < NUMSAMPLES; i++) {
    average += samples[i];
  }
  average /= NUMSAMPLES;

  Serial.print("Average analog reading: ");
  Serial.println(average);

  // Convert the average value to resistance
  average = 1023 / average - 1;  // Calculate resistance using voltage divider formula
  average = SERIESRESISTOR / average;

  Serial.print("Thermistor resistance: ");
  Serial.println(average);

  float steinhart;
  steinhart = average / THERMISTORNOMINAL;                 // Calculate (R/Ro)
  steinhart = log(steinhart);                              // Natural logarithm of (R/Ro)
  steinhart /= BCOEFFICIENT;                               // Divide by the beta coefficient (1/B * ln(R/Ro))
  steinhart += 1.0 / (TEMPERATURENOMINAL + 273.15);        // Add (1/To) where To is the nominal temperature in Kelvin
  steinhart = 1.0 / steinhart;                             // Invert the value
  steinhart -= 273.15;                                     // Convert absolute temperature to Celsius

  Serial.print("Temperature: ");
  Serial.print(steinhart);
  Serial.println(" °C");

  delay(100);  // Delay before taking the next set of readings
}