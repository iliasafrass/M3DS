#version 130

uniform sampler2D depthTexture;

in vec4 fTexCoord;

out vec4 fragColor;

void main() {

    vec4 texCoord=fTexCoord;

    texCoord.xyz/=texCoord.w; // clip coordinates => ndc

    texCoord.xyz += 1.0;
    texCoord.xyz /= 2.0;


    fragColor=texture(depthTexture,texCoord.xy);

    //3/Exercice2/Question7:
    //fragColor=1.0-clamp(50.0*(1.0-fragColor),0,1);
    if(texCoord.x <= 0 || texCoord.x >= 1 || texCoord.y <= 0 || texCoord.y >= 1 || texCoord.z <= 0 || texCoord.z >= 1)
      fragColor = vec4(0.0,0.0,0.0,0.0);
    else if(texCoord.z-0.001 < fragColor.r)
      fragColor = vec4(0.0,0.0,0.0,0.0);
    else
      fragColor = vec4(0.0,0.0,0.0,0.6);

}
