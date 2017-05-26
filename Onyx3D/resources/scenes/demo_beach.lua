
include("resources/resources.lua")
include("resources/demos/beach/beach.res")

shader("mysky", "resources/shaders/sky.vert", "resources/shaders/sky.frag")
material("mat_sky", "mysky");
sky("sky")
	set_material("mat_sky")

exposure(1)

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
--[[
octa("lightsource")
	set_parent("sun")
	set_local_position(0,0,0)
	set_material("white")
	]]
water("water",512,512,10)
	set_scale(100,1,100)
	set_position(0,-0.05,0)