#include <LiquidCrystal.h>

// FOR BLUETOOTH MODULE

// MODULE RX -> ARDUINO TX

// MODULE TX -> ARDUINO RX

int Contrast = 1; // Contrast value for LCD screen

// Pins in parenthese used to communicate with the LCD screen
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

// ENUM with list of all pages
enum PAGE {MAIN_MENU, SET_PRESET, SET_RANDOM, SET_ONDEMAND, SET_LIST};

// Allows current page to be Main Menu
enum PAGE currentPage = MAIN_MENU;

//Tx Pin
const int TxPin = 18;
//Rx Pin
const int RxPin = 19;

void setup()
{
  Serial1.begin(9600); // Enables Serial1 Communication - 9600 Baud Rate

  Serial.begin(9600);  // Enables Serial Communication - 9600 Baud Rate

  pinMode(13, OUTPUT); // Changing pin 6 to output (LCD Contrast)

  analogWrite(13, Contrast); // Writing value for LCD screen contrast to pin 6

  lcd.begin(16, 2); // LCD Screen used only has 16X2 characters

  // Initial characters printed on LCD when code initialized
  lcd.print(F("Baseball Front"));
  lcd.setCursor(0,1);
  lcd.print(F("Toss Machine"));

  // While loop to wait for 'OK' to be sent from app before menu operation ===============
  boolean startup = true;
  while(startup)
  {
    while(Serial1.available()>1)
    {
      char data[2];
      Serial1.readBytes(data,2); // Read first 2 bytes
      if (data[0] == 'O' && data[1] == 'K')
      {
        startup = false; // Escape while loop if 2 bytes sent = 'OK'
      }
    }
  }
  // =====================================================================================
  Serial1.print(1); // Sends a placeholer '1' to notify app that the ardiuno has recieved 'OK' from the Bluetooth Module
}

// End of Setup
//----------------------------------------------------------------------------------------
// Start of Loop

void loop()
{
  switch (currentPage)
  {
    case MAIN_MENU: // Main Menu

      pg_MAIN_MENU(); // Starting Menu. Select Mode Here
      
    break;

    case SET_PRESET: // Mode 1 Preset Launching - Predetermined Location Selection

      pg_SET_PRESET(); // Asks for number of balls, location of balls, launches
      lcd.clear(); // Clears characters on LCD screen
      lcd.setCursor(0,0);
      lcd.print(F("DONE")); // Prints DONE on LCD
      
    break;

    case SET_RANDOM: // Mode 2 Random Launching - Random Location Selection

      pg_SET_RANDOM(); // Asks for number of balls, launches in random locations
      lcd.clear(); // Clears characters on LCD screen
      lcd.setCursor(0,0);
      lcd.print(F("DONE")); // Prints DONE on LCD

    break;

    case SET_ONDEMAND: // Mode 3 OnDemand Launching - Location Selected in Real Time w/ Remote

      pg_SET_ONDEMAND(); // Asks for a location, then lauches
      lcd.clear(); // Clears characters on LCD screen
      lcd.setCursor(0,0);
      lcd.print(F("DONE")); // Prints DONE on LCD
      
    break;

    case SET_LIST: // Mode 4 Preset Launching - Predetermined Location Selection

      pg_SET_LIST(); // Asks for number of balls at location, launches
      lcd.clear(); // Clears characters on LCD screen
      lcd.setCursor(0,0);
      lcd.print(F("DONE")); // Prints DONE on LCD
      
    break;
  }
}

// MAIN MENU =============================================================================
void pg_MAIN_MENU()
{

  bool UpdateDisplay = true; // Used to indicate a need to Update the LCD Screen

  char mode = NULL; // Used to store the mode select serial value transmitted by the Bluetooth module

  while(true) // Main Loop in Main Menu function
  {
    if(UpdateDisplay)
    {
      lcd.clear(); // Clears characters on LCD screen
      lcd.setCursor(0,0);   // Prints 1st row
      lcd.print(F("Menu:")); // <-
      lcd.setCursor(0,1);   // Prints 2nd row
      lcd.print(F("Choose A Mode")); // <-
      UpdateDisplay = false; // Prevents LCD screen from updating every loop
    }
    
    if(Serial1.available()>0)
    {
      mode = Serial1.read(); //Reads in the mode - should be a number 1-4
    }

    if(mode != NULL)
    {
      switch(mode) // Sets the next page based on the value of char mode
      {
        case '1': currentPage = SET_PRESET; return;
        case '2': currentPage = SET_RANDOM; return;
        case '3': currentPage = SET_ONDEMAND; return;
        case '4': currentPage = SET_LIST; return;
        default: break;
      }
    }
  }
}
// =======================================================================================

// PRESET MENU ===========================================================================
void pg_SET_PRESET()
{

  bool UpdateDisplay = true; // Used to indicate a need to Update the LCD Screen
  bool ListComplete = false; // Used to exit while loop once list of locations are complete

  int Num_of_Balls, MAX_NUM_BALLS = 25; // Num_of_Balls used to store the converted byte to int, MAX_NUM_BALLS is set to 25 to indicate max stored baseballs

  byte num_of_balls; // Used to store the number of balls serial value transmitted by the Bluetooth module

  while (true)
  {
    if(UpdateDisplay)
        {
          lcd.clear();
          lcd.setCursor(0,0);   // Prints 1st row
          lcd.print(F("PRESET MODE:")); // <-
          lcd.setCursor(0,1);   // Prints 2nd row
          lcd.print(F("Enter # of Ball")); // <-
          UpdateDisplay = false; // Won't run an update to the LCD screen again
        }

    if(Serial1.available()>0)
    {
      num_of_balls = Serial1.read(); // Reads byte value for number of baseballs

      // UPDATES SCREEN TO DISPLAY NUMBER
      lcd.clear(); // Clear screen
      lcd.setCursor(0,0);   // Prints 1st row
      lcd.print(F("PRESET MODE:")); // <-

      // CONVERTS CHAR "num_of_balls" TO INT Num_of_Balls
      Num_of_Balls = Number_of_Balls_Processor(num_of_balls);

      lcd.setCursor(0,1);
      lcd.print(Num_of_Balls); // Prints # of Baseballs on LCD Screen

      lcd.setCursor(3,1);
      lcd.print(F("Baseballs")); // After # of Baseballs on LCD Screen
    }

    if(Num_of_Balls > 0)
    {
      int List_of_Balls[Num_of_Balls]; // Initializes the list of positions


      while(!ListComplete)
      {

        if(Serial1.available()==Num_of_Balls)
        {
          byte List[Num_of_Balls]; // Used to store the ball location serial values transmitted by the Bluetooth module

          Serial1.readBytes(List,Num_of_Balls); // Read bytes until a new line is read, each byte is a location for the baseball

          for(int i=0; i<Num_of_Balls; ++i)
          {
            // CONVERTS CHAR "List" TO INT List_of_Balls
            List_of_Balls[i] = Location_Processor(i, List); // Converts array of char list of locations into array of int 'List_of_Balls' which is an array the size of number of balls with the location of the balls as contents
          }
          ListComplete = true; // Way to exit while loop
        }
      }

      Preset_Tossing_Processor(List_of_Balls, Num_of_Balls); // Function to aim and launch the baseballs using ball location and number of balls as a parameter

      currentPage = MAIN_MENU; // Main Menu will be the next page

      return; // Return to Main Menu
    }
  }
}
// =======================================================================================

// RANDOM MENU ===========================================================================
void pg_SET_RANDOM()
{
  bool UpdateDisplay = true; // Used to indicate a need to Update the LCD Screen

  int Num_of_Balls; // Used to store the converted byte to int

  byte num_of_balls; // Used to store the number of balls serial value transmitted by the Bluetooth module

  while (true) 
  {
    if(UpdateDisplay)
    {
      lcd.clear();
      lcd.setCursor(0,0);   // Prints 1st row
      lcd.print(F("RANDOM MODE:")); // <-
      lcd.setCursor(0,1);   // Prints 2nd row
      lcd.print(F("Enter # of Ball")); // <-
      UpdateDisplay = false; // Won't run an update to the LCD screen again
    }

    if(Serial1.available()>0)
    {
      num_of_balls = Serial1.read(); // Reads byte value for number of baseballs

      // UPDATES SCREEN TO DISPLAY NUMBER
      lcd.clear(); // Clear screen
      lcd.setCursor(0,0);   // Prints 1st row
      lcd.print(F("RANDOM MODE:")); // <-

      // CONVERTS CHAR "num_of_balls" TO INT Num_of_Balls
      Num_of_Balls = Number_of_Balls_Processor(num_of_balls);

      lcd.setCursor(0,1);
      lcd.print(Num_of_Balls); // Prints # of Baseballs on LCD Screen

      lcd.setCursor(3,1);
      lcd.print(F("Baseballs")); // After # of Baseballs on LCD Screen
    }

    if(Num_of_Balls > 0)
    {
      Random_Tossing_Processor(Num_of_Balls); // Function to aim and launch the baseballs using number of balls as a parameter

      currentPage = MAIN_MENU; // Sets the page back to Main Menu after motors finished

      return; // Return to Main Menu
    }
  }
}
// =======================================================================================

// ON DEMAND MENU ========================================================================
void pg_SET_ONDEMAND()
{
  bool UpdateDisplay = true; // Used to indicate a need to Update the LCD Screen

  int Ball; // Used to store the converted byte to int

  byte Ball_Position[1]; // Used to store the ball location serial value transmitted by the Bluetooth module

  while (true)
  {
    if(UpdateDisplay)
    {
      lcd.clear();
      lcd.setCursor(0,0);   // Prints 1st row
      lcd.print(F("ON DEMAND MODE:")); // <-
      lcd.setCursor(0,1);   // Prints 2nd row
      lcd.print(F("Enter Position")); // <-
      UpdateDisplay = false; // Won't run an update to the LCD screen again
    }

    if(Serial1.available()>0)
    {
      Ball_Position[0] = Serial1.read(); // Read byte in the buffer for location of a baseball

      // CONVERTS CHAR "Ball_Position" TO INT Ball
      Ball = Location_Processor(0, Ball_Position);

      
      if(Ball == 0) // If Ball = 0, EXIT button was pushed on app. This sets the current page to main menu then exits
      {
        currentPage = MAIN_MENU;
        return; // Return to Main Menu
      }

      OnDemand_Tossing_Processor(Ball); // Function to aim and launch the baseball using ball location as a parameter

      UpdateDisplay = true; // Update LED after toss

    }
  }
}
// =======================================================================================

// LIST MENU =============================================================================
void pg_SET_LIST()
{

  bool UpdateDisplay = true, ListComplete = false;

  int list_data_int = 0, MAX_NUM_BALLS = 25, ListDataArray[18], Num_of_Balls=0;

  byte list_data;

  while (true)
  {
    if(UpdateDisplay)
        {
          lcd.clear();
          lcd.setCursor(0,0);   // Prints 1st row
          lcd.print(F("LIST MODE:")); // <-
          lcd.setCursor(0,1);   // Prints 2nd row
          lcd.print(F("Enter # of Ball")); // <-
          UpdateDisplay = false; // Won't run an update to the LCD screen again
        }


    if(Serial1.available()>17) // When Serial data is sent
    {
      for(int i=0; i<18; ++i)
      {
        list_data = Serial1.read(); // Reads byte value

        // CONVERTS CHAR "num_of_balls" TO INT Num_of_Balls
        list_data_int = Number_of_Balls_Processor(list_data);

        // The data that comes from this format is an array of 18 elements that contain location and ball numbers. [Location1,#ofBaseBalls1,Location2,#ofBaseballs2,...]
        ListDataArray[i] = list_data_int;
      }

      // The Addition of all the number of baseballs
      Num_of_Balls = ListDataArray[1] + ListDataArray[3] + ListDataArray[5] + ListDataArray[7] + ListDataArray[9] + ListDataArray[11] + ListDataArray[13] + ListDataArray[15]+ListDataArray[17];

    }

    if(Num_of_Balls > 0)
    {
      List_Tossing_Processor(ListDataArray); // Function to aim and launch the baseballs using ball location as a parameter

      currentPage = MAIN_MENU; // Main Menu will be the next page

      return; // Return to Main Menu
    }
  }
}
// =======================================================================================

// NUMBER OF BALLS PROCESSOR =============================================================
int Number_of_Balls_Processor(byte num) // Used to convert a byte to an int
{

  String numstring = String(num);

  int intnum = numstring.toInt(); // Converts string to int

  return intnum; // Returns int
}
// =======================================================================================

// Location Processing ===================================================================
int Location_Processor(int i, byte list[]) // Used to convert a byte to an int
{
  int intlist = int(list[i]) - '0'; // Converts element in char array to int
  return intlist; // Returns int
}
// =======================================================================================