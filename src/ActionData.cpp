#include <iostream>
#include "ActionData.h"
#include "PPM.h"

ActionData::ActionData(std::istream& is, std::ostream& os)
    : mInput(is), mOutput(os), mDone(false), mNum_grid(0), mColor_table(16) {
    Color color1(0, 255, 0);
    Color color2(255, 0, 255);
    mColor_table.insertGradient(color1, color2, 0, 15);
}
std::istream& ActionData::getIS() {
    return mInput;
}
std::ostream& ActionData::getOS() {
    return mOutput;
}
PPM& ActionData::getInputImage1() {
    return mIn_image_1;
}
PPM& ActionData::getInputImage2() {
    return mIn_image_2;
}
PPM& ActionData::getOutputImage() {
    return mOut_image;
}
bool ActionData::getDone() const {
    return mDone;
}
void ActionData::setDone() {
    mDone = true;
}
ActionData::~ActionData() {
    if(mNum_grid != 0) {
        delete mNum_grid;
    }
}
NumberGrid& ActionData::getGrid() {
    return *(this->mNum_grid);
}
void ActionData::setGrid(NumberGrid *grid) {
    if(mNum_grid != 0) {
        delete mNum_grid;
    }
    mNum_grid = grid;
}
ColorTable& ActionData::getTable() {
    return (this->mColor_table);
}