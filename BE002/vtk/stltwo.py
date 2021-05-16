import vtk
import time

cone = vtk.vtkConeSource()
cone.SetHeight(50.0)
cone.SetRadius(10.0)
cone.SetResolution(10)

reader = vtk.vtkSTLReader()
reader.SetFileName("arm.stl")

stlMapper = vtk.vtkPolyDataMapper()
stlMapper.SetInputConnection(reader.GetOutputPort())

coneMapper = vtk.vtkPolyDataMapper()
coneMapper.SetInputConnection(cone.GetOutputPort())

coneActor = vtk.vtkActor()
coneActor.SetMapper(coneMapper)
coneActor.GetProperty().SetColor(0.2, 0.63, 0.79)
coneActor.GetProperty().SetDiffuse(0.7)
coneActor.GetProperty().SetSpecular(0.4)
coneActor.GetProperty().SetSpecularPower(20)

property = vtk.vtkProperty()
property.SetColor(0, 1, 0)
property.SetDiffuse(0.7)
property.SetSpecular(0.4)
property.SetSpecularPower(20)

coneActor2 = vtk.vtkActor()
coneActor2.SetMapper(stlMapper)
coneActor2.SetProperty(property)
coneActor2.SetPosition(20, 17, -122)
coneActor2.SetOrigin(-20, -17, 122)
coneActor2.SetMapper(stlMapper)

ren1 = vtk.vtkRenderer()
ren1.AddActor(coneActor)
ren1.AddActor(coneActor2)
ren1.SetBackground(0.1, 0.2, 0.4)

renWin = vtk.vtkRenderWindow()
renWin.AddRenderer(ren1)
renWin.SetSize(600, 600)

coneActor2.RotateX(-90)
coneActor2.RotateZ(90)
coneActor2.RotateX(30)

for i in range(0, 360):
    time.sleep(0.1)
    renWin.Render()
    coneActor2.RotateX(1)
    # ren1.GetActiveCamera().Azimuth(1)
