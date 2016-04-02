// Hands-On Arduino:
// Dr. Robert Paz:
// BD4x rotary encoder detection - double channel interrupt method:
// using Array:
// rotary encoder controlling RGB led with push button mode selector:


// rotary encoder max/min pulse counts (if clamping is required):
// mechanical (switch) rotatry encoder - 24 pulses per rot x4 (quadrature):

#define QMAX 96       // limit quadrature maximum pulse count for cw rotation:
#define QMIN 0        // limit quadrature minimum pulse count for ccw rotation:

/*
// uncomment this line if using a Common Anode LED:
#define COMMON_ANODE
*/

// mode switching:
byte modeButton = 7;          // rgb mode selector button pin:
boolean lastButton = LOW;
boolean currentButton = LOW;
byte modeIndicator = 13;      // rgb mode button on/off indicator led pin:
byte stateLedR = 14;          // Red mode indicator led (A0) pin:
byte stateLedG = 15;          // Green mode indicator led (A1) pin:
byte stateLedB = 16;          // Blue mode indicator led (A2) pin:
byte modeState = 0;           // mode cycle - 0, 1, 2, 3:
boolean mode = false;         // present state of indicator led (on/off):

// RGB led:
// RED:
byte rLed = 9;                // red led pin (~ PWM):
int rLevel = 255;               // red led pwm level;
int rCount = 0;               // red counter:
// GREEN:
byte gLed = 10;               // green led pin (~ PWM):
int gLevel = 255;               // green led pwm level:
int gCount = 0;               // green count:
// BLUE:
byte bLed = 11;               // blue led pin (~ PWM):
int bLevel = 255;               // blue led pwm level:
int bCount = 0;               // blue count:

// timing:
#define SETTIME 1000000       // microseconds:
unsigned long timep, time, etime;

// interupt counter:
long count = 0;
byte state, statep, index;

// Quadrature Encoder Matrix (Array):
int QEM [16] = {0, -1, 0, 1, 1, 0, -1, 0, 0, 1, 0, -1, -1, 0, 1, 0};

boolean A, B;                 // interrupt read:


void setup () {

    pinMode (stateLedR, OUTPUT);
    pinMode (stateLedG, OUTPUT);
    pinMode (stateLedB, OUTPUT);
    pinMode (modeIndicator, OUTPUT);
    digitalWrite (modeIndicator, LOW);
    pinMode (rLed, OUTPUT);
    analogWrite (rLed, 255);
    pinMode (gLed, OUTPUT);
    analogWrite (gLed, 255);
    pinMode (bLed, OUTPUT);
    analogWrite (bLed, 255);
    pinMode (modeButton, INPUT);          // to encoder push-button:

    Serial.begin (9600);                  // start serial monitor:
    
    pinMode (2, INPUT);                   // connect Channel A to pin 2:
    pinMode (3, INPUT);                   // connect Channel B to pin 3:
    
    attachInterrupt (0, ABchange, CHANGE); // setup interrupts (pins 2 and 3):
    attachInterrupt (1, ABchange, CHANGE);
    
    timep = micros ();                    // set the initial time:
    
    B = digitalRead (2);                  // read initial values of pins 2 and 3:
    A = digitalRead (3);
    
    if ((A == HIGH) && (B == HIGH)) statep = 0; // set initail state values:
    if ((A == HIGH) && (B == LOW)) statep = 1;
    if ((A == LOW) && (B == LOW)) statep = 2;
    if ((A == LOW) && (B == HIGH)) statep = 3;

    delay (500);

    printModeState ();
}


void loop () {

    buttonPress ();
    modeLed ();
    setMonitor ();    // serial monitor feed-back:

}


void ABchange () {                         // Interrupt Service Routine - Achange:

    B = digitalRead (2);
    A = digitalRead (3);
    
    if ((A == HIGH) && (B == HIGH)) state = 0;  // determine current state value:
    if ((A == HIGH) && (B == LOW)) state = 1;
    if ((A == LOW) && (B == LOW)) state = 2;
    if ((A == LOW) && (B == HIGH)) state = 3;

  //QEM [16] = {0, -1, 0, 1, 1, 0, -1, 0, 0, 1, 0, -1, -1, 0, 1, 0};
    index = (4 * state) + statep;
    count = count + QEM [index];

    countClamp ();                        // clamp count to max/min of quadrature of encoder:

    statep = state;                       // save current state:

}

/*
void Bchange () {                         // Interrupt Service Routine - Bchange:

    B = digitalRead (2);
    A = digitalRead (3);
    
    if ((A == HIGH) && (B == HIGH)) state = 0;  // determine current state value:
    if ((A == HIGH) && (B == LOW)) state = 1;
    if ((A == LOW) && (B == LOW)) state = 2;
    if ((A == LOW) && (B == HIGH)) state = 3;

  //QEM [16] = {0, -1, 0, 1, 1, 0, -1, 0, 0, 1, 0, -1, -1, 0, 1, 0};
    index = 4 * state + statep;
    count = count + QEM [index];

    countClamp ();                        // clamp count to max/min of quadrature of encoder:

    statep = state;

}
*/


void countClamp () {                      // clamp count from QMIN to QMAX:

    if (count > QMAX) {
        count = QMAX;
    }
    else if (count < QMIN) {
        count = QMIN;
    }

}


boolean debounce (boolean last) {         // mode button debounce:

    boolean current = digitalRead (modeButton);
    if (last != current) {
        delay (5);
        current = digitalRead (modeButton);
    }
    return current;

}


void printModeState () {
    Serial.print ("Mode: ");
    Serial.println (modeState);
}


void buttonPress () {
// if mode button is pressed (goes from 0 to 1) increment modeSate by 1
// when modeState is greater than 3, reset to 0:

    currentButton = debounce (lastButton);
    if (currentButton != lastButton) {
        if (currentButton == HIGH) {
            modeState ++;
            if (modeState > 3) {
                modeState = 0;
                printModeState ();
            }
            else {
                printModeState ();
            }
            mode = 1;
            digitalWrite (modeIndicator, mode);
        }
        else {
            mode = 0;
            digitalWrite (modeIndicator, mode);
        }
        
    }
    lastButton = currentButton;

}


void modeLed () {

    switch (modeState) {
        case 1:         // Red:
        {
            count = rCount;
            
            digitalWrite (stateLedR, HIGH);
            digitalWrite (stateLedG, LOW);
            digitalWrite (stateLedB, LOW);

            rLevel = map (count, QMIN, QMAX, 255, 0);
//            ifAnode ();
            analogWrite (rLed, rLevel);
            rCount = count;
            
            break;
        }
        case 2:         // Green:
        {
            count = gCount;
            
            digitalWrite (stateLedR, LOW);
            digitalWrite (stateLedG, HIGH);
            digitalWrite (stateLedB, LOW);

            gLevel = map (count, QMIN, QMAX, 255, 0);
//           ifAnode ();
            analogWrite (gLed, gLevel);
            gCount = count;
            
            break;
        }
        case 3:         // Blue:
        {
            count = bCount;
            
            digitalWrite (stateLedR, LOW);
            digitalWrite (stateLedG, LOW);
            digitalWrite (stateLedB, HIGH);

            bLevel = map (count, QMIN, QMAX, 255, 0);
//            ifAnode ();
            analogWrite (bLed, bLevel);
            bCount = count;
            
            break;
        }
        default:        // None:
        {
            digitalWrite (stateLedR, LOW);
            digitalWrite (stateLedG, LOW);
            digitalWrite (stateLedB, LOW);

            //count = count;
            
            break;
        }
    }

}


// Serial Monitor set-up feed-back and debugging:
void setMonitor () {                //    used only for serial monitor de-bugging:

    time = micros ();                     // set the current time:   
    etime = time - timep;                 // calculate elapsed time:
    if (etime > SETTIME) {                // test for time > 1 second:
        modeMonitor ();
        timep = time;                     // reset timer:
    }
}


void modeMonitor () {

    if (modeState == 1) {
        Serial.print ("Red mode selected: ");
        monitorPrint ();
    }
    else if (modeState == 2) {
        Serial.print ("Green mode selected: ");
        monitorPrint ();
    }
    else if (modeState == 3) {
        Serial.print ("Blue mode selected: ");
        monitorPrint ();
    }
    else {
        Serial.println ("No mode selected");
        monitorPrint ();
    }

}


void printRGBLevels () {
    Serial.print ("R:");
    Serial.print (255 - rLevel);
    Serial.print ("\tG:");
    Serial.print (255 - gLevel);
    Serial.print ("\tB:");
    Serial.println (255 - bLevel);
    Serial.println ();
}


void monitorPrint () {

    if (modeState > 0) {
        Serial.println (count);
        printRGBLevels ();
    }
    else {
        printRGBLevels ();
    }
     
}



/*
void ifAnode () {
    #ifdef COMMON_ANODE
          rLevel = 255 - rLevel;
          gLevel = 255 - gLevel;
          bLevel = 255 - bLevel;
    #endif
}
*/


