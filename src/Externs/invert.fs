#version 330
// usa #version 100 para ES2/WebGL
uniform sampler2D texture0;
in vec2 fragTexCoord;
in vec4 fragColor;
out vec4 finalColor;

void main() {
    vec4 c = texture(texture0, fragTexCoord) * fragColor;
    finalColor = vec4(1.2 - c.rgb, c.a);
}