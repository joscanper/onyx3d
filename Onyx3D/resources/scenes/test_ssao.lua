
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

default_material("mat_teapot")
	set_mat_texture("specular", "o3d_textures/white", 1)
	set_mat_cubemap("environment", "skymap",3)
	set_mat_float("reflectivity",1)
	set_mat_float("fresnel",1)
	set_mat_vec4("color",1,0.3,0.3,1)
	

model("teapot", "resources/models/teapot.obj")
	set_model_material("teapot.005","mat_teapot")


for x=1,5 do
	for y=1,5 do
		model_instance("teapot"..x.."-"..y, "teapot")
			set_position(x*1.25-3.5,0,y*1.25-3.5)
	end
end	

for x=1,10 do
	for y=1,10 do
		quad("floor"..x.."-"..y)
			set_rotation(-90,0,0)
			set_material("mat_floor")
			set_position(x-5.5,0,y-5.5)
	end
end


dir_light("light")
	set_position(-5,3,0)
	set_rotation(45,90,0)
	set_light_shadows(1024, 0.01, 20, 6)
	set_parent("pivot")

octa("lightsource")
	set_parent("light")
	set_local_position(0,0,0)


