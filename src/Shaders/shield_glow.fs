// shield_glow.frag
#version 330

in vec2 fragTexCoord;
in vec4 fragColor;

out vec4 finalColor;

uniform sampler2D texture0;

uniform vec2 uDirection;
uniform float uTime;
uniform float uSpeed;
uniform float uWidth;
uniform float uIntensity;
uniform vec3 uColor;
uniform float uOffset;

void main()
{
    vec4 base = texture(texture0, fragTexCoord); // sin fragColor
    vec2 uv = fragTexCoord;

    float proj = dot(uv - vec2(0.5), normalize(uDirection)) + 0.5;
    float pos = mod(uTime * uSpeed + uOffset, 1.0);
    float d = abs(proj - pos);

    float edge0 = 0.0;
    float edge1 = uWidth * 0.5;   // controla la caida lateral
    float mask = 1.0 - smoothstep(edge0, edge1, d);
    mask = pow(mask, 1.5);        // hace mas brillante el centro

    vec3 glow = uColor * mask * uIntensity;
    vec3 outRGB = base.rgb + glow;



    finalColor = vec4(outRGB, base.a);
}
