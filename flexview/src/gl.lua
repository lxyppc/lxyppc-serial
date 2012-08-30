viewer = QGLViewer(mainWindow)
logEdit:clear()
viewer.axisIsDrawn = true
viewer.gridIsDrawn = true
class "Particle"
function Particle:__init()
   self.pos = QGLVec(0.0,0.0,0.0)
   angle = 2.0 * math.pi *2 * math.random()
   norm  = 0.04 * math.random()
   self.speed = QGLVec(norm*math.cos(angle), norm*math.sin(angle), math.random());
   self.age = 0
   self.ageMax = 50 + 100.0 * math.random()
end

function Particle:draw()
  gl.Color(self.age/self.ageMax, self.age/self.ageMax, 1.0);
  gl.Vertex(self.pos.x,self.pos.y,self.pos.z);
end

function Particle:animate()
  self.speed.z = self.speed.z - 0.05;
  self.pos = self.pos + self.speed * 0.1;

  if self.pos.z < 0.0 then
      self.speed.z = -0.8*self.speed.z;
      self.pos.z = 0.0;
  end

  self.age = self.age + 1
  if self.age >= self.ageMax then
    self:__init()
  end
end

local nbPart = 2000
Particles = {}
for i=1,nbPart do
    Particles[i] = Particle()
end

viewer.animateNeeded = function()
    for i=1,nbPart do
        Particles[i]:animate()
    end
end

function draw1()
  gl.Begin("QUAD_STRIP")
  local i = 0
  local nbSteps = 200.0
  for i=0,nbSteps do
      ratio = i/nbSteps;
      angle = 21.0*ratio;
      c = math.cos(angle);
      s = math.sin(angle);
      r1 = 1.0 - 0.8*ratio;
      r2 = 0.8 - 0.8*ratio;
      alt = ratio - 0.5;
      nor = 0.5;
      up = math.sqrt(1.0-nor*nor);
      gl.Color(1.0-ratio, 0.2 , ratio);
      gl.Normal(nor*c, up, nor*s);
      gl.Vertex({r1*c, alt, r1*s});
      gl.Vertex(r2*c, alt+0.05, r2*s);
   end
  gl.End();
end
function draw2()
    gl.Begin("POINTS")
    for i=1,nbPart do
        Particles[i]:draw()
    end
    gl.End()
end
ss = QGLVec(1,1,1)
ss = ss * 2

viewer.drawNeeded = draw2
viewer:startAnimation()
mdiArea:addSubWindow(viewer):show()
