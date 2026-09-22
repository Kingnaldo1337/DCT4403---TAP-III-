#include <stdio.h>
#include <stdlib.h>
#include <jpeglib.h>

void info_jpg(char * input, int * img_width, int * img_height, int * img_channels)
{
    // abrindo a imagem como um arquivo
    FILE *infile = fopen(input, "rb");
    if (!infile) {
        fprintf(stderr, "Error opening input file\n");
        exit(1);
    }
    
    // structs para armazenar a decompressao (dinfo)
    struct jpeg_decompress_struct dinfo;
    struct jpeg_error_mgr jerr;

    // processo de decrompressao
    dinfo.err = jpeg_std_error(&jerr);
    jpeg_create_decompress(&dinfo);
    jpeg_stdio_src(&dinfo, infile);
    jpeg_read_header(&dinfo, TRUE);
    jpeg_start_decompress(&dinfo);

    // informaÃ§oes da imagem
    *img_width = dinfo.output_width;
    *img_height = dinfo.output_height;
    *img_channels = dinfo.output_components; // 3 para RGB
    
    // finish and clean
    jpeg_destroy_decompress(&dinfo);
    fclose(infile);
}

unsigned char * load_jpg(char * input, int * img_width, int * img_height, int * img_channels)
{
    // abrindo a imagem como um arquivo
    FILE *infile = fopen(input, "rb");
    if (!infile) {
        fprintf(stderr, "Error opening input file\n");
        exit(1);
    }
    
    // structs para armazenar a decompressao (dinfo)
    struct jpeg_decompress_struct dinfo;
    struct jpeg_error_mgr jerr;
    unsigned char *row_pointer;

    // processo de decrompressao
    dinfo.err = jpeg_std_error(&jerr);
    jpeg_create_decompress(&dinfo);
    jpeg_stdio_src(&dinfo, infile);
    jpeg_read_header(&dinfo, TRUE);
    jpeg_start_decompress(&dinfo);

    // informaÃ§oes da imagem
    *img_width = dinfo.output_width;
    *img_height = dinfo.output_height;
    *img_channels = dinfo.output_components; // 3 para RGB
    
    // TODO: precisa retornar essa informacao?
    // printf("color space: %d\n", dinfo.out_color_space);

    // alocando o buffer pra imagem
    int img_size = *img_width * *img_height * *img_channels;
    unsigned char * img_buffer = (unsigned char*)malloc(img_size);
    
    // verificando se foi possivel alocar o buffer da imagem
    if (!img_buffer)
    {
        fprintf(stderr, "memory error\n");
        exit(1);
    }

    // read the image line by line
    row_pointer = img_buffer;
    while (dinfo.output_scanline < dinfo.output_height)
    {
        jpeg_read_scanlines(&dinfo, &row_pointer, 1);
        row_pointer += *img_width * *img_channels;
    }

    // finish and clean
    jpeg_finish_decompress(&dinfo);
    jpeg_destroy_decompress(&dinfo);
    fclose(infile);

    return img_buffer;
}

void save_jpg(char * output, int img_width, int img_height, int img_channels, unsigned char * img_buffer)
{
    // abrindo o arquivo pra escrita
    FILE *outfile = fopen(output, "wb");
    if (!outfile) {
        fprintf(stderr, "Error opening output file\n");
        exit(1);
    }

    // estruturas pra compressao (cinfo)
    struct jpeg_compress_struct cinfo;
    struct jpeg_error_mgr jerr;
    unsigned char *row_pointer;

    cinfo.err = jpeg_std_error(&jerr);
    jpeg_create_compress(&cinfo);

    jpeg_stdio_dest(&cinfo, outfile);

    // definindo parametros da imagem a ser salva
    cinfo.image_width = img_width;
    cinfo.image_height = img_height;
    cinfo.input_components = img_channels;      // 1 channel
    
    // TODO: ver se precisa desse valor como parametro
    // cinfo.in_color_space = JCS_GRAYSCALE;
    cinfo.in_color_space = JCS_RGB;

    jpeg_set_defaults(&cinfo);
    jpeg_set_quality(&cinfo, 100, TRUE);  // quality 0-100
    
    // iniciando a compressao
    jpeg_start_compress(&cinfo, TRUE);

    // write line by line
    while (cinfo.next_scanline < cinfo.image_height)
    {
        row_pointer = &img_buffer[cinfo.next_scanline * img_width * img_channels];
        jpeg_write_scanlines(&cinfo, &row_pointer, 1);
    }
    
    // finalizando e limpando
    jpeg_finish_compress(&cinfo);
    jpeg_destroy_compress(&cinfo);
    fclose(outfile);

}
