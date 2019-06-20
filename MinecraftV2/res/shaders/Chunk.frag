#version 330

out vec4 outColor;
in vec2 passTextureCoord;
in float passCardinalLight;

uniform sampler2D texSampler;

void main()
{
    outColor = texture(texSampler, passTextureCoord) * passCardinalLight;
    if (outColor.a == 0) discard;
}