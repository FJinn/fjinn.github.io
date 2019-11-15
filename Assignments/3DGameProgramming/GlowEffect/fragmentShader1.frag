precision mediump float;
varying vec4 fColor;
varying vec2 fTexCoord;

//uniform sampler2D sampler2d;

uniform sampler2D Tex1;  // The texture  (we'll bind to texture unit 0)
uniform sampler2D Tex2;   // The bump-map (we'll bind to texture unit 1)

uniform int uBlurDirection;
uniform float uTextureW;
uniform float uTextureH;

float gaussianFunction(float x)
{
	float variance = 0.15; //x should be 0-1.0 with this variance

	float alpha = -(x*x / (2.0*variance));
	return exp(alpha);
}

float gaussianFunction2D(float x, float y)
{
	float variance = 0.25; //x and y should be 0-1.0 with this variance

	float alpha = -( (x*x+y*y) / (2.0*variance));
	return exp(alpha);
}

void main()
{
	float textureW = uTextureW;
	float textureH = uTextureH;

	float highPassThreshold = 0.95;

	// bloom/blur intensity
	float boxSize = 100.0;
	float totalWeight = 0.0;

	vec4 accumulatedColor;

	if(uBlurDirection == 1) //blur horizontally
	{
		float v = fTexCoord.y;
		float x;

		for(x = -boxSize; x<= boxSize; x+= 2.0)
		{
			float u = fTexCoord.x + x/ textureW;
		
			if(u>= 0.0 && u<=1.0)
			{
				float weight = gaussianFunction(x/boxSize);
				accumulatedColor += texture2D(Tex1, vec2(u,v)) * weight;
				totalWeight += weight;

			}
		}
		
		gl_FragColor = accumulatedColor / totalWeight;
				
	}
	else if(uBlurDirection == 2) // blur vertically
	{
		float u = fTexCoord.x;
		float y;
		for(y = -boxSize; y<= boxSize ; y+= 2.0)
		{
			float v = fTexCoord.y + y/textureH;
			if(v>=0.0 && v<=1.0)
			{
				float weight = gaussianFunction(y/boxSize);
				accumulatedColor += texture2D(Tex1, vec2(u,v)) * weight;
				totalWeight += weight;
			}
		}
		
		gl_FragColor = accumulatedColor / totalWeight;
	}
	else if(uBlurDirection == 10) // for high pass texture
	{
		gl_FragColor = texture2D(Tex1, fTexCoord);
		float average = (gl_FragColor.r + gl_FragColor.g + gl_FragColor.b) / 3.0;

		if(average < highPassThreshold) // threshold
		{
			gl_FragColor = vec4( 0.0, 0.0, 0.0, 1.0);
		}
		else
		{
			gl_FragColor = texture2D(Tex1, fTexCoord);
		}

	}
	else if(uBlurDirection == 100) // combine texture
	{
		vec3 hdrColor = texture2D(Tex1, fTexCoord).rgb;      
		vec3 bloomColor = texture2D(Tex2, fTexCoord).rgb;
		hdrColor += bloomColor; // additive blending
		
		gl_FragColor = vec4(hdrColor, 1.0);
	}
	else //no blur
	{
		gl_FragColor = texture2D(Tex1, fTexCoord);
	}


//====================================================================================================
/*
	float textureW = uTextureW;
	float textureH = uTextureH;

	float radiusSize = 50.0;
	float totalWeight = 0.0;

	vec4 accumulatedColor;

	if(uBlurDirection == 1) //blur
	{
		float x;
		float y;
		float radiusSqr = radiusSize * radiusSize;
		for(x=-radiusSize; x<=radiusSize; x+=1.0)
		{
			float u = fTexCoord.x + x/textureW;
			if(u>=0.0 && u<=1.0)
			{
				for(y=-radiusSize; y<=radiusSize; y+=1.0)
				{
					if(x*x + y*y <= radiusSqr) //filter the pixels that fall within the circle only
					{
						float v = fTexCoord.y + y/textureH;
						if(v>=0.0 && v<=1.0)
						{
							float weight = gaussianFunction2D(x/radiusSize, y/radiusSize);
							accumulatedColor += texture2D(sampler2d, vec2(u,v)) * weight;
							totalWeight += weight;
						}
					}
				}
			}
		}
		
		gl_FragColor = accumulatedColor / totalWeight;
				
	}
	else //no blur
	{
		gl_FragColor = texture2D(sampler2d, fTexCoord);
	}
	*/
}
