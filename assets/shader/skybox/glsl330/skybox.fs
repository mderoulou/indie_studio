
#version 330

in vec3 fragPosition;

uniform samplerCube env;
uniform float time;
uniform vec2 res;

out vec4 finalColor;

const float GAIN = 0.5;
const float LACUNARITY = 2.0;

float rand(vec2 pos)
{
    return (fract(sin(dot(floor(pos), vec2(12.3862, 24.233))) * 41234.23456784));
}

float noise(vec2 pos)
{
    vec2 integer = floor(pos);
    vec2 frac = fract(pos);

    float a = rand(integer);
    float b = rand(integer + vec2(1.0, 0.0));
    float c = rand(integer + vec2(0.0, 1.0));
    float d = rand(integer + vec2(1.0, 1.0));
    vec2 e = frac * frac * (3.0 - 2.0 * frac);

    return (mix(a, b, e.x) + (c - a) * e.y * (1.0 - e.x) + (d - b) * e.x * e.y);
}

float fract_brown_motion(vec2 pos)
{
    float amplitude = 0.3;
    float freq = 1.0;
    float total = 0.0;
    mat2 rot = mat2(cos(0.5), sin(0.5),
                    -sin(0.5), cos(0.50));

    for (int i = 0; i < 4; ++i) {
        total += noise(rot * pos * freq) * amplitude;
        freq *= LACUNARITY;
        amplitude *= GAIN;
    }
    return (total);
}

void main()
{
    vec3 color = vec3(0.0);

    vec2 st = gl_FragCoord.xy / res.xy * 1.0;
    st.x += time / 1.0 - gl_FragCoord.x / 600.0;
    st.y += time / 4.0 + gl_FragCoord.y / 400.0;

    vec2 q = vec2(0.);
    q.x = fract_brown_motion(st + time / 1.0);
    q.y = fract_brown_motion(st + vec2(1.0));

    vec2 r = vec2(0.);
    r.x = fract_brown_motion(st + q + vec2(1.7,9.2) + time / 1.0);
    r.y = fract_brown_motion(st + q + vec2(8.3,2.8) + time / 12.0);

    float f = fract_brown_motion(st+r);

    color = mix(vec3(0.1, 0.6, 0.6), vec3(0.6, 0.6, 0.4), clamp((f*f)*4.0,0.0,1.0));
    color = mix(color, vec3(0.1, 0.1, 0.1), clamp(length(q), 0.0, 1.0));
    color = mix(color, vec3(1., 1., 1.0), clamp(length(r.x), 0.0, 1.0));
    color = mix(color, texture(env, fragPosition).rgb, 0.5);

    gl_FragColor = vec4((f*f*f+.6*f*f+.5*f)*color, 2.0 * f);

    //vec4(vec3(fract_brown_motion(gl_FragCoord.xy / res.xy)), 1.0);
    //
    //vec4(vec3(q.xy, 0), 1.0);


    /*vec2 l = vec2(0.5, 0.5);
    vec2 pos = (gl_FragCoord.xy / res.xy) - l;
    gl_FragColor = vec4(vec3(length(pos)), 1.0);*/

}
