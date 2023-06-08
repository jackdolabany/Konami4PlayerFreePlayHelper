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
const unsigned int disableTime = 8000;

// The amount of time in miliseconds the button will register as pressed
const unsigned int outputTime = 8000;

const unsigned long MAX_LONG = 0 - 1;

const int StateWaitingForInput = 1;
const int StateHoldingOutput = 2;
const int StateIgnoringInputs = 3;

class ControlledPin
{
  public: 
    ControlledPin::ControlledPin(int input, int output);
    void Setup();
    void Update(int elapsedTime);
  private:
    int _inputPin;
    int _outputPin;
    int _state;
    unsigned long _timer;
};

ControlledPin::ControlledPin(int input, int output)
{
  _inputPin = input;
  _outputPin = output;
  _state = StateWaitingForInput;
  _timer = 0;
}

void ControlledPin::Setup()
{
  pinMode(_inputPin, INPUT);
  pinMode(_outputPin, OUTPUT);
}

void ControlledPin::Update(int elapsedTime) 
{
  switch (_state) {
    case StateWaitingForInput:
        // Wait for them to press the coin in button.
        int input = digitalRead(_inputPin);
        if(input == HIGH)
        {
          _state = StateHoldingOutput;
          _timer = 0;
        }
      break;
    case StateHoldingOutput:
      // They pressed it! Now hold high on the output in for a short time to simulate a coin going in.
      _timer += elapsedTime;
      if(_timer < 100)
      {
        digitalWrite(_outputPin, HIGH);
      }
      else
      {
        digitalWrite(_outputPin, LOW);
        _state = StateIgnoringInputs;
        _timer = 0;
      }
      break;
    case StateIgnoringInputs:
      // Now just sit in a state for some time and don't register them pressing the button again.
      _timer += elapsedTime;
      if(_timer >= disableTime)
      {
        _state = StateWaitingForInput;
        _timer = 0;
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

unsigned long previousMillis = 0;
unsigned long elapsedTime = 0;

void setup() 
{
  for(int i = 0; i <= 3; i++)
  {
    pins[i].Setup();
  }
}

void loop() 
{
  if (millis() >= previousMillis)
  {
    elapsedTime = millis() - previousMillis;
  }
  else
  {
    // Deal with a weird edge case that the timer might have overflowed.
    // This would only happen after like 2 days of running anyway.
    elapsedTime = MAX_LONG - previousMillis + millis();
  }

  for(int i = 0; i <= 3; i++)
  {
    pins[i].Update(elapsedTime);
  }

  previousMillis = millis();

}
