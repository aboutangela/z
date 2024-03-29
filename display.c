/*====================== display.c ========================
Contains functions for basic manipulation of a screen
represented as a 2 dimensional array of colors.

A color is an ordered triple of ints, with each value standing
for red, green and blue respectively
==================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "ml6.h"
#include "display.h"


/*======== void plot() ==========
Inputs:   screen s
         color c
         int x
         int y
Returns:
Sets the color at pixel x, y to the color represented by c

Note that s[0][0] will be the upper left hand corner of the screen.

If you wish to change this behavior, you can change the indicies
of s that get set. For example, using s[x][YRES-1-y] will have
pixel 0, 0 located at the lower left corner of the screen

dw
====================*/
void plot( screen s, zbuffer zb, color c, int x, int y, double z) {
  int newy = YRES - 1 - y;
  if ( x >= 0 && x < XRES && newy >=0 && newy < YRES ){
    if(z >= zb[x][newy]){
      s[x][newy] = c;
      zb[x][newy] = z;
    }
  }
}

/*======== void clear_screen() ==========
Inputs:   screen s
Returns:
Sets every color in screen s to the default color.

dw
====================*/
void clear_screen( screen s ) {

  int x, y;
  color c;

  c.red = DEFAULT_COLOR;
  c.green = DEFAULT_COLOR;
  c.blue = DEFAULT_COLOR;

  for ( y=0; y < YRES; y++ )
    for ( x=0; x < XRES; x++)
      s[x][y] = c;
}

/*======== void clear_zbuffer() ==========
Inputs:   zbuffer
Returns:
Sets all entries in the zbufffer to LONG_MIN
====================*/
void clear_zbuffer( zbuffer zb ) {

  int x, y;

  for ( y=0; y < YRES; y++ )
    for ( x=0; x < XRES; x++)
      zb[x][y] = LONG_MIN;
}

/*======== void save_ppm() ==========
Inputs:   screen s
         char *file
Returns:
Saves screen s as a valid ppm file using the settings in ml6.h

dw
====================*/
void save_ppm( screen s, char *file) {

  int x, y;
  FILE *f;

  f = fopen(file, "w");
  fprintf(f, "P3\n%d %d\n%d\n", XRES, YRES, MAX_COLOR);
  for ( y=0; y < YRES; y++ ) {
    for ( x=0; x < XRES; x++)
      fprintf(f, "%d %d %d ", s[x][y].red, s[x][y].green, s[x][y].blue);
    fprintf(f, "\n");
  }
  fclose(f);
}

/*======== void save_extension() ==========
Inputs: screen s
        char *file
Returns:

Saves the screen stored in s to the filename represented by file.

If the extension for file is an image format supported by the "convert"
command, the image will be saved in that format.

dw
====================*/
void save_extension( screen s, char *file) {

  int x, y;
  FILE *f;
  char line[256];

  sprintf(line, "convert - %s", file);

  f = popen(line, "w");
  fprintf(f, "P3\n%d %d\n%d\n", XRES, YRES, MAX_COLOR);
  for ( y=0; y < YRES; y++ ) {
    for ( x=0; x < XRES; x++)
      fprintf(f, "%d %d %d ", s[x][y].red, s[x][y].green, s[x][y].blue);
    fprintf(f, "\n");
  }
  pclose(f);
}


/*======== void display() ==========
Inputs:   screen s
Returns:

Will display the screen s on your monitor.

Requires imagemagick to be installed.

dw
====================*/
void display( screen s) {

  int x, y;
  FILE *f;

  f = popen("display", "w");

  fprintf(f, "P3\n%d %d\n%d\n", XRES, YRES, MAX_COLOR);
  for ( y=0; y < YRES; y++ ) {
    for ( x=0; x < XRES; x++)
      fprintf(f, "%d %d %d ", s[x][y].red, s[x][y].green, s[x][y].blue);
    fprintf(f, "\n");
  }
  pclose(f);
}
