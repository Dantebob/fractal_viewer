#include <iostream>
#include <string>
#include "image_menu.h"

std::string getString( ActionData& action_data, const std::string& prompt ) {
	std::string result;
	action_data.getOS() << prompt;
	action_data.getIS() >> result;
	return result;
}
int getInteger( ActionData& action_data, const std::string& prompt ) {
    int result;
    action_data.getOS() << prompt;
    action_data.getIS() >> result;
    return result;
}
double getDouble( ActionData& action_data, const std::string& prompt ) {
    double result;
    action_data.getOS() << prompt;
    action_data.getIS() >> result;
    return result;
}
int askQuestions3( ActionData& action_data ) {
    std::string fcolor;
    int finteger;
    double fnumber;
    fcolor = getString( action_data, "What is your favorite color? " );
    finteger = getInteger( action_data, "What is your favorite integer? " );
    fnumber = getDouble( action_data, "What is your favorite number? " );
    for(int i = 1; i <= finteger; i++) {
        action_data.getOS() << i <<" "<< fcolor <<" "<< fnumber << std::endl;
    }
    return finteger;
}
int askInquisitorQuestions(ActionData& action_data) {
	std::string pokemon;
	int level;
	double health;
	pokemon = getString( action_data, "What is your most powerful Pokemon? " );
	level = getInteger( action_data, "What is its level? " );
	health = getDouble( action_data, "What is its health? " );
	action_data.getOS() << pokemon << " is level " << level << " and " << health << " HP" << std::endl;
	return level;
}
std::string getChoice(ActionData& action_data) {
    std::string choice; 
    choice = getString( action_data, "Choice? ");
    return choice;

}
void commentLine(ActionData& action_data) {
    char c = '\0';
    while( c != '\n' ){
        action_data.getIS().read( &c, 1 );
        if( !action_data.getIS().good() ) {
            return;
        }
    }
}
void quit(ActionData& action_data) {
    action_data.setDone();
}

