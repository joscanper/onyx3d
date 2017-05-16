
include("resources/resources.lua")


skybox("sky")
	set_material("mat_sky")

grid("grid");
	set_position(-5,0.01,-5)
	set_material("grey")

default_camera("main_camera")
    set_position(0,0.7,1.5)
    set_rotation(0,0,0)

ambient_light(0.001,0.001,0.001)

node("pivot")
	set_rotation(0,0,0)
	


get_material("mat_floor")
	set_mat_float("shininess",70)
--[[
cube("floor")
	set_scale(5,0.01,5)
	set_material("mat_floor")

quad("ceiling")
	set_scale(5,5,5)
	set_rotation(90,0,0)
	set_position(0,1,0)
	set_material("mat_floor")
]]

function createCube(index, x, z)
cube("w"..index)
	set_material("mat_wall")
	set_position(x,0.5,z)
end

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


octa("o0")
	set_scale(0.15,0.15,0.15)
	set_parent("pivot")
	set_material("white")
	set_position(0,0.3,1.5)


spot_light("dir_light")
	set_parent("o0")
	set_local_rotation(0,0,0)
	set_light_intensity(0.3)
	set_light_range(3)
	set_light_angle(45)
	set_light_color(1,1,1)
	set_light_specular(2,2,2)
	set_light_shadows(1024, 0.1, 10, 300)
	set_local_position(0,0,0)


for x=1,5 do
	for y=1,5 do
		quad("floor"..x.."-"..y)
			set_rotation(-90,0,0)
			set_material("mat_floor")
			set_position(x-2.5,0,y-2.5)
	end
end

for x=1,5 do
	for y=1,5 do
		quad("ceiling"..x.."-"..y)
			set_rotation(90,0,0)
			set_material("mat_ceiling")
			set_position(x-2.5,1,y-2.5)
	end
end


	
include("resources/models/cobra.model")
model_instance("cobra", "car");
	set_local_scale(0.5,0.5,0.5)


texture("fence", "resources/textures/fence.png")
default_material("mat_fence","CUTOUT")
	set_mat_texture("diffuse", "fence", 0)


cube("cuby")
	set_scale(1,1,0.01)
	set_position(-1.2,0.5,0)
	set_material("mat_fence")

cube("cuby2")
	set_scale(1,1,0.01)
	set_position(1.2,0.5,0)
	set_material("mat_fence")

cube("pos1")
	set_scale(0.1,1,0.1)
	set_position(-0.7,0.5,0)
	set_material("mat_ceiling")

cube("pos2")
	set_scale(0.1,1,0.1)
	set_position(0.7,0.5,0)
	set_material("mat_ceiling")


