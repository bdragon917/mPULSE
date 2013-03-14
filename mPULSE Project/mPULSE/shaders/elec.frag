uniform float ambientGlow;
uniform vec4 color;
uniform float glowStrength;
uniform float ambientGlowHeightScale;
uniform float glowFallOff;
uniform float height;
uniform float sampleDist;
uniform float speed;
uniform float vertNoise;
uniform float time_0_X;
uniform sampler3D Noise;

varying vec2 vTexCoord;

void main(void)
{
   vec2 t = vec2(speed * time_0_X * 0.5871 - vertNoise * abs(vTexCoord.y), speed * time_0_X);

   // Sample at three positions for some horizontal blur
   // The shader should blur fine by itself in vertical direction
   float xs0 = vTexCoord.x - sampleDist;
   float xs1 = vTexCoord.x;
   float xs2 = vTexCoord.x + sampleDist;

   // Noise for the three samples
   float noise0 = texture3D(Noise, vec3(xs0, t)).x;
   float noise1 = texture3D(Noise, vec3(xs1, t)).x;
   float noise2 = texture3D(Noise, vec3(xs2, t)).x;

   // The position of the flash
   float mid0 = height * (noise0 * 2.0 - 1.0) * (1.0 - xs0 * xs0);
   float mid1 = height * (noise1 * 2.0 - 1.0) * (1.0 - xs1 * xs1);
   float mid2 = height * (noise2 * 2.0 - 1.0) * (1.0 - xs2 * xs2);

   // Distance to flash
   float dist0 = abs(vTexCoord.y - mid0);
   float dist1 = abs(vTexCoord.y - mid1);
   float dist2 = abs(vTexCoord.y - mid2);

   // Glow according to distance to flash
   float glow = 1.0 - pow(0.25 * (dist0 + 2.0 * dist1 + dist2), glowFallOff);

   // Add some ambient glow to get some power in the air feeling
   float ambGlow = ambientGlow * (1.0 - xs1 * xs1) * (1.0 - abs(ambientGlowHeightScale * vTexCoord.y));

   gl_FragColor =  (glowStrength * glow * glow + ambGlow) * color;
  
}