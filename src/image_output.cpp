#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <fstream>  //std::ofstream, std::ifstream, (FileStreams)
#include <ios>      //std::ios::binary
#include "image_menu.h"
#include "Image.h"
#include "PPM.h"
#include "ActionData.h"

void drawAsciiImage(ActionData& action_data) {
    float intensity, red, green, blue;
    char c;
    std::vector<char> symbols = {' ', '.', '-', '~', ';', '+', '|', '*', '%', '#', '@'};
    for(int row = 0; row < action_data.getOutputImage().getHeight(); row++) {
        for(int column = 0; column < action_data.getOutputImage().getWidth(); column++) {
            //get intensity and add the appropriate ASCII symbol to out_row
            red = action_data.getOutputImage().getChannel(row, column, 0);
            green = action_data.getOutputImage().getChannel(row, column, 1);
            blue = action_data.getOutputImage().getChannel(row, column, 2);
            intensity = (red + green + blue) / 765;
			// turn float into int between 0 and 10
            int symbol_index = static_cast<int>(std::floor(intensity * 10));
            c = symbols[symbol_index];
        	action_data.getOS() << c ;
        }
		action_data.getOS() << "\n";
    }
}

void writeUserImage(ActionData& action_data) {
    std::string file_name;
file_name = getString(action_data, "Output filename? ");
    // OutputFileStream, in Binary mode
    std::ofstream file_out(file_name, std::ios::binary);
    action_data.getOutputImage().writeStream(file_out);
    file_out.close();
}
void copyImage(ActionData& action_data) {
    action_data.getOutputImage() = action_data.getInputImage1();
}
void readUserImage1( ActionData& action_data ) {
    std::string ppm_file = getString(action_data, "Input filename? ");
    std::ifstream file_in(ppm_file, std::ios::binary);
    // test if file can be opened.
    if(file_in.is_open()) {
		action_data.getInputImage1().readStream(file_in);
		file_in.close();
    } else {
        //std::cerr << ppm_file << " could not be opened." << std::endl;
        action_data.getOS() << ppm_file << " could not be opened." << std::endl;
    }
}
void readUserImage2( ActionData& action_data ) {
    std::string ppm_file = getString(action_data, "Input filename? ");
    std::ifstream file_in(ppm_file, std::ios::binary);
    // test if file can be opened.
    if(file_in.is_open()) {
		action_data.getInputImage2().readStream(file_in);
		file_in.close();
    } else {
        //std::cerr << ppm_file << " could not be opened." << std::endl;
        action_data.getOS() << ppm_file << " could not be opened." << std::endl;
    }
}
void copyOutputImageToImage1(ActionData& action_data) {
    action_data.getInputImage1() = action_data.getOutputImage();
}