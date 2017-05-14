
include("resources/resources.lua")
include("resources/demos/dungeon/dungeon.res")

model("mod_metalbars", "resources/demos/dungeon/metalbars.obj")
	set_model_material("grid_Cube.006","mat_metal")
model("mod_metalbarsB", "resources/demos/dungeon/metalbarsB.obj")
	set_model_material("grid_Cube.018","mat_metal")

get_material("mat_wall")
	set_mat_float("shininess",1)


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

ambient_light(0.006,0.008,0.01)

node("pivot")
	set_rotation(0,0,0)


model_instance("cr1", "mod_crossroof")
	set_scale(1.2,1.2,1.2)
	set_position(0,-0.7,0)
model_instance("ar1", "mod_arch")
	set_position(0,0,1.45)
model_instance("ar2", "mod_arch")
	set_position(0,0,-1.45)
model_instance("ar3", "mod_arch")
	set_position(1.45,0,0)
	set_rotation(0,90,0)
model_instance("ar4", "mod_arch")
	set_position(-1.45,0,0)
	set_rotation(0,90,0)

model_instance("co1", "mod_corridor")
	set_position(0,0,2.9)
model_instance("co2", "mod_corridor")
	set_position(0,0,5)
model_instance("co3", "mod_corridor")
	set_position(0,0,-2.7)
	set_rotation(0,180,0)
model_instance("co4", "mod_corridor")
	set_position(0,0,-4.8)
	set_rotation(0,180,0)

model_instance("co41", "mod_corridor")
	set_position(0,0,7)


model_instance("co5", "mod_corridorH")
	set_position(-2.7,0,0)
	set_rotation(0,270,0)
model_instance("co6", "mod_corridorH")
	set_position(-4.8,0,0)
	set_rotation(0,270,0)
model_instance("co7", "mod_corridor")
	set_position(2.7,0,0)
	set_rotation(0,90,0)
model_instance("co8", "mod_corridor")
	set_position(4.8,0,0)
	set_rotation(0,90,0)


quad("q")
	set_rotation(-90,0,0)
	set_position(0,-0.20,0)
	set_scale(3.3,3.3,1)
	set_material("mat_wall")

model_instance("le1", "mod_lightentry")
	set_position(0,0,7)


model_instance("mb1", "mod_metalbars")
	set_position(0,-1,6)
	set_scale(1.5,1.5,1.5)
model_instance("mb2", "mod_metalbarsB")
	set_position(0,-1,1.35)
	set_scale(1.5,1.5,1.5)
----------------------------------
-- LIGHTING ----------------------
----------------------------------

spot_light("center_light")
	set_position(0,4.5,0)
	set_light_angle(25)
	set_rotation(-90,0,0)
	set_light_color(0.6,0.8,1)
	set_light_range(5)
	set_light_intensity(5)
	set_light_shadows(512,0.1,10)

spot_light("light_entry1")
	set_position(0,3.3,7)
	set_light_angle(25)
	set_rotation(-90,0,0)
	set_light_color(0.6,0.8,1)
	set_light_range(5)
	set_light_intensity(3)
	set_light_shadows(256,0.1,10)

dir_light("light")
	set_position(-5,3,0)
	set_rotation(90,0,0)
	set_light_intensity(1)
	set_light_color(0.1,0.1,0.1)
	--set_light_shadows(1024, 0.01, 20, 6)
	set_parent("pivot")

octa("lightsource")
	set_parent("center_light")
	set_local_position(0,0,0)
	


