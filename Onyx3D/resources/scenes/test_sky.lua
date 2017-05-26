
shader("mysky", "resources/shaders/sky.vert", "resources/shaders/sky.frag")
material("mat_sky", "mysky");
sky("sky")
	set_material("mat_sky")


default_camera("main_camera")
    set_position(0,0.7,1.5)
    set_rotation(0,0,0)

ambient_light(0.1,0.1,0.1)
exposure(1)

node("pivot")
	set_rotation(80,0,0)

cube("cube")

dir_light("sun")
	set_parent("pivot");
	set_position(-135,3,0)
	set_rotation(45,25,0)

water("water", 512,512,10)
	set_scale(200,1,200)

--model_instance("s", "o3d_models/skydome")