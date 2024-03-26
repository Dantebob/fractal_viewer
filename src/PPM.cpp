#include <iostream>
#include <fstream>  //std::ofstream, std::ifstream, (FileStreams)
#include <ios>      //std::ios::binary
#include <vector>
#include <string>
#include "PPM.h"

PPM::PPM()
    : Image(), mMaxValue(1) {
        int size = mHeight * mWidth * 3;
        mIndex.resize(size);
}
PPM::PPM( const int& height, const int& width )
    : Image( height, width ), mMaxValue(1) {
        int size = mHeight * mWidth * 3;
        mIndex.resize(size);
}
PPM::PPM( const int& height, const int& width, const int& max_color_value )
    : Image( height, width ), mMaxValue(max_color_value) {
        int size = mHeight * mWidth * 3;
        mIndex.resize(size);
}
int PPM::getMaxColorValue() const {
    return mMaxValue;
}
bool PPM::valueValid( const int& value ) const {
    if((value >= 0) and (value <= mMaxValue)) {
        return true;
    } else {
        return false;
    }
}

void PPM::setMaxColorValue( const int& max_color_value ) {
    if(max_color_value >= 1 && max_color_value <= 255) {
        mMaxValue = max_color_value;
    }
}
void PPM::setChannel( const int& row, const int& column, const int& channel, const int& value ) {
    if(valueValid(value)) {
        Image::setChannel(row, column, channel, value);
    }
}
void PPM::setPixel( const int& row, const int& column, const int& red, const int& green, const int& blue ) {
    setChannel(row, column, 0, red);
    setChannel(row, column, 1, green);
    setChannel(row, column, 2, blue);
}
void PPM::writeStream(std::ostream& os) const {
    os << "P6" << " " << mWidth << " " << mHeight << " " << mMaxValue << "\n";
    for(int row = 0; row < mHeight; row++) {
		for(int column = 0; column < mWidth; column++) {
			unsigned char red = getChannel(row, column, 0);
			unsigned char green = getChannel(row, column, 1);
			unsigned char blue = getChannel(row, column, 2);
			// sizeof(red) = 1 byte
			// an unsigned char doesn't include negative numbers and is 1 byte
            os.write((char *) &red, 1);
            os.write((char *) &green, 1);
            os.write((char *) &blue, 1);
        }
    }
}

void PPM::readStream(std::istream& is) {
	std::string trash;
	int width, height, max_value;
	is >> trash;
	is >> width;
	is >> height;
	is >> max_value;
	setWidth(width);
	setHeight(height);
	setMaxColorValue(max_value);
    //remove newline character
	char v[1] = {};
	is.read(v, 1);
    //read binary data
    for(int row = 0; row < mHeight; row++) {
		for(int column = 0; column < mWidth; column++) {
			unsigned char red, green, blue;
			// sizeof(red) = 1 byte
			// an unsigned char doesn't include negative numbers and is 1 byte
            is.read((char *) &red, 1);
            is.read((char *) &green, 1);
            is.read((char *) &blue, 1);
            setChannel(row, column, 0, red);
            setChannel(row, column, 1, green);
            setChannel(row, column, 2, blue);
        }
    }
}
bool PPM::operator==( const PPM& rhs ) const {
    return this->mHeight == rhs.mHeight && this->mWidth == rhs.mWidth;
}
bool PPM::operator!=( const PPM& rhs ) const {
    return this->mHeight != rhs.mHeight || this->mWidth != rhs.mWidth;
}
bool PPM::operator<( const PPM& rhs ) const {
    return this->mHeight < rhs.mHeight && this->mWidth < rhs.mWidth;
}
bool PPM::operator<=( const PPM& rhs ) const {
    return this->mHeight <= rhs.mHeight && this->mWidth <= rhs.mWidth;
}
bool PPM::operator>( const PPM& rhs ) const {
    return this->mHeight > rhs.mHeight && this->mWidth > rhs.mWidth;
}
bool PPM::operator>=( const PPM& rhs ) const {
    return this->mHeight >= rhs.mHeight && this->mWidth >= rhs.mWidth;
    //return (this->mHeight * this->mWidth) >= (rhs.mHeight * rhs.mWidth);
}
PPM& PPM::operator+=( const PPM& rhs ) {
    for(int row = 0; row < this->mHeight; row++) {
        for(int column = 0; column < this->mWidth; column++) {
            for(int channel = 0; channel <= 2; channel++) {
                int value = this->getChannel(row, column, channel);
                int value2 = rhs.getChannel(row, column, channel);
                value += value2;
                if(value >= this->getMaxColorValue()) {
                    setChannel(row, column, channel, this->getMaxColorValue());
                } else {
                    setChannel(row, column, channel, value);
                }
            }
        }
    }
    return *this;
}
PPM& PPM::operator-=( const PPM& rhs ) {
    for(int row = 0; row < this->mHeight; row++) {
        for(int column = 0; column < this->mWidth; column++) {
            for(int channel = 0; channel <= 2; channel++) {
                int value = this->getChannel(row, column, channel);
                int value2 = rhs.getChannel(row, column, channel);
                value -= value2;
                if(value <= 0) {
                    setChannel(row, column, channel, 0);
                } else {
                    setChannel(row, column, channel, value);
                }
            }
        }
    }
    return *this;
}
PPM& PPM::operator*=( const double& rhs ) {
    for(int row = 0; row < this->mHeight; row++) {
        for(int column = 0; column < this->mWidth; column++) {
            for(int channel = 0; channel <= 2; channel++) {
                int value = this->getChannel(row, column, channel);
                value *= rhs;
                if(value >= this->getMaxColorValue()) {
                    setChannel(row, column, channel, this->getMaxColorValue());
                } else if(value <= 0) {
                    setChannel(row, column, channel, 0);
                } else {
                    setChannel(row, column, channel, value);
                }
            }
        }
    }
    return *this;
}
PPM& PPM::operator/=( const double& rhs ) {
    for(int row = 0; row < this->mHeight; row++) {
        for(int column = 0; column < this->mWidth; column++) {
            for(int channel = 0; channel <= 2; channel++) {
                int value = this->getChannel(row, column, channel);
                value /= rhs;
                if(value >= this->getMaxColorValue()) {
                    setChannel(row, column, channel, this->getMaxColorValue());
                } else if(value <= 0) {
                    setChannel(row, column, channel, 0);
                } else {
                    setChannel(row, column, channel, value);
                }
            }
        }
    }
    return *this;
}
PPM PPM::operator+( const PPM& rhs ) const {
    PPM result(this->mHeight, this->mWidth, this->mMaxValue);
    //add this to result object
    result += *this;
    result += rhs;
    return result;
}
PPM PPM::operator-( const PPM& rhs ) const {
    PPM result(this->mHeight, this->mWidth, this->mMaxValue);
    //add this to result object
    result += *this;
    result -= rhs;
    return result;
}
PPM PPM::operator*( const double& rhs ) const {
    PPM result(this->mHeight, this->mWidth, this->mMaxValue);
    result += *this;
    result *= rhs;
    return result;
}
PPM PPM::operator/( const double& rhs ) const {
    PPM result(this->mHeight, this->mWidth, this->mMaxValue);
    result += *this;
    result /= rhs;
    return result;
}
void PPM::grayFromChannel( PPM& dst, const int& src_channel ) const {
    dst.setHeight(this->mHeight);
    dst.setWidth(this->mWidth);
    dst.setMaxColorValue(this->mMaxValue);
    for(int row = 0; row < this->mHeight; row++) {
        for(int column = 0; column < this->mWidth; column++) {
            int red = this->getChannel(row, column, 0);
            int green = this->getChannel(row, column, 1);
            int blue = this->getChannel(row, column, 2);
            if(src_channel == 0) {
                dst.setPixel(row, column, red, red, red);
            } else if(src_channel == 1) {
                dst.setPixel(row, column, green, green, green);
            } else if(src_channel == 2) {
                dst.setPixel(row, column, blue, blue, blue);
            }
        }
    }
}
void PPM::grayFromRed( PPM& dst ) const {
    grayFromChannel(dst, 0);
}
void PPM::grayFromGreen( PPM& dst ) const {
    grayFromChannel(dst, 1);
}
void PPM::grayFromBlue( PPM& dst ) const {
    grayFromChannel(dst, 2);
}
double PPM::linearColorimetricPixelValue( const int& row, const int& column ) const {
     int red = this->getChannel(row, column, 0);
     int green = this->getChannel(row, column, 1);
     int blue = this->getChannel(row, column, 2);
     double brightness = 0.2126*red + 0.7152*green + 0.0722*blue;
     return brightness;
}
void PPM::grayFromLinearColorimetric( PPM& dst ) const {
    dst.setHeight(this->mHeight);
    dst.setWidth(this->mWidth);
    dst.setMaxColorValue(this->mMaxValue);
    for(int row = 0; row < this->mHeight; row++) {
        for(int column = 0; column < this->mWidth; column++) {
            double value = linearColorimetricPixelValue(row, column);
            dst.setChannel(row, column, 0, value);
            dst.setChannel(row, column, 1, value);
            dst.setChannel(row, column, 2, value);
        }
    }
}
PPM& PPM::operator+=( const int& rhs ) {
    for(int row = 0; row < this->mHeight; row++) {
        for(int column = 0; column < this->mWidth; column++) {
            for(int channel = 0; channel <= 2; channel++) {
                int value = this->getChannel(row, column, channel);
                value += rhs;
                if(value >= this->getMaxColorValue()) {
                    this->setChannel(row, column, channel, this->getMaxColorValue());
                } else if( value < 0) {
                    this->setChannel(row, column, channel, 0);
                } else {
                    this->setChannel(row, column, channel, value);
                }
            }
        }
    }
    return *this;
}
void PPM::sepiaFilter( PPM& dst ) const {
    dst.setHeight(this->mHeight);
    dst.setWidth(this->mWidth);
    dst.setMaxColorValue(this->mMaxValue);
    int max_color = dst.getMaxColorValue();
    for(int row = 0; row < this->mHeight; row++) {
        for(int column = 0; column < this->mWidth; column++) {
            int red = this->getChannel(row, column, 0);
            int green = this->getChannel(row, column, 1);
            int blue = this->getChannel(row, column, 2);
            int new_red = 0.393*red + 0.769*green + 0.189*blue;
            int new_green = 0.349*red + 0.686*green + 0.168*blue;
            int new_blue = 0.272*red + 0.534*green + 0.131*blue;
            if(new_red > max_color) {
                new_red = max_color;
            }
            if(new_green > max_color) {
                new_green = max_color;
            }
            if(new_blue > max_color) {
                new_blue = max_color;
            }
            dst.setChannel(row, column, 0, new_red);
            dst.setChannel(row, column, 1, new_green);
            dst.setChannel(row, column, 2, new_blue);
        }
    }   
}
void PPM::orangeFilter(PPM& dst) const {
    dst.setHeight(this->mHeight);
    dst.setWidth(this->mWidth);
    dst.setMaxColorValue(this->mMaxValue);
    int max_color = dst.getMaxColorValue();
    for(int row = 0; row < this->mHeight; row++) {
        for(int column = 0; column < this->mWidth; column++) {
            int red = this->getChannel(row, column, 0);
            int green = this->getChannel(row, column, 1);
            int blue = this->getChannel(row, column, 2);
            int new_red = 2 * (2 * red + green) / 3;
            int new_green = 2 * (2 * red + green) / 6;
            int new_blue = blue / 2;
            if(new_red > max_color) {
                new_red = max_color;
            }
            if(new_green > max_color) {
                new_green = max_color;
            }
            if(new_blue > max_color) {
                new_blue = max_color;
            }
            dst.setChannel(row, column, 0, new_red);
            dst.setChannel(row, column, 1, new_green);
            dst.setChannel(row, column, 2, new_blue);
        }
    }
}
int PPM::antiAliasPixelValue(int n, int row, int column, int channel) const {
    int sum = 0;
    int f_row, f_column;
    for(f_row = row * n; f_row < ((row + 1) * n); f_row ++) {
        for(f_column = column * n; f_column < ((column + 1) * n); f_column ++) {
            sum += this->getChannel(f_row, f_column, channel);
        }
    }
    int avg = sum / (n * n);
    return avg;
}
void PPM::antiAlias(const int& n, PPM& dst) const {
    dst.setHeight(mHeight/n);
    dst.setWidth(mWidth/n);
    dst.setMaxColorValue(this->getMaxColorValue());
    //iterate through smaller dst ppm
    for(int row = 0; row < dst.getHeight(); row++) {
        for(int column = 0; column < dst.getWidth(); column++) {
            for(int channel = 0; channel < 3; channel ++) {
                int value = antiAliasPixelValue(n, row, column, channel);
                dst.setChannel(row, column, channel, value);
            }
        }
    }
            
}
