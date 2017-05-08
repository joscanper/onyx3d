
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

texture("wall", "resources/textures/wall.jpg")
texture("floor", "resources/textures/floor.png")
default_material("mat_wall")
	set_mat_texture("diffuse", "wall", 0)
	set_mat_texture("specular", "o3d_textures/white",1)
	set_mat_float("shininess", 1)
default_material("mat_floor")
	set_mat_texture("diffuse", "floor", 0)

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
    set_position(0,0.7,1.5)
    set_rotation(0,0,0)

ambient_light(0.1,0.1,0.1)


node("pivot")
	set_rotation(0,0,0)
	


cube("floor")
	set_scale(5,0.01,5)
	set_material("mat_floor")
cube("ceiling")
	set_scale(5,0.01,5)
	set_position(0,1,0)
	set_material("mat_floor")

function createCube(index, x, z)
cube("w"..index)
	set_material("mat_wall")
	set_position(x,0.5,z)
end

createCube(0,0,0)
	set_scale(0.5,1,0.5)

createCube(10,-2,2)
createCube(11,-1,2)
createCube(12,0,2)
createCube(13,1,2)
createCube(14,2,2)

createCube(20,-2,-2)
createCube(21,-1,-2)
createCube(22,0,-2)
createCube(23,1,-2)
createCube(24,2,-2)

createCube(31,2,-1)
createCube(32,2,0)
createCube(33,2,1)

createCube(41,-2,-1)
createCube(42,-2,0)
createCube(43,-2,1)

function createLight(index, x, z, cr,cg,cb, mat)

octa("o"..index)
	set_scale(0.15,0.15,0.15)
	set_parent("pivot")
	set_material(mat)
	set_position(x,1,z)

spot_light("l"..index)
	set_parent("o"..index)	
	set_light_angle(40)
	set_light_range(1)
	set_light_intensity(3)
	set_local_position(0,0,0)
	set_local_rotation(-90,0,0)
	set_light_color(cr,cg,cb)
	set_light_specular(cr+0.3,cg+0.3,cb+0.3)

end

createLight(0,1,1, 0,1,0, "green")
createLight(1,-1,1, 1,0,0, "red")
createLight(2,0,-1.41, 0,0,1, "blue")



