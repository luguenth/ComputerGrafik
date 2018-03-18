#include "rgbimage.h"
#include "color.h"

RGBImage::RGBImage( unsigned int Width, unsigned int Height)
{
	this->m_Height = Height;
	this->m_Width = Width;
	this->m_Image = new Color[Width * Height];
}

RGBImage::~RGBImage()
{
	free(this->m_Image);
}

void RGBImage::setPixelColor( unsigned int x, unsigned int y, const Color& c)
{
    if(x > this->width())
        x = this->width()-1;
    if(y > this->height())
        y = this->height()-1;
    this->m_Image[x + width()*y]= c;
}

const Color& RGBImage::getPixelColor( unsigned int x, unsigned int y) const
{
    if(x > this->width())
        x = this->width()-1;
    if(y > this->height())
        y = this->height()-1;
	return this->m_Image[x + width()*y]; // dummy (remove)
}

unsigned int RGBImage::width() const
{
	return this->m_Width; // dummy (remove)
}
unsigned int RGBImage::height() const
{
	return this->m_Height; // dummy (remove)
}

unsigned char RGBImage::convertColorChannel( float v)
{
    if(v<0){
        v =0;
    }
    if(v>255){
        v=255;
    }
    return (unsigned char) (v * 256.0f);
}


bool RGBImage::saveToDisk( const char* filename)
{
    FILE * outfile;
    int red, green, blue;
    int x, y;
    int bildgroesse;
    outfile = fopen(filename, "wb");

    uint32_t i;
    uint16_t s;

    bildgroesse = (width() * 3) * height();


    unsigned int headers[13];

    unsigned int paddedsize;



    paddedsize = (width() * 3) * height();


    headers[0]  = paddedsize + 54;      // Dateigroesse
    headers[1]  = 0;                    // 4 Bytes auf Null gesetzt
    headers[2]  = 54;                   // Pixeloffset
    headers[3]  = 40;                   // Infoblockgroesse
    headers[4]  = width();              // bildbreite
    headers[5]  = height();             // bildhoehe
    headers[7]  = 0;                    // Kompression unkompriemiert 0
    headers[8]  = paddedsize;           // Bildgroesse
    headers[9]  = 0;                    // Pixel per Meter X
    headers[10] = 0;                    // Pixel per Meter Y
    headers[11] = 0;                    // Farbtabelle
    headers[12] = 0;                    // Wichtige Farben in der Farbtabelle


    outfile = fopen(filename, "wb");
    fprintf(outfile, "BM"); // Header beginnt immer mit "BM"
    int n;

    for (n = 0; n <= 5; n++)
    {
        write_int_binary(headers[n],outfile);
    }

    fprintf(outfile, "%c", 1); //Ebene
    fprintf(outfile, "%c", 0); //Auf 2 Bytes aufstocken
    fprintf(outfile, "%c", 24); //Bits per Pixel
    fprintf(outfile, "%c", 0); //Auf 2 Byte aufstocken

    for (n = 7; n <= 12; n++)
    {
        write_int_binary(headers[n],outfile);
    }


    for (y = height() - 1; y >= 0; y--)
    {
        for (x = 0; x <= width() - 1; x++)
        {

            red = convertColorChannel(getPixelColor(x, y).R);
            green = convertColorChannel(getPixelColor(x, y).G);
            blue = convertColorChannel(getPixelColor(x, y).B);

            fprintf(outfile, "%c", blue);
            fprintf(outfile, "%c", green);
            fprintf(outfile, "%c", red);
        }
    }

    fclose(outfile);
	return true; // dummy (remove)
}

void RGBImage::write_int_binary(int n, FILE *outfile) {

    fprintf(outfile, "%c", n & 0x000000FF);
    fprintf(outfile, "%c", (n & 0x0000FF00) >> 8);
    fprintf(outfile, "%c", (n & 0x00FF0000) >> 16);
    fprintf(outfile, "%c", (n & (unsigned int) 0xFF000000) >> 24);

     }