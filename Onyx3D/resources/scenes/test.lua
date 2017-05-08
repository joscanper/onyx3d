
material("red", "o3d_shaders/unlit_color");
	set_mat_vec4("color", 1,0,0,1)
material("blue", "o3d_shaders/unlit_color");
	set_mat_vec4("color", 0,0,1,1)
material("green", "o3d_shaders/unlit_color");
	set_mat_vec4("color", 0,1,0,1)
material("white", "o3d_shaders/unlit_color");
	set_mat_vec4("color", 1,1,1,1)
material("grey", "o3d_shaders/unlit_color");
	set_mat_vec4("color", 0.5,0.5,0.5,1)



cubemap("skymap",
	"resources/skyboxes/4/right.tga",
	"resources/skyboxes/4/left.tga",
	"resources/skyboxes/4/top.tga",
	"resources/skyboxes/4/bottom.tga",
	"resources/skyboxes/4/back.tga",
	"resources/skyboxes/4/front.tga")
material("mat_sky", "o3d_shaders/skybox");
	set_mat_cubemap("skybox", "skymap", 0)

skybox("sky")
	set_material("mat_sky")


grid("grid");
	set_position(-5,0.01,-5)
	set_material("grey")

default_camera("main_camera")
    set_position(0,1,5)
    set_rotation(0,0,0)

ambient_light(0.4,0.4,0.4)

node("pivot")
	set_rotation(0,0,0)



	--set_parent("pivot")
--	set_scale(0.5,0.5,0.5)
--	set_material("mat_wall")
--[[
texture("r2d2_diffuse", "resources/textures/R2D2_Diffuse.jpg");
texture("r2d2_specular", "resources/textures/R2D2_Specular.jpg");

default_material("mat_r2d2");
	set_mat_texture("diffuse", "r2d2_diffuse", 0)
	set_mat_texture("specular", "r2d2_specular", 1)
	set_mat_texture("normal", "o3d_textures/normal", 2)
	set_mat_float("shininess",1)
	set_mat_float("reflectivity",2)
	set_mat_float("fresnel", 0.3)
	set_mat_cubemap("environment","skymap",3)

--include("resources/Triss/triss.model")
--model_proxy("triss2", "triss");
--	set_parent("pivot")
--	set_position(0,0,0)
]]
--[[
cube("c1")
	set_position(0,0.5,0)
	set_scale(10,1,1)

cube("c2")
	set_position(0,0.5,-1)
	set_scale(3,1,1)


cube("c3")
	set_position(0,0.5,-2)
	set_scale(1,1,3)

cube("c4")
	set_position(-3,0.5,-1)
	set_scale(1,1,3)


cube("c5")
	set_position(2,4,2)
	set_scale(2,8,2)


cube("floor")
	set_position(0,-0.2,0)
	set_scale(100,0.2,100)
]]


texture("car_diffuse","resources/cobra/textures/body_diffuse.png")
texture("car_specular","resources/cobra/textures/body_specular.png")
texture("car_normal","resources/cobra/textures/body_normal_map.png")
default_material("mat_car")
	set_mat_texture("diffuse", "car_diffuse",0)
	set_mat_texture("specular", "car_specular",1)
	set_mat_texture("normal", "car_normal",2)
	set_mat_cubemap("environment", "skymap", 3)
	set_mat_float("reflectivity", 0.5)
	set_mat_float("fresnel", 0.5)

texture("car_diffuse_interior","resources/cobra/textures/interior_diffuse.png")
texture("car_specular_interior","resources/cobra/textures/interior_specular.png")
texture("car_normal_interior","resources/cobra/textures/interior_normal_map.png")
default_material("mat_car_interior")
	set_mat_texture("diffuse", "car_diffuse_interior",0)
	set_mat_texture("specular", "car_specular_interior",1)
	set_mat_texture("normal", "car_normal_interior",2)
	set_mat_cubemap("environment", "skymap", 3)
	set_mat_float("reflectivity", 5)
	set_mat_float("fresnel", 1)

texture("car_diffuse_chrome","resources/cobra/textures/chrome_ao_map.png")
texture("car_specular_chrome","resources/cobra/textures/chrome_specular.png")
texture("car_normal_chrome","resources/cobra/textures/chrome_normal_map.png")
default_material("mat_car_chrome")
	set_mat_vec4("color",0.5,0.5,0.5,1)
	set_mat_texture("diffuse", "car_diffuse_chrome",0)
	set_mat_texture("specular", "car_specular_chrome",1)
	set_mat_texture("normal", "car_normal_chrome",2)
	set_mat_cubemap("environment", "skymap", 3)
	set_mat_float("reflectivity", 5)
	set_mat_float("fresnel", 1)

default_material("mat_car_glass", true)
	set_mat_vec4("color",1,1,1,0)
	set_mat_texture("specular", "o3d_textures/white",2)
	set_mat_cubemap("environment", "skymap", 3)
	set_mat_float("reflectivity", 1)
	set_mat_float("fresnel", 0.7)

texture("car_diffuse_under","resources/cobra/textures/undercarriage_diffuse.png")
texture("car_specular_under","resources/cobra/textures/undercarriage_specular.png")
texture("car_normal_under","resources/cobra/textures/undercarriage_normal_map.png")
default_material("mat_car_under")
	set_mat_texture("diffuse", "car_diffuse_under",0)
	set_mat_texture("specular", "car_specular_under",1)
	set_mat_texture("normal", "car_normal_under",2)
	set_mat_cubemap("environment", "skymap", 3)
	set_mat_float("reflectivity", 1)
	set_mat_float("fresnel", 1)

model("car", "resources/cobra/cobra.obj")
	--set_parent("pivot")
	--set_scale(0.003,0.003,0.003)
	
	set_model_material("body_mesh_Cube.018", "mat_car")
	set_model_material("interior_mesh_Cube.016", "mat_car_interior")
	set_model_material("chrome_metal_mesh_Cube.022", "mat_car_chrome")
	set_model_material("undercarriage_mesh_Cube.012","mat_car_under")
	set_model_material("windshield_mesh_Cube.006","mat_car_glass")
	
model_instance("cobra", "car");
	set_parent("pivot")

model_instance("cobra2", "car");
	set_parent("pivot")
	set_position(1.8,0,0)


--[[
function createLight(index, x,z,r,g,b, material)
	point_light("l"..index)
		set_light_color(r,g,b)
		set_position(x,0.5,z)
    	--set_parent("pivot")

    octa("lightbox"..index)
		set_parent("l"..index)
		set_scale(0.2,0.2,0.2)
		set_material(material)
end

createLight(1,0.7,0.7,1,1,1,"white")
createLight(2,-0.7,0.7,1,1,1,"white")
]]


--[[
model("testmodel2", "resources/models/tank.obj")
	set_scale(0.003,0.003,0.003)
	set_position(-1,0,0)


createLight(1, 1.7,0, 1,0,0, "red");
createLight(2, -1.7,0, 0,1,0, "green");
createLight(3, 0,1.7, 0,0,1, "blue");
createLight(4, 0,-1.7, 1,1,1, "white");
]]



spot_light("point_light")
	set_rotation(90,0,40)
	set_light_intensity(2)
	set_light_range(3)
	set_light_color(0,1,0.0)
	set_light_specular(2,2,2)
	set_position(-5,5,0)


dir_light("dir_light")
	set_rotation(90,0,-40)
	set_light_intensity(2)
	set_light_color(0.5,0.5,0.4)
	set_light_specular(2,2,2)
	set_light_shadows(1024)
	set_position(2,5,0)

octa("lightsource")
	set_scale(0.5,0.5,0.5)
	set_parent("dir_light")
	set_material("white")

cube("floor")
	set_scale(10,0.01,10)

	
--[[

point_light("spotlight")
	set_rotation(-90,0,0)
	--set_light_angle(25)
	set_light_specular(0,1,0)
	set_light_color(0,1,0)
	set_light_range(1)
	set_light_intensity(1)
	set_position(-0.3,0.3,0)

octa("slbox")
	set_material("green")
	set_scale(0.2,0.2,0.2)
	set_parent("spotlight")


point_light("spotlight2")
	set_rotation(0,-45,0)
	--set_light_angle(65)
	set_light_color(1,0,0)
	set_position(-1.7,0,0)
	set_parent("pivot")

octa("sl2box")
	set_material("red")
	set_scale(0.2,0.2,0.2)
	set_parent("spotlight2")
	]]
--[[

function createCube(index,x,y,z,sx,sz)
	cube("wall"..index)
		set_position(x,y,z)
		set_scale(sx,2,sz)
		set_material("mat_wall")
end

createCube(1,4,0,0,2,2);
createCube(2,4,0,2,2,2);
createCube(3,4,0,-2,2,2);
createCube(4,-4,0,0,2,2);
createCube(5,-4,0,2,2,2);
createCube(6,-4,0,-2,2,2);
createCube(7,0,0,3,2,2);
createCube(8,2,0,3,2,2);
createCube(9,-2,0,3,2,2);
createCube(10,0,0,-3,2,2);
createCube(11,2,0,-3,2,2);
createCube(12,-2,0,-3,2,2);
createCube(13,0,0,0,0.5,1);
createCube(14,0,0,0,1,0.5);
createCube(15,0,-2,0,7,7);
createCube(16,0,2,0,7,7);



-- Ceiling
for i=0,5 do
	for j=0,5 do
		quad("ceiling"..i.."-"..j)
			set_position(i-2.5,0.99,j-2.5)
			set_rotation(90,0,0)
			set_scale(1,1,1)
			set_material("mat_ceiling")
	end
end
]]
