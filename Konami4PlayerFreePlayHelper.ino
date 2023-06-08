const int MargeIn = 9;
const int HomerIn = 8;
const int BartIn = 7;
const int LisaIn = 6;

const int MargeOut = 10;
const int HomerOut = 11;
const int BartOut = 12;
const int LisaOut = 13;

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
      if(_timer >= 8000)
      {
        _state = StateWaitingForInput;
        _timer = 0;
      }
      break;
    default:
      break;
  }
}

ControlledPin Bart(MargeIn, MargeOut);
ControlledPin Homer(HomerIn, HomerOut);
ControlledPin Marge(BartIn, BartOut);
ControlledPin Lisa(LisaIn, LisaOut);

ControlledPin pins[] = { Bart, Homer, Marge, Lisa };

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
