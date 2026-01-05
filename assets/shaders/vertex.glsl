		#version 460 core
		layout (location = 0) in vec3 aPos;
		layout(location = 1) in vec2 aUV;

		uniform float time;
		uniform float speed;

		out vec3 ourColor;
		out vec2 uv;

		uniform mat4 transform;
		uniform mat4 viewMatrix;
		uniform mat4 projectionMatrix;

		void main()
		{
			//float dx = 0.3;
			//float offset = dx * sin(time*speed);
			//float scale=1.0/time;

			//gl_Position = vec4(aPos.x+offset,aPos.y,aPos.z,1.0);
			//ourColor = aColor*(cos(time)+1.0)/2.0;
			//vec3 sPos=aPos*scale;

			vec4 position = vec4(aPos, 1.0);

			position = projectionMatrix * viewMatrix * transform * position;
			//position =viewMatrix * transform * position;
			gl_Position = position;
			//ourColor = aColor;
			//float deltaU=time*speed*0.1;
			uv = aUV;

		}