#version 400

// Attributes passed from the vertex shader
in vec3 position_interp;
in vec3 normal_interp;
in vec4 colour_interp;
in vec3 light_pos;

// Attributes passed with the material file
uniform vec4 ambient_colour_1;
uniform vec4 diffuse_colour_1;
uniform vec4 ambient_colour_2;
uniform vec4 diffuse_colour_2;
uniform vec4 specular_colour;
uniform float phong_exponent;
uniform float timer;
uniform float health;
uniform float maxhealth;

void main() 
{
    // Blinn–Phong shading

	vec4 alphaAdjustment = vec4(1,1,1,1);


    vec3 N, // Interpolated normal for fragment
	     L, // Light-source direction
		 V, // View direction
		 H; // Half-way vector

	// Compute Lambertian lighting Id
    N = normalize(normal_interp);

	L = (light_pos - position_interp);
	L = normalize(L);

	
	
	// Compute specular term for Blinn–Phong shading
	// Initially: V = (eye_position - position_interp);
	V = - position_interp; // Eye position is (0, 0, 0) in view coordinates
    V = normalize(V);

    H = 0.5*(V + L); // Halfway vector
    H = normalize(H);

	float Id = min(max((.4/(3*dot(V, N))), 0.0),.7) * ((abs(sin(timer)/2)+.5));

	alphaAdjustment.a = Id;
	
	

    float spec_angle_cos = max(dot(N, H), 0.0);
	float Is = pow(spec_angle_cos, phong_exponent);
	    
	// Assign light to the fragment
	gl_FragColor = (((ambient_colour_2 + Id*diffuse_colour_2)*(1-(health/maxhealth))) +((ambient_colour_1 + Id*diffuse_colour_1)*health/maxhealth))* alphaAdjustment;

}