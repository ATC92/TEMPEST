#version 330

in vec2 fragTexCoord;
out vec4 finalColor;

uniform sampler2D texture0;
uniform vec2 resolution;
uniform float radius;

void main()
{
    vec4 sum = vec4(0.0);
    float count = 0.0;

    for (float x = -radius; x <= radius; x++)
    {
        for (float y = -radius; y <= radius; y++)
        {
            vec2 offset = vec2(x / resolution.x, y / resolution.y);
            sum += texture(texture0, fragTexCoord + offset);
            count += 1.0;
        }
    }

    finalColor = sum / count;
}
    