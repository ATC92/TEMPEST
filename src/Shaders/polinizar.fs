#version 330

in vec2 fragTexCoord;
in vec4 fragColor;

uniform sampler2D textureSampler; 
uniform float fadeIntensity;      
uniform vec4 fadeColor;          

out vec4 finalColor;

void main()
{

    vec4 texelColor = texture(textureSampler, fragTexCoord);
    
    vec4 finalTint = texelColor * fragColor;
    if (finalTint.a < 0.01)
    {
        discard;
    }
    finalColor = mix(finalTint, fadeColor, fadeIntensity);
}