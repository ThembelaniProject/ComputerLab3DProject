#version 330 core

struct DirLight
{
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight
{
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};

#define NR_POINT_LIGHTS 6

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;

out vec4 FragColor;

uniform DirLight dirLight;
uniform PointLight pointLights[NR_POINT_LIGHTS];

uniform vec3 viewPos;
uniform vec3 objectColor;

uniform sampler2D texture1;
uniform bool useTexture;

vec3 CalcDirectionalLight(
    DirLight light,
    vec3 normal,
    vec3 viewDir,
    vec3 color)
{
    vec3 lightDir = normalize(-light.direction);

    float diff = max(dot(normal, lightDir), 0.0);

    vec3 reflectDir = reflect(-lightDir, normal);

    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 64.0);

    vec3 ambient = light.ambient * color;

    vec3 diffuse = light.diffuse * diff * color;

    vec3 specular = light.specular * spec * 0.5;

    return ambient + diffuse + specular;
}

vec3 CalcPointLight(
    PointLight light,
    vec3 normal,
    vec3 fragPos,
    vec3 viewDir,
    vec3 color)
{
    vec3 lightDir = normalize(light.position - fragPos);

    float diff = max(dot(normal, lightDir), 0.0);

    vec3 reflectDir = reflect(-lightDir, normal);

    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 64.0);

    float distance = length(light.position - fragPos);

    float attenuation =
        1.0 /
        (
            light.constant +
            light.linear * distance +
            light.quadratic * distance * distance
        );

    vec3 ambient = light.ambient * color;
    vec3 diffuse = light.diffuse * diff * color;
    vec3 specular = light.specular * spec * 0.5;

    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;

    return ambient + diffuse + specular;
}

void main()
{
    vec3 normal = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);

    // Choose between texture and solid colour
    vec3 baseColor = objectColor;

    if (useTexture)
        baseColor = texture(texture1, TexCoord).rgb;

    vec3 result =
        CalcDirectionalLight(
            dirLight,
            normal,
            viewDir,
            baseColor);

    for(int i = 0; i < NR_POINT_LIGHTS; i++)
    {
        result +=
            CalcPointLight(
                pointLights[i],
                normal,
                FragPos,
                viewDir,
                baseColor);
    }

    FragColor = vec4(result, 1.0);
}