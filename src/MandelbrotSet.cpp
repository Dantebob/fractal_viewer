#include "MandelbrotSet.h"
#include <cmath>

MandelbrotSet::MandelbrotSet( )
    : ComplexFractal() {
}
MandelbrotSet::MandelbrotSet( const int& height, const int& width, const double& min_x, const double& max_x, const double& min_y, const double& max_y )
    : ComplexFractal(height, width, min_x, max_x, min_y, max_y) {
}
MandelbrotSet::~MandelbrotSet( ) {}
/*void MandelbrotSet::calculateNextPoint( const double x0, const double y0, const double& a, const double& b, double& x1, double &y1 ) const {
    x1 = x0*x0 - y0*y0 + a;
    y1 = 2*x0*y0 + b;
}*/
void MandelbrotSet::calculateNextPoint(const double x0, const double y0, const double& a, const double& b, double& x1, double &y1) const {
    x1 = x0*x0 - y0*y0 + a;
    y1 = 2*x0*y0 + b;
}
int MandelbrotSet::calculatePlaneEscapeCount( const double& a, const double& b ) const {
    double x0 = 0.0;
    double y0 = 0.0;
    double x1, y1;
    this->calculateNextPoint(x0, y0, a, b, x1, y1);
    x0 = x1;
    y0 = y1;
    for(int c = 0; c <= mMax_value; c++) {
        // if x, y outside the of circle circumfrence 2 centered at 0,0
        if(x0*x0 + y0*y0 > 4) {
            return c;
        } else {
            this->calculateNextPoint(x0, y0, a, b, x1, y1);
            x0 = x1;
            y0 = y1;
        }
    }
    return mMax_value;
}
int MandelbrotSet::calculateNumber( const int& row, const int& column ) const {
    if(row < 0 || row >= mHeight || column < 0 || column >= mWidth) {
        return -1;
    }
    double x, y;
    this->calculatePlaneCoordinatesFromPixelCoordinates(row, column, x, y );
    int iterations = calculatePlaneEscapeCount(x, y);
    return iterations;
}
MandelbrotPower::MandelbrotPower()
    : MandelbrotSet(), mPower(2.0) {
}
MandelbrotPower::~MandelbrotPower( ) {}
double MandelbrotPower::getPower() const {
    return mPower;
}
void MandelbrotPower::setPower(const double& power) {
    mPower = power;
}
void MandelbrotPower::calculateNextPoint(const double x0, const double y0, const double& a, const double& b, double& x1, double &y1) const {
    double r = sqrt( x0*x0 + y0*y0 );
    double theta = atan2( y0, x0 );
    x1 = pow(r, mPower) * cos( mPower * theta ) + a;
    y1 = pow(r, mPower) * sin( mPower * theta ) + b;
}
    