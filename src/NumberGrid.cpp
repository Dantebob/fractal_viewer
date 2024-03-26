#include "NumberGrid.h"
#include <vector>
#include <tuple>


NumberGrid::NumberGrid()
    : mHeight(300), mWidth(400), mMax_value(255) {
        // set size of grid and fill grid with 0's
        int size = mHeight * mWidth;
        mGrid_values.resize(size);
        fill(mGrid_values.begin(), mGrid_values.end(), 0);
    }
NumberGrid::NumberGrid( const int& height, const int& width )
    : mHeight(height), mWidth(width), mMax_value(255) {
        // set size of grid and fill grid with 0's
        int size = mHeight * mWidth;
        mGrid_values.resize(size);
        fill(mGrid_values.begin(), mGrid_values.end(), 0);
}
NumberGrid::~NumberGrid(){}
int NumberGrid::getHeight() const {
    return mHeight;
}
int NumberGrid::getWidth() const {
    return mWidth;
}
int NumberGrid::getMaxNumber() const {
    return mMax_value;
}
void NumberGrid::setGridSize( const int& height, const int& width ) {
    if(height >= 2 && width >= 2) {
        mHeight = height;
        mWidth = width;
        int size = mHeight * mWidth;
        mGrid_values.resize(size);
    }
}
void NumberGrid::setMaxNumber( const int& number ) {
    if(number >= 0) {
        mMax_value = number;
    }
}
const std::vector< int >& NumberGrid::getNumbers() const {
    return mGrid_values;
}
int NumberGrid::index( const int& row, const int& column ) const {
    int index = (row * mWidth) + column;
    return index;
}
bool NumberGrid::indexValid( const int& row, const int& column ) const {
    if(row < mHeight && row >= 0 && column < mWidth && column >= 0) {
        return true;
    } else {
        return false;
    }
}
bool NumberGrid::numberValid( const int& number ) const {
    if(number >= 0 && number <= mMax_value) {
        return true;
    } else {
        return false;
    }
}
int NumberGrid::getNumber( const int& row, const int& column ) const {
    if(indexValid(row, column)) {
        return mGrid_values[index(row, column)];
    } else {
        return -1;
    }
}
void NumberGrid::setNumber( const int& row, const int& column, const int& number ) {
    if(indexValid(row, column) && numberValid(number)) {
        mGrid_values[index(row, column)] = number;
    }
}
void NumberGrid::setPPM( PPM& ppm ) const {
    ppm.setHeight(mHeight);
    ppm.setWidth(mWidth);
    ppm.setMaxColorValue(63);
    // set pixel color
    for(int row=0; row < mHeight; row++) {
        for(int column=0; column < mWidth; column++){
            if(this->getNumber(row, column) == 0){
                ppm.setPixel(row, column, 0, 0, 0);
            } else if(this->getNumber(row, column) == mMax_value) {
                ppm.setPixel(row, column, 63, 31, 31);
            } else if((this->getNumber(row, column) % 8) == 0) {
                ppm.setPixel(row, column, 63, 63, 63);
            } else if((this->getNumber(row, column) % 8) == 1) {
                ppm.setPixel(row, column, 63, 31, 31);
            } else if((this->getNumber(row, column) % 8) == 2) {
                ppm.setPixel(row, column, 63, 63, 31);
            } else if((this->getNumber(row, column) % 8) == 3) {
                ppm.setPixel(row, column, 31, 63, 31);
            } else if((this->getNumber(row, column) % 8) == 4) {
                ppm.setPixel(row, column, 0, 0, 0);
            } else if((this->getNumber(row, column) % 8) == 5) {
                ppm.setPixel(row, column, 31, 63, 63);
            } else if((this->getNumber(row, column) % 8) == 6) {
                ppm.setPixel(row, column, 31, 31, 63);
            } else if((this->getNumber(row, column) % 8) == 7) {
                ppm.setPixel(row, column, 63, 31, 63);
            }
        }
    }
}
void NumberGrid::setPPM( PPM& ppm, const ColorTable& colors ) const {
    int colors_size = colors.getNumberOfColors();
    int max_grid_value = this->getMaxNumber();
    if(colors_size >= 2) {
        ppm.setHeight(mHeight);
        ppm.setWidth(mWidth);
        ppm.setMaxColorValue(colors.getMaxChannelValue());
        for(int row=0; row < mHeight; row++) {
            for(int column=0; column < mWidth; column++){
                int i = (row * mWidth) + column;
                int value = mGrid_values[i] % colors_size;    
                if(mGrid_values[i] == max_grid_value) {
                    value = colors_size - 1;
                }
                int ct_red = colors[value].getRed();
                int ct_green = colors[value].getGreen();
                int ct_blue = colors[value].getBlue();
                ppm.setPixel(row, column, ct_red, ct_green, ct_blue);
            }
        }
    }
}
//int NumberGrid::calculateNumber(const int& row, const int& column) const = 0 {}
void NumberGrid::calculateAllNumbers() {
    for(int row=0; row < mHeight; row++) {
        for(int column=0; column < mWidth; column++){
            int number = calculateNumber(row, column);
            setNumber(row, column, number);
        }
    }    
}
