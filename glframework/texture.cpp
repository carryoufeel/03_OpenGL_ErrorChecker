#include "texture.h"
#include "../wrapper/chackError.h"
#define STB_IMAGE_IMPLEMENTATION
#include "../application/stb_image.h"

Texture::Texture(const std::string& filePath, unsigned int unit)
{
	mUnit = unit;
	//1 使用stb_image加载图片
	int width, height, channels;
	stbi_set_flip_vertically_on_load(true); //翻转图片y轴
	unsigned char* data = stbi_load(filePath.c_str(), &mWidth, &mHeight, &channels, STBI_rgb_alpha);
	//2 生成纹理对象并激活单元绑定
	GL_CALL(glGenTextures(1, &mTexture));
	GL_CALL(glActiveTexture(GL_TEXTURE0 + mUnit));
	GL_CALL(glBindTexture(GL_TEXTURE_2D, mTexture));
	//3 传输纹理数据
	GL_CALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, mWidth, mHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data));
	//释放数据
	stbi_image_free(data);
	//4 设置纹理过滤方式
	GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
	GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	//5 设置纹理环绕方式
	GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));//U
	GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));//V
}

Texture::~Texture()
{
	if(mTexture!=0)
		GL_CALL(glDeleteTextures(1, &mTexture));
}

void Texture::bind()
{
	GL_CALL(glActiveTexture(GL_TEXTURE0 + mUnit));
	GL_CALL(glBindTexture(GL_TEXTURE_2D, mTexture));
}
