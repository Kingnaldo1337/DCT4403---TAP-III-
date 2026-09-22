#include <stdio.h>
#include <stdlib.h>
#include <jpeglib.h>

void info_jpg(char * input, int * img_width, int * img_height, int * img_channels);

unsigned char * load_jpg(char * input, int * img_width, int * img_height, int * img_channels);

void save_jpg(char * output, int img_width, int img_height, int img_channels, unsigned char * img_buffer);
