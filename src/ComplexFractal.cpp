#include "ComplexFractal.h"
#include <cmath>

ComplexFractal::ComplexFractal( )
    : ThreadedGrid(201, 301), mMin_x(-1.5), mMax_x(1.5), mMin_y(-1), mMax_y(1), mDelta_x(0.01), mDelta_y(0.01) {

}
ComplexFractal::ComplexFractal( const int& height, const int& width, const double& min_x, const double& max_x, const double& min_y, const double& max_y )
    : ThreadedGrid(height, width), mMin_x(min_x), mMax_x(max_x), mMin_y(min_y), mMax_y(max_y), mDelta_x((max_x - min_x) / (width - 1)), mDelta_y((max_y - min_y) / (height - 1)) {

}
ComplexFractal::~ComplexFractal( ) {}
double ComplexFractal::getMinX( ) const{
    return mMin_x;
}
double ComplexFractal::getMaxX( ) const {
    return mMax_x;
}
double ComplexFractal::getMinY( ) const {
    return mMin_y;
}
double ComplexFractal::getMaxY( ) const {
    return mMax_y;
}
void ComplexFractal::setGridSize( const int& height, const int& width ) {
    if(height >= 2 && width >= 2) {
        NumberGrid::setGridSize(height, width);
        double delta_x = calculateDeltaX();
        double delta_y = calculateDeltaY();
        setDeltas(delta_x, delta_y);
    }
}
void ComplexFractal::setPlaneSize( const double& min_x, const double& max_x, const double& min_y, const double& max_y ) {
    if(min_x != max_x && min_y != max_y 
    && min_x >= -2.0 && min_x <= 2.0 
    && max_x >= -2.0 && max_x <= 2.0 
    && min_y >= -2.0 && min_y <= 2.0
    && max_y >= -2.0 && max_y <= 2.0) { 
        mMin_x = min_x;
        mMax_x = max_x;
        mMin_y = min_y;
        mMax_y = max_y;
        if(min_x > max_x) {
            mMax_x = min_x;
            mMin_x = max_x;
        }
        if(min_y > max_y) {
            mMax_y = min_y;
            mMin_y = max_y;
        }
        double delta_x = calculateDeltaX();
        double delta_y = calculateDeltaY();
        setDeltas(delta_x, delta_y);
    }
}
double ComplexFractal::getDeltaX( ) const {
    return mDelta_x;
}
double ComplexFractal::getDeltaY( ) const {
    return mDelta_y;
}
void ComplexFractal::setDeltas( const double& delta_x, const double& delta_y ) {
    if(delta_x > 0 && delta_y > 0) {
        mDelta_x = delta_x;
        mDelta_y = delta_y;
    }
}
double ComplexFractal::calculateDeltaY( ) const {
    double delta_y = (mMax_y - mMin_y) / (mHeight - 1);
    return delta_y;
}
double ComplexFractal::calculateDeltaX( ) const {
    double delta_x = (mMax_x - mMin_x) / (mWidth - 1);
    return delta_x;
}
double ComplexFractal::calculatePlaneXFromPixelColumn( const int& column ) const {
    if(column < 0 || column >= mWidth) {
        return 0;
    }
    double plane_x_value = mMin_x + (column * mDelta_x);
    return plane_x_value;
}
double ComplexFractal::calculatePlaneYFromPixelRow( const int& row ) const {
    if(row < 0 || row >= mHeight) {
        return 0;
    }
    double plane_y_value = mMax_y - (row * mDelta_y);
    return plane_y_value;
}
void ComplexFractal::calculatePlaneCoordinatesFromPixelCoordinates( const int& row, const int& column, double& x, double& y ) const {
    double plane_x_value, plane_y_value;
    if(row < 0 || row >= mHeight || column < 0 || column >= mWidth) {
        x = 0;
        y = 0;
    } else {
    plane_x_value = calculatePlaneXFromPixelColumn(column);
    plane_y_value = calculatePlaneYFromPixelRow(row);
    x = plane_x_value;
    y = plane_y_value;
    }
}
int ComplexFractal::calculateNumber( const int& row, const int& column ) const {
    if(this->indexValid(row, column)) {
        double x, y;
        //change x and y using calculatePlaneCoordinatesFromPixelCoordinates()
        calculatePlaneCoordinatesFromPixelCoordinates(row, column, x, y);
        int number = std::abs(getMaxNumber() * std::sin(10*x) * std::cos(10*y));
        return number;
    } else {
        return -1;
    }
}
void ComplexFractal::zoomPlane(const double& zoom_factor) {
    double x_length = mMax_x - mMin_x;
    double y_length = mMax_y - mMin_y;
    double x_zoom = x_length * zoom_factor;
    double y_zoom = y_length * zoom_factor;
    double x_change = (x_length - x_zoom) / 2.0;
    double y_change = (y_length - y_zoom) / 2.0;
    double new_min_x = mMin_x + x_change;
    double new_max_x = mMax_x - x_change;
    double new_min_y = mMin_y + y_change;
    double new_max_y = mMax_y - y_change;
    if(new_min_x < -2.0) {
        new_min_x = -2.0;
    }
    if(new_max_x > 2.0) {
        new_max_x = 2.0;
    }
    if(new_min_y < -2.0) {
        new_min_y = -2.0;
    }
    if(new_max_y > 2.0) {
        new_max_y = 2.0;
    }
    setPlaneSize(new_min_x, new_max_x, new_min_y, new_max_y);
}
void ComplexFractal::panPlaneRight(const double& pan_factor) {
    double x_size = mMax_x - mMin_x;
    double pan_size = x_size * pan_factor;
    double new_min_x = mMin_x + pan_size;
    double new_max_x = mMax_x + pan_size;
    if(new_min_x <= 2.0 && new_max_x <= 2.0) {
        setPlaneSize(new_min_x, new_max_x, mMin_y, mMax_y);
    }
}
void ComplexFractal::panPlaneLeft(const double& pan_factor) {
    double x_size = mMax_x - mMin_x;
    double pan_size = x_size * pan_factor;
    double new_min_x = mMin_x - pan_size;
    double new_max_x = mMax_x - pan_size;
    if(new_min_x >= -2.0 && new_max_x >= -2.0) {
        setPlaneSize(new_min_x, new_max_x, mMin_y, mMax_y);
    }
}
void ComplexFractal::panPlaneUp(const double& pan_factor) {
    double y_size = mMax_y - mMin_y;
    double pan_size = y_size * pan_factor;
    double new_min_y = mMin_y + pan_size;
    double new_max_y = mMax_y + pan_size;
    if(new_min_y <= 2.0 && new_max_y <= 2.0) {
        setPlaneSize(mMin_x, mMax_x, new_min_y, new_max_y);
    }
}
void ComplexFractal::panPlaneDown(const double& pan_factor) {
    double y_size = mMax_y - mMin_y;
    double pan_size = y_size * pan_factor;
    double new_min_y = mMin_y - pan_size;
    double new_max_y = mMax_y - pan_size;
    if(new_min_y >= -2.0 && new_max_y >= -2.0) {
        setPlaneSize(mMin_x, mMax_x, new_min_y, new_max_y);
    }
}