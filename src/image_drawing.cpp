#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include "image_menu.h"
//#include "Image.h"
//#include "PPM.h"
//#include "ActionData.h"

void diagonalQuadPattern( ActionData& action_data ) {
    int max_color_value = 255;
    action_data.getInputImage1().setMaxColorValue(max_color_value);
    int height, width;
    height = getInteger(action_data, "Image height? ");
    width = getInteger(action_data, "Image width? ");
	action_data.getInputImage1().setHeight(height);
	action_data.getInputImage1().setWidth(width);
    //assign image according to assignment rules
    for(int row = 0; row < height; row++) {
        for(int column = 0; column < width; column++) {
            //edit red channels (channel 0)
            if(row < (action_data.getInputImage1().getHeight() / 2)) {
                action_data.getInputImage1().setChannel(row, column, 0, 0);
            } else {
                action_data.getInputImage1().setChannel(row, column, 0, max_color_value);
            }
            //edit green channels (channel 1)
            int green = (2 * row + 2 * column) % (max_color_value + 1);
            action_data.getInputImage1().setChannel(row, column, 1, green);
            //edit blue channels (channel 2)
            if(column < ( width / 2)) {
                action_data.getInputImage1().setChannel(row, column, 2, 0);
            } else {
                action_data.getInputImage1().setChannel(row, column, 2, max_color_value); 
            }
        }
    }
}
void stripedDiagonalPattern( ActionData& action_data ) {
    int max_color_value = 255;
    action_data.getInputImage1().setMaxColorValue(max_color_value);
    int height = getInteger(action_data, "Image height? ");
    int width = getInteger(action_data, "Image width? ");
    action_data.getInputImage1().setHeight(height);
    action_data.getInputImage1().setWidth(width);
    max_color_value = (height + width) / 3;
    if( max_color_value > 255 ) {
        max_color_value = 255;
    }
    action_data.getInputImage1().setMaxColorValue( max_color_value );
    int red, green, blue;
    for(int row = 0; row < action_data.getInputImage1().getHeight(); row++) {
        for(int column = 0; column < action_data.getInputImage1().getWidth(); column++) {
            //edit red channels (channel 0)
            if(row < (action_data.getInputImage1().getHeight() / 2)) {
                red = 0;
            } else if((row >= (action_data.getInputImage1().getHeight() / 2)) && (row % 3 == 0)){
                red = 0;
            } else if(row >= (action_data.getInputImage1().getHeight() / 2)){
                red = action_data.getInputImage1().getMaxColorValue();
            }
            //edit green channels (channel 1)
            green = (row + action_data.getInputImage1().getWidth() - column - 1) % (action_data.getInputImage1().getMaxColorValue() + 1);
            //edit blue channels (channel 2)
            if(column < row) {
				blue = 0;
            } else {
				blue = action_data.getInputImage1().getMaxColorValue();
            }
			action_data.getInputImage1().setPixel(row, column, red, green, blue);
        }
    }
}
void simpleSquaresPattern(ActionData& action_data) {
	int size = getInteger(action_data, "Image size? ");
	action_data.getInputImage1().setHeight(size);
	action_data.getInputImage1().setWidth(size);
    for(int row = 0; row < action_data.getInputImage1().getHeight(); row++) {
        for(int column = 0; column < action_data.getInputImage1().getWidth(); column++) {
            //edit red channels (channel 0)
            if(row < (action_data.getInputImage1().getHeight() / 2)) {
                action_data.getInputImage1().setChannel(row, column, 0, 127);
            } else {
                action_data.getInputImage1().setChannel(row, column, 0, 255);
            }
            //edit green channels (channel 1)
            if(column < (action_data.getInputImage1().getWidth() / 2)) {
                action_data.getInputImage1().setChannel(row, column, 1, 0);
            } else {
                action_data.getInputImage1().setChannel(row, column, 1, 255);
            }
            //edit blue channels (channel 2)
            action_data.getInputImage1().setChannel(row, column, 2, 255);
        }
    }
}
void flagRomaniaPattern(ActionData& action_data) {
	int height = getInteger(action_data, "Image height? ");
	int width = (height * 3) / 2;
	action_data.getInputImage1().setHeight(height);
	action_data.getInputImage1().setWidth(width);
	action_data.getInputImage1().setMaxColorValue(255);
    for(int row = 0; row < action_data.getInputImage1().getHeight(); row++) {
        for(int column = 0; column < action_data.getInputImage1().getWidth(); column++) {
			if(column >= 0) {
				//left then middle then right
				if(column < (action_data.getInputImage1().getWidth() / 3)) {
					action_data.getInputImage1().setPixel(row, column, 0, 43, 127);
				} else if(column < ((action_data.getInputImage1().getWidth() / 3) * 2)) {
					action_data.getInputImage1().setPixel(row, column, 252, 209, 22);
				} else if(column < action_data.getInputImage1().getWidth()) {
					action_data.getInputImage1().setPixel(row, column, 206, 17, 38);
				}
			}
        }
    }
}
void setSize(ActionData& action_data) {
    int height = getInteger(action_data, "Height? ");
    int width = getInteger(action_data, "Width? ");
	action_data.getInputImage1().setHeight(height);
	action_data.getInputImage1().setWidth(width);
}
void setMaxColorValue( ActionData& action_data ) {
    int max_color_value = getInteger(action_data, "Max color value? ");
    action_data.getInputImage1().setMaxColorValue(max_color_value);
}
void setChannel( ActionData& action_data ) {
    int row = getInteger(action_data, "Row? ");
    int column = getInteger(action_data, "Column? ");
    int channel = getInteger(action_data, "Channel? ");
    int value = getInteger(action_data, "Value? ");
    action_data.getInputImage1().setChannel(row, column, channel, value);
}
void setPixel( ActionData& action_data ) {
    int row = getInteger(action_data, "Row? ");
    int column = getInteger(action_data, "Column? ");
    int red = getInteger(action_data, "Red? ");
    int green = getInteger(action_data, "Green? ");
    int blue = getInteger(action_data, "Blue? ");
    action_data.getInputImage1().setPixel(row, column, red, green, blue);
}
void clearAll( ActionData& action_data ) {
    for(int row = 0; row < action_data.getInputImage1().getHeight(); row++) {
        for(int column = 0; column < action_data.getInputImage1().getWidth(); column++) {
            action_data.getInputImage1().setPixel(row, column, 0, 0, 0);
        }
    }
}
void drawCircle(ActionData& action_data) {
    int ctr_row = getInteger(action_data, "Center Row? ");
    int ctr_column = getInteger(action_data, "Center Column? ");
    int radius = getInteger(action_data, "Radius? ");
    int red = getInteger(action_data, "Red? ");
    int green = getInteger(action_data, "Green? ");
    int blue = getInteger(action_data, "Blue? ");
    for(int row = 0; row < action_data.getInputImage1().getHeight(); row++) {
        for(int column = 0; column < action_data.getInputImage1().getWidth(); column++) {
            int row_diff_squared = (ctr_row - row) * (ctr_row - row);
            int column_diff_squared = (ctr_column - column) * (ctr_column - column);
            double distance = std::sqrt(row_diff_squared + column_diff_squared);
            if(distance <= radius) {
                action_data.getInputImage1().setPixel(row, column, red, green, blue);
            }
        }
    } 
}
void drawBox(ActionData& action_data) {
    int t_row = getInteger(action_data, "Top Row? ");
    int l_column = getInteger(action_data, "Left Column? ");
    int b_row = getInteger(action_data, "Bottom Row? ");
    int r_column = getInteger(action_data, "Right Column? ");
    int red = getInteger(action_data, "Red? ");
    int green = getInteger(action_data, "Green? ");
    int blue = getInteger(action_data, "Blue? ");
    for(int row = 0; row < action_data.getInputImage1().getHeight(); row++) {
        for(int column = 0; column < action_data.getInputImage1().getWidth(); column++) {
            if(row >= t_row && row <= b_row){
                if(column >= l_column && column <= r_column) {
                    action_data.getInputImage1().setPixel(row, column, red, green, blue);
                }
            }
        }
    } 
}
void drawTestColorPattern(ActionData& action_data) {
    int height = getInteger(action_data, "Height? ");
    int width = getInteger(action_data, "Width? ");
    int max_color_value = getInteger(action_data, "Max color value? ");
	action_data.getInputImage1().setHeight(height);
	action_data.getInputImage1().setWidth(width);
    action_data.getInputImage1().setMaxColorValue(max_color_value);
    for(int row = 0; row < height; row++) {
        for(int column = 0; column < width; column++) {
            if(row < (height/2) && column < (width/2)){
                // make red
                action_data.getInputImage1().setPixel(row, column, max_color_value, 0, 0);
            } else if(row < (height/2) && column >= (width/2)) {
                // make green
                action_data.getInputImage1().setPixel(row, column, 0, max_color_value, 0);
            } else if (row >= (height/2) && column < (width/2)){
                // make blue
                action_data.getInputImage1().setPixel(row, column, 0, 0, max_color_value);
            } else if (row >= (height/2) && column >= (width/2)){
                // make grey
                action_data.getInputImage1().setPixel(row, column, max_color_value/2, max_color_value/2, max_color_value/2);
            }
        }
    }
}
void drawSquare(ActionData& action_data) {
    int center_row = getInteger(action_data, "Row? ");
    int center_column = getInteger(action_data, "Column? ");
    int size = getInteger(action_data, "Size? ");
    int red = getInteger(action_data, "Red? ");
    int green = getInteger(action_data, "Green? ");
    int blue = getInteger(action_data, "Blue? ");
    int left_side = center_column - (size / 2);
    int right_side = center_column + (size / 2);
    int top_side = center_row - (size / 2);
    int bottom_side = center_row + (size / 2);
    for(int row = 0; row < action_data.getInputImage1().getHeight(); row++) {
        for(int column = 0; column < action_data.getInputImage1().getWidth(); column++) {
            if(row >= top_side && row <= bottom_side){
                if(column >= left_side && column <= right_side){
                    action_data.getInputImage1().setPixel(row, column, red, green, blue);
                }
            }
        }
    } 
}
void configureGrid(ActionData& action_data) {
    int height = getInteger(action_data, "Grid Height? ");
    int width = getInteger(action_data, "Grid Width? ");
    int max_value = getInteger(action_data, "Grid Max Value? ");
    //configure numberGrid object in actiondata
    action_data.getGrid().setGridSize(height, width);
    action_data.getGrid().setMaxNumber(max_value);
}
void setGrid(ActionData& action_data) {
    int row = getInteger(action_data, "Grid Row? ");
    int column = getInteger(action_data, "Grid Column? ");
    int value = getInteger(action_data, "Grid Value? ");
    action_data.getGrid().setNumber(row, column, value);
}
void applyGrid(ActionData& action_data) {
    NumberGrid& grid = action_data.getGrid();
    PPM& output_image = action_data.getOutputImage();
    grid.setPPM(output_image);
}
void setColorTableSize(ActionData& action_data) {
    int size = getInteger(action_data, "Size? ");
    ColorTable& color_table = action_data.getTable();
    color_table.setNumberOfColors(size);
}
void setColor(ActionData& action_data) {
    int position = getInteger(action_data, "Position? ");
    int red = getInteger(action_data, "Red? ");
    int green = getInteger(action_data, "Green? ");
    int blue = getInteger(action_data, "Blue? ");
    ColorTable& color_table = action_data.getTable();
    color_table[position].setRed(red);
    color_table[position].setGreen(green);
    color_table[position].setBlue(blue);
}
void setRandomColor(ActionData& action_data) {
    int position = getInteger(action_data, "Position? ");
    ColorTable& color_table = action_data.getTable();
    color_table.setRandomColor(255, position);
}
void setColorGradient(ActionData& action_data) {
    int position1 = getInteger(action_data, "First position? ");
    int red1 = getInteger(action_data, "First red? ");
    int green1 = getInteger(action_data, "First green? ");
    int blue1 = getInteger(action_data, "First blue? ");
    int position2 = getInteger(action_data, "Second position? ");
    int red2 = getInteger(action_data, "Second red? ");
    int green2 = getInteger(action_data, "Second green? ");
    int blue2 = getInteger(action_data, "Second blue? ");
    Color color1(red1, green1, blue1);
    Color color2(red2, green2, blue2);
    ColorTable& color_table = action_data.getTable();
    color_table.insertGradient(color1, color2, position1, position2);
    // action_data.getTable().insertGradient(color1, color2, position1, position2);
}
void applyGridColorTable(ActionData& action_data) {
    NumberGrid& grid = action_data.getGrid();
    PPM& output_image = action_data.getOutputImage();
    ColorTable& color_table = action_data.getTable();
    grid.setPPM(output_image, color_table);
}
void setFractalPlaneSize(ActionData& action_data) {
    NumberGrid& grid = action_data.getGrid();
    ComplexFractal *cf_grid = dynamic_cast<ComplexFractal*>(&grid);
    //if(grid() is ComplexFractal object) { do setPlaneSize()}
    if(cf_grid != nullptr) {
        double min_x = getDouble(action_data, "Min X? ");
        double max_x = getDouble(action_data, "Max X? ");
        double min_y = getDouble(action_data, "Min Y? ");
        double max_y = getDouble(action_data, "Max Y? ");
        // -> is used with pointers and . is used with objects themselves
        // alternatively (*cf_grid).setPlaneSize(min_x, max_x, min_y, max_y);
        cf_grid->setPlaneSize(min_x, max_x, min_y, max_y);
    } else {
        action_data.getOS() << "Not a ComplexFractal object. Can't set plane size." << std::endl;
    }
}
void calculateFractal(ActionData& action_data) {
    //Calculates all numbers for the grid stored in action_data
    NumberGrid& grid = action_data.getGrid();
    grid.calculateAllNumbers();
}
void setJuliaParameters(ActionData& action_data) {
    NumberGrid& grid = action_data.getGrid();
    JuliaSet *js_grid = dynamic_cast<JuliaSet*>(&grid);
    if(js_grid != nullptr) {
        double a = getDouble(action_data, "Parameter a? ");
        double b = getDouble(action_data, "Parameter b? ");
        js_grid->setParameters(a, b);
    } else {
        action_data.getOS() << "Not a JuliaSet object. Can't set parameters." << std::endl;
    }
}
void setMandelbrotPower(ActionData& action_data) {
    NumberGrid& grid = action_data.getGrid();
    MandelbrotPower *mb_grid = dynamic_cast<MandelbrotPower*>(&grid);
    if(mb_grid != nullptr) {
        double power = getDouble(action_data, "Power? ");
        mb_grid->setPower(power);

    } else {
        action_data.getOS() << "Not a MandelbrotPower object. Can't set power." << std::endl;
    }
}
void zoomPlane(ActionData& action_data) {
    NumberGrid& grid = action_data.getGrid();
    ComplexFractal *cf_grid = dynamic_cast<ComplexFractal*>(&grid);
    if(cf_grid != nullptr) {
        double zoom_factor = getDouble(action_data, "Zoom Factor? ");
        cf_grid->zoomPlane(zoom_factor);
    } else {
        action_data.getOS() << "Not a ComplexFractal object. Can't zoom plane" << std::endl;
    }
}
void setEasyRandomColorGradient(ActionData& action_data) {
    int position1 = getInteger(action_data, "First position? ");
    int position2 = getInteger(action_data, "Second position? ");
    ColorTable& color_table = action_data.getTable();
    color_table.insertEasyRandomGradient(position1, position2);
}
void panPlaneRight(ActionData& action_data) {
    NumberGrid& grid = action_data.getGrid();
    ComplexFractal *cf_grid = dynamic_cast<ComplexFractal*>(&grid);
    if(cf_grid != nullptr) {
        cf_grid->panPlaneRight(0.1);
    } else {
        action_data.getOS() << "Not a ComplexFractal object. Can't pan plane." <<std::endl;
    }
}
void panPlaneLeft(ActionData& action_data) {
    NumberGrid& grid = action_data.getGrid();
    ComplexFractal *cf_grid = dynamic_cast<ComplexFractal*>(&grid);
    if(cf_grid != nullptr) {
        cf_grid->panPlaneLeft(0.1);
    } else {
        action_data.getOS() << "Not a ComplexFractal object. Can't pan plane." <<std::endl;
    }
}
void panPlaneUp(ActionData& action_data) {
    NumberGrid& grid = action_data.getGrid();
    ComplexFractal *cf_grid = dynamic_cast<ComplexFractal*>(&grid);
    if(cf_grid != nullptr) {
        cf_grid->panPlaneUp(0.1);
    } else {
        action_data.getOS() << "Not a ComplexFractal object. Can't pan plane." <<std::endl;
    }
}
void panPlaneDown(ActionData& action_data) {
    NumberGrid& grid = action_data.getGrid();
    ComplexFractal *cf_grid = dynamic_cast<ComplexFractal*>(&grid);
    if(cf_grid != nullptr) {
        cf_grid->panPlaneDown(0.1);
    } else {
        action_data.getOS() << "Not a ComplexFractal object. Can't pan plane." <<std::endl;
    }
}
void calculateFractalSingleThread(ActionData& action_data) {
    NumberGrid& grid = action_data.getGrid();
    grid.NumberGrid::calculateAllNumbers();
}
