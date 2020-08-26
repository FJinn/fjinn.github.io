Shader "Custom/FirstShader03"
{
    Properties
    {
        _Color ("Color", Color) = (1,1,1,1)
        _MainTex ("Albedo (RGB)", 2D) = "white" {}
        _Scale("Scale",Vector) = (1,1,1,1)
    }
    SubShader
    {
        Tags 
        { 
            "Queue"="Overlay" 
        }

        GrabPass
        {
            "_Background"
        }

        Pass
        {
            CGPROGRAM

            #pragma vertex MyVert
            #pragma fragment MyFrag
            #include "UnityCG.cginc"

            sampler2D _MainTex;
            sampler2D _Background;

            struct VertexData
            {
                float4 position : POSITION;
                float2 uv : TEXCOORD0;
            };

            struct Input
            {
                float4 position : SV_POSITION;
                float4 grabPos : TEXCOORD0;
            };

            float4 _Scale;

            Input MyVert(VertexData v)
            {
                Input Out;
                Out.position = UnityObjectToClipPos(v.position);
                Out.grabPos = ComputeGrabScreenPos(Out.position);

                return Out;
            }

            float4 MyFrag(Input input) : SV_Target
            {
                float4 c = tex2Dproj(_MainTex, input.grabPos / _Scale);

                c.rgb += float3(0.3, 0.3, 0.3);
                c.rgb /= 2;

                return c;
            }

            ENDCG
        }
    }
}
