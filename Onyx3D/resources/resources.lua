

-- BASIC MATERIALS --
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
material("transparent", "o3d_shaders/unlit_color");
    set_mat_vec4("color", 0,0,0,0)

-- BASIC SKYMAP --
cubemap("skymap",
	"resources/skyboxes/4/right.tga",
	"resources/skyboxes/4/left.tga",
	"resources/skyboxes/4/top.tga",
	"resources/skyboxes/4/bottom.tga",
	"resources/skyboxes/4/back.tga",
	"resources/skyboxes/4/front.tga")

material("mat_sky", "o3d_shaders/skybox");
	set_mat_cubemap("skybox", "skymap", 0)


-- OTHER MATERIALS ---

texture("tilesD", "resources/textures/floor1/diffuse.jpg")
texture("tilesS", "resources/textures/floor1/specular.jpg")
texture("tilesN", "resources/textures/floor1/normal.jpg")
texture("tilesH", "resources/textures/floor1/disp.jpg")	
default_material("mat_floor")
	set_mat_texture("diffuse", "tilesD", 0)
	set_mat_texture("specular", "tilesS", 1)
	set_mat_texture("normal", "tilesN", 2)
	set_mat_float("shininess",10)
	set_mat_texture("height", "tilesH",4)
	set_mat_float("heightScale", 0.01)
	set_mat_float("reflectivity",0)

texture("floorD", "resources/textures/floor.png")
texture("floorN", "resources/textures/floor_normal.png")
texture("floorS", "resources/textures/floor_spec.png")	
texture("floorH", "resources/textures/floor_disp.png")	
default_material("mat_ceiling")
	set_mat_texture("diffuse", "floorD", 0)
	set_mat_texture("specular", "floorS",1)
	set_mat_texture("normal", "floorN",2)
	set_mat_texture("height", "floorD",4)
	set_mat_float("shininess",30)
	set_mat_float("heightScale",0.04)

texture("wallD", "resources/textures/wall.png")
texture("wallN", "resources/textures/wall_normal.png")
texture("wallS", "resources/textures/wall_spec.png")
default_material("mat_wall")
	set_mat_texture("diffuse", "wallD", 0)
	set_mat_texture("specular", "wallS",1)
	set_mat_texture("normal", "wallN",2)
	set_mat_float("shininess",10)
