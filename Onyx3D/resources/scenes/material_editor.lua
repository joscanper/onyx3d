
include("resources/resources.lua")

skybox("sky")
	set_material("mat_sky")


default_camera("main_camera")
    set_position(0,0.7,1.5)
    set_rotation(0,0,0)

ambient_light(0.1,0.1,0.1)

grid("grid");
	set_position(-5,0.01,-5)
	set_material("grey")


node("pivot")
	set_rotation(0,0,0)