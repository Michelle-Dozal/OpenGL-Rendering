varying vec3 normal;
varying vec4 world_position;


void main()
{
    vec4 ambient = vec4(1, 0, 0, 1);
    vec4 diffuse = vec4(0, 1, 0, 1);
    vec4 specular = vec4(0, 0, 1, 1);

       ambient = gl_LightModel.ambient * gl_FrontMaterial.ambient;
    
    vec3 l = normalize(gl_LightSource[0].position.xyz - world_position.xyz);
    
    vec3 r = normalize(-l + 2.0 * dot(l ,normal)*normal);
    /*vec4 x = normalize(vec4(r[0], r[1], r[2], 0));*/
    
     diffuse = gl_FrontMaterial.diffuse * gl_LightSource[0].diffuse * (max(0.0, dot(normal, l))); 
    specular = gl_FrontMaterial.specular * gl_LightSource[0].specular * pow(max(0.0, dot(normalize(-world_position.xyz),r.xyz)),gl_FrontMaterial.shininess);

    




    gl_FragColor = ambient + diffuse + specular;
}
