		#version 460 core

		out vec4 FragColor;

		uniform sampler2D Sampler;
		in vec2 uv;
		in vec3 normal;
		in vec3 worldPosition;
		
		//光源参数
		uniform vec3 lightDirection;
		uniform vec3 lightColor;

		uniform vec3 ambientColor;

		//相机世界位置
		uniform vec3 cameraPosition;

		uniform float specularIntensity;

		void main()
		{
			vec3 objectColor=texture(Sampler,uv).xyz;
			vec3 lightDir=normalize(lightDirection);
			vec3 normalN = normalize(normal);
			vec3 viewDir=normalize(cameraPosition-worldPosition);

			float diffuse=clamp(dot(-lightDir,normalN),0.0,1.0);

			vec3 diffuseColor=lightColor *diffuse* objectColor;
			
			float dotResult=dot(-lightDir,normalN);
			float flag=step(0.0,dotResult);

			vec3 lightReflect=normalize(reflect(lightDir,normalN));

			float specular=clamp(dot(viewDir,lightReflect),0.0,1.0);
			
			specular=pow(specular,32);

			vec3 specularColor=lightColor * specular*flag*specularIntensity;

			vec3 ambientColor=objectColor*ambientColor;

			vec3 finalColor=diffuseColor + specularColor+ambientColor;
			//FragColor=vec4(viewDir,1.0);
			FragColor=vec4(finalColor,1.0);
		}