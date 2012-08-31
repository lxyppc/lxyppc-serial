logEdit:clear()
function draw1()
    --gl.Clear(gl.COLOR_BUFFER_BIT);
    gl.PointSize(8.0)
    gl.LineWidth(5)
    gl.Begin("LINES")     
        gl.Color(0.9,0.9,1.0)
        gl.Vertex(0.0,0.0,0.0)
        gl.Color(0.9,0.9,0.0)
        gl.Vertex(1.0,1.0,1.0)

        --gl.Vertex(1.0,1.0,1.0)
        --gl.Vertex(0.0,0.0,0.0)
    gl.End()
    gl.Color(0.0,0.9,0.0)
    
    --glu.NewQuadric():Sphere(1, 20, 20);
    --gl.Rect(-0.5, -0.5, 0.5, 0.5)
end
day = 200

function draw_solar()
    gl.Enable("DEPTH_TEST")
    gl.Clear("COLOR_BUFFER_BIT")
    --gl.MatrixMode("PROJECTION");
    --gl.LoadIdentity();
    --glu.Perspective(75, 1, 1, 400000000);
    --gl.MatrixMode("MODELVIEW");
    --gl.LoadIdentity();
    --glu.LookAt(0, -200000000, 200000000, 0, 0, 0, 0, 0, 1);

    -- 绘制红色的“太阳”
    gl.Color(1.0, 0.0, 0.0);
    --glu.NewQuadric():Sphere(69600000, 20, 20);
    glu.NewQuadric():Sphere(0.1, 20, 20);

    gl.Color(0.0, 0.0, 1.0);
    gl.Rotate(day/360.0*360.0, 0.0, 0.0, -1.0);
    gl.Translate(0.7, 0.0, 0.0);
    glu.NewQuadric():Sphere(0.05, 20, 20);

    -- 绘制黄色的“月亮”
    gl.Color(1.0, 1.0, 0.0);
    gl.Rotate(day/30.0*360.0 - day/360.0*360.0, 0.0, 0.0, -1.0);
    gl.Translate(0.1, 0.0, 0.0);
    glu.NewQuadric():Sphere(0.02, 20, 20);
--[[
    -- 绘制蓝色的“地球”
    gl.Color(0.0, 0.0, 1.0);
    gl.Rotate(day/360.0*360.0, 0.0, 0.0, -1.0);
    gl.Translate(150000000, 0.0, 0.0);
    glu.NewQuadric():Sphere(15945000, 20, 20);
    -- 绘制黄色的“月亮”
    gl.Color(1.0, 1.0, 0.0);
    gl.Rotate(day/30.0*360.0 - day/360.0*360.0, 0.0, 0.0, -1.0);
    gl.Translate(38000000, 0.0, 0.0);
    glu.NewQuadric():Sphere(4345000, 20, 20);
--]]
    gl.Flush();
end

viewer = QGLViewer(mainWindow)
viewer.axisIsDrawn = true
--viewer.gridIsDrawn = true
--gl.PointSize(3.0)
--gl.Disable("LIGHTING")
--viewer.sceneRadius = 0.1
viewer.animateNeeded = function()
    day = day + 1
    if day > 360 then
        day = 0
    end
end
viewer.drawNeeded = draw_solar
viewer:startAnimation()
mdiArea:addSubWindow(viewer):show()