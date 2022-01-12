#pragma once
namespace Magnus {
	enum class ShaderType
	{
		NONE = -1,
		VERTEX = 0,
		FRAGMENT = 1
	};
	struct ShaderProgramSource
	{
		std::string vertexSource;
		std::string FragmentSource;
	};
	class Shader
	{
	public:
		virtual ~Shader() = default;
		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;
		virtual const std::string& GetName() const = 0;
		static Ref<Shader> Create(const std::string& filepath);

		static Ref<Shader> Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
	
	};
	class ShaderLibrary
	{
	public:
		void Add(const std::string& name, const Ref<Shader>& shader) {
			if (m_Shaders.find(name) != m_Shaders.end()) {
				MG_CORE_ERROR("Shader {0} already exists!", name);
				MG_CORE_ASSERT(false, "");
			}
			m_Shaders[name] = shader;
		}
		Ref<Shader> Load(const std::string& filepath) {
			auto shader = Shader::Create(filepath);
			auto name = shader->GetName();
			Add(name, shader);
			return shader;
		};
		Ref<Shader> Load(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc) {
			auto shader =  Shader::Create(name, vertexSrc, fragmentSrc);
			Add(name, shader);
			return shader;
		};
		inline Ref<Shader> GetShader(const std::string& name) {
			return m_Shaders[name];
		}
	private:
		std::unordered_map<std::string, Ref<Shader>> m_Shaders;

	};
}
