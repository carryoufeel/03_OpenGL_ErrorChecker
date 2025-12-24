		#version 460 core
		out vec4 FragColor;

		uniform sampler2D grassSampler;
		uniform sampler2D landSampler;
		uniform sampler2D noiseSampler;

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
			//FragColor = texture(sampler, uv);
			vec4 grassColor=texture(grassSampler, uv);
			vec4 landColor=texture(landSampler, uv);
			vec4 noiseColor=texture(noiseSampler, uv);

			float weight=noiseColor.r;
			
			//vec4 finalColor=grassColor*(1.0-weight)+landColor*weight;
			//
			vec4 finalColor=mix(grassColor, landColor, weight);
			FragColor =vec4(finalColor.rgb,1.0);
		}