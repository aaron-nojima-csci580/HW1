/*   CS580 HW1 display functions to be completed   */

#include   "stdafx.h"  
#include	"Gz.h"
#include	"disp.h"


int GzNewFrameBuffer(char** framebuffer, int width, int height)
{
/* HW1.1 create a framebuffer for MS Windows display:
 -- allocate memory for framebuffer : 3 bytes(b, g, r) x width x height
 -- pass back pointer 
 */
	*framebuffer = (char *)malloc(3 * sizeof(char) * width * height);
	return GZ_SUCCESS;
}

int GzNewDisplay(GzDisplay	**display, int xRes, int yRes)
{
/* HW1.2 create a display:
  -- allocate memory for indicated resolution
  -- pass back pointer to GzDisplay object in display
*/
	*display = (GzDisplay *)malloc(sizeof(GzDisplay));
	(*display)->xres = xRes;
	(*display)->yres = yRes;
	(*display)->fbuf = (GzPixel *)malloc(sizeof(GzPixel) * yRes * xRes);
	return GZ_SUCCESS;
}


int GzFreeDisplay(GzDisplay	*display)
{
/* HW1.3 clean up, free memory */
	if (display != NULL) {
		free(display);
	}
	return GZ_SUCCESS;
}


int GzGetDisplayParams(GzDisplay *display, int *xRes, int *yRes)
{
/* HW1.4 pass back values for a display */
	if (display != NULL) {
		*xRes = display->xres;
		*yRes = display->yres;
		return GZ_SUCCESS;
	}
	return GZ_FAILURE;
}


int GzInitDisplay(GzDisplay	*display)
{
/* HW1.5 set everything to some default values - start a new frame */
	if (display != NULL) {
		for (int i = 0; i < display->xres; ++i) {
			for (int j = 0; j < display->yres; j++) {
				GzPixel pixel = display->fbuf[ARRAY(i, j)];
				display->fbuf[ARRAY(i, j)].red = 2000;
				display->fbuf[ARRAY(i, j)].green = 2000;
				display->fbuf[ARRAY(i, j)].blue = 2000;
				display->fbuf[ARRAY(i, j)].alpha = 4095;
				display->fbuf[ARRAY(i, j)].z = 4095;
			}
		}
		return GZ_SUCCESS;
	}
	return GZ_FAILURE;
}


int GzPutDisplay(GzDisplay *display, int i, int j, GzIntensity r, GzIntensity g, GzIntensity b, GzIntensity a, GzDepth z)
{
/* HW1.6 write pixel values into the display */
	r = max(0, min(4095, r));
	b = max(0, min(4095, b));
	g = max(0, min(4095, g));
	if (display != NULL) {
		if (i >= 0 && i < display->xres && j >= 0 && j < display->yres) {
			display->fbuf[ARRAY(i, j)].red = r;
			display->fbuf[ARRAY(i, j)].green = g;
			display->fbuf[ARRAY(i, j)].blue = b;
			display->fbuf[ARRAY(i, j)].alpha = a;
			display->fbuf[ARRAY(i, j)].z = z;
		}
		return GZ_SUCCESS;
	}
	return GZ_FAILURE;
}


int GzGetDisplay(GzDisplay *display, int i, int j, GzIntensity *r, GzIntensity *g, GzIntensity *b, GzIntensity *a, GzDepth *z)
{
/* HW1.7 pass back a pixel value to the display */
	if (display != NULL) {
		if (i >= 0 && i < display->xres && j >= 0 && j < display->yres) {
			*r = display->fbuf[ARRAY(i, j)].red;
			*g = display->fbuf[ARRAY(i, j)].green;
			*b = display->fbuf[ARRAY(i, j)].blue;
			*a = display->fbuf[ARRAY(i, j)].alpha;
			*z = display->fbuf[ARRAY(i, j)].z;
		}
		return GZ_SUCCESS;
	}
	return GZ_FAILURE;
}


int GzFlushDisplay2File(FILE* outfile, GzDisplay *display)
{

/* HW1.8 write pixels to ppm file -- "P6 %d %d 255\r" */
	if (display != NULL && outfile != NULL) {
		int xRes = display->xres;
		int yRes = display->yres;
		fprintf(outfile, "P6 %d %d 255\r", xRes, yRes);
		char r, g, b;
		for (int y = 0; y < yRes; ++y) {
			for (int x = 0; x < xRes; ++x) {
				r = display->fbuf[ARRAY(x, y)].red >> 4;
				g = display->fbuf[ARRAY(x, y)].green >> 4;
				b = display->fbuf[ARRAY(x, y)].blue >> 4;
				fprintf(outfile, "%c%c%c", r, g, b);
			}
		}
		return GZ_SUCCESS;
	}
	return GZ_FAILURE;
}

int GzFlushDisplay2FrameBuffer(char* framebuffer, GzDisplay *display)
{

/* HW1.9 write pixels to framebuffer: 
	- put the pixels into the frame buffer
	- CAUTION: when storing the pixels into the frame buffer, the order is blue, green, and red 
	- NOT red, green, and blue !!!
*/
	if (display != NULL && framebuffer != NULL) {
		int xRes = display->xres;
		int yRes = display->yres;
		char r, g, b;
		for (int i = 0; i < xRes; ++i) {
			for (int j = 0; j < yRes; ++j) {
				r = display->fbuf[ARRAY(i, j)].red >> 4;
				g = display->fbuf[ARRAY(i, j)].green >> 4;
				b = display->fbuf[ARRAY(i, j)].blue >> 4;
				framebuffer[3 * ARRAY(i, j) + 0] = b;
				framebuffer[3 * ARRAY(i, j) + 1] = g;
				framebuffer[3 * ARRAY(i, j) + 2] = r;
			}
		}
		return GZ_SUCCESS;
	}
	return GZ_FAILURE;
}