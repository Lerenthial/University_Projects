#include <LiquidCrystal.h>            //libraries for LCD screen and 4x4 keypad
#include <Keypad.h>

LiquidCrystal lcd(13, 12, 11, 10, 9, 8); 

long firstNum = 0;              
long secondNum = 0;
double result = 0;
int position = 0;
char customKey;
const byte ROWS = 4;
const byte COLUMNS = 4;

char keys[ROWS][COLUMNS] =         //defining function keys on keypad
{ 
    {'1', '2', '3', '+'},
    {'4', '5', '6', '-'},
    {'7', '8', '9', '*'},
    {'C', '0', '=', '/'}
};
    
byte rowPins[ROWS] = {7, 6, 5, 4}; //defining row pins in Arduino
byte colPins[COLUMNS] = {3, 2, 1, 0}; //defining column pins in Arduino

Keypad customKeypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLUMNS); //initialisation keypad class instance

void setup()
{
  lcd.begin(16,2);
  lcd.setCursor(0,0);                 //visual tweaking
  lcd.print("A = +");
  lcd.setCursor(7,0);
  lcd.print("||");
  lcd.setCursor(11,0);
  lcd.print("B = -");
  lcd.setCursor(0,1);
  lcd.print("C = *");
  lcd.setCursor(7,1);
  lcd.print("||");
  lcd.setCursor(11,1);
  lcd.print("D = /");
    delay(2000);
  	lcd.clear();
  lcd.setCursor(3,0);
  lcd.print("* = CLEAR");
  lcd.setCursor(3,1);
  lcd.print("# = RESULT");
    delay(2000);
    lcd.clear();
}

void loop()
{

    customKey = customKeypad.getKey();
    
    switch (customKey)
    {
    case '0' ... '9':                 //first number input
        lcd.setCursor(0, 0);
        firstNum = firstNum * 10 + (customKey - '0');
        lcd.print(firstNum);
        position++;
        break;

    case '+':                         //adding implementation
        firstNum = (result != 0 ? result : firstNum);
        lcd.setCursor(position, 0);
        lcd.print("+");
        position++;
        secondNum = SecondNumber(); //second number input
        result = firstNum + secondNum;
        lcd.setCursor(1, 1);
        lcd.print(result);
        firstNum = 0, secondNum = 0; //clearing values
        position = 0;
        break;

    case '-':                         //subtraction implementation
        firstNum = (result != 0 ? result : firstNum);
        lcd.setCursor(position, 0);
        lcd.print("-");
        position++;
        secondNum = SecondNumber(); 
        result = firstNum - secondNum;
        lcd.setCursor(1, 1);
        lcd.print(result);
        firstNum = 0, secondNum = 0;
        position = 0;
        break;

    case '*':                         //multiplication implementation
        firstNum = (result != 0 ? result : firstNum);
        lcd.setCursor(position, 0);
        lcd.print("*");
        position++;
        secondNum = SecondNumber(); 
        result = firstNum * secondNum;
        lcd.setCursor(1, 1);
        lcd.print(result);
        firstNum = 0, secondNum = 0;
        position = 0;
        break;

    case '/':                         //division implementation
        firstNum = (result != 0 ? result : firstNum);
        lcd.setCursor(position, 0);
        lcd.print("/");
        position++;
        secondNum = SecondNumber(); 
        lcd.setCursor(1, 1);

        secondNum == 0 ? lcd.print("ERROR") : result = (float)firstNum / (float)secondNum; //division by 0 error implementation

        // lcd.print(result);
        firstNum = 0, secondNum = 0;
        position = 0;
        break;

    case 'C':                         //clear screen implementation
        result = 0;
        firstNum = 0;
        secondNum = 0;
        position = 0;
        lcd.clear();
        break;
    }
}

long SecondNumber()
{
    while (1)
    {
        customKey = customKeypad.getKey();
        if (customKey >= '0' && customKey <= '9')
        {
            secondNum = secondNum * 10 + (customKey - '0');
            lcd.setCursor(position, 0);
            lcd.print(secondNum);
        }
        if (customKey == 'C')
        {
            result = 0;
            firstNum = 0;
            secondNum = 0;
            position = 0;
            lcd.clear();
            break;
        }

        if (customKey == '=')         //equation result implementation
        {
            lcd.setCursor(0, 1);
            lcd.print("=");

            position = result;
            lcd.clear();
            lcd.setCursor(0, 1);
            lcd.print("=");
            break;
        }
    }
    return secondNum;
}
