#include "GlutApp.h"
#include "glut_app.h"
#include "image_menu.h"

GlutApp::GlutApp(int height, int width)
  : mData(height, width) {
  //display julia set at start
  DrawCircle(0, 0, 50);
  this->displayColorTable();
  /*mData.selectJulia();
  mData.setInteractionMode(IM_FRACTAL);
  mData.setFractalMode(M_JULIA);
  display();*/
}

void GlutApp::setSize(int height, int width) {
  mData.setSize(height, width);
  mData.createFractal();
}

int GlutApp::getHeight() const {
  return mData.getHeight();
}
int GlutApp::getWidth() const {
  return mData.getWidth();
}

void GlutApp::display() {
  if(mData.getInteractionMode() == IM_FRACTAL) {
    this->displayOutputImage();
  }
  if(mData.getInteractionMode() == IM_COLORTABLE) {
    this->displayColorTable();
  }
  if(mData.getInteractionMode() == IM_COLOR1 
  || mData.getInteractionMode() == IM_COLOR2 
  || mData.getInteractionMode() == IM_COLOR3) {
    this->displayColorTable();
  }
}
void GlutApp::displayOutputImage() {
  PPM& p = mData.getOutputImage();
  double max = static_cast<double>(p.getMaxColorValue());
  glBegin(GL_POINTS);
  for(int row = 0; row < p.getHeight(); row++) {
    for(int column = 0; column < p.getWidth(); column++) {
      double red = double(p.getChannel(row, column, 0)) / max;
      double green = double(p.getChannel(row, column, 1)) / max;
      double blue = double(p.getChannel(row, column, 2)) / max;
      glColor3d(red,green,blue);
      glVertex2i(column, p.getHeight() - row - 1);
    }
  }
  glEnd();
}
void GlutApp::displayColorTable() {
  glBegin(GL_POINTS);
  for(int row = 0; row < mData.getHeight(); row++) {
    for(int column = 0; column < mData.getWidth(); column++) {
      int i = column * mData.getColorTable().getNumberOfColors() / mData.getWidth();
      double red = mData.getColorTable()[i].getRed() / 255.0;
      double green = mData.getColorTable()[i].getGreen() / 255.0;
      double blue = mData.getColorTable()[i].getBlue() / 255.0;
      glColor3d(red,green,blue);
      glVertex2i(column, row);
    }
  }
  glEnd();
}
bool GlutApp::keyboard(unsigned char c) {
  switch(c) {
    case 'J':
      mData.createJulia1();
      mData.createFractal();
      break;
    case 'j':
      mData.createJulia2();
      mData.createFractal();
      break;
    case 'M':
      mData.createMandelbrot1();
      mData.createFractal();
      break;
    case 'm':
      mData.createMandelbrot2();
      mData.createFractal();
      break;
    case 'C':
      mData.createComplexFractal1();
      mData.createFractal();
      break;
    case 'c':
      mData.createComplexFractal2();
      mData.createFractal();
      break;
    case 'T':
      mData.setInteractionMode(IM_COLORTABLE);
      break;
    case 't':
      mData.setInteractionMode(IM_FRACTAL);
      break;
    case 'b':
      mData.setFractalMode(M_MANDELBROT);
      mData.createFractal();
      break;
    case 'n':
      mData.setFractalMode(M_JULIA);
      mData.createFractal();
      break;
    case 'F':
      mData.setFractalMode(M_COMPLEX);
      mData.createFractal();
      break;
    case '>':
    case '.':
      mData.increaseColorTableSize();
      break;
    case '<':
    case ',':
      mData.decreaseColorTableSize();
      break;
    case 'r':
      mData.randomColor1();
      break;
    case 'e':
      mData.randomColor3();
      break;
    case 'R':
      if(mData.getInteractionMode() == IM_COLORTABLE) {
        mData.randomColor2();
      }
      if(mData.getInteractionMode() == IM_FRACTAL) {
        mData.resetPlane();
        mData.createFractal();
      }
      break;
    case 'z':
      mData.zoomIn();
      mData.createFractal();
      break;
    case 'Z':
      mData.zoomOut();
      mData.createFractal();
      break;
    case '+':
    case '=':
      mData.increaseMaxNumber();
      mData.createFractal();
      break;
    case '_':  
    case '-':
      mData.decreaseMaxNumber();
      mData.createFractal();
      break;
    case '0':
      mData.nextColorTableMode();
      break;
    case '1':
      mData.setInteractionMode(IM_COLOR1);
      break;
    case '2':
      mData.setInteractionMode(IM_COLOR2);
      break;
    case '3':
      mData.setInteractionMode(IM_COLOR3);
      break;
    case 'Y':
      mData.increaseRed();
      break;
    case 'y':
      mData.decreaseRed();
      break;
    case 'U':
      mData.increaseGreen();
      break;
    case 'u':
      mData.decreaseGreen();
      break;
    case 'I':
      mData.increaseBlue();
      break;
    case 'i':
      mData.decreaseBlue();
      break;
    case 'a':
      mData.toggleAntiAlias();
      mData.createFractal();
      break;
    case 's':
      mData.decreaseAntiAliasReductionCount();
      mData.createFractal();
      break;
    case 'S':
      mData.increaseAntiAliasReductionCount();
      mData.createFractal();
      break;
    default:
      return false;
  }
  return true;
}
bool GlutApp::special(unsigned char c) {
  switch(c) {
    case GLUT_KEY_LEFT:
      mData.moveLeft();
      mData.createFractal();
      break;
    case GLUT_KEY_RIGHT:
      mData.moveRight();
      mData.createFractal();
      break;
    case GLUT_KEY_DOWN:
      mData.moveDown();
      mData.createFractal();
      break;
    case GLUT_KEY_UP:
      mData.moveUp();
      mData.createFractal();
      break;
    default:
      return false;
  }
  return true;
}
bool GlutApp::mouse(int mouse_button, int state, int x, int y) {
  if(mouse_button == GLUT_LEFT_BUTTON && x < mData.getWidth() && x >= 0 
  && y >= 0 && y < mData.getHeight() && state == GLUT_DOWN
  && mData.getInteractionMode() == IM_FRACTAL && mData.getFractalMode() == M_MANDELBROT) {
    mData.setAB(x, y);
    mData.setFractalMode(M_JULIA);
    mData.createFractal();
  } else {
    return false;
  }
  return true;
}