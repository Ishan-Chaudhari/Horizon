#include "ModelLib.h"
#include "DirectX11.h"
#include "assimp/postprocess.h"
#include "Core/Logger.h"

std::unordered_map<const char*, ModelLib::Model*> ModelLib::ModelStack;
std::vector<ModelLib::Textures*> ModelLib::TextureStack;

Assimp::Importer ModelLib::Model::importer;

uint32_t ModelLib::index = 0;

uint32_t ModelLib::GenTextureIndex()
{
	return index++;
}

void ModelLib::LoadModel(const char* Filepath, const char* ModelName)
{
	if (!ModelStack.contains(ModelName))
	{
		Model* model = new Model();
		model->Create(Filepath);
		ModelStack[ModelName] = model;
	}

}

void ModelLib::RenderModel(const char* ModelName)
{
	ModelStack[ModelName]->Render();
}

void ModelLib::DestroyModel(const char* ModelName)
{
	delete ModelStack[ModelName];
	ModelStack.erase(ModelName);
}

void ModelLib::DestroyLibrary()
{
	for (auto& Model : ModelStack)
	{
		if (ModelStack.find(Model.first) != ModelStack.end())
		{
			delete ModelStack[Model.first];
			ModelStack.erase(Model.first);
		}
	}
}


void ModelLib::Model::LoadData(const aiScene* scene)
{
	uint64_t vN = 0;
	uint64_t iN = 0;

	for (uint64_t i = 0; i < scene->mNumMeshes; i++)
	{
		vN += scene->mMeshes[i]->mNumVertices;
		iN += static_cast<unsigned long long>(scene->mMeshes[i]->mNumFaces) * 3;
	}
	
	Vertex* vertices = new Vertex[vN];
	uint32_t* Indices = new uint32_t[iN];

	int offset = 0;
	int k = 0;
	int l = 0;
	for (uint64_t i = 0; i < scene->mNumMeshes; i++)
	{
		const aiMesh* mesh = scene->mMeshes[i];
		for (uint64_t j = 0; j < mesh->mNumFaces; j++)
		{
			Indices[k++] = mesh->mFaces[j].mIndices[0] + offset;
			Indices[k++] = mesh->mFaces[j].mIndices[1] + offset;
			Indices[k++] = mesh->mFaces[j].mIndices[2] + offset;
		}
		offset += mesh->mNumVertices;

		for (uint64_t j = 0; j < mesh->mNumVertices; j++)
		{
			
			vertices[l].x = mesh->mVertices[j].x;
			vertices[l].y = mesh->mVertices[j].y;
			vertices[l].z = mesh->mVertices[j].z;
			
			if (mesh->HasNormals())
			{
				vertices[l].Nx = mesh->mNormals[j].x;
				vertices[l].Ny = mesh->mNormals[j].y;
				vertices[l].Nz = mesh->mNormals[j].z;
			}
			else
			{
				vertices[l].Nx = 0.f;
				vertices[l].Ny = 0.f;
				vertices[l].Nz = 0.f;
			}
			if (mesh->HasTextureCoords(0))
			{
				vertices[l].Tx = mesh->mTextureCoords[0][j].x;
				vertices[l].Ty = mesh->mTextureCoords[0][j].y;
			}
			else
			{
				vertices[l].Tx = 0.f;
				vertices[l].Ty = 0.f;
			};
			l++;
		}

	}
	
	vb.Create(sizeof(Vertex) * vN, vertices, sizeof(Vertex), BufferType::HzVertexBuffer);
	ib.Create(sizeof(uint32_t) * iN, Indices, sizeof(uint32_t), BufferType::HzIndexBuffer);

	delete[] vertices;
	delete[] Indices;

}
void ModelLib::Model::Create(const char* Filepath)
{
	const aiScene* scene = importer.ReadFile(Filepath, 
		aiProcess_JoinIdenticalVertices | aiProcess_Triangulate | aiProcess_FlipUVs);
	LoadData(scene);
}

void ModelLib::Model::Render()
{
	vb.Bind(); ib.Bind();
	DirectX11::GetContext()->DrawIndexed(ib.GetCount(), 0, 0);
}