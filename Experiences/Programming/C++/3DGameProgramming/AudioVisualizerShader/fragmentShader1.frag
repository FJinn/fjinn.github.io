precision mediump float;
varying vec4 fColor;
varying vec2 fTexCoord;

uniform sampler2D sampler2d;
uniform float Factor1;
uniform float SpectrumLeftZero;

void main()                           
{     
	float xCenter = 400.0;
	float yCenter = 300.0;

	vec4 texColor = texture2D(sampler2d, fTexCoord);
	vec4 combinedColor;
	combinedColor = fColor * texColor;
	
	vec4 resultColor;

	resultColor.r = mod(combinedColor.r + Factor1, 1.0);
	resultColor.g = mod(combinedColor.g + Factor1, 1.0);
	resultColor.b = mod(combinedColor.b + Factor1, 1.0);
	resultColor.a = combinedColor.a;

	float rainbowWaveLength = 0.025 / 2.0;
	float rainbowAmplitude = 1.0;
	float rainbowAmplitudeControl = 2.0;
	float rainbowR, rainbowG, rainbowB;        
	float rainbowX = gl_FragCoord.x * rainbowWaveLength + Factor1;
	rainbowR = (sin(rainbowX) + rainbowAmplitude) / rainbowAmplitudeControl;
	rainbowB = (sin(rainbowX + 2.0)  + rainbowAmplitude) / rainbowAmplitudeControl;
	rainbowG = (sin(rainbowX + 4.0)  + rainbowAmplitude) / rainbowAmplitudeControl;
	
	vec4 spectrumColor;
	spectrumColor = texColor;
	spectrumColor.r += sin(SpectrumLeftZero + Factor1* 10.0);
	spectrumColor.g = mix(0.7, mod(SpectrumLeftZero + Factor1 * 2.5 , 1.0), 0.7 );
	spectrumColor.b = mix(0.7, mod(spectrumColor.b + Factor1 * 2.5 , 1.0), 0.7);
	spectrumColor.a = texColor.a;
	
	vec4 rainbowColor = vec4(rainbowR, rainbowG, rainbowB, 1.0);

	
	//===========================================

	float gray = (texColor.r + texColor.g + texColor.b) /3.0;
	vec4 grayScale = vec4(gray,gray, gray, 1.0);

	//===========================================
	// sine wave
	
	float amplitude = 50.0;
	if(SpectrumLeftZero > 0.0)
	{
		 amplitude = mix(50.0, 60.0 * sin(Factor1 * 4.0), 1.0);
	}
	float offset = Factor1 * 100.0;
	float frequency = 0.025;
	float lineWidth = 20.0;
	//float haloWidth = 10.0;

	float minLineWidth =  300.0 - lineWidth;
	float maxLineWidth =  300.0 + lineWidth;

	float x = gl_FragCoord.x + offset;
	float xRotation = 0.0; //sin(Factor1)* (gl_FragCoord.x - xCenter);

	// sine wave graph
	// y        = sin x
	float tempX = xRotation + sin(frequency * x) * amplitude;

	// center position + line width + offset sine wave
	float minLinePosY = minLineWidth + tempX;
	float maxLinePosY = maxLineWidth + tempX;
	float midLinePos = (maxLinePosY + minLinePosY) / 2.0;
	
	float distanceFromLineMid = abs(gl_FragCoord.y - midLinePos);

	if(gl_FragCoord.y >= minLinePosY && gl_FragCoord.y <=  maxLinePosY)
	{
		rainbowWaveLength = 0.025 / 4.0;
		rainbowX = gl_FragCoord.x * rainbowWaveLength + Factor1;
		rainbowR = (sin(rainbowX) + rainbowAmplitude) / rainbowAmplitudeControl;
		rainbowB = (sin(rainbowX + 2.0)  + rainbowAmplitude) / rainbowAmplitudeControl;
		rainbowG = (sin(rainbowX + 4.0)  + rainbowAmplitude) / rainbowAmplitudeControl;
	
		rainbowColor = vec4(rainbowR, rainbowG, rainbowB, 1.0);

		rainbowColor.a = 0.7;

		float alpha =  ( lineWidth - distanceFromLineMid) / lineWidth - 0.4;

		if(alpha <= 0.0)
		{
			gl_FragColor = texColor;
		}
		else
		{
			gl_FragColor = mix(texColor, rainbowColor, alpha);
		}

	}
	else
	{
		gl_FragColor = texColor;
		
	}

	//===========================================
	// reset rainbow color

	rainbowWaveLength = 0.025 / 2.0;
	rainbowX = gl_FragCoord.x * rainbowWaveLength + Factor1;
	rainbowR = (sin(rainbowX) + rainbowAmplitude) / rainbowAmplitudeControl;
	rainbowB = (sin(rainbowX + 2.0)  + rainbowAmplitude) / rainbowAmplitudeControl;
	rainbowG = (sin(rainbowX + 4.0)  + rainbowAmplitude) / rainbowAmplitudeControl;
	
	rainbowColor = vec4(rainbowR, rainbowG, rainbowB, 1.0);
	
	rainbowColor.a = 1.0;

	//===========================================

	// curve with 2 circle
	// aFactor = xOffest
	// bFactor = yOffset
	// pow ( (x - aFactor) , 2.0) + pow ( (y - bFactor), 2.0 ) < pow(curveRadius, 2.0)
	// pow ( (x - aFactor - 1.0) , 2.0) + pow ( (y - bFactor), 2.0 ) > pow(curveRadius, 2.0)
	float curveRadius = 280.0;
	curveRadius = pow(curveRadius, 2.0);

	float aFactor = xCenter;
	float bFactor = yCenter;
	// left = -1.0, right = 1.0, size
	float curveXControl = sin(Factor1*5.0) * 20.0;
	// up = 1.0. down = 1.0, size
	float curveYControl = cos(Factor1*5.0) * 20.0;
	// first circle 
	float firstCircle = pow ( (gl_FragCoord.x - aFactor) , 2.0) + pow ( (gl_FragCoord.y - bFactor), 2.0 );
	// second circle 
	float secondCircle = pow ( (gl_FragCoord.x - aFactor + curveXControl) , 2.0) + pow ( (gl_FragCoord.y - bFactor + curveYControl), 2.0 );

	if(firstCircle < curveRadius && secondCircle > curveRadius)
	{
		gl_FragColor = mix(texColor, rainbowColor, 0.4);
	}

	//===========================================

	// circle
	float dTemp = pow(gl_FragCoord.x - xCenter , 2.0)  +  pow(gl_FragCoord.y- yCenter , 2.0);
	float distance = sqrt(dTemp);

	//===========================================

	// for circular sine wave
	// R = radius
	// a = sine wave amplitude
	// n = number of sine wave
	// xc, yc = center point
	// theta = 0 to 360
	
	float R = 100.0;
	float a = mix(10.0, 500.0* SpectrumLeftZero, 0.4);
	if(a > 30.0)
	{// set amplitude limit
		a = 30.0;
	}
	float n = 10.0;
	float circularLineWidth = 2.0;
	// rotate circular sine wave
	float circularSpeed = Factor1 * 10.0;

	//===========================================

	// back to circle
	float changeRadius = R - a;
	
	if(distance <= changeRadius && gl_FragCoord.y >= minLinePosY && gl_FragCoord.y <=  maxLinePosY)
	{
		gl_FragColor = mix(texColor, rainbowColor, ( lineWidth - distanceFromLineMid) / lineWidth);
	}
	
	// inner circle (a background circle for inner moving circle and static circle)
	dTemp = pow(gl_FragCoord.x - xCenter, 2.0)  +  pow(gl_FragCoord.y - yCenter, 2.0);
	distance = sqrt(dTemp);

	changeRadius =  40.0 + SpectrumLeftZero * 100.0;
	if(changeRadius > 70.0)
	{
		changeRadius = 70.0;
	}

	if(distance <= changeRadius)
	{
		//gl_FragColor = mix(texColor, rainbowColor, 0.4);
		gl_FragColor = grayScale;
	}
	
	// inner moving circle
	changeRadius =  40.0;
	float innerCircleSpeed = 10.0;
	float innerCircleMoveRadius = changeRadius * 0.8;
	float circleX = innerCircleMoveRadius * cos(Factor1*innerCircleSpeed + 2.0);
	float circleY = innerCircleMoveRadius * sin(Factor1*innerCircleSpeed + 2.0);

	dTemp = pow(gl_FragCoord.x - xCenter - circleX , 2.0)  +  pow(gl_FragCoord.y - yCenter - circleY , 2.0);
	distance = sqrt(dTemp);

	changeRadius =  10.0;

	if(distance <= changeRadius)
	{
		gl_FragColor = mix(texColor, rainbowColor, 1.0);
	}

	// inner inner circle (static circle at the center)
	dTemp = pow(gl_FragCoord.x - xCenter , 2.0)  +  pow(gl_FragCoord.y - yCenter , 2.0);
	distance = sqrt(dTemp);

	changeRadius =  10.0;

	if(distance <= changeRadius)
	{
		gl_FragColor = mix(texColor, spectrumColor, 0.7);
	}

	//===========================================
	// circular sine wave
	for(float j = -1.0; j < 2.0; j += 2.0)
	{
		// -1 is inverse circular sine wave
		for (float i = 0.0; i<= 1.0; i += 0.005)
		{
			float theta = i * 360.0;

			R = 100.0;

			float xPos = (R + j*(a * sin(n*theta + circularSpeed))) * cos(theta) + xCenter;
			float yPos = (R + j*(a * sin(n*theta + circularSpeed))) * sin(theta) + yCenter;
	
			if(gl_FragCoord.x + circularLineWidth >= xPos && gl_FragCoord.y - circularLineWidth <= yPos &&
				gl_FragCoord.x - circularLineWidth <= xPos && gl_FragCoord.y + circularLineWidth >= yPos 
			)
			{	
				//  if(i <= 0.2)
				//	{
						gl_FragColor = mix(texColor, rainbowColor, 0.8);
				//	}
			}
		}
	}

	//===========================================
	// balls outside the circle
	for (float i = 0.0; i< n + 50.0; i ++)
	{
		float theta = i * 360.0;
		R = 100.0;
		a = 150.0;
		circularSpeed = Factor1 * 5.0 ; //circularSpeed; 

		float xPos = (R + abs(a * sin(n*theta + circularSpeed))) * cos(theta) + xCenter;
		float yPos = (R + abs(a * sin(n*theta + circularSpeed))) * sin(theta) + yCenter;

		dTemp = pow(gl_FragCoord.x - xPos, 2.0)  +  pow(gl_FragCoord.y - yPos, 2.0);
		distance = sqrt(dTemp);

		changeRadius =  5.0;

		if(distance <= changeRadius)
		{
			gl_FragColor = mix(texColor, spectrumColor, 0.7);
		}
	}

	//===========================================
	
	
	//float gray = (texColor.r + texColor.g + texColor.b) /3.0;
	//vec4 grayScale = vec4(gray,gray, gray, 1.0);
	//gl_FragColor = grayScale;

	//===========================================

	// use texture color only
	// gl_FragColor = texture2D(sampler2d, fTexCoord);

} 
