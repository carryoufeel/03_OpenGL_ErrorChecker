		#version 460 core
		layout (location = 0) in vec3 aPos;
		layout (location = 1) in vec3 aColor;

		uniform float time;
		uniform float speed;
		out vec3 ourColor;
		void main()
		{
			float dx = 0.3;
			float offset = dx * sin(time*speed);
			gl_Position = vec4(aPos.x+offset,aPos.y,aPos.z,1.0);
			ourColor = aColor*(cos(time)+1.0)/2.0;
		}