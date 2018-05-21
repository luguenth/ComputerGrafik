#include "Terrain.h"
#include "rgbimage.h"
#include "Terrainshader.h"

Terrain::Terrain(const char* HeightMap, const char* DetailMap1, const char* DetailMap2) : Size(10,1,10)
{
    if(HeightMap && DetailMap1 && DetailMap2)
    {
        bool loaded = load( HeightMap, DetailMap1, DetailMap2);
        if(!loaded)
            throw std::exception();
    }
}

Terrain::~Terrain()
{
    
}

bool Terrain::load( const char* HeightMap, const char* DetailMap1, const char* DetailMap2)
{
    if( !HeightTex.load(HeightMap) )
        return false;
    if( !DetailTex[0].load(DetailMap1) )
        return false;
    if( !DetailTex[1].load(DetailMap2) )
        return false;
    
	Texture hm = Texture(HeightMap);
	const RGBImage *hmrgb = hm.getRGBImage();
	width(hmrgb->width());
	depth(hmrgb->height());
	std::cout
		<< width()
		<< ";"
		<< depth()
		<< std::endl;
	VB.begin();
	for (int x = -width()/2; x < width()/2; ++x) {
		for (int z = -depth()/2 ;  z < depth()/2; ++z) {
			if (hmrgb->getPixelColor(x+width()/2, z + depth() / 2).R) {
				double y = hmrgb->getPixelColor(x, z).R*height();
				VB.addNormal(x*1.f,y,z*1.f);
				VB.addTexcoord0(0,0);
				VB.addVertex(Vector(x, y, z));
			}
		}
	}
	VB.end();
	IB.begin();

	
	for (unsigned int z = 0; z < depth()-2; ++z) {
		for (unsigned int x = 0; x < width() - 1; ++x) {
			//0,0
			IB.addIndex(x + width()*z);
			IB.addIndex(x+1+width()*z);
			IB.addIndex((x+1) + width()*(z+1));
			/*
			IB.addIndex((x + 1) * z);
			IB.addIndex((x + 2) * (z + 1));
			IB.addIndex((x + 1) * (z + 1));
			*/
			
			
		}
	}
	IB.end();
    return true;
}

void Terrain::shader( BaseShader* shader, bool deleteOnDestruction )
{
    BaseModel::shader(shader, deleteOnDestruction);
}

void Terrain::draw(const BaseCamera& Cam)
{
    applyShaderParameter();
    BaseModel::draw(Cam);
	VB.activate();
	IB.activate();
	//glDrawArrays(GL_TRIANGLES, 0, IB.indexCount());
	glDrawElements(GL_TRIANGLES, IB.indexCount(), IB.indexFormat(), 0);
	IB.deactivate();
	VB.deactivate();
}

void Terrain::applyShaderParameter()
{
    TerrainShader* Shader = dynamic_cast<TerrainShader*>(BaseModel::shader());
    if(!Shader)
        return;
    
    Shader->mixTex(&MixTex);
    for(int i=0; i<2; i++)
        Shader->detailTex(i,&DetailTex[i]);
    Shader->scaling(Size);
    
    // TODO: add additional parameters if needed..
}
