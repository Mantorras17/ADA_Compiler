with Ada.Text_IO; use Ada.Text_IO;
with Ada.Integer_Text_IO; use Ada.Integer_Text_IO;

procedure Main7 is
   Name : String := Get_Line;
begin
   Put_Line("Hello: ");
   Put_Line(Name);
end Main7;
