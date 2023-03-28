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

struct SpotLight {
	vec3 position;
	vec3 direction;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	vec3 coefs;

	float cut_off;
	float outer_cut_off;
};

struct Material
{
	vec3 color;
	sampler2D diffuse_map;
	sampler2D specular_map;
	float shininess;
	int maps_mask; // 0 bit - diffuse; 1 bit - specular
};

vec3 calcPointLight(PointLight light, vec3 normal, vec3 viewDir);
vec3 calcDirLight(DirLight light, vec3 normal, vec3 viewDir);
vec3 calcSpotLight(SpotLight light, vec3 normal, vec3 viewDir);

out vec4 out_color;

in vec3 normal;
in vec2 tex_coord;
in vec3 frag_pos;
in vec3 view_pos;

uniform Material material;

#define LIGHTS_NR 4
uniform uint point_lights_count;
uniform uint spot_lights_count;
uniform PointLight point_lights[LIGHTS_NR];
uniform SpotLight spot_lights[LIGHTS_NR];
uniform DirLight dir_light;

Colors frag_colors;

void main() 
{
	vec3 norm = normalize(normal);
	vec3 view_dir = normalize(view_pos - frag_pos);

	frag_colors.ambient = material.color;
	frag_colors.diffuse = material.color;
	frag_colors.specular = material.color;
	if((material.maps_mask & 1) != 0)
	{
		vec3 base_color = texture(material.diffuse_map, tex_coord).rgb;

		frag_colors.ambient = base_color;
		frag_colors.diffuse = base_color;
		frag_colors.specular = base_color;
	}
	if((material.maps_mask & 2) != 0)
		frag_colors.specular = texture(material.specular_map, tex_coord).rgb;

	vec3 result = calcDirLight(dir_light, norm, view_dir);
	for (uint i = 0u; i < point_lights_count; i++)
		result += calcPointLight(point_lights[i], norm, view_dir);
	for (uint i = 0u; i < spot_lights_count; i++)
		result += calcSpotLight(spot_lights[i], norm, view_dir);
	

	out_color = vec4(result, 1);
}

vec3 calcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
	vec3 light_dir = normalize(-light.direction);
	float diff = max(dot(normal, light_dir), 0.0);
	vec3 reflectDir = reflect(-light_dir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 ambient  = light.ambient  * frag_colors.ambient;
	vec3 diffuse  = light.diffuse  * diff * frag_colors.diffuse;
	vec3 specular = light.specular * spec * frag_colors.specular;

	return (ambient + diffuse + specular);
}

vec3 calcPointLight(PointLight light, vec3 normal, vec3 viewDir) 
{
	vec3 light_dir = normalize(light.position - frag_pos);

	float diff = max(dot(normal, light_dir), 0.0);

	vec3 reflectDir = reflect(-light_dir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

	float distance = length(light.position - frag_pos);
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

vec3 calcSpotLight(SpotLight light, vec3 normal, vec3 viewDir)
{
	vec3 light_dir = normalize(light.position - frag_pos);
	float theta = dot(light_dir, -normalize(light.direction));
	float epsilon   = light.cut_off - light.outer_cut_off;
	float intensity = clamp((theta - light.outer_cut_off) / epsilon, 0.0, 1.0);

	if(theta <= light.outer_cut_off) 
	{       
		return light.ambient * frag_colors.ambient;
	}

	float diff = max(dot(normal, light_dir), 0.0);

	vec3 reflectDir = reflect(-light_dir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

	float distance = length(light.position - frag_pos);
	float attenuation = 1.0 / (light.coefs.x + light.coefs.y * distance +
									light.coefs.y * (distance * distance));

	vec3 ambient = light.ambient * frag_colors.ambient;
	vec3 diffuse = light.diffuse * diff * frag_colors.diffuse;
	vec3 specular = light.specular * spec * frag_colors.specular;
	ambient *= attenuation;
	diffuse *= attenuation * intensity;
	specular *= attenuation * intensity;

	return (ambient + diffuse + specular);
}