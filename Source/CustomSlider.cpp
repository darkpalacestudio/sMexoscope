#include "CustomSlider.h"

CustomSlider::CustomSlider(const juce::Image& image) : handleImage(image)
{
    setSliderStyle(juce::Slider::LinearBarVertical);
    setRange(0.0, 1.0, 0.0);
    setTextBoxStyle(juce::Slider::NoTextBox, false, 90, 0);
    setPopupDisplayEnabled(false, false, this);
}

void CustomSlider::paint(juce::Graphics& g)
{
    int offset = 267 - int(getValue() * 267);
    int width = handleImage.getWidth();
    int height = handleImage.getHeight();
    g.drawImage(handleImage, 0, offset, width, height, 0, 0, width, height);
}