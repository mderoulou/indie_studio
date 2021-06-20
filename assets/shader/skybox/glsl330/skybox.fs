
#version 330

in vec3 fragPosition;

uniform samplerCube env;
uniform float time;

out vec4 finalColor;

void main()
{
    vec3 color = vec3(0.0);
    color = texture(env, fragPosition).rgb;

    color.r = cos(time / 1);
    finalColor = vec4(color, 1.0);
}
