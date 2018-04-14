#version 130

in vec3 fN,fL,fV;

out vec4 fragColor;

uniform vec3 materialDiffuse,materialSpecular;
uniform vec4 materialAmbient;

void main() {

    vec3 N,L,V,R;
    vec4 color=vec4(0,0,0,0);
    float specularIntensity = 0;
    float diffuseIntensity;

    V=normalize(fV);
    L=normalize(fL);
    N=normalize(fN);

    //2/question3
    R = 2 * dot(L,N) * N - L;
    R = normalize(R);

    // notez le max pour ne pas éclairer lorsque le produit scalaire est négatif
    diffuseIntensity=max(dot(N,L),0.0);

    //2/question3
    specularIntensity = pow(dot(V,R), 50.0);

    // rouge, vert,bleu de l'éclairement :
    color.rgb=diffuseIntensity*materialDiffuse+materialAmbient.xyz;

    //2/question3
    color.rgb = color.rgb + materialSpecular * specularIntensity;

    // le alpha est porté uniquement par materialAmbient.a.:
    color.a=materialAmbient.a;

    fragColor=color;
}
