#ifdef GL_ES
precision mediump int;
precision mediump float;
#endif

//фрагментвный шейдер для отрисовки скайбокса

uniform samplerCube texture;
varying vec3 v_texcoord;
vec4 col;
//float x, z;

void main()
{
    col = textureCube(texture, v_texcoord);
    if (col == vec4(1,0,1,1)) col = vec4(0,1,0,1);
    gl_FragColor = col;

//    //cиний
//    if ((x < 0) && (z < 0)) {
//        gl_FragColor = vec4(0,0,1,0);
//    }
//    else if ((x < 0) && (z > 0)) {
//        //красный
//        gl_FragColor = vec4(1,0,0,0);
//    }
//    else if ((x > 0) && (z > 0)) {
//        //зеленый
//        gl_FragColor = vec4(0,1,0,0);
//    }
    //else {
//        //желтый
//        gl_FragColor = vec4(1,1, 0, 0);
        //gl_FragColor = textureCube(texture, v_texcoord);
    //}
}


