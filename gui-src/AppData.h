#ifndef _APPDATA_H_
#define _APPDATA_H_

#include "ActionData.h"
#include "MenuData.h"
#include <sstream>

enum InteractionMode { IM_FRACTAL, IM_COLORTABLE, IM_COLOR1, IM_COLOR2, IM_COLOR3}; //Used to track whether to display the output image or the color table.
enum FractalMode { M_MANDELBROT, M_JULIA, M_COMPLEX };
enum ColorTableMode { CT_GRADIENT, CT_RANDOM3, CT_RANDOM, CT_REVERSE };
class AppData {
public:
  AppData(int height, int width);
  void setSize(int height, int width);
  int getHeight() const;
  int getWidth() const;
  PPM& getOutputImage();
  ColorTable& getColorTable();
  void createJulia1();
  void createJulia2();
  void createMandelbrot1();
  void createMandelbrot2();
  void createComplexFractal1();
  void createComplexFractal2();
  void clearStreams();
  void runCommand(const std::string& choice);
  void selectJulia();
  void selectMandelbrot();
  void selectComplexFractal();
  void configureGrid(int max);
  void juliaParameters(double a, double b);
  void fractalPlaneSize(double x_min, double x_max, double y_min, double y_max);
  void fractalCalculate();
  void gridApplyColorTable();
  void setInteractionMode(InteractionMode mode);
  InteractionMode getInteractionMode() const;
  void setColorTable();
  void decreaseColorTableSize();
  void increaseColorTableSize();
  void randomColor1();
  void randomColor2();
  void randomColor3();  
  void zoomIn();
  void zoomOut();
  void moveLeft();
  void moveRight();
  void moveDown();
  void moveUp();
  void setFractalMode(FractalMode mode);
  FractalMode getFractalMode() const;
  void nextColorTableMode();
  ColorTableMode getColorTableMode() const;
  void set3RandomColors();
  void increaseMaxNumber();
  void decreaseMaxNumber();
  void setAB(int x, int y);
  void resetPlane();
  void createFractal();
  void setAllRandomColors();
  void setReverseGradient();
  void increaseChannel(Color& color, int channel);
  void decreaseChannel(Color& color, int channel);
  Color& fetchColor();
  void increaseRed();
  void decreaseRed();
  void increaseGreen();
  void decreaseGreen();
  void increaseBlue();
  void decreaseBlue();
  void copyOutputToInput1();
  void antiAlias(int reduction_count);
  void applyAntiAlias();
  void toggleAntiAlias();
  void increaseAntiAliasReductionCount();
  void decreaseAntiAliasReductionCount();

protected:
  int mHeight;
  int mWidth;
  int mMaxNumber;
  InteractionMode mInteractionMode;
  FractalMode mFractalMode;
  ColorTableMode mColorTableMode;
  int mNumColor;
  Color mColor1;
  Color mColor2;
  Color mColor3;
  double mMinX;
  double mMaxX;
  double mMinY;
  double mMaxY;
  double mA;
  double mB;
  std::stringstream mInputStream;
  std::stringstream mOutputStream;
  ActionData mActionData;
  MenuData mMenuData;
  int mDebug;
  int mAntiAliasReductionCount;
  bool mAntiAlias;
};

#endif /* _APPDATA_H_ */
/* Local Variables: */
/* mode:c++         */
/* End:             */