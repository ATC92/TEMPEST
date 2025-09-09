#version 330
// Use #version 100 for ES2/WebGL
uniform sampler2D texture0;
in vec2 fragTexCoord;
in vec4 fragColor;
out vec4 finalColor;

/**
* @file invert.fs
* @brief Fragment shader to invert the color of a texture.
*
* This shader takes a texture and inverts its RGB channels while preserving the alpha channel.
* The final color is computed by subtracting the RGB values from 1.0.
*
* @note This shader is designed for use with OpenGL or WebGL.
* It assumes that the texture is already bound to the sampler2D uniform `texture0`.
* The `fragTexCoord` provides the texture coordinates,
* and `fragColor` is the color from the vertex shader or previous stage.

* @example
* // Vertex shader should pass fragTexCoord and fragColor to this fragment shader.
* // The texture should be bound to texture0 before rendering.

* @usage
* This shader can be used in a rendering pipeline where you want to apply an inversion
* effect to a texture, such as for visual effects or artistic rendering.

* @note
* Ensure that the texture is in a format compatible with this shader,
* typically an RGBA format where the RGB channels are in the range [0.0, 1.0].
* The shader assumes that the texture is already bound to the `texture0` uniform.

* @warning
* This shader does not handle any special cases for non-standard texture formats.
* It is designed for standard RGBA textures.
* If you use a different format, you may need to adjust the shader accordingly.

* @author ATC92

* @date 2025-05-29

* @version 1.0

*/

void main() {
    vec4 c = texture(texture0, fragTexCoord) * fragColor;
    finalColor = vec4(1.2 - c.rgb, c.a);
}