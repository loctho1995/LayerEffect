/*
 uniform mat4 CC_PMatrix;
 uniform mat4 CC_MVMatrix;
 uniform mat4 CC_MVPMatrix;
 uniform mat3 CC_NormalMatrix;
 uniform vec4 CC_Time;
 uniform vec4 CC_SinTime;
 uniform vec4 CC_CosTime;
 uniform vec4 CC_Random01;
 uniform sampler2D CC_Texture0;
 uniform sampler2D CC_Texture1;
 uniform sampler2D CC_Texture2;
 uniform sampler2D CC_Texture3;
 //CC INCLUDES END
 
 float time = _director->getTotalFrames() * _director->getAnimationInterval();
 setUniformLocationWith4f(_builtInUniforms[GLProgram::UNIFORM_TIME], time/10.0, time, time*2, time*4);
 setUniformLocationWith4f(_builtInUniforms[GLProgram::UNIFORM_SIN_TIME], time/8.0, time/4.0, time/2.0, sinf(time));
 setUniformLocationWith4f(_builtInUniforms[GLProgram::UNIFORM_COS_TIME], time/8.0, time/4.0, time/2.0, cosf(time));
 */

#ifdef GL_ES
precision mediump float;
#endif

varying vec4 v_fragmentColor;
varying vec2 v_texCoord;
varying vec2 v_position;

uniform vec2 resolution;

void main()
{
    vec4 color = vec4(0.0);
    
    //Horizontal Blur
    color += texture2D(CC_Texture0, v_texCoord) * 0.382928;
    
    color += texture2D(CC_Texture0, v_texCoord + vec2(0, -1.0 / resolution.y)) * 0.000229;
    color += texture2D(CC_Texture0, v_texCoord + vec2(0, -2.0 / resolution.y)) * 0.005977;
    color += texture2D(CC_Texture0, v_texCoord + vec2(0, -3.0 / resolution.y)) * 0.060598;
    color += texture2D(CC_Texture0, v_texCoord + vec2(0, -4.0 / resolution.y)) * 0.241732;
    
    color += texture2D(CC_Texture0, v_texCoord + vec2(0, 1.0 / resolution.y)) * 0.241732;
    color += texture2D(CC_Texture0, v_texCoord + vec2(0, 2.0 / resolution.y)) * 0.060598;
    color += texture2D(CC_Texture0, v_texCoord + vec2(0, 3.0 / resolution.y)) * 0.005977;
    color += texture2D(CC_Texture0, v_texCoord + vec2(0, 4.0 / resolution.y)) * 0.000229;
    
    gl_FragColor = vec4(color.rgb, 1.0);
}
