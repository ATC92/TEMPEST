// outline.fs
#version 330

in vec2 fragTexCoord;
out vec4 finalColor;

uniform sampler2D texture0; // tu textura
uniform vec2 resolution;    // tamaño de la textura
uniform float outlineThickness; // grosor del borde en píxeles
uniform vec3 outlineColor;      // color del borde

void main()
{
    vec4 color = texture(texture0, fragTexCoord);

    if(color.a > 0.0){
        // pixel dentro de la imagen: dibujar normalmente
        finalColor = color;
        return;
    }

    // Pixel transparente: buscar vecinos opacos
    float alpha = 0.0;
    int radius = int(outlineThickness);
    for(int x=-radius; x<=radius; x++){
        for(int y=-radius; y<=radius; y++){
            vec2 offset = vec2(float(x)/resolution.x, float(y)/resolution.y);
            vec4 sample = texture(texture0, fragTexCoord + offset);
            if(sample.a > 0.0) alpha = 1.0; // si hay un pixel opaco cercano, marcar borde
        }
    }

    finalColor = vec4(outlineColor, alpha);
}
