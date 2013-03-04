varying vec3 lightDir,normal;
uniform sampler2D tex;
 
void main()
{
    vec3 ct,cf;
    vec4 texel;
    float intensity,at,af;
 
    texel = texture2D(tex,gl_TexCoord[0].st);
 
    ct = texel.rgb;
    at = texel.a;
	
	if (ct == vec3(0.0,0.0,1.0))
		discard;
	
    gl_FragColor = vec4(ct, at);
 
}
