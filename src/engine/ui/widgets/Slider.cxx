#include "Slider.hxx"

Slider::Slider(const SDL_Rect &uiElementRect) : UIElement(uiElementRect)
{
  // testing width is 200, pos_x is 400, y is 520, height is 40
  sliderLine = uiElementRect;
  sliderLine.x = uiElementRect.h / 2 - m_lineThickness / 2;
  sliderLine.h = m_lineThickness;

  sliderButton = uiElementRect;
  sliderButton.w = 20;
  sliderButton.h = 40;
  sliderButton.y = uiElementRect.y - uiElementRect.h / 2 + m_lineThickness / 2;
  sliderButton.x = uiElementRect.w / 2 - sliderButton.w / 2;
};

void Slider::draw()
{
  drawFrame(sliderLine);
  drawButtonFrame(sliderButton);
}

void Slider::setValue(int val)
{
  int range = m_maxVal - m_minVal;
  // calculate position to set
  // translate that to position on the slider (For the button)
  curVal = val;
}

int Slider::getValue(int x)
{
  // based on where the button is on the line, find the corresponding value
  int range = m_maxVal - m_minVal;
  double ratio = (x - sliderLine.x) / (double) sliderLine.w;
  int val = ratio * range + m_minVal;
  return val;
}

bool Slider::overSliderButton(int x, int y)
{
  return x > sliderButton.x && x < (sliderButton.x + sliderButton.w) && y > sliderButton.y &&
         y < (sliderButton.y + sliderButton.h);
}

bool Slider::overSliderLine(int x, int y)
{
  return x > sliderLine.x && x < (sliderLine.x + sliderLine.w) && y > sliderLine.y && y < (sliderLine.y + sliderLine.h);
}

bool Slider::onMouseButtonDown(const SDL_Event &event)
{
  if (overSliderLine(event.button.x, event.button.y))
  {
    sliderButton.x = event.button.x - sliderButton.w / 2; // sets the middle of the button to where the user clicked
    curVal = getValue(event.button.x);
    return true;
  }
  if (overSliderButton(event.button.x, event.button.y))
  {
    return true;
  }
  return false;
}

bool Slider::onMouseButtonUp(const SDL_Event &event) { return false; }
