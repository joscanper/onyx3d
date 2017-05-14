

draw("bg","o3d_textures/white",50,@H,100,70);
	set_color(0,0,0,0.5)
draw("bgline","o3d_textures/white",0,@H,10,70);
	set_color(0,0,0,0.5)
text("textFPS", ">>", 20,745, 300,50);
	set_color(0,1,0,1)
text("textRender", ">>", 20,730, 300,50);
	set_color(0,1,0,1)
text("textDrawCalls", "DrawCalls:", 20,715, 300,50);
	set_color(0,1,0,1)


--[[
draw("consoleBg","o3d_textures/white",0,140,@W,110);
	set_color(0,0,0,0.5)
draw("consoleLineBg","o3d_textures/white",0,0,@W,30);
	set_color(0,0,0,0.7)

text("consoleText", ">> This is a console entry",20,10,@W,30)

for n=1,7 do
	text("consoleLine"..n, "Console output",20,15 + 30*n,@W,30)
		set_color(0,1,0,1)
end

]]