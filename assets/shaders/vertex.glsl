		#version 460 core
		layout (location = 0) in vec3 aPos;
		layout (location = 1) in vec3 aColor;
		layout(location = 2) in vec2 aUV;

		uniform float time;
		uniform float speed;

		out vec3 ourColor;
		out vec2 uv;

		void main()
		{
			//float dx = 0.3;
			//float offset = dx * sin(time*speed);
			//gl_Position = vec4(aPos.x+offset,aPos.y,aPos.z,1.0);
			//ourColor = aColor*(cos(time)+1.0)/2.0;

			float scale=1.0/time;
			vec3 sPos=aPos*scale;

			gl_Position = vec4(sPos, 1.0);
			ourColor = aColor;
			//float deltaU=time*speed*0.1;
			//uv = vec2(aUV.x + deltaU, aUV.y);
			uv = aUV;

		}