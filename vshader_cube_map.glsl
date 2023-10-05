#ifdef GL_ES
precision mediump int;
precision mediump float;
#endif

//шейдер для отрисвоки врешин кубмапа
uniform mat4 mvp_matrix;

attribute vec3 a_position;

varying vec3 v_texcoord;

void main()
{
    // считаем позицию точки на экране
    gl_Position = mvp_matrix * vec4(a_position, 1.0);
    //gl_Position = a_position.xyz;
    //так как матричные преобразовния меняют только положние в простанстве (положее камеры)
    //передеем координату без проеброазрваний
    v_texcoord = a_position.xyz;
}
