#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "MenuData.h"
#include "ActionData.h"

MenuData::MenuData() {}

void MenuData::addAction(const std::string& name, ActionFunctionType func, const std::string& description) {
    mCmd_names.push_back(name);
    mCommands[name] = func;
    mCmd_descriptions[name] = description;
}
const std::vector<std::string>& MenuData::getNames() const {
    return mCmd_names;
}
ActionFunctionType MenuData::getFunction(const std::string& name) {
    //if mCommands[name] exists return value.
    if(mCommands.find(name) != mCommands.end()) {
        return mCommands[name];
    } else{
        return 0;
    }
}
const std::string& MenuData::getDescription(const std::string& name) {
    static std::string return_str;
    if(mCommands.find(name) != mCommands.end()) {
        return mCmd_descriptions[name];
    } else{
        return return_str;
    }
}

