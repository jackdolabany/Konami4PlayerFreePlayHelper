// Change these pins to define whatever pins on the Arduino you want to use for inputs and outputs.
const int PlayerOneIn = 9;
const int PlayerTwoIn = 8;
const int PlayerThreeIn = 7;
const int PlayerFourIn = 6;

const int PlayerOneOut = 10;
const int PlayerTwoOut = 11;
const int PlayerThreeOut = 12;
const int PlayerFourOut = 13;

// Enter whatever time in miliseconds that you want to disable the button for after it's pressed.
const unsigned long DISABLE_TIME = 8000;

const unsigned long MAX_LONG = 0 - 1;

enum State
{
  WaitingForButtonPress,
  ButtonPressed,
  IgnoringButtonPress
};

class ControlledPin
{
  public: 
    ControlledPin::ControlledPin(int input, int output);
    void Setup();
    void Update();
  private:
    int _inputPin;
    int _outputPin;
    State _state;
    unsigned long _expirationMillis;
};

ControlledPin::ControlledPin(int input, int output)
{
  _inputPin = input;
  _outputPin = output;
  _state = WaitingForButtonPress;
  _expirationMillis = 0;
}

void ControlledPin::Setup()
{
  pinMode(_inputPin, INPUT);
  pinMode(_outputPin, OUTPUT);

  // Default is to write HIGH. Buttin presses are LOW.
  digitalWrite(_outputPin, HIGH);
}

void ControlledPin::Update() 
{
  // This is designed for JAMMA buttons so HIGH 5v is up and LOW 0v is pressed.
  int input = digitalRead(_inputPin);

  switch (_state) 
  {
    case WaitingForButtonPress:
        // Wait for them to press the coin in button.
        
        if(input == LOW)
        {
          // They pressed it! Set the output LOW and wait for them to release it.
          _state = ButtonPressed;
          digitalWrite(_outputPin, LOW);
          
          // Sleep with the output low for a little to account for any bounce from the button.
          delay(20);
        }
      break;
    case ButtonPressed:
      // The button is currently down, keep LOW on the output pin until they release the button.
      if(input == HIGH)
      {
        // They released it! Set the output HIGH and disable the button for a period.
        digitalWrite(_outputPin, HIGH);
        _state = IgnoringButtonPress;
        _expirationMillis = millis() + DISABLE_TIME;
      }
      break;
    case IgnoringButtonPress:
      // Do nothing until the timer is up, then we'll read inputs again.
      if(millis() >= _expirationMillis)
      {
        _state = WaitingForButtonPress;
      }
      break;
    default:
      break;
  }
}

ControlledPin PlayerOne(PlayerOneIn, PlayerOneOut);
ControlledPin PlayerTwo(PlayerTwoIn, PlayerTwoOut);
ControlledPin PlayerThree(PlayerThreeIn, PlayerThreeOut);
ControlledPin PlayerFour(PlayerFourIn, PlayerFourOut);

ControlledPin pins[] = { PlayerOne, PlayerTwo, PlayerThree, PlayerFour };

void setup() 
{
  for(int i = 0; i <= 3; i++)
  {
    pins[i].Setup();
  }
}

void loop() 
{
  for(int i = 0; i <= 3; i++)
  {
    pins[i].Update();
  }

}
