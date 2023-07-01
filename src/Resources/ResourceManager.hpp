#pragma once

#include <string>
#include <vector>
#include <memory>
#include <map>

namespace RenderEngine{
	class Texture2D;
	class ShaderProgram;
}

namespace Game {
	class ResourceManager {
	public:
		static void setExecutablePath(const std::string& executablePath);
		static void unloadAllResources();

		~ResourceManager() = delete;
		ResourceManager() = delete;
		ResourceManager(const ResourceManager&) = delete;
		ResourceManager(ResourceManager&&) = delete;
		ResourceManager& operator=(const ResourceManager&) = delete;
		ResourceManager& operator=(ResourceManager&&) = delete;

		static std::shared_ptr<RenderEngine::ShaderProgram> loadShader(const std::string& shaderName, const std::string& vertexPath, const std::string& fragmentPath);
		static std::shared_ptr<RenderEngine::ShaderProgram> getShader(const std::string& shaderName);
		static std::shared_ptr<RenderEngine::Texture2D> loadTexture(const std::string& textureName, const std::string& texturePath);
		static std::shared_ptr<RenderEngine::Texture2D> getTexture(const std::string& textureName);
		static std::shared_ptr<RenderEngine::Texture2D> loadTextureAtlas(std::string textureName, std::string texturePath, std::vector<std::string> subTextures, const unsigned int width, const unsigned int height);

	private:
		static std::string getFileString(const std::string& relativeFilePath);

		using  ShaderProgramsMap = std::map<const std::string, const std::shared_ptr<RenderEngine::ShaderProgram>>;
		static ShaderProgramsMap m_shaderPrograms;

		using  TexturesMap = std::map<const std::string, std::shared_ptr<RenderEngine::Texture2D>>;
		static TexturesMap m_textures;

		static std::string m_path;
	};
}