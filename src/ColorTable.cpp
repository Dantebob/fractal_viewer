#include <iostream>
#include <cstdlib>
#include "ColorTable.h"

Color::Color()
    : mRed(0), mGreen(0), mBlue(0) {
}
Color::Color( const int& red, const int& green, const int& blue )
    : mRed(red), mGreen(green), mBlue(blue) {
}
int Color::getRed( ) const {
    return mRed;
}
int Color::getGreen( ) const {
    return mGreen;
}
int Color::getBlue( ) const {
    return mBlue;
}
int Color::getChannel( const int& channel ) const {
    // if channel out of range return -1
    if(channel == 0) {
        return mRed;
    } else if(channel == 1) {
        return mGreen;
    } else if(channel == 2) {
        return mBlue;
    } else {
    return -1;
    }
}
void Color::setRed( const int& value ) {
    if(value >= 0) {
        mRed = value;
    }
}
void Color::setGreen( const int& value ) {
    if(value >= 0) {
        mGreen = value;
    }
}
void Color::setBlue( const int& value ) {
    if(value >= 0) {
        mBlue = value;
    }
}
void Color::setChannel( const int& channel, const int& value ) {
    if(value >= 0) {
        if(channel == 0) {
            mRed = value;
        } else if(channel == 1) {
            mGreen = value;
        } else if(channel == 2) {
            mBlue = value;
        }
    }
}
void Color::invert( const int& max_color_value ) {
    if(mRed <= max_color_value && mGreen <= max_color_value && mBlue <= max_color_value) {
        mRed = max_color_value - mRed;
        mGreen = max_color_value - mGreen;
        mBlue = max_color_value - mBlue;
    }
}
bool Color::operator==( const Color& rhs ) const {
    if(this->mRed == rhs.mRed &&
    this->mGreen == rhs.mGreen &&
    this->mBlue == rhs.mBlue) {
        return true;
    } else {
        return false;
    }
}
std::ostream& operator<<( std::ostream& os, const Color& color ) {
    os << color.getRed() << ':' << color.getGreen() << ':' << color.getBlue();
    return os;
}
//########################
ColorTable::ColorTable( const int& size ) {
    mColors.resize(size);
}
int ColorTable::getNumberOfColors( ) const {
    int length = mColors.size();
    return length;
}
void ColorTable::setNumberOfColors( const int& size ) {
    mColors.resize(size);
}
const Color& ColorTable::operator[]( const int& i ) const {
    // make sure user doesn't change static variable
    static Color ec( -1, -1, -1 );
    static Color c( -1, -1, -1 );
    c = ec;
    int length = this->getNumberOfColors();
    if(i < length && i >= 0) {
        return mColors[i];
    } else {
        return c;
    }
}
Color& ColorTable::operator[]( const int& i ) {
    // make sure user doesn't change static variable
    static Color ec( -1, -1, -1 );
    static Color c( -1, -1, -1 );
    c = ec;
    int length = this->getNumberOfColors();
    if(i < length && i >= 0) {
        return mColors[i];
    } else {
        return c;
    }
}
void ColorTable::setRandomColor( const int& max_color_value, const int& position ) {
    int length = this->getNumberOfColors();
    if(position >= 0 && position < length && max_color_value >= 0) {
        int red = std::rand() % (max_color_value + 1);
        int green = std::rand() % (max_color_value + 1);
        int blue = std::rand() % (max_color_value + 1);
        mColors[position].setRed(red);
        mColors[position].setGreen(green);
        mColors[position].setBlue(blue);
    }
}
double ColorTable::gradientSlope(const double y1, const double y2, const double x1, const double x2) const {
    double delta_y = y2 - y1;
    double delta_x = x2 - x1;
    if(delta_x != 0.0) {
        double slope = delta_y/delta_x;
        return slope;
    } else {
        return 0.0;
    }
}
double ColorTable::gradientValue(const double y1, const double x1, const double slope, const double x) const {
    double delta_x = x - x1;
    double y = y1 + (delta_x * slope);
    return y;
}
void ColorTable::insertGradient( const Color& color1, const Color& color2, const int& position1, const int& position2 ) {
    int length = this->getNumberOfColors();
    if(position1 < position2 
    && position1 >= 0 && position1 < length
    && position2 >=0 && position2 < length) {
        int red1 = color1.getRed();
        int green1 = color1.getGreen();
        int blue1 = color1.getBlue();
        int red2 = color2.getRed();
        int green2 = color2.getGreen();
        int blue2 = color2.getBlue();
        double red_slope = gradientSlope(red1, red2, position1, position2);
        double green_slope = gradientSlope(green1, green2, position1, position2);
        double blue_slope = gradientSlope(blue1, blue2, position1, position2);
        for(int p = position1; p <= position2; p++) {
            int red_gvalue = gradientValue(red1, position1, red_slope, p);
            int green_gvalue = gradientValue(green1, position1, green_slope, p);
            int blue_gvalue = gradientValue(blue1, position1, blue_slope, p);
            mColors[p].setRed(red_gvalue);
            mColors[p].setGreen(green_gvalue);
            mColors[p].setBlue(blue_gvalue);
        }
    }
}
int ColorTable::getMaxChannelValue( ) const {
    int biggest = 0;
    int length = this->getNumberOfColors();
    for( int i = 0; i < length; i++) {
        if(mColors[i].getRed() > biggest) {
            biggest = mColors[i].getRed();
        }
        if(mColors[i].getGreen() > biggest) {
            biggest = mColors[i].getGreen();
        }
        if(mColors[i].getBlue() > biggest) {
            biggest = mColors[i].getBlue();
        }
    }
    return biggest;
}
void ColorTable::insertEasyRandomGradient(const int& position1, const int& position2) {
    if(position1 < position2 && position1 >= 0 && position1 < this->getNumberOfColors() 
    && position2 >= 0 && position2 < this->getNumberOfColors()) {
        setRandomColor(255, position1);
        setRandomColor(255, position2);
        insertGradient(mColors[position1], mColors[position2], position1, position2);
    }
}