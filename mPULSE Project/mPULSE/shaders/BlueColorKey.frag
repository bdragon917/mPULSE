varying vec3 lightDir,normal;
uniform sampler2D tex;
uniform float alphaOffset = 0.0f;
uniform float mode = 0;
 
void main()
{
    vec3 ct,cf;
    vec4 texel;
    float intensity,at,af;
 
    texel = texture2D(tex,gl_TexCoord[0].st);
 
    ct = texel.rgb;
    at = texel.a;
	
	
	//if (ct == vec3(0.0,0.0,1.0))
	if ((ct.x < 0.05) && (ct.y < 0.05) && (ct.z > 0.95))
		discard;
		
	else if ((ct.x < 0.1) && (ct.y < 0.1) && (ct.z > 0.8))
		at = 0.1;
		
	else if ((ct.x < 0.2) && (ct.y < 0.2) && (ct.z > 0.7))
		at = 0.3;
		
	else if ((ct.x < 0.3) && (ct.y < 0.3) && (ct.z > 0.6))
		at = 0.5;
		
	else if ((ct.x < 0.4) && (ct.y < 0.4) && (ct.z > 0.4))
		at = 0.7;
		
	at = at + alphaOffset;
	
	if (at < 0)
		at = 0;
		
	//if (mode == 1)
	//	at = 0;
		
    gl_FragColor = vec4(ct, at);
 
}
