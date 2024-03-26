#ifndef _IMAGE_H_
#define _IMAGE_H_
#include <iostream>
#include <string>
#include <vector>

class Image {
public:
    Image(); // default sets height=0, width=0
    Image( const int& height, const int& width );
    int getHeight() const;
    int getWidth() const;
    bool indexValid( const int& row, const int& column, const int& channel ) const;
    int index( const int& row, const int& column, const int& channel ) const;
    int getChannel( const int& row, const int& column, const int& channel ) const;
    void setHeight( const int& height );
    void setWidth( const int& width );
    void setChannel( const int& row, const int& column, const int& channel, const int& value );

//private:
protected:
    std::vector<int> mIndex;
    int mHeight;
    int mWidth;
};

#endif /*_IMAGE_H_*/
