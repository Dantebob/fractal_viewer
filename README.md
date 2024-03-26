# Fractal_viewer
Generates image of Mandelbrot and Julia sets that can be navigated and swapped

# Controls
'J' = createJulia1

'j' = createJulia2

'M' = createMandelbrot1

'm' = createMandelbrot2

'C' = createComplexFractal1

'c' = createComplexFractal2

'T' = setInteractionMode to IM_COLORTABLE

't' = setInteractionMode to IM_FRACTAL

'b' = setFractalMode to M_MANDELBROT

'n' = setFractalMode to M_JULIA

'F' = setFractalMode to M_COMPLEX

'.' = increaseColorTableSize

',' = decreaseColorTableSize

'r' = randomColor1

'e' = randomColor3

'R':
  if getInteractionMode == IM_COLORTABLE
  then randomColor2
  
  if getInteractionMode == IM_FRACTAL
  then resetPlane
  
'z' = zoomIn

'Z' = zoomOut

'=' = increaseMaxNumber

'-' = decreaseMaxNumber

'0' = nextColorTableMode

'1' = setInteractionMode to IM_COLOR1

'2' = setInteractionMode to IM_COLOR2

'3' = setInteractionMode to IM_COLOR3

'Y' = increaseRed

'y' = decreaseRed

'U' = increaseGreen

'u' = decreaseGreen

'I' = increaseBlue

'i' = decreaseBlue

'a' = toggleAntiAlias

's' = decreaseAntiAliasReductionCount

'S' = increaseAntiAliasReductionCount
