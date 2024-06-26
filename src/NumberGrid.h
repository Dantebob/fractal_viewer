#ifndef _NUMBER_GRID_H_
#define _NUMBER_GRID_H_
#include <vector>
#include "PPM.h"
#include "ColorTable.h"

class NumberGrid {
public:
    NumberGrid();
    NumberGrid( const int& height, const int& width );
    virtual ~NumberGrid();
    int getHeight( ) const;
    int getWidth( ) const;
    int getMaxNumber( ) const;
    virtual void setGridSize( const int& height, const int& width );
    void setMaxNumber( const int& number );
    const std::vector< int >& getNumbers( ) const;
    int index( const int& row, const int& column ) const;
    bool indexValid( const int& row, const int& column ) const;
    bool numberValid( const int& number ) const;
    int getNumber( const int& row, const int& column ) const;
    void setNumber( const int& row, const int& column, const int& number );
    void setPPM( PPM& ppm ) const;
    void setPPM( PPM& ppm, const ColorTable& colors ) const;
    virtual int calculateNumber(const int& row, const int& column) const = 0;
    virtual void calculateAllNumbers();

protected:
    int mHeight;
    int mWidth;
    int mMax_value;
    std::vector<int> mGrid_values;
};

#endif /* _NUMBER_GRID_H_ */