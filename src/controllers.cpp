#include <iostream>
#include <vector>
#include "image_menu.h"
#include "ActionData.h"
#include "MenuData.h"
#include <algorithm>

int assignment1( std::istream& is, std::ostream& os ) {
    ActionData action_data(is, os);
    int result;
    result = askQuestions3(action_data);
    return result;
}
int assignment2( std::istream& is, std::ostream& os ) {
    ActionData action_data(is, os);
    //Create an Image object.
    Image image;
    diagonalQuadPattern(action_data);
    copyImage(action_data);
    drawAsciiImage(action_data);
    return 0;
}
int assignment3( std::istream& is, std::ostream& os ) {
    ActionData action_data(is, os);
    PPM ppm;
    stripedDiagonalPattern( action_data );
    copyImage(action_data);
    writeUserImage( action_data );
    return 0;
}
int inquisitor( std::istream& is, std::ostream& os ) {
    ActionData action_data(is, os);
	int value = askInquisitorQuestions( action_data );
	return value;
}
int simple_squares_ascii( std::istream& is, std::ostream& os ) {
    ActionData action_data(is, os);
	Image image;
	simpleSquaresPattern(action_data);
    copyImage(action_data);
    drawAsciiImage(action_data);
	return 0;
}
int flag_romania( std::istream& is, std::ostream& os ) {
    ActionData action_data(is, os);
	PPM romania_flag;
	flagRomaniaPattern( action_data );
    copyImage(action_data);
	writeUserImage( action_data );
	return 0;
}

void showMenu( MenuData& menu_data, ActionData& action_data ) {
    std::vector<std::string> cmd_names;
    cmd_names = menu_data.getNames();
    //for(size_t i = 0; i < cmd_names.size(); i++){}
    for(const std::string& name : cmd_names) {
        action_data.getOS() << name << ") " << menu_data.getDescription(name) << std::endl;
    }
}
std::string toLowerCase(const std::string& str) {
    std::string lowerStr = str;
    std::transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);
    return lowerStr;
}
void takeAction(const std::string& choice_a, MenuData& menu_data, ActionData& action_data) {
    std::string choice = toLowerCase(choice_a);
    ActionFunctionType func = menu_data.getFunction(choice);
    if(choice == "menu") {
        showMenu(menu_data, action_data);
    } else if (func != 0) {
        func(action_data);
    } else {
        action_data.getOS() << "Unknown action '" << choice << "'." << std::endl;
    }
}
void configureMenu( MenuData& menu_data ) {
    menu_data.addAction("draw-ascii", drawAsciiImage, "Write output image to terminal as ASCII art.");
    menu_data.addAction("write", writeUserImage, "Write output image to file.");
    menu_data.addAction("copy", copyImage, "Copy input image 1 to output image.");
    menu_data.addAction("read1", readUserImage1, "Read file into input image 1.");
    menu_data.addAction("#", commentLine, "Comment to end of line.");
    menu_data.addAction("size", setSize, "Set the size of input image 1.");
    menu_data.addAction("max-color-value", setMaxColorValue, "Set the max color value of input image 1.");
    menu_data.addAction("channel", setChannel, "Set a channel value in input image 1.");
    menu_data.addAction("pixel", setPixel, "Set a pixel's 3 values in input image 1.");
    menu_data.addAction("clear", clearAll, "Set all pixels to 0,0,0 in input image 1.");
    menu_data.addAction("quit", quit, "Quit.");
    menu_data.addAction("read2", readUserImage2, "Read file into input image 2.");
    menu_data.addAction("+", plus, "Set output image from sum of input image 1 and input image 2.");
    menu_data.addAction("+=", plusEquals, "Set input image 1 by adding in input image 2.");
    menu_data.addAction("-", minus, "Set output image from difference of input image 1 and input image 2.");
    menu_data.addAction("-=", minusEquals, "Set input image 1 by subtracting input image 2.");
    menu_data.addAction("*", times, "Set output image from input image 1 multiplied by a number.");
    menu_data.addAction("*=", timesEquals, "Set input image 1 by multiplying by a number.");
    menu_data.addAction("/", divide, "Set output image from input image 1 divided by a number.");
    menu_data.addAction("/=", divideEquals, "Set input image 1 by dividing by a number.");
    menu_data.addAction("red-gray", grayFromRed, "Set output image by grayscale from red on input image 1.");
    menu_data.addAction("green-gray", grayFromGreen, "Set output image by grayscale from green on input image 1.");
    menu_data.addAction("blue-gray", grayFromBlue, "Set output image by grayscale from blue on input image 1.");
    menu_data.addAction("linear-gray", grayFromLinearColorimetric, "Set output image by linear colorimetric grayscale on input image 1.");
    menu_data.addAction("circle", drawCircle, "Draw a circle shape in input image 1.");
    menu_data.addAction("box", drawBox, "Draw a box shape in input image 1.");
    menu_data.addAction("test-pattern", drawTestColorPattern, "Draw a test pattern in input image 1.");
    menu_data.addAction("diagonal-quad", diagonalQuadPattern, "Draw a diagonal quad pattern in input image 1.");
    menu_data.addAction("striped-diagonal", stripedDiagonalPattern, "Draw a striped diagonal pattern in input image 1.");
    menu_data.addAction("+=-int", plusEqualsInt, "Set input image 1 by adding by an integer.");
    menu_data.addAction("sepia", sepiaFilter, "Set output image from sepia filter on input image 1.");
    menu_data.addAction("square", drawSquare, "Draw a square shape in input image 1.");
    menu_data.addAction("orange", orangeFilter, "Set output image from orange filter on input image 1.");
    menu_data.addAction("grid", configureGrid, "Configure the grid.");
    menu_data.addAction("grid-set", setGrid, "Set a single value in the grid.");
    menu_data.addAction("grid-apply", applyGrid, "Use the grid values to set colors in the output image.");
    menu_data.addAction("set-color-table-size", setColorTableSize, "Change the number of slots in the color table.");
    menu_data.addAction("set-color", setColor, "Set the RGB values for one slot in the color table.");
    menu_data.addAction("set-random-color", setRandomColor, "Randomly set the RGB values for one slot in the color table.");
    menu_data.addAction("set-color-gradient", setColorGradient, "Smoothly set the RGB values for a range of slots in the color table.");
    menu_data.addAction("grid-apply-color-table", applyGridColorTable, "Use the grid values to set colors in the output image using the color table.");
    menu_data.addAction("fractal-plane-size", setFractalPlaneSize, "Set the dimensions of the grid in the complex plane.");
    menu_data.addAction("julia-parameters", setJuliaParameters, "Set the parameters of the Julia Set function.");
    menu_data.addAction("complex-fractal", setComplexFractal, "Choose to make a complex plane.");
    menu_data.addAction("julia", setJuliaFractal, "Choose to make a Julia set.");
    menu_data.addAction("mandelbrot", setMandelbrotFractal, "Choose to make a Mandelbrot set.");
    menu_data.addAction("mandelbrot-power", setMandelbrotPowerFractal, "Choose to make a Mandelbrot set with the power function.");
    menu_data.addAction("set-mandelbrot-power", setMandelbrotPower, "Choose a power for the Mandelbrot power function.");
    menu_data.addAction("fractal-zoom", zoomPlane, "Zoom in or out of the complex plane.");
    menu_data.addAction("set-easy-random-color-gradient", setEasyRandomColorGradient, "Smoothly set the values for a range of slots in the color table, using two random colors.");
    menu_data.addAction("fractal-right", panPlaneRight, "Pan complex plane right.");
    menu_data.addAction("fractal-left", panPlaneLeft, "Pan complex plane left.");
    menu_data.addAction("fractal-up", panPlaneUp, "Pan complex plane up.");
    menu_data.addAction("fractal-down", panPlaneDown, "Pan complex plane down.");
    menu_data.addAction("fractal-calculate", calculateFractal, "Calculate the escape values for the fractal.");
    menu_data.addAction("fractal-calculate-single-thread", calculateFractalSingleThread, "Calculate the escape values for the fractal, single-thread.");
    menu_data.addAction("anti-alias", antiAliasFilter, "Set output image from Anti-alias filter on input image 1.");
    menu_data.addAction("copyo1", copyOutputImageToImage1, "Copy output image to input image 1.");
}

int imageMenu(std::istream& is, std::ostream& os) {
    ActionData action_data( is, os );
    /*Memory Allocation: In C++, objects need memory to store their data members and perform their functions.
    When you create an object using new ComplexFractal, it allocates the necessary memory for a 
    ComplexFractal object on the heap.*/
    /*Pointer to Access Object: The new operator returns a pointer to the dynamically allocated object. 
    To work with this object, you need to capture that memory address by assigning it to a pointer. 
    That's why you initialize new_complex_fractal with new ComplexFractal.*/
    ComplexFractal *new_complex_fractal = new ComplexFractal;
    action_data.setGrid(new_complex_fractal);
    MenuData menu_data;
    configureMenu( menu_data );
    //run while done is false and input stream is good.
    while(!action_data.getDone() && action_data.getIS().good()) {
        std::string choice = getChoice(action_data);
        takeAction(choice, menu_data, action_data);
    }
    /*Remember that in modern C++, it's often recommended to use 
    smart pointers like std::shared_ptr or std::unique_ptr 
    to manage dynamic memory more safely and automatically.*/
    return 0;
}
void setComplexFractal( ActionData& action_data ) {
    ComplexFractal *new_complex_fractal = new ComplexFractal;
    action_data.setGrid(new_complex_fractal);
}
void setJuliaFractal( ActionData& action_data ) {
    JuliaSet *new_julia_set = new JuliaSet;
    action_data.setGrid(new_julia_set);
}
void setMandelbrotFractal( ActionData& action_data ) {
    MandelbrotSet *new_mandelbrot_set = new MandelbrotSet;
    action_data.setGrid(new_mandelbrot_set);
}
void setMandelbrotPowerFractal(ActionData& action_data) {
    MandelbrotPower *new_mandelbrot_power = new MandelbrotPower;
    action_data.setGrid(new_mandelbrot_power);
}