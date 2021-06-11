### Some basic OpenGL functions that I used:  

**glutInit**
This function is used to initialize glut. Here, we can pass the pointers to the  arguments we get in the Main function, that is argc and argv.

**glutInitDisplayMode**
This function is used to set the initial display mode for the window. There are several different modes available. Some of them are as follows:
GLUT_DOUBLE - allows for display on the double buffer window
GLUT_RGBA - shows color (Red, green, blue) and an alpha
GLUT_RGB - shows color (Red, green , blue)
GLUT_DEPTH - allows for depth buffer

**glutInitWindowPosition**
This function is used to set the initial window position. The initial value of the initial window position GLUT state is -1 and -1. If either the X or Y component to the initial window position is negative, the actual window position is left to the window system to determine. It is not necessary to specify a window position.

**glutInitWindowSize**
This function is used to specify the initial window size. By default, the value is 300 by 300.

**glutCreateWindow**
This function is used to actually create the window.

**glutDisplayFunc**
This is used to set a display callback for the current window. It takes a function as an argument. The function must have certain commands to cleanup and window, and also have the code to draw the graphics.

**glutReshapeFunc**
This is used to set a reshape callback for the current window. It is triggered when the window is reshaped. It takes a function as an argument. The function must have commands to set the new viewport dimensions and also to set the orthogonal structure to draw on. 

**glutMainLoop**
This function helps enter into the GLUT event processing loop. This routine should be called at most once in a program. Once called, this routine will never return. It will call as necessary any callbacks that have been registered.

**glClear**
This is used to clear the screen. GL_COLOR_BUFFER_BIT argument can be used to clean up previous shapes or colors. 

**glFlush**
This is used to force execution of GL commands in finite time.

**glMatrixMode**
This is used to set the mode for the window. It takes different arguments. GL_MODELVIEW is used to draw shapes. GL_PROJECTION is used to set the projection mode.

**gluOrtho2D**
This is used to set the orthogonal structure using a cartesian plane. The function call takes 4 arguments, top, bottom, left and right.

**glClearColor**
This is used to specify clear values for the color buffers. Which means, that if we set a different color here, then each time the window is created, it will act as the background color. It takes 4 arguments, red, blue, green and alpha.

**glColor3f**
This function is used to set the color. It takes 3 values red, blue and green. All the values need to be between 0 and 1.

**glBegin**
This function is used to signify the beginning of drawing. It takes different arguments as modes to draw different shapes. A few of them are as follows:
GL_POINTS - Treats each vertex as a single point.
GL_LINES - Treats each pair of vertices as individual line segments.
GL_LINE_STRIP - Draws a connected group of line segments from the first vertex to the last.
GL_LINE_LOOP - Draws a connected group of line segments from the first vertex to the last, then back to the first. 
GL_TRIANGLES - Treats each triplet of vertices as an independent triangle.
GL_QUADS - Treats each group of four vertices as an independent quadrilateral. 
GL_POLYGON - Draws a single, convex polygon. 

**glVertex**
This function is used to specify a vertex. There are different variations of this, based on the use case. glVertex2d is used to specify x and y as double. Similarly glVertex2f is used for float and glVertex2i for integer. To specify 3 coordinates, we can use the same but with 3 as a prefix, that is glVertex3f.

**glEnd**
This function is used to signify the end of drawing vertices.


