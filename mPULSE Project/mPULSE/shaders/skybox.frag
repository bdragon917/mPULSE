varying vec3 lightDir,normal;
uniform sampler2D tex;
 
void main()
{
    vec3 ct,cf;
    vec4 texel;
    float intensity,at,af;
    intensity = max(dot(lightDir,normalize(normal)),0.0);
 
    texel = texture2D(tex,gl_TexCoord[0].st);
 
    ct = texel.rgb;
    at = texel.a;
    gl_FragColor = vec4(ct, at);
 
}
