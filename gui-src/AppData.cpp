#include "AppData.h"
#include "image_menu.h"
#include <sstream>
#include <iostream>
#include <cstdlib>
#include <ctime>

AppData::AppData(int height, int width) 
  : mHeight(height), mWidth(width), mMaxNumber(36), 
  mInteractionMode(IM_FRACTAL), mFractalMode(M_JULIA), mColorTableMode(CT_GRADIENT),
  mNumColor(mMaxNumber), mColor1(0, 150, 150), mColor2(150, 0, 150), mColor3(0, 200, 30), 
  mMinX(-2.0), mMaxX(2.0), mMinY(-2.0), mMaxY(2.0),
  mA(-0.650492), mB(-0.478235), 
  mActionData(mInputStream, mOutputStream), mDebug(1),
  mAntiAliasReductionCount(2), mAntiAlias(false) {
  configureMenu(mMenuData);
  mActionData.setGrid(new ComplexFractal);
  setColorTable();
  createFractal();
  std::srand(std::time(0));
}

void AppData::setSize(int height, int width) {
  mHeight = height;
  mWidth = width;
}
int AppData::getHeight() const {
  return mHeight;
}
int AppData::getWidth() const {
  return mWidth;
}
PPM& AppData::getOutputImage() {
  return mActionData.getOutputImage();
}
ColorTable& AppData::getColorTable() {
  return mActionData.getTable();
}
void AppData::createJulia1() {
  mA = 0.285;
  mB = 0.01;
  JuliaSet( mHeight, mWidth, mMinX, mMaxX, mMinY, mMaxY, mA, mB );
}
void AppData::createJulia2() {
  mA = -0.7269;
  mB = 0.1889;
  JuliaSet( mHeight, mWidth, mMinX, mMaxX, mMinY, mMaxY, mA, mB );
}
void AppData::createMandelbrot1() {
  mMinX = -0.8;
  mMaxX = -0.4;
  mMinY = -0.9;
  mMaxY = -0.3;
  MandelbrotSet( mHeight, mWidth, mMinX, mMaxX, mMinY, mMaxY );
}
void AppData::createMandelbrot2() {
  mMinX = 0.25;
  mMaxX = 0.35;
  mMinY = -0.05;
  mMaxY = 0.03;
  MandelbrotSet( mHeight, mWidth, mMinX, mMaxX, mMinY, mMaxY );
}
void AppData::createComplexFractal1() {
  mMinX = -0.7;
  mMaxX = -0.7;
  mMinY = -0.44;
  mMaxY = 0.3;
  ComplexFractal( mHeight, mWidth, mMinX, mMaxX, mMinY, mMaxY );
}
void AppData::createComplexFractal2() {
  mMinX = -0.25;
  mMaxX = 0.35;
  mMinY = -0.5;
  mMaxY = 0.3;
  ComplexFractal( mHeight, mWidth, mMinX, mMaxX, mMinY, mMaxY );
}
void AppData::clearStreams() {
  mInputStream.clear();
  mInputStream.str("");
  mOutputStream.clear();
  mOutputStream.str("");
}
void AppData::runCommand(const std::string& choice) {
  if(mDebug != 0) {
    std::cout << choice << " " << mInputStream.str() << std::endl;
    takeAction(choice, mMenuData, mActionData);
    std::cout << mOutputStream.str() << std::endl;
  } else {
    takeAction(choice, mMenuData, mActionData);
  }
  clearStreams();
}
void AppData::selectJulia() {
  this->runCommand("julia");
}
void AppData::selectMandelbrot() {
  this->runCommand("mandelbrot");
}
void AppData::selectComplexFractal() {
  this->runCommand("complex-fractal");
}
void AppData::configureGrid(int max) {
  int height = mHeight;
  int width = mWidth;
  if(mAntiAlias == true) {
    height = mHeight * mAntiAliasReductionCount;
    width = mWidth * mAntiAliasReductionCount;
  }
  this->clearStreams();
  mInputStream << height << " " << width << " " << max << std::endl;
  this->runCommand("grid");
}
void AppData::juliaParameters(double a, double b) {
  mA = a;
  mB = b;
  this->clearStreams();
  //tmp << mA << " " << mB << std::endl;
  //mInputStream.str(str(tmp))
  mInputStream << mA << " " << mB << std::endl;
  this->runCommand("julia-parameters");
}
void AppData::fractalPlaneSize(double x_min, double x_max, double y_min, double y_max) {
  mMinX = x_min;
  mMaxX = x_max;
  mMinY = y_min;
  mMaxY = y_max;
  this->clearStreams();
  mInputStream << mMinX << " " << mMaxX << " " << mMinY << " " << mMaxY << std::endl;
  this->runCommand("fractal-plane-size");
}
void AppData::fractalCalculate() {
  this->runCommand("fractal-calculate");
}
void AppData::gridApplyColorTable() {
  this->runCommand("grid-apply-color-table");
  this->applyAntiAlias();
}
void AppData::setInteractionMode(InteractionMode mode) {
  //Modifies the data member to store the current interaction mode.
  mInteractionMode = mode;
}
InteractionMode AppData::getInteractionMode() const {
  return mInteractionMode;
}
void AppData::setColorTable() {
  /*if(mColorTableMode == CT_RANDOM3) {
    set3RandomColors();
  }*/
  this->clearStreams();
  mInputStream << mNumColor << std::endl;
  this->runCommand("set-color-table-size");
  int pos_1 = 0;
  int red_1 = mColor1.getRed();
  int green_1 = mColor1.getGreen();
  int blue_1 = mColor1.getBlue();
  int pos_2 = (mNumColor / 2) -1;
  int red_2 = mColor2.getRed();
  int green_2 = mColor2.getGreen();
  int blue_2 = mColor2.getBlue();
  this->clearStreams();
  mInputStream << pos_1 << " " << red_1 << " " << green_1 << " " << blue_1 << " " << pos_2 << " " << red_2 << " " << green_2 << " " << blue_2 << std::endl;
  this->runCommand("set-color-gradient");
  int pos_3 = mNumColor - 1;
  int red_3 = mColor3.getRed();
  int green_3 = mColor3.getGreen();
  int blue_3 = mColor3.getBlue();
  this->clearStreams();
  mInputStream << pos_2 << " " << red_2 << " " << green_2 << " " << blue_2 << " " << pos_3 << " " << red_3 << " " << green_3 << " " << blue_3 << std::endl;
  this->runCommand("set-color-gradient");
  if(mColorTableMode == CT_RANDOM3) {
    set3RandomColors();
  }
  if(mColorTableMode == CT_RANDOM) {
    setAllRandomColors();
  }
  if(mColorTableMode == CT_REVERSE) {
    setReverseGradient();
  }
}
void AppData::decreaseColorTableSize() {
  if(mNumColor > 10) {
    mNumColor /= 1.1;
    setColorTable();
    gridApplyColorTable();
  }
}
void AppData::increaseColorTableSize() {
  if(mNumColor < 1024) {
    mNumColor *= 1.1;
    setColorTable();
    gridApplyColorTable();
  }
}
void AppData::randomColor1() {
  int red = std::rand() % (255 + 1);
  int green = std::rand() % (255 + 1);
  int blue = std::rand() % (255 + 1);
  mColor1.setRed(red);
  mColor1.setGreen(green);
  mColor1.setBlue(blue);
  setColorTable();
  gridApplyColorTable();
}
void AppData::randomColor2() {
  int red = std::rand() % (255 + 1);
  int green = std::rand() % (255 + 1);
  int blue = std::rand() % (255 + 1);
  mColor2.setRed(red);
  mColor2.setGreen(green);
  mColor2.setBlue(blue);
  setColorTable();
  gridApplyColorTable();
}
void AppData::randomColor3() {
  int red = std::rand() % (255 + 1);
  int green = std::rand() % (255 + 1);
  int blue = std::rand() % (255 + 1);
  mColor3.setRed(red);
  mColor3.setGreen(green);
  mColor3.setBlue(blue);
  setColorTable();
  gridApplyColorTable();
}
void AppData::zoomIn() {
  /*this->clearStreams();
  mInputStream << 0.1 << std::endl;
  this->runCommand("zoomPlane");*/
  double dx = (1.0 - 0.9)*(mMaxX - mMinX) / 2.0;
  double dy = (1.0 - 0.9)*(mMaxY - mMinY) / 2.0;
  mMinX += dx;
  mMaxX -= dx;
  mMinY += dy;
  mMaxY -= dy;
}
void AppData::zoomOut() {
  /*this->clearStreams();
  mInputStream << -0.1 << std::endl;
  this->runCommand("zoomPlane");*/
  double dx = (1.1 - 1.0)*(mMaxX - mMinX) / 2.0;
  double dy = (1.1 - 1.0)*(mMaxY - mMinY) / 2.0;
  if(mMinX - dx >= -2.0 || mMaxX + dx <= 2.0 
  || mMinY - dy >= -2.0 || mMaxY + dy <= 2.0) {
    mMinX -= dx;
    mMaxX += dx;
    mMinY -= dy;
    mMaxY += dy;
  }
}
void AppData::moveLeft() {
  //this->runCommand("fractal-left");
  double dx = (0.05)*(mMaxX - mMinX);
  if(mMinX - dx >= -2.0) {
    mMinX -= dx;
    mMaxX -= dx;
  }
}
void AppData::moveRight() {
  //this->runCommand("fractal-right");
  double dx = (0.05)*(mMaxX - mMinX);
  if(mMaxX + dx <= 2.0) {
    mMinX += dx;
    mMaxX += dx;
  }
}
void AppData::moveDown() {
  //this->runCommand("fractal-down");
  double dy = (0.05)*(mMaxY - mMinY);
  if(mMinY - dy >= -2.0) {
    mMinY -= dy;
    mMaxY -= dy;
  }
  
}
void AppData::moveUp() {
  //this->runCommand("fractal-up");
  double dy = (0.05)*(mMaxY - mMinY);
  if(mMaxY + dy <= 2.0) {
    mMinY += dy;
    mMaxY += dy;
  }
}
void AppData::setFractalMode(FractalMode mode) {
  mFractalMode = mode;
}
FractalMode AppData::getFractalMode() const {
  return mFractalMode;
}
void AppData::nextColorTableMode() {
  if(mColorTableMode == CT_GRADIENT){
    mColorTableMode = CT_RANDOM3;
    std::cout << "#Color table mode is: CT_RANDOM3" << std::endl;
  } else if(mColorTableMode == CT_RANDOM3) {
    mColorTableMode = CT_RANDOM;
    std::cout << "#Color table mode is: CT_RANDOM" << std::endl;
  } else if(mColorTableMode == CT_RANDOM) {
    mColorTableMode = CT_REVERSE;
    std::cout << "#Color table mode is: CT_REVERSE" << std::endl;
  } else if(mColorTableMode == CT_REVERSE) {
    mColorTableMode = CT_GRADIENT;
    std::cout << "#Color table mode is: CT_GRADIENT" << std::endl;
  }
  setColorTable();
  gridApplyColorTable();
}
ColorTableMode AppData::getColorTableMode() const {
  return mColorTableMode;
}
void AppData::set3RandomColors() {
  if(mColorTableMode == CT_RANDOM3) {
    int pos_1, pos_2, pos_3;
    pos_1 = 0;
    pos_2 = (mNumColor / 2)-1;
    pos_3 = mNumColor - 1;
    mInputStream << pos_1 << std::endl;
    this->runCommand("set-random-color");
    mInputStream << pos_2 << std::endl;
    this->runCommand("set-random-color");
    mInputStream << pos_3 << std::endl;
    this->runCommand("set-random-color");
  }
  /*int red, green, blue;
  red = std::rand() % (255 + 1);
  green = std::rand() % (255 + 1);
  blue = std::rand() % (255 + 1);
  mColor1.setRed(red);
  mColor1.setGreen(green);
  mColor1.setBlue(blue);
  red = std::rand() % (255 + 1);
  green = std::rand() % (255 + 1);
  blue = std::rand() % (255 + 1);
  mColor2.setRed(red);
  mColor2.setGreen(green);
  mColor2.setBlue(blue);
  red = std::rand() % (255 + 1);
  green = std::rand() % (255 + 1);
  blue = std::rand() % (255 + 1);
  mColor3.setRed(red);
  mColor3.setGreen(green);
  mColor3.setBlue(blue);*/
}
void AppData::setAllRandomColors() {
  for(int pos = 0; pos < mNumColor; pos++) {
    mInputStream << pos << std::endl;
    this->runCommand("set-random-color");
  }
}
void AppData::setReverseGradient() {
  int pos_1 = 0;
  int red_1 = mColor3.getRed();
  int green_1 = mColor3.getGreen();
  int blue_1 = mColor3.getBlue();
  int pos_2 = (mNumColor / 2) -1;
  int red_2 = mColor2.getRed();
  int green_2 = mColor2.getGreen();
  int blue_2 = mColor2.getBlue();
  this->clearStreams();
  mInputStream << pos_1 << " " << red_1 << " " << green_1 << " " << blue_1 << " " << pos_2 << " " << red_2 << " " << green_2 << " " << blue_2 << std::endl;
  this->runCommand("set-color-gradient");
  int pos_3 = mNumColor - 1;
  int red_3 = mColor1.getRed();
  int green_3 = mColor1.getGreen();
  int blue_3 = mColor1.getBlue();
  this->clearStreams();
  mInputStream << pos_2 << " " << red_2 << " " << green_2 << " " << blue_2 << " " << pos_3 << " " << red_3 << " " << green_3 << " " << blue_3 << std::endl;
  this->runCommand("set-color-gradient");
}
void AppData::increaseMaxNumber() {
  if(mMaxNumber < 2048) {
    mMaxNumber *= 1.1;
  }
}
void AppData::decreaseMaxNumber() {
  if(mMaxNumber > 11) {
    mMaxNumber /= 1.1;
  }
}
void AppData::setAB(int x, int y) {
  NumberGrid& grid = mActionData.getGrid();
  ComplexFractal *cf_grid = dynamic_cast<ComplexFractal*>(&grid);
  if(mFractalMode == M_MANDELBROT && cf_grid != nullptr) {
    double delta_x = cf_grid->getDeltaX();
    double delta_y = cf_grid->getDeltaY();
    mA = mMinX + x * delta_x;
    mB = mMinY + y * delta_y;
    std::cout << "###### mA: " << mA << " mB: " << mB << std::endl;
  }
}
void AppData::resetPlane() {
 mMinX = -2.0;
 mMaxX = 2.0;
 mMinY = -2.0;
 mMaxY = 2.0;
}
void AppData::createFractal() {
  if(mFractalMode == M_MANDELBROT) {
    selectMandelbrot();
  } else if(mFractalMode == M_JULIA) {
    selectJulia();
    juliaParameters(mA, mB);
  } else if (mFractalMode == M_COMPLEX) {
    selectComplexFractal();
  }
  if(mColorTableMode == CT_GRADIENT || mColorTableMode == CT_REVERSE) {
    setColorTable();
  }
  configureGrid(mMaxNumber);
  fractalPlaneSize(mMinX, mMaxX, mMinY, mMaxY);
  fractalCalculate();
  gridApplyColorTable();
}
void AppData::increaseChannel(Color& color, int channel) {
  int new_c = color.getChannel(channel) + 10;
  if(new_c > 255) {
    new_c = 255;
  }
  color.setChannel(channel, new_c);
  setColorTable();
  gridApplyColorTable();
}
void AppData::decreaseChannel(Color& color, int channel) {
  int new_c = color.getChannel(channel) - 10;
  if(new_c < 0) {
    new_c = 0;
  }
  color.setChannel(channel, new_c);
  setColorTable();
  gridApplyColorTable();
}
Color& AppData::fetchColor() {
  static Color default_color(1, 50, 32);
  if(mInteractionMode == IM_COLOR1) {
    return mColor1;
  } else if(mInteractionMode == IM_COLOR2) {
    return mColor2;
  } else if(mInteractionMode == IM_COLOR3) {
    return mColor3;
  } else {
    return default_color;
  }
}
void AppData::increaseRed() {
  this->increaseChannel(this->fetchColor(), 0);
  std::cout << " + RED" << std::endl;
}
void AppData::decreaseRed() {
  this->decreaseChannel(this->fetchColor(), 0);
  std::cout << " - RED" << std::endl;
}
void AppData::increaseGreen() {
  this->increaseChannel(this->fetchColor(), 1);
  std::cout << " + GREEN" << std::endl;
}
void AppData::decreaseGreen() {
  this->decreaseChannel(this->fetchColor(), 1);
  std::cout << " - GREEN" << std::endl;
}
void AppData::increaseBlue() {
  this->increaseChannel(this->fetchColor(), 2);
  std::cout << " + BLUE" << std::endl;
}
void AppData::decreaseBlue() {
  this->decreaseChannel(this->fetchColor(), 2);
  std::cout << " - BLUE" << std::endl;
}
void AppData::copyOutputToInput1() {
  this->runCommand("copyo1");
}
void AppData::antiAlias(int reduction_count) {
  this->clearStreams();
  mInputStream << reduction_count << std::endl;
  this->runCommand("anti-alias");
}
void AppData::applyAntiAlias() {
  if(mAntiAlias == true) {
    copyOutputToInput1();
    antiAlias(mAntiAliasReductionCount);
  }
}
void AppData::toggleAntiAlias() {
  if(mAntiAlias == true) {
    mAntiAlias = false;
    std::cout << "anti-alias = FALSE" << std::endl;
  } else if(mAntiAlias == false) {
    mAntiAlias = true;
    std::cout << "anti-alias = TRUE" << std::endl;
  }
}
void AppData::increaseAntiAliasReductionCount() {
  mAntiAliasReductionCount += 1;
  std::cout << "Alias reduction count is: " << mAntiAliasReductionCount << std::endl;
}
void AppData::decreaseAntiAliasReductionCount() {
  mAntiAliasReductionCount -= 1;
  std::cout << "Alias reduction count is: " << mAntiAliasReductionCount << std::endl;
}