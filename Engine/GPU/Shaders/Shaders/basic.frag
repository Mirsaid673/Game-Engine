#version 330 core

struct Colors {
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

struct DirLight {
	vec3 direction;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

struct PointLight {
	vec3 position;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	vec3 coefs;
};

struct Material
{
	vec3 color;
	sampler2D diffuse_map;
	sampler2D specular_map;
	float shininess;
};

vec3 calcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
vec3 calcDirLight(DirLight light, vec3 normal, vec3 viewDir);

out vec4 out_color;

in vec3 normal;
in vec2 tex_coord;
in vec3 frag_pos;
in vec3 view_pos;

uniform Material material;

#define POINT_LIGHTS_NR 4
uniform uint point_lights_count;
uniform PointLight point_lights[POINT_LIGHTS_NR];
uniform DirLight dir_light;

Colors frag_colors;

void main() 
{
	vec3 norm = normalize(normal);
	vec3 view_dir = normalize(view_pos - frag_pos);

	vec3 base_color = texture(material.diffuse_map, tex_coord).rgb;
	frag_colors.ambient = base_color;
	frag_colors.diffuse = base_color;
	frag_colors.specular = base_color;

	vec3 result = calcDirLight(dir_light, norm, view_dir);
	for (uint i = 0u; i < point_lights_count; i++)
		result += calcPointLight(point_lights[i], norm, frag_pos, view_dir);
	

	out_color = vec4(result, 1);
}

vec3 calcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir) 
{
	vec3 lightDir = normalize(light.position - fragPos);

	float diff = max(dot(normal, lightDir), 0.0);

	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

	float distance = length(light.position - fragPos);
	float attenuation = 1.0 / (light.coefs.x + light.coefs.y * distance +
								light.coefs.y * (distance * distance));

	vec3 ambient = light.ambient * frag_colors.ambient;
	vec3 diffuse = light.diffuse * diff * frag_colors.diffuse;
	vec3 specular = light.specular * spec * frag_colors.specular;
	ambient *= attenuation;
	diffuse *= attenuation;
	specular *= attenuation;

	return (ambient + diffuse + specular);
}

vec3 calcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
	vec3 lightDir = normalize(-light.direction);
	float diff = max(dot(normal, lightDir), 0.0);
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 ambient  = light.ambient  * frag_colors.ambient;
	vec3 diffuse  = light.diffuse  * diff * frag_colors.diffuse;
	vec3 specular = light.specular * spec * frag_colors.specular;

	return (ambient + diffuse + specular);
}