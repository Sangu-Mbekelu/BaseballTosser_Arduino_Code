// PRESET MODE ===========================================================================
// THERE IS NO ACTUAL MOTOR FUNCTIONING YET. THAT IS STILL TO BE DETERMINED
void Preset_Tossing_Processor(int *Location_of_Balls, int Num_of_Balls)
{
  int num;

  for (int i=0; i<Num_of_Balls; ++i)
  {
    num = Location_of_Balls[i];
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(F("Tossing:")); // Prints the tossing: prompt. No user input.
    lcd.setCursor(0,1);

    switch(num)
    {
      case 1:
        lcd.print(F("Top-Left"));
        Serial.println("GO");
        delay(3000);
      break;
      case 2:
        lcd.print(F("Top-Center"));
        Serial.println("GO");
        delay(3000);
      break;
      case 3:
        lcd.print(F("Top-Right"));
        Serial.println("GO");
        delay(3000);
      break;
      case 4:
        lcd.print(F("Center-Left"));
        Serial.println("GO");
        delay(3000);
      break;
      case 5:
        lcd.print(F("Center-Center"));
        Serial.println("GO");
        delay(3000);
      break;
      case 6:
        lcd.print(F("Center-Right"));
        Serial.println("GO");
        delay(3000);
      break;
      case 7:
        lcd.print(F("Bottom-Left"));
        Serial.println("GO");
        delay(3000);
      break;
      case 8:
        lcd.print(F("Bottom-Center"));
        Serial.println("GO");
        delay(3000);
      break;
      case 9:
        lcd.print(F("Bottom-Right"));
        Serial.println("GO");
        delay(3000);
      break;
    }
  }
  Serial1.print(1); // SENDS A '1' TO NOTIFY APP THE LAUNCHING HAS FINISHED
}
// =======================================================================================

// RANDOM MODE ===========================================================================
// THERE IS NO ACTUAL MOTOR FUNCTIONING YET. THAT IS STILL TO BE DETERMINED
void Random_Tossing_Processor(int Num_of_Balls)
{
  int num;

  for (int i=0; i<Num_of_Balls; ++i)
  {
    num = random(1,10);

    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(F("Tossing:")); // Prints the tossing: prompt. No user input.
    lcd.setCursor(0,1);

    switch(num)
    {
      case 1:
        lcd.print(F("Top-Left"));
        Serial.println("GO");
        delay(3000);
      break;
      case 2:
        lcd.print(F("Top-Center"));
        Serial.println("GO");
        delay(3000);
      break;
      case 3:
        lcd.print(F("Top-Right"));
        Serial.println("GO");
        delay(3000);
      break;
      case 4:
        lcd.print(F("Center-Left"));
        Serial.println("GO");
        delay(3000);
      break;
      case 5:
        lcd.print(F("Center-Center"));
        Serial.println("GO");
        delay(3000);
      break;
      case 6:
        lcd.print(F("Center-Right"));
        Serial.println("GO");
        delay(3000);
      break;
      case 7:
        lcd.print(F("Bottom-Left"));
        Serial.println("GO");
        delay(3000);
      break;
      case 8:
        lcd.print(F("Bottom-Center"));
        Serial.println("GO");
        delay(3000);
      break;
      case 9:
        lcd.print(F("Bottom-Right"));
        Serial.println("GO");
        delay(3000);
      break;
    }
  }
  Serial1.print(1); // SENDS A '1' TO NOTIFY APP THE LAUNCHING HAS FINISHED
}
// =======================================================================================

// ON DEMAND MODE ========================================================================
// THERE IS NO ACTUAL MOTOR FUNCTIONING YET. THAT IS STILL TO BE DETERMINED
void OnDemand_Tossing_Processor(int Location_of_Ball)
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(F("Tossing:")); // Prints the tossing: prompt. No user input.
  lcd.setCursor(0,1);

  switch(Location_of_Ball)
  {
    case 1:
      lcd.print(F("Top-Left"));
      Serial.println("GO");
      delay(3000);
    break;
    case 2:
      lcd.print(F("Top-Center"));
      Serial.println("GO");
      delay(3000);
    break;
    case 3:
      lcd.print(F("Top-Right"));
      Serial.println("GO");
      delay(3000);
    break;
    case 4:
      lcd.print(F("Center-Left"));
      Serial.println("GO");
      delay(3000);
    break;
    case 5:
      lcd.print(F("Center-Center"));
      Serial.println("GO");
      delay(3000);
    break;
    case 6:
      lcd.print(F("Center-Right"));
      Serial.println("GO");
      delay(3000);
    break;
    case 7:
      lcd.print(F("Bottom-Left"));
      Serial.println("GO");
      delay(3000);
    break;
    case 8:
      lcd.print(F("Bottom-Center"));
      Serial.println("GO");
      delay(3000);
    break;
    case 9:
      lcd.print(F("Bottom-Right"));
      Serial.println("GO");
      delay(3000);
    break;

    default:
      lcd.print(F("BAD VALUE"));
      delay(3000);
    break;
  }
}
// =======================================================================================

// LIST MODE =============================================================================
// THERE IS NO ACTUAL MOTOR FUNCTIONING YET. THAT IS STILL TO BE DETERMINED
void List_Tossing_Processor(int *List_Data)
{
  int Location, num;

  for (int i=0; i<17; ++i)
  {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(F("Tossing:")); // Prints the tossing: prompt. No user input.
    lcd.setCursor(0,1);

    if(i%2 == 0)
    {
      Location = List_Data[i];

      num = List_Data[i+1];

      switch(Location)
      {
        case 1:
          lcd.print(F("Top-Left"));
          for(int j=0;j<num;j++)
          {
            Serial.println("GO");
            delay(3000);
          }
        break;
        case 2:
          lcd.print(F("Top-Center"));
          for(int j=0;j<num;j++)
          {
            Serial.println("GO");
            delay(3000);
          }
        break;
        case 3:
          lcd.print(F("Top-Right"));
          for(int j=0;j<num;j++)
          {
            Serial.println("GO");
            delay(3000);
          }
        break;
        case 4:
          lcd.print(F("Center-Left"));
          for(int j=0;j<num;j++)
          {
            Serial.println("GO");
            delay(3000);
          }
        break;
        case 5:
          lcd.print(F("Center-Center"));
          for(int j=0;j<num;j++)
          {
            Serial.println("GO");
            delay(3000);
          }
        break;
        case 6:
          lcd.print(F("Center-Right"));
          for(int j=0;j<num;j++)
          {
            Serial.println("GO");
            delay(3000);
          }
        break;
        case 7:
          lcd.print(F("Bottom-Left"));
          for(int j=0;j<num;j++)
          {
            Serial.println("GO");
            delay(3000);
          }
        break;
        case 8:
          lcd.print(F("Bottom-Center"));
          for(int j=0;j<num;j++)
          {
            Serial.println("GO");
            delay(3000);
          }
        break;
        case 9:
          lcd.print(F("Bottom-Right"));
          for(int j=0;j<num;j++)
          {
            Serial.println("GO");
            delay(3000);
          }
        break;

        default:
          lcd.print(F("BAD VALUE"));
          delay(3000);
        break;
      }

    }

  }
  Serial1.print(1); // SENDS A '1' TO NOTIFY APP THE LAUNCHING HAS FINISHED
}
// =======================================================================================
