		#version 460 core

		out vec4 FragColor;

		uniform sampler2D Sampler;
		in vec2 uv;

		void main()
		{
			FragColor = texture(Sampler, uv);
		}