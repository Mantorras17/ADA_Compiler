with Ada.Text_IO; use Ada.Text_IO;
with Ada.Integer_Text_IO; use Ada.Integer_Text_IO;

procedure Main8 is
   Text : String (1 .. 255);
   L : Integer;
begin
   Put_Line("Type something:");
   L := 50;
   Get_Line(Text,L);
   Put_Line(Text);
end Main8;
