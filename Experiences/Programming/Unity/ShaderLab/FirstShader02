// Upgrade NOTE: replaced 'mul(UNITY_MATRIX_MVP,*)' with 'UnityObjectToClipPos(*)'

Shader "Custom/FirstShader02"
{
    Properties
    {
        _Color ("Color", Color) = (1,1,1,1)
        _TargetPos ("Target Position", vector) = (0,0,0,1)
        _MainTex ("Albedo (RGB)", 2D) = "white" {}
        _MaskTex ("Mask Texture", 2D) = "white" {}
    }
    SubShader
    {
        Tags 
        { 
            "RenderType"="Opaque" 
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
            sampler2D _MaskTex;

            struct Input
            {
                float2 uv_MainTex;
            };

            struct VertexData
            {
                float4 vertex : POSITION;
                float2 texCoord : TEXCOORD0;
            };

            struct Interpolators
            {
                float4 position : SV_POSITION;
                float3 worldPos : TEXCOORD0;
                float2 uv : TEXCOORD1;
                float2 uv_Mask : TEXCOORD2;
            };

            vector _TargetPos;
            fixed4 _Color;
            fixed4 _MaskTex_TexelSize;
            fixed4 _MainTex_TexelSize;
            float4 _MaskTex_ST;

            Interpolators MyVertex(VertexData v)
            {
                Interpolators OUT;
                OUT.position = UnityObjectToClipPos(v.vertex);
                OUT.worldPos = mul(unity_ObjectToWorld, v.vertex);
                OUT.uv = v.texCoord;
                OUT.uv_Mask = v.texCoord * _MaskTex_ST.xy + _MaskTex_ST.zw;

                return OUT;
            }

            float4 MyFragment(Interpolators IN) : SV_TARGET
            {
                float4 c = tex2D(_MainTex, IN.uv);
                float4 m = tex2D(_MaskTex, IN.uv_Mask - _TargetPos.xy * _MainTex_TexelSize * 50);
                
                if(m.a > 0)
                {
                    c += float4(0.3,0.3,0.3, 1);
                    c /= 2;
                }

                return c;
            }

            ENDCG
        }
    }
}
