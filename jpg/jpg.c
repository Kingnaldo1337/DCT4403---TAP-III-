#include <stdio.h>
#include "jpg_functions.h"
int main(){

    int w, h, c;
    unsigned char * img;

    img = load_jpg("input.jpg", &w, &h, &c);

    printf("Width: %d, Height: %d, Channels: %d\n", w, h, c);

    #pragma omp parallel for num_threads(4)
    for(int i=0; i<w*h*c; i+=c)
    {
        img[i] = 0.299 * img[i] + 0.587 * img[i+1] + 0.114 * img[i+2];
        img[i+1] = img[i];
        img[i+2] = img[i];
    }

    save_jpg("outputgrey.jpg", w, h, c, img);

    return 0;

}