#ifndef _IMAGE_MENU_H_
#define _IMAGE_MENU_H_

#include <iostream>
#include <string>
#include "Image.h"
#include "PPM.h"
#include "ActionData.h"
#include "MenuData.h"
#include "NumberGrid.h"
#include "image_menu.h"
#include "ComplexFractal.h"
#include "JuliaSet.h"
#include "MandelbrotSet.h"
#include "ThreadedGrid.h"

//user_io.cpp
std::string getString(ActionData& action_data, const std::string& prompt);
int getInteger(ActionData& action_data, const std::string& prompt);
double getDouble(ActionData& action_data, const std::string& prompt);
int askQuestions3(ActionData& action_data);
int askInquisitorQuestions(ActionData& action_data);
std::string getChoice(ActionData& action_data);
void commentLine(ActionData& action_data);
void quit(ActionData& action_data);

//image_drawing.cpp
void diagonalQuadPattern(ActionData& action_data);
void stripedDiagonalPattern(ActionData& action_data);
void simpleSquaresPattern(ActionData& action_data);
void flagRomaniaPattern(ActionData& action_data);
void setSize(ActionData& action_data);
void setMaxColorValue( ActionData& action_data );
void setChannel( ActionData& action_data );
void setPixel( ActionData& action_data );
void clearAll( ActionData& action_data );
void drawCircle(ActionData& action_data);
void drawBox(ActionData& action_data);
void drawTestColorPattern(ActionData& action_data);
void drawSquare(ActionData& action_data);
void configureGrid(ActionData& action_data);
void setGrid(ActionData& action_data);
void applyGrid(ActionData& action_data);
void setColorTableSize(ActionData& action_data);
void setColor(ActionData& action_data);
void setRandomColor(ActionData& action_data);
void setColorGradient(ActionData& action_data);
void applyGridColorTable(ActionData& action_data);
void setFractalPlaneSize(ActionData& action_data);
void calculateFractal(ActionData& action_data);
void setJuliaParameters(ActionData& action_data);
void setMandelbrotPower(ActionData& action_data);
void zoomPlane(ActionData& action_data);
void setEasyRandomColorGradient(ActionData& action_data);
void panPlaneRight(ActionData& action_data);
void panPlaneLeft(ActionData& action_data);
void panPlaneUp(ActionData& action_data);
void panPlaneDown(ActionData& action_data);
void calculateFractalSingleThread(ActionData& action_data);

//image_output.cpp
void drawAsciiImage(ActionData& action_data);
void writeUserImage(ActionData& action_data);
void copyImage(ActionData& action_data);
void readUserImage1( ActionData& action_data );
void readUserImage2( ActionData& action_data );
void copyOutputImageToImage1(ActionData& action_data);

//controllers.cpp
int assignment1(std::istream& is, std::ostream& os);
int assignment2(std::istream& is, std::ostream& os);
int assignment3(std::istream& is, std::ostream& os);
int inquisitor( std::istream& is, std::ostream& os );
int simple_squares_ascii(std::istream& is, std::ostream& os);
int flag_romania( std::istream& is, std::ostream& os );
void showMenu( MenuData& menu_data, ActionData& action_data );
void takeAction(const std::string& choice, MenuData& menu_data, ActionData& action_data);
void configureMenu( MenuData& menu_data );
int imageMenu(std::istream& is, std::ostream& os);
void setComplexFractal( ActionData& action_data );
void setJuliaFractal( ActionData& action_data );
void setMandelbrotFractal( ActionData& action_data );
void setMandelbrotPowerFractal(ActionData& action_data);

//image_filter.cpp
void plusEquals( ActionData& action_data );
void minusEquals( ActionData& action_data );
void timesEquals( ActionData& action_data );
void divideEquals( ActionData& action_data );
void plus( ActionData& action_data );
void minus( ActionData& action_data );
void times( ActionData& action_data );
void divide( ActionData& action_data );
void grayFromRed(ActionData& action_data);
void grayFromGreen(ActionData& action_data);
void grayFromBlue(ActionData& action_data);
void grayFromLinearColorimetric(ActionData& action_data);
void plusEqualsInt( ActionData& action_data );
void sepiaFilter(ActionData& action_data);
void orangeFilter(ActionData& action_data);
void antiAliasFilter(ActionData& action_data);

#endif /*_IMAGE_MENU_H_*/
