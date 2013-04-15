varying vec3 normal, eyeVec;
#define MAX_LIGHTS 8
#define NUM_LIGHTS 3
varying vec3 lightDir[MAX_LIGHTS];
uniform sampler2D tex;
uniform float alpha = 1.0f;
uniform float discard_blue = 0.0f;
void main (void)
{
  vec4 texel, renderColor;
  vec3 ct;
  texel = texture2D(tex,gl_TexCoord[0].st);
  ct = texel.rgb;


  vec4 final_color = 
       gl_FrontLightModelProduct.sceneColor;
  vec3 N = normalize(normal);
  int i;
  for (i=0; i<NUM_LIGHTS; ++i)
  {  
    vec3 L = normalize(lightDir[i]);
    float lambertTerm = dot(N,L);
    if (lambertTerm > 0.0)
    {
      final_color += 
        gl_LightSource[i].diffuse * 
        gl_FrontMaterial.diffuse * 
        lambertTerm;	
      vec3 E = normalize(eyeVec);
      vec3 R = reflect(-L, N);
      float specular = pow(max(dot(R, E), 0.0), 
                           gl_FrontMaterial.shininess);
      final_color += 
        gl_LightSource[i].specular * 
        gl_FrontMaterial.specular * 
        specular;	
    }
  }
  
  renderColor = vec4(ct, alpha);
  final_color = (final_color * (renderColor)) + (renderColor * 0.5);
  final_color.w = alpha;
  
	if (discard_blue < 0.5)		//Basically if = 0
	{
		
	}
	else if (discard_blue < 1.5)	//Basically if = 1
	{
		if (ct == vec3(0.0,0.0,1.0))
			discard;
	}
	else
	{
		if (ct == vec3(0.0,0.0,1.0))
			discard;
		else
			{
				final_color.w = 0.5 + ((1.0 - ct.z) * 0.5);
			}
	}
  
  gl_FragColor = final_color;			
}
