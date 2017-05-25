
include("resources/resources.lua")
include("resources/demos/beach/beach.res")

cubemap("skymap2",
	"resources/skyboxes/1/right.jpg",
	"resources/skyboxes/1/left.jpg",
	"resources/skyboxes/1/top.jpg",
	"resources/skyboxes/1/bottom.jpg",
	"resources/skyboxes/1/back.jpg",
	"resources/skyboxes/1/front.jpg")

material("mat_sky2", "o3d_shaders/skybox");
	set_mat_cubemap("skybox", "skymap2", 0)


skybox("sky")
	set_material("mat_sky2")

model("mod_beach", "resources/demos/beach/beach.obj")
--model("mod_beach", "resources/models/teapot.obj")

model_instance("beach", "mod_beach")

default_camera("main_camera")
    set_position(0,0.7,1.5)
    set_rotation(0,0,0)

--[[
grid("grid");
	set_position(-5,0.01,-5)
	set_material("grey")
]]
ambient_light(0.2,0.2,0.2)

node("pivot")
	set_rotation(0,0,0)

----------------------------------
-- LIGHTING ----------------------
----------------------------------

dir_light("sun")
	set_position(2,5,-7)
	set_rotation(50,20,0)
	set_light_intensity(0.5)
	set_light_color(0.8,0.8,0.5)
	set_light_shadows(1024, 0.01, 50, 15)
	set_parent("pivot")

octa("lightsource")
	set_parent("sun")
	set_local_position(0,0,0)
	set_material("white")
	
water("water",512,512,10)
	set_scale(100,1,100)
	set_position(0,-0.05,0)