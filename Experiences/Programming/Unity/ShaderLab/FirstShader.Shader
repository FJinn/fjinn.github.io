// Upgrade NOTE: replaced 'mul(UNITY_MATRIX_MVP,*)' with 'UnityObjectToClipPos(*)'

Shader "Custom/FirstShader"
{
    Properties
    {
        _Tint ("Tint", color) = (1, 1, 1, 1)
        _OutlineThickness ("Outline Thickness", float) = 1
        _OutlineColor ("Outline Color", Color) = (0, 0, 0, 1)
        _OffsetFactor ("Offset Factor", float) = 0
        _HeartValue ("Heart Value", Range(0, 1)) = 0
        _Degree ("Degree", Range(0, 360)) = 0
        _MainTex ("Texture", 2D) = "white" {}
        _NoiseTex ("Noise Texture", 2D) = "white" {}
        _NoiseTexB ("NoiseB Texture", 2D) = "white" {}
        _HeartTex ("Heart Texture", 2D) = "white" {}
    }

    SubShader
    {
        Tags
        {
            "Queue"="Transparent" 
			"IgnoreProjector"="True" 
			"RenderType"="Transparent" 
			"PreviewType"="Plane"
			"CanUseSpriteAtlas"="True"
        }

        Pass
        {
            Cull off
            Blend One OneMinusSrcAlpha 

            CGPROGRAM

            #pragma vertex MyVertex
            #pragma fragment MyFragment

            #include "UnityCG.cginc"

            sampler2D _MainTex;
            sampler2D _NoiseTex;
            sampler2D _NoiseTexB;
            sampler2D _HeartTex;

            fixed4 _OutlineColor;
            float4 _MainTex_TexelSize;
            float _OffsetFactor;
            float _Degree;
            float _OutlineThickness;
            float _HeartValue;
            float4 _Tint;

            struct VertexData
            {
                float4 vertex : POSITION;
                float4 color : COLOR;
                float2 texCoord : TEXCOORD0;
            };

            struct Interpolators
            {
                float4 position : SV_POSITION;
                float4 color : COLOR;
                float2 uv : TEXCOORD0;
            };

            float3x3 ZRotationMatrix(float degrees)
            {
                float alpha = degrees * UNITY_PI / 180.0;
                float sina, cosa;
                sincos(alpha, sina, cosa);
                return float3x3(
                    cosa, -sina, 0,
                    sina,  cosa, 0,
                       0,     0, 1);
            }

            Interpolators MyVertex(VertexData v)
            {
                float4 pos = v.vertex;

                //Rotate
                pos.xyz = mul(ZRotationMatrix(_Degree), pos.xyz);
             
                v.vertex = pos;

                Interpolators inter;
                inter.position = UnityObjectToClipPos(v.vertex);
                inter.color = v.color;
                
                inter.uv = v.texCoord;
                return inter;
            }

            float random (float2 uv)
            {
                return frac(sin(dot(uv,float2(12.9898,78.233)))*43758.5453123);
            }

            float4 MyFragment(Interpolators inter) : SV_TARGET
            {
                float4 c = 0;

                float noiseA = tex2D (_NoiseTex, inter.uv).r;
                float noiseB = tex2D (_NoiseTexB, inter.uv).r;
               
                float4 heartC = tex2D (_HeartTex, inter.uv);

                int signX = 1, signY = 1;

                if (noiseA >= 0.7)
                {
                    signX = -1;
                }
                if (noiseB >= 0.5)
                {
                    signY = -1;
                }

                c = tex2D(_MainTex, inter.uv + fixed2(_MainTex_TexelSize.x * signX, _MainTex_TexelSize.y * signY) * _OffsetFactor * 300 * random(inter.uv));

                float4 upC = 0, downC = 0, leftC = 0, rightC = 0;

                upC = tex2D(_MainTex, inter.uv + fixed2(0, _MainTex_TexelSize.y * _OutlineThickness));
                downC = tex2D(_MainTex, inter.uv - fixed2(0, _MainTex_TexelSize.y * _OutlineThickness));
                rightC = tex2D(_MainTex, inter.uv + fixed2(_MainTex_TexelSize.x * _OutlineThickness, 0));
                leftC = tex2D(_MainTex, inter.uv - fixed2(_MainTex_TexelSize.x * _OutlineThickness, 0));

                half4 outlineC = _OutlineColor;

                outlineC.a *= ceil(c.a);
                outlineC.rgb *= c.a;
                c.rgb *= c.a;
                heartC.rgb *= heartC.a;

                float4 result = lerp(outlineC, c, ceil(upC.a * downC.a * rightC.a * leftC.a));

                if(_OutlineThickness <= 0)
                {
                    result = c;
                }

                heartC *= _HeartValue;

                return (result + heartC) *_Tint;
            }

            ENDCG
        }
    }
}
