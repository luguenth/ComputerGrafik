#include "RGBImage.h"
#include "Color.h"

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
    unsigned int headers[13];
    FILE * outfile;
    unsigned int paddedsize;
    int x; int y; int n;
    int red, green, blue;

    paddedsize = (width() * 3) * height();


    headers[0]  = paddedsize + 54;      // bfSize (whole file size)
    headers[1]  = 0;                    // bfReserved (both)
    headers[2]  = 54;                   // bfOffbits
    headers[3]  = 40;                   // biSize
    headers[4]  = width();              // biWidth
    headers[5]  = height();             // biHeight
    headers[7]  = 0;                    // biCompression
    headers[8]  = paddedsize;           // biSizeImage
    headers[9]  = 0;                    // biXPelsPerMeter
    headers[10] = 0;                    // biYPelsPerMeter
    headers[11] = 0;                    // biClrUsed
    headers[12] = 0;                    // biClrImportant

    outfile = fopen(filename, "wb");
    fprintf(outfile, "BM");

    for (n = 0; n <= 5; n++)
    {
        fprintf(outfile, "%c", headers[n] & 0x000000FF);
        fprintf(outfile, "%c", (headers[n] & 0x0000FF00) >> 8);
        fprintf(outfile, "%c", (headers[n] & 0x00FF0000) >> 16);
        fprintf(outfile, "%c", (headers[n] & (unsigned int) 0xFF000000) >> 24);
    }


    fprintf(outfile, "%c", 1);
    fprintf(outfile, "%c", 0);
    fprintf(outfile, "%c", 24);
    fprintf(outfile, "%c", 0);

    for (n = 7; n <= 12; n++)
    {
        fprintf(outfile, "%c", headers[n] & 0x000000FF);
        fprintf(outfile, "%c", (headers[n] & 0x0000FF00) >> 8);
        fprintf(outfile, "%c", (headers[n] & 0x00FF0000) >> 16);
        fprintf(outfile, "%c", (headers[n] & (unsigned int) 0xFF000000) >> 24);
    }

//
// Headers done, now write the data...
//

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