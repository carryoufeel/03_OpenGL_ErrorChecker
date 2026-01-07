		#version 460 core

		layout (location = 0) in vec3 aPos;
		layout(location = 1) in vec2 aUV;
		layout(location = 2) in vec3 aNormal;

		out vec2 uv;
		out vec3 normal;
		out vec3 worldPosition;

		uniform mat4 modelMatrix;
		uniform mat4 viewMatrix;
		uniform mat4 projectionMatrix;

		void main()
		{
			//将输入的顶点位置转化为齐次坐标
			vec4 transformPosition=vec4(aPos,1.0);

			transformPosition=modelMatrix*transformPosition;

			worldPosition=transformPosition.xyz;

			gl_Position = projectionMatrix * viewMatrix * transformPosition;

			uv = aUV;
			normal = aNormal;
		}