#version 330 core
out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

uniform vec3 viewPos;

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float     shininess;
};

uniform Material material;

struct Light {
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform Light light;

struct DirLight {
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);
uniform int DirLightSize;
#define MAX_DIR_LIGHTS_SIZE 8
uniform DirLight dirLights[MAX_DIR_LIGHTS_SIZE];

struct PointLight {
    vec3 position;

    float constant;
    float linear;
    float quadratic;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
uniform int PointLightSize;
#define MAX_POINT_LIGHTS_SIZE 16
uniform PointLight pointLights[MAX_POINT_LIGHTS_SIZE];

void main()
{
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 result = vec3(0, 0, 0);

    // фаза 1: Направленный источник освещения
    for(int i = 0; i < DirLightSize; i++)
        result += CalcDirLight(dirLights[i], norm, viewDir);
    // фаза 2: Точечные источники
    for(int i = 0; i < PointLightSize; i++)
        result += CalcPointLight(pointLights[i], norm, FragPos, viewDir);
    // фаза 3: фонарик
    //result += CalcSpotLight(spotLight, norm, FragPos, viewDir);

    FragColor = vec4(result, 1.0);
//     // ambient
//     vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));
//
//     // diffuse
//     vec3 norm = normalize(Normal);
//     vec3 lightDir = normalize(light.position - FragPos);
//     float diff = max(dot(norm, lightDir), 0.0);
//     vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));
//
//     // specular
//     vec3 viewDir = normalize(viewPos - FragPos);
//     vec3 reflectDir = reflect(-lightDir, norm);
//     float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
//     vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));
//
//     vec3 result = ambient + diffuse + specular;
//     FragColor = vec4(result, 1.0);
}

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.direction);
    // диффузное освещение
    float diff = max(dot(normal, lightDir), 0.0);
    // освещение зеркальных бликов
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // комбинируем результаты
    vec3 ambient  = light.ambient  * vec3(texture(material.diffuse, TexCoords));
    vec3 diffuse  = light.diffuse  * diff * vec3(texture(material.diffuse, TexCoords));
    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));
    return (ambient + diffuse + specular);
}

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    // диффузное освещение
    float diff = max(dot(normal, lightDir), 0.0);
    // освещение зеркальных бликов
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // затухание
    float distance    = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance +
  			     light.quadratic * (distance * distance));
    // комбинируем результаты
    vec3 ambient  = light.ambient  * vec3(texture(material.diffuse, TexCoords));
    vec3 diffuse  = light.diffuse  * diff * vec3(texture(material.diffuse, TexCoords));
    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));
    ambient  *= attenuation;
    diffuse  *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);
}