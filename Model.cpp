//
//  Model.cpp
//  ogl4
//
//  Created by Philipp Lensing on 21.09.16.
//  Copyright © 2016 Philipp Lensing. All rights reserved.
//

#include "Model.h"
#include "phongshader.h"
#include <list>

Model::Model() : pMeshes(NULL), MeshCount(0), pMaterials(NULL), MaterialCount(0)
{

}
Model::Model(const char* ModelFile, bool FitSize) : pMeshes(NULL), MeshCount(0), pMaterials(NULL), MaterialCount(0)
{
	bool ret = load(ModelFile, FitSize);
	if (!ret)
		throw std::exception();
}
Model::~Model()
{
	// TODO: Add your code (Exercise 3)
	deleteNodes(&RootNode);
}

void Model::deleteNodes(Node* pNode)
{
	if (!pNode)
		return;
	for (unsigned int i = 0; i<pNode->ChildCount; ++i)
		deleteNodes(&(pNode->Children[i]));
	if (pNode->ChildCount>0)
		delete[] pNode->Children;
	if (pNode->MeshCount>0)
		delete[] pNode->Meshes;
}

bool Model::load(const char* ModelFile, bool FitSize)
{
	const aiScene* pScene = aiImportFile(ModelFile, aiProcessPreset_TargetRealtime_Fast | aiProcess_FlipUVs | aiProcess_TransformUVCoords);

	if (pScene == NULL || pScene->mNumMeshes <= 0)
		return false;

	Filepath = ModelFile;
	Path = Filepath;
	size_t pos = Filepath.rfind('/');
	if (pos == std::string::npos)
		pos = Filepath.rfind('\\');
	if (pos != std::string::npos)
		Path.resize(pos + 1);

	loadMeshes(pScene, FitSize);
	loadMaterials(pScene);
	loadNodes(pScene);

	return true;
}

void Model::loadMeshes(const aiScene* pScene, bool FitSize)
{
	float fs_size = 5;
	AABB bb(0, 0, 0, 0, 0, 0);
	AABB fs(-fs_size/2, -fs_size/2, -fs_size/2, fs_size/2, fs_size/2, fs_size/2);
	calcBoundingBox(pScene, bb);
	float factor = 1.0;
	if (FitSize)
		factor = fs.size().length() / bb.size().length();
	this->MeshCount = pScene->mNumMeshes;
	this->pMeshes = new Mesh[this->MeshCount];
	float x, y, z;

	for (int i = 0; i < this->MeshCount; i++) {
		Mesh& eachMesh = this->pMeshes[i];
		eachMesh.MaterialIdx = pScene->mMeshes[i]->mMaterialIndex;
		//Vertices:
		eachMesh.VB.begin();
		for (int j = 0; j < pScene->mMeshes[i]->mNumVertices; j++) {

			eachMesh.VB.addNormal(
				pScene->mMeshes[i]->mNormals[j].x, 
				pScene->mMeshes[i]->mNormals[j].y, 
				pScene->mMeshes[i]->mNormals[j].z
			);

			if (pScene->mMeshes[i]->mTextureCoords[0]) {
				eachMesh.VB.addTexcoord0(
					pScene->mMeshes[i]->mTextureCoords[0][j].x,
					pScene->mMeshes[i]->mTextureCoords[0][j].y
				);
			}

			eachMesh.VB.addVertex(
				pScene->mMeshes[i]->mVertices[j].x* factor,
				pScene->mMeshes[i]->mVertices[j].y* factor,
				pScene->mMeshes[i]->mVertices[j].z* factor
			);

		}
		eachMesh.VB.end();

		//Indices:
		eachMesh.IB.begin();
		for (int j = 0; j < pScene->mMeshes[i]->mNumFaces; j++) {
			for (int k = 0; k < pScene->mMeshes[i]->mFaces[j].mNumIndices; k++) {
				eachMesh.IB.addIndex(pScene->mMeshes[i]->mFaces[j].mIndices[k]);
			}
		}
		eachMesh.IB.end();
	}

}
void Model::loadMaterials(const aiScene* pScene)
{
	
	pMaterials = new Material[pScene->mNumMaterials];
	MaterialCount = pScene->mNumMaterials;
	for (unsigned int i = 0; i < MeshCount; i++)
	{
		unsigned int mtr_idx = pMeshes[i].MaterialIdx;
		for (unsigned int j = 0; j < pScene->mMaterials[mtr_idx]->mNumProperties; j++)
		{
			aiString tex_path;
			aiColor4D ai_color;
			//aiGetMaterialString(pScene->mMaterials[mtr_idx], AI_MATKEY_NAME, &tex_path);

			aiGetMaterialTexture(pScene->mMaterials[mtr_idx], aiTextureType_DIFFUSE, 0, &tex_path);
			std::string s ="../../assets/";
			s+= tex_path.C_Str();
			pMaterials[mtr_idx].DiffTex = Texture::LoadShared(s.c_str());

			aiGetMaterialColor(pScene->mMaterials[mtr_idx], AI_MATKEY_COLOR_DIFFUSE, &ai_color);
			pMaterials[mtr_idx].DiffColor.B = ai_color.b;
			pMaterials[mtr_idx].DiffColor.G = ai_color.g;
			pMaterials[mtr_idx].DiffColor.R = ai_color.r;

			aiGetMaterialColor(pScene->mMaterials[mtr_idx], AI_MATKEY_COLOR_SPECULAR, &ai_color);
			pMaterials[mtr_idx].SpecColor.B = ai_color.b;
			pMaterials[mtr_idx].SpecColor.G = ai_color.g;
			pMaterials[mtr_idx].SpecColor.R = ai_color.r;

			aiGetMaterialColor(pScene->mMaterials[mtr_idx], AI_MATKEY_COLOR_AMBIENT, &ai_color);
			pMaterials[mtr_idx].AmbColor.B = ai_color.b;
			pMaterials[mtr_idx].AmbColor.G = ai_color.g;
			pMaterials[mtr_idx].AmbColor.R = ai_color.r;

			
		}
		
	}

}
void Model::calcBoundingBox(const aiScene* pScene, AABB& Box)
{
	float minX = 0, minY = 0, minZ = 0, maxX = 0, maxY = 0, maxZ = 0;
	for (unsigned int i = 0; i < pScene->mNumMeshes; ++i) {
		for (unsigned int j = 0; j < pScene->mMeshes[i]->mNumVertices; j++)
		{
			float tx = pScene->mMeshes[i]->mVertices[j].x;
			float ty = pScene->mMeshes[i]->mVertices[j].y;
			float tz = pScene->mMeshes[i]->mVertices[j].z;
			
			defineExtremes(tx, maxX, minX);
			defineExtremes(ty, maxY, minY);
			defineExtremes(tz, maxZ, minZ);

		}
	}
	Box = *new AABB(minX, minY, minZ, maxX, maxY, maxZ);
}

void Model::defineExtremes(float point, float &max, float &min) {
	if (point < min + EPSILON)
		min = point;
	else if (point > max - EPSILON)
		max = point;
}

void Model::loadNodes(const aiScene* pScene)
{
	deleteNodes(&RootNode);
	copyNodesRecursive(pScene->mRootNode, &RootNode);
}

void Model::copyNodesRecursive(const aiNode* paiNode, Node* pNode)
{
	pNode->Name = paiNode->mName.C_Str();
	pNode->Trans = convert(paiNode->mTransformation);

	if (paiNode->mNumMeshes > 0)
	{
		pNode->MeshCount = paiNode->mNumMeshes;
		pNode->Meshes = new int[pNode->MeshCount];
		for (unsigned int i = 0; i<pNode->MeshCount; ++i)
			pNode->Meshes[i] = (int)paiNode->mMeshes[i];
	}

	if (paiNode->mNumChildren <= 0)
		return;

	pNode->ChildCount = paiNode->mNumChildren;
	pNode->Children = new Node[pNode->ChildCount];
	for (unsigned int i = 0; i<paiNode->mNumChildren; ++i)
	{
		copyNodesRecursive(paiNode->mChildren[i], &(pNode->Children[i]));
		pNode->Children[i].Parent = pNode;
	}
}

void Model::applyMaterial(unsigned int index)
{
	if (index >= MaterialCount)
		return;

	PhongShader* pPhong = dynamic_cast<PhongShader*>(shader());
	if (!pPhong) {
		std::cout << "Model::applyMaterial(): WARNING Invalid shader-type. Please apply PhongShader for rendering models.\n";
		return;
	}

	Material* pMat = &pMaterials[index];
	pPhong->ambientColor(pMat->AmbColor);
	pPhong->diffuseColor(pMat->DiffColor);
	pPhong->specularExp(pMat->SpecExp);
	pPhong->specularColor(pMat->SpecColor);
	pPhong->diffuseTexture(pMat->DiffTex);
}

void Model::draw(const BaseCamera& Cam)
{
	if (!pShader) {
		std::cout << "BaseModel::draw() no shader found" << std::endl;
		return;
	}
	pShader->modelTransform(transform());

	std::list<Node*> DrawNodes;
	DrawNodes.push_back(&RootNode);

	while (!DrawNodes.empty())
	{
		Node* pNode = DrawNodes.front();
		Matrix GlobalTransform;

		if (pNode->Parent != NULL)
			pNode->GlobalTrans = pNode->Parent->GlobalTrans * pNode->Trans;
		else
			pNode->GlobalTrans = transform() * pNode->Trans;

		pShader->modelTransform(pNode->GlobalTrans);

		for (unsigned int i = 0; i<pNode->MeshCount; ++i)
		{
			Mesh& mesh = pMeshes[pNode->Meshes[i]];
			mesh.VB.activate();
			mesh.IB.activate();
			applyMaterial(mesh.MaterialIdx);
			pShader->activate(Cam);
			glDrawElements(GL_TRIANGLES, mesh.IB.indexCount(), mesh.IB.indexFormat(), 0);
			mesh.IB.deactivate();
			mesh.VB.deactivate();
		}
		for (unsigned int i = 0; i<pNode->ChildCount; ++i)
			DrawNodes.push_back(&(pNode->Children[i]));

		DrawNodes.pop_front();
	}
}

Matrix Model::convert(const aiMatrix4x4& m)
{
	return Matrix(m.a1, m.a2, m.a3, m.a4,
		m.b1, m.b2, m.b3, m.b4,
		m.c1, m.c2, m.c3, m.c4,
		m.d1, m.d2, m.d3, m.d4);
}