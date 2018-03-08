#version 130

in vec4 fColor;
in vec2 fTexCoord;

out vec4 fragColor;



uniform sampler2D textureUnit;

uniform float coeff;

void main() {
    //fragColor = vec4(fColor);
    //fragColor= texture(textureUnit,fTexCoord);
    //fragColor= texture(textureUnit,fTexCoord)*fColor;

    fragColor=texture(textureUnit,fTexCoord)*fColor.b;
    // coeff = uniform passée par l'application (questions précédentes).
    fragColor.g*=(1.0-coeff);
}
