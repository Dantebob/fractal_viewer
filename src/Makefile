CXX := g++
CXXFLAGS := -Wall -std=c++11 -Wpedantic -Wextra -Werror -g
LDFLAGS := -lpthread
OPENGL_LDFLAGS := -lglut -lGLU -lGL
COMMON_OBJECTS := controllers.o user_io.o Image.o image_drawing.o image_output.o PPM.o ActionData.o MenuData.o \
image_filters.o NumberGrid.o ColorTable.o ComplexFractal.o JuliaSet.o MandelbrotSet.o ThreadedGrid.o

UNAME := $(shell uname)

# OS X specific options
ifeq ($(UNAME), Darwin)
OPENGL_LDFLAGS := -framework OpenGL -framework GLUT
CXXFLAGS := $(CXXFLAGS) -Wno-deprecated
endif

TARGETS := hello questions_3 ascii_image image_file ppm_menu

all: $(TARGETS)

ThreadedGrid.o: ThreadedGrid.cpp ThreadedGrid.h
	$(CXX) $(CXXFLAGS) -c $<

MandelbrotSet.o: MandelbrotSet.cpp MandelbrotSet.h
	$(CXX) $(CXXFLAGS) -c $<

JuliaSet.o: JuliaSet.cpp JuliaSet.h
	$(CXX) $(CXXFLAGS) -c $<

ComplexFractal.o: ComplexFractal.cpp ComplexFractal.h
	$(CXX) $(CXXFLAGS) -c $<

ColorTable.o: ColorTable.cpp ColorTable.h
	$(CXX) $(CXXFLAGS) -c $<

NumberGrid.o: NumberGrid.cpp NumberGrid.h
	$(CXX) $(CXXFLAGS) -c $<

image_filters.o: image_filters.cpp image_menu.h ActionData.h
	$(CXX) $(CXXFLAGS) -c $<

ppm_menu: ppm_menu.o $(COMMON_OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

ppm_menu.o: ppm_menu.cpp image_menu.h
	$(CXX) $(CXXFLAGS) -c $<

ActionData.o: ActionData.cpp ActionData.h
	$(CXX) $(CXXFLAGS) -c $<

MenuData.o: MenuData.cpp MenuData.h ActionData.h
	$(CXX) $(CXXFLAGS) -c $<

controllers.o: controllers.cpp image_menu.h Image.h PPM.h ActionData.h MenuData.h
	$(CXX) $(CXXFLAGS) -c $<

image_drawing.o: image_drawing.cpp image_menu.h Image.h PPM.h ActionData.h MenuData.h
	$(CXX) $(CXXFLAGS) -c $<

image_output.o: image_output.cpp image_menu.h Image.h PPM.h ActionData.h MenuData.h
	$(CXX) $(CXXFLAGS) -c $<

flag_romania: flag_romania.o controllers.o user_io.o Image.o image_drawing.o image_output.o PPM.o ActionData.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

flag_romania.o: flag_romania.cpp image_menu.h
	$(CXX) $(CXXFLAGS) -c $<

simple_squares_ascii: simple_squares_ascii.o $(COMMON_OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

simple_squares_ascii.o: simple_squares_ascii.cpp image_menu.h
	$(CXX) $(CXXFLAGS) -c $<

inquisitor: inquisitor.o controllers.o user_io.o Image.o image_drawing.o image_output.o PPM.o ActionData.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

inquisitor.o: inquisitor.cpp image_menu.h
	$(CXX) $(CXXFLAGS) -c $<

image_file: image_file.o $(COMMON_OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

image_file.o: image_file.cpp image_menu.h
	$(CXX) $(CXXFLAGS) -c $<

PPM.o: PPM.cpp PPM.h
	$(CXX) $(CXXFLAGS) -c $<

ascii_image: ascii_image.o $(COMMON_OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

ascii_image.o: ascii_image.cpp image_menu.h
	$(CXX) $(CXXFLAGS) -c $<

Image.o: Image.cpp Image.h
	$(CXX) $(CXXFLAGS) -c $<

questions_3: questions_3.o $(COMMON_OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

questions_3.o: questions_3.cpp image_menu.h
	$(CXX) $(CXXFLAGS) -c $<

user_io.o: user_io.cpp image_menu.h
	$(CXX) $(CXXFLAGS) -c $<

#hello: hello.o
#	g++ -std=c++11 -o hello hello.o

# $@ is hello and $^ is hello.o but what is LDFLAGS?
hello: hello.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

hello.o: hello.cpp
	$(CXX) $(CXXFLAGS) -o $@ -c $<

glut_main: glut_main.o gl_draw.o glut_app.o GlutApp.o glut_callback.o Rectangle.o Shape.o ShapeList.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS) $(OPENGL_LDFLAGS)

glut_main.o: glut_main.cpp glut_app.h GlutApp.h ShapeList.h Shape.h
	$(CXX) $(CXXFLAGS) -o $@ -c $<

gl_draw.o: gl_draw.cpp glut_app.h GlutApp.h ShapeList.h Shape.h
	$(CXX) $(CXXFLAGS) -o $@ -c $<

glut_app.o: glut_app.cpp glut_app.h GlutApp.h ShapeList.h Shape.h
	$(CXX) $(CXXFLAGS) -o $@ -c $<

GlutApp.o: GlutApp.cpp GlutApp.h Rectangle.h glut_app.h ShapeList.h Shape.h
	$(CXX) $(CXXFLAGS) -o $@ -c $<

glut_callback.o: glut_callback.cpp glut_app.h GlutApp.h ShapeList.h Shape.h
	$(CXX) $(CXXFLAGS) -o $@ -c $<

Rectangle.o: Rectangle.cpp Rectangle.h Shape.h
	$(CXX) $(CXXFLAGS) -o $@ -c $<

Shape.o: Shape.cpp Shape.h
	$(CXX) $(CXXFLAGS) -o $@ -c $<

ShapeList.o: ShapeList.cpp ShapeList.h Shape.h
	$(CXX) $(CXXFLAGS) -o $@ -c $<

clean:
	-rm -f *.o *~
	-rm -f $(TARGETS)

