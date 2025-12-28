with Ada.Text_IO; use Ada.Text_IO;
with Ada.Integer_Text_IO; use Ada.Integer_Text_IO;

procedure Main4 is
   Limit : Integer := 20;
   Count : Integer := 0;
   Flag : String := "check";
begin
   while Count < Limit loop
      if Count*2 <= Limit then
         Put_Line("Half");
      else
         Put_Line("More Than Half");
      end if;
      Put_Line(Flag);
      Count := Count + 1;
   end loop;
end Main4;
