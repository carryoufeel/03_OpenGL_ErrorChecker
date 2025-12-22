		#version 460 core
		out vec4 FragColor;

		uniform sampler2D sampler;

		in vec3 ourColor;
		uniform float time;
		uniform vec3 uColor;
		in vec2 uv;

		void main()
		{
			//FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
			//float intensity = (sin(time)+1.0)/2.0;
			//FragColor = vec4(vec3(intensity)+ uColor, 1.0f);
			//FragColor = vec4(ourColor, 1.0f);
			FragColor = texture(sampler, uv);

		}