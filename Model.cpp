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
	bool ret = load(ModelFile);
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
	const aiScene* pScene = aiImportFile(ModelFile, aiProcessPreset_TargetRealtime_Fast | aiProcess_TransformUVCoords);

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

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	//  if (pScene->HasMeshes && pScene->HasTextures) {
	pMeshes = new Mesh[pScene->mNumMeshes];
	for (unsigned int i = 0; i < pScene->mNumMeshes; ++i) {

			pMeshes[i].IB.begin();
			pMeshes[i].VB.begin();
			unsigned int vertice_counter = 0;
			for (unsigned int k = 0; k < pScene->mMeshes[i]->mNumFaces; ++k) {
				
					for (unsigned int l = 0; l < pScene->mMeshes[i]->mFaces[k].mNumIndices; ++l) {

						unsigned int vertex_index = pScene->mMeshes[i]->mFaces[k].mIndices[l];
						aiVector3D bla = pScene->mMeshes[i]->mVertices[vertex_index];

						
						pMeshes[i].VB.addNormal(
						pScene->mMeshes[i]->mNormals[vertex_index].x,
						pScene->mMeshes[i]->mNormals[vertex_index].y,
						pScene->mMeshes[i]->mNormals[vertex_index].z
						);
						/*
						pMeshes[i].VB.addNormal(
							pScene->mMeshes[i]->mVertices[vertex_index].x,
							pScene->mMeshes[i]->mVertices[vertex_index].y,
							pScene->mMeshes[i]->mVertices[vertex_index].z
						);
						*/
						//pMeshes[i].MaterialIdx = pScene->mMeshes[i]->mMaterialIndex;

						pMeshes[i].VB.addColor(Color(0, 255, 0));

						pMeshes[i].VB.addVertex(
							pScene->mMeshes[i]->mVertices[vertex_index].x,
							pScene->mMeshes[i]->mVertices[vertex_index].y,
							pScene->mMeshes[i]->mVertices[vertex_index].z

						);
						pMeshes[i].IB.addIndex(vertice_counter++);
						
					}
				
			}
			/*
			pMeshes[i].VB.addNormal(
				pScene->mMeshes[i]->mVertices[j].x,
				pScene->mMeshes[i]->mVertices[j].y,
				pScene->mMeshes[i]->mVertices[j].z
			);
			pMeshes[i].MaterialIdx = pScene->mMeshes[i]->mMaterialIndex;
			
			pMeshes[i].VB.addColor(Color(0, 255, 0));
			
			pMeshes[i].VB.addVertex(
				pScene->mMeshes[i]->mVertices[j].x,
				pScene->mMeshes[i]->mVertices[j].y,
				pScene->mMeshes[i]->mVertices[j].z
			);
			
			pMeshes[i].IB.addIndex(j);
			*/
		

			pMeshes[i].IB.end();
			pMeshes[i].VB.end();
	}
	//  }
	pMeshes->VB.end();
	pMeshes->IB.end();
	calcBoundingBox(pScene, AABB());
}
void Model::loadMaterials(const aiScene* pScene)
{
	/*
	if (pScene->HasMaterials) {
		pMaterials = new Material[pScene->mNumMaterials];
		for (unsigned int i = 0; i < pScene->mNumMaterials; ++i) {
			pMaterials[i]. = pScene->mMaterials[i]->GetTexture;
		}
	}
	*/
}
void Model::calcBoundingBox(const aiScene* pScene, AABB& Box)
{
	// TODO: Add your code (Exercise 3)
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