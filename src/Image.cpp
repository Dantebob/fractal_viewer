#include <iostream>
#include <string>
#include <vector>
#include "Image.h"


Image::Image()
    : mHeight(0), mWidth(0) {
        int size = mHeight * mWidth * 3;
        mIndex.resize(size);
}
Image::Image( const int& height, const int& width )
    : mHeight( height ), mWidth( width ) {
        int size = mHeight * mWidth * 3;
        mIndex.resize(size);
}

int Image::getHeight() const {
    return mHeight;
}
int Image::getWidth() const {
    return mWidth;
}
int Image::index( const int& row, const int& column, const int& channel ) const {
    int width, index;
    width = getWidth();
    index = row * width * 3 + column * 3 + channel;
    return index;
}
bool Image::indexValid( const int& row, const int& column, const int& channel ) const{
    if(row >= 0 && row < mHeight) {
        if(column >= 0 && column < mWidth) {
            if(channel == 0 || channel == 1 || channel == 2) {
                return true;
            }
        }
    }
    return false;
}
int Image::getChannel( const int& row, const int& column, const int& channel ) const {
    bool valid;
    int index;
    valid = indexValid(row, column, channel);
    index = Image::index(row, column, channel);
    if(valid) {
        return mIndex[index];
    } else {
        return -1;
    }
}
void Image::setHeight( const int& height ) {
    int size;
    if(height >= 0) {
        mHeight = height;
        size = mHeight * mWidth * 3;
        mIndex.resize(size);
    }
}
void Image::setWidth( const int& width ) {
    int size;
    if(width >= 0) {
        mWidth = width;
        size = mHeight * mWidth * 3;
        mIndex.resize(size);
    }
}
void Image::setChannel( const int& row, const int& column, const int& channel, const int& value ) {
    bool valid;
    int index;
    valid = indexValid(row, column, channel);
    index = Image::index(row, column, channel);
    if(valid) {
        mIndex[index] = value;
    }
}

