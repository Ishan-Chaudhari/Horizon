#pragma once
#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "Math/DxMath.h"
#include "Buffer.h"
#include <unordered_map>
#include "TextureLib.h"

class ModelLib
{
private:
	class Model
	{
	private:
		struct Vertex
		{
			float x, y, z;
			float Nx, Ny, Nz;
			float Tx, Ty;
		};
		Buffer vb;
		Buffer ib;
		uint32_t TextureIndex;
	private:
		static Assimp::Importer importer;
		void LoadData(const aiScene* scene);
	public:
		void Create(const char* Filepath);
		inline uint32_t GetTextureIndex() { return TextureIndex; }
		void Render();
	};
	class Textures
	{
	
	};
public:
	static void LoadModel(const char* Filepath, const char* ModelName);
	static void RenderModel(const char* ModelName);
	static void DestroyModel(const char* ModelName);
	static void DestroyLibrary();
private:
	static std::unordered_map<const char*, Model*> ModelStack;
	static std::vector<Textures*> TextureStack;
private:
	static uint32_t GenTextureIndex();
	static uint32_t index;
};

