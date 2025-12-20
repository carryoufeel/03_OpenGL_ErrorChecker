		#version 460 core
		out vec4 FragColor;
		in vec3 ourColor;
		uniform float time;
		uniform vec3 uColor;
		void main()
		{
			//FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
			float intensity = (sin(time)+1.0)/2.0;
			FragColor = vec4(vec3(intensity)+ uColor, 1.0f);
		}