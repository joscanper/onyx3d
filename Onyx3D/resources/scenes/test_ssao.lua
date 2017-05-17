
include("resources/resources.lua")

skybox("sky")
	set_material("mat_sky")


default_camera("main_camera")
    set_position(0,0.7,1.5)
    set_rotation(0,0,0)

--[[
grid("grid");
	set_position(-5,0.01,-5)
	set_material("grey")
]]

ambient_light(0.1,0.1,0.1)

node("pivot")
	set_rotation(0,0,0)



--texture("tilesD", "resources/textures/floor1/diffuse.jpg")
texture("testD", "resources/textures/test_wallD.jpg")
texture("testN", "resources/textures/test_wallN.jpg")
texture("testH", "resources/textures/test_wallH.jpg")
--texture("testN", "resources/textures/test_normals2.jpg")
default_material("mat_test")
	set_mat_texture("diffuse", "testD", 0)
	--set_mat_texture("specular", "tilesR", 1)
	set_mat_texture("normal", "testN", 2)
	----set_mat_cubemap("environment", "skymap", 3)
	set_mat_texture("height", "testH", 4)
	--set_mat_float("reflectivity",1.8)
	--set_mat_float("fresnel",1)
	--set_mat_float("shininess",32)
	set_mat_float("heightScale",0.08)

default_material("mat_testN")
	set_mat_texture("diffuse", "o3d_textures/white", 0)
	--set_mat_texture("specular", "tilesR", 1)
	set_mat_texture("normal", "testN", 2)
	----set_mat_cubemap("environment", "skymap", 3)
	--set_mat_texture("height", "testH", 4)
	--set_mat_float("reflectivity",1.8)
	--set_mat_float("fresnel",1)
	--set_mat_float("shininess",32)
	set_mat_float("heightScale",0.0)


default_material("mat_teapot")
	set_mat_texture("specular", "o3d_textures/white", 1)
	set_mat_cubemap("environment", "skymap",3)
	set_mat_float("reflectivity",1)
	set_mat_float("fresnel",0.8)
	set_mat_vec4("color",1,0.3,0.3,1)
	
model("teapot", "resources/models/teapot.obj")
	set_model_material("teapot.005","mat_teapot")


for x=1,1 do
	for y=1,1 do
		model_instance("teapot"..x.."-"..y, "teapot")
			set_position(x*1.25-3.5,0,y*1.25-3.5)
	end
end	
--[[
get_material("mat_floor")
	set_mat_float("reflectivity", 2)
	set_mat_cubemap("environment", "skymap", 3)
	set_mat_float("fresnel",0.8)
	set_mat_float("shininess",32)
	set_mat_texture("diffuse", "o3d_textures/white", 0)
	set_mat_texture("specular", "tilesS", 1)

for x=1,10 do
	for y=1,10 do
		quad("floor"..x.."-"..y)
			set_rotation(-90,0,0)
			set_material("mat_floor")
			set_position(x-5.5,0,y-5.5)
	end
end
]]

water("wat")
	set_scale(10,1,10)

model("cyl", "resources/models/blocky.obj")
	set_model_material("Cube", "mat_test")

model_instance("testcube", "cyl")
	set_position(0,0.5,0)
	set_scale(0.5,0.5,0.5)

cube("tsc")
	set_material("mat_test")
	set_position(2,0,2)
	set_rotation(-45,0,0)
	set_scale(1,3,1)

dir_light("light")
	set_position(-5,3,0)
	set_rotation(45,90,0)
	set_light_shadows(512, 0.01, 20, 6)
	set_parent("pivot")
--[[
point_light("light")
	set_scale(0.2,0.2,0.2)

	set_position(-2,0.5,0)
	set_parent("pivot")
]]
octa("lightsource")
	set_parent("light")
	set_material("white")
	set_local_position(0,0,0)


