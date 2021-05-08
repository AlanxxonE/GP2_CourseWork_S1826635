#version 120

#ifdef GL_ES
precision highp float;
#endif

varying vec2 texCoord0;
varying vec3 normalsPass;

uniform sampler2D diffuse;

uniform vec2 u_lineSize;

uniform float u_speedColor;

vec3 hsb2rgb( in vec3 c )
{
    vec3 rgb = sin(c.x + vec3(3.985,1.653,4.000) * u_speedColor);
    return rgb;
}

float random (in vec2 _st) 
{
    return fract(sin(dot(_st.xy, vec2(12.9898,78.233))) * 43758.5453123);
}

vec2 truchetPattern(in vec2 _st, in float _index)
{
    _index = fract(((_index + (u_speedColor / 2.0))*2.0));

    if (_index > 0.75) {
        _st = vec2(1.0) - _st;
    } else if (_index > 0.5) {
        _st = vec2(1.0-_st.x,_st.y);
    } else if (_index > 0.25) {
        _st = 1.0-vec2(1.0-_st.x,_st.y);
    }
    return _st;
}

void main()
{
    vec2 st = gl_FragCoord.xy / u_lineSize;

    st *= 20.0;

    vec2 ipos = floor(st);  
    vec2 fpos = fract(st);  

    vec2 tile = truchetPattern(fpos, random( ipos ));

    float color = 0.0;

    color = smoothstep(tile.x-0.1,tile.x * 0.893,tile.y)-
            smoothstep(tile.x - 0.1,tile.x+0.1,tile.y);

    vec2 toCenter = vec2(0.5,0.5)-st;
    float angle = atan(toCenter.y,toCenter.x);

    gl_FragColor = fract(mix(texture2D(diffuse, texCoord0),vec4(vec3(color * vec4(hsb2rgb(vec3(1.0 * angle,1.0,1.0)),1.0)),1.0),0.5));

    //float distance = length(abs(st) - sin(u_speedColor));

    //gl_FragColor = fract(mix(texture2D(diffuse, texCoord0) , vec4(hsb2rgb(vec3(1.0 * angle,1.0,1.0)),1.0), 0.1));

	//vec2 st = gl_FragCoord.xy / u_lineSize;
	//gl_FragColor = mix(texture2D(diffuse, texCoord0) , vec4(0.0,st.y,sin(st.x * u_speedColor), 0.5) , 0.1);
	//gl_FragColor = texture2D(diffuse, texCoord0) * vec4(abs(sin(u_speedColor)), abs(sin(u_speedColor * 4.0)), abs(sin(u_speedColor / 2.0)), 0.5);
}
