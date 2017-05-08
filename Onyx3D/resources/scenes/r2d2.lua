
texture("r2d2_difusse", "resources/textures/R2D2_Diffuse.jpg");
texture("r2d2_specular", "resources/textures/R2D2_Specular.jpg");

default_material("mat_r2d2");
	set_mat_texture("difusse", "r2d2_difusse", 0)
	set_mat_texture("specular", "r2d2_specular", 1)
	set_mat_texture("normal", "o3d_textures/normal", 2)
	set_mat_float("shininess",1)

model("model_base2", "resources/models/r2-d2.obj")
	set_rotation(0,90,0)
	set_scale(0.003,0.003,0.003)
	set_position(0,0,-0.4)
	set_model_material("Merged_Meshes", "mat_r2d2")