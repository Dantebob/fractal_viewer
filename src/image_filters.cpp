#include <iostream>
#include "image_menu.h"
#include "ActionData.h"

void plusEquals( ActionData& action_data ) {
    action_data.getInputImage1() += action_data.getInputImage2();
}
void minusEquals( ActionData& action_data ) {
    action_data.getInputImage1() -= action_data.getInputImage2();
}
void timesEquals( ActionData& action_data ) {
    double factor = getDouble(action_data, "Factor? ");
    action_data.getInputImage1() *= factor;
}
void divideEquals( ActionData& action_data ) {
    double factor = getDouble(action_data, "Factor? ");
    action_data.getInputImage1() /= factor;
}
void plus( ActionData& action_data ) {
    action_data.getOutputImage() = action_data.getInputImage1() + action_data.getInputImage2();
}
void minus( ActionData& action_data ) {
    action_data.getOutputImage() = action_data.getInputImage1() - action_data.getInputImage2();
}
void times( ActionData& action_data ) {
    double factor = getDouble(action_data, "Factor? ");
    action_data.getOutputImage() = action_data.getInputImage1() * factor;
}
void divide( ActionData& action_data ) {
    double factor = getDouble(action_data, "Factor? ");
    action_data.getOutputImage() = action_data.getInputImage1() / factor;
}
void grayFromRed(ActionData& action_data) {
    action_data.getInputImage1().grayFromRed(action_data.getOutputImage());
}
void grayFromGreen(ActionData& action_data) {
    action_data.getInputImage1().grayFromGreen(action_data.getOutputImage());
}
void grayFromBlue(ActionData& action_data) {
    action_data.getInputImage1().grayFromBlue(action_data.getOutputImage());
}
void grayFromLinearColorimetric(ActionData& action_data) {
    action_data.getInputImage1().grayFromLinearColorimetric(action_data.getOutputImage());
}
void plusEqualsInt( ActionData& action_data ) {
    int boost = getInteger(action_data, "Boost? ");
    action_data.getInputImage1() += boost;
}
void sepiaFilter(ActionData& action_data) {
    action_data.getInputImage1().sepiaFilter(action_data.getOutputImage());
}
void orangeFilter(ActionData& action_data) {
    action_data.getInputImage1().orangeFilter(action_data.getOutputImage());
}
void antiAliasFilter(ActionData& action_data) {
    int n = getInteger(action_data, "Reduction count? ");
    action_data.getInputImage1().antiAlias(n, action_data.getOutputImage());
}