#ifndef _ACTIONDATA_H_
#define _ACTIONDATA_H_
#include <iostream>
#include <string>
#include <vector>
#include "PPM.h"
#include "NumberGrid.h"
#include "ColorTable.h"

class ActionData {
public:
    ActionData( std::istream& is, std::ostream& os );
    std::istream& getIS();
    std::ostream& getOS();
    PPM& getInputImage1();
    PPM& getInputImage2();
    PPM& getOutputImage();
    bool getDone() const;
    void setDone();
    ~ActionData();
    NumberGrid& getGrid();
    void setGrid(NumberGrid *grid);
    ColorTable& getTable();

protected:
    std::istream& mInput;
    std::ostream& mOutput;
	PPM mIn_image_1;
	PPM mIn_image_2;
	PPM mOut_image;
	bool mDone;
    NumberGrid *mNum_grid;
    ColorTable mColor_table;
};

#endif /*_ACTIONDATA_H_*/
