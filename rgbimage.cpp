#include "rgbimage.h"
#include "color.h"
#include "assert.h"

RGBImage::RGBImage( unsigned int Width, unsigned int Height)
{
	this->m_Height = Height;
	this->m_Width = Width;
	this->m_Image = new Color[Width * Height];
}

RGBImage::~RGBImage()
{
	// TODO: add your code
}

void RGBImage::setPixelColor( unsigned int x, unsigned int y, const Color& c)
{
    this->m_Image[x + width()*y]= c;
}

const Color& RGBImage::getPixelColor( unsigned int x, unsigned int y) const
{
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
    return (unsigned char) (v * 256.0f);
}


bool RGBImage::saveToDisk( const char* filename)
{
    unsigned int headers[13];
    FILE * outfile;
    int extrabytes;
    int paddedsize;
    int x; int y; int n;
    int red, green, blue;

    extrabytes = 4 - ((width() * 3) % 4);                 // How many bytes of padding to add to each
    // horizontal line - the size of which must
    // be a multiple of 4 bytes.
    if (extrabytes == 4)
        extrabytes = 0;

    paddedsize = ((width() * 3) + extrabytes) * height();


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

    for (y = height() - 1; y >= 0; y--)     // BMP image format is written from bottom to top...
    {
        for (x = 0; x <= width() - 1; x++)
        {

            red = convertColorChannel(getPixelColor(x, y).R);
            green = convertColorChannel(getPixelColor(x, y).G);
            blue = convertColorChannel(getPixelColor(x, y).B);

            if (red > 255) red = 255; if (red < 0) red = 0;
            if (green > 255) green = 255; if (green < 0) green = 0;
            if (blue > 255) blue = 255; if (blue < 0) blue = 0;

        }
        if (extrabytes)      // See above - BMP lines must be of lengths divisible by 4.
        {
            for (n = 1; n <= extrabytes; n++)
            {
                fprintf(outfile, "%c", 0);
            }
        }
    }

    fclose(outfile);
	return true; // dummy (remove)
}
