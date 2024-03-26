#include "JuliaSet.h"

JuliaSet::JuliaSet( )
    : ComplexFractal(), mA(-0.650492), mB(-0.478235) {
    this->setMaxNumber(255);
}

JuliaSet::JuliaSet( const int& height, const int& width, const double& min_x, const double& max_x, const double& min_y, const double& max_y, const double& a, const double& b )
    : ComplexFractal(height, width, min_x, max_x, min_y, max_y), mA(a), mB(b) {
}
JuliaSet::~JuliaSet( ) {}
double JuliaSet::getA( ) const {
    return mA;
}
double JuliaSet::getB( ) const {
    return mB;
}
void JuliaSet::setParameters( const double& a, const double& b ) {
    if( a >= -2.0 && a <= 2.0 && b >= -2.0 && b <= 2.0) {
        mA = a;
        mB = b;
    }
}
void JuliaSet::calculateNextPoint( const double x0, const double y0, double& x1, double &y1 ) const {
    x1 = x0*x0 - y0*y0 + mA;
    y1 = 2*x0*y0 + mB;
}
int JuliaSet::calculatePlaneEscapeCount( const double& x0, const double& y0 ) const {
    double x1 = x0;
    double y1 = y0; 
    double x2, y2;
    for(int c = 0; c <= mMax_value; c++) {
        // if x, y outside the of circle circumfrence 2 centered at 0,0
        if(x1*x1 + y1*y1 > 4) {
            return c;
        } else {
            this->calculateNextPoint(x1, y1, x2, y2);
            x1 = x2;
            y1 = y2;
        }
    }
    return mMax_value;
}
int JuliaSet::calculateNumber( const int& row, const int& column ) const {
    if(row < 0 || row >= mHeight || column < 0 || column >= mWidth) {
        return -1;
    }
    double x, y;
    this->calculatePlaneCoordinatesFromPixelCoordinates(row, column, x, y );
    int iterations = calculatePlaneEscapeCount(x, y);
    return iterations;
}
