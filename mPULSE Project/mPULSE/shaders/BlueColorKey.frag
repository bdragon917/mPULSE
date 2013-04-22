varying vec3 lightDir,normal;
uniform sampler2D tex;
uniform float sensentiveOffset = 0.0f;
 
void main()
{
    vec3 ct,cf;
    vec4 texel;
    float intensity,at,af;
 
    texel = texture2D(tex,gl_TexCoord[0].st);
 
    ct = texel.rgb;
    at = texel.a;
	
	
	//if (ct == vec3(0.0,0.0,1.0))
	if ((ct.x < (0.05 + sensentiveOffset)) && (ct.y < (0.05 + sensentiveOffset)) && (ct.z > (0.95-sensentiveOffset)))
		discard;
		
	else if ((ct.x < (0.1+sensentiveOffset)) && (ct.y < (0.1+sensentiveOffset)) && (ct.z > (0.8-sensentiveOffset)))
		at = 0.1;
		
	else if ((ct.x < (0.2+sensentiveOffset)) && (ct.y < (0.2+sensentiveOffset)) && (ct.z > (0.7-sensentiveOffset)))
		at = 0.3;
		
	else if ((ct.x < (0.3+sensentiveOffset)) && (ct.y < (0.3+sensentiveOffset)) && (ct.z > (0.6-sensentiveOffset)))
		at = 0.5;
		
	else if ((ct.x < (0.4+sensentiveOffset)) && (ct.y < (0.4+sensentiveOffset)) && (ct.z > (0.4-sensentiveOffset)))
		at = 0.7;
		
		
    gl_FragColor = vec4(ct, at);
 
}
