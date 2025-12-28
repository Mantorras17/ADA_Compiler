with Ada.Text_IO; use Ada.Text_IO;
with Ada.Integer_Text_IO; use Ada.Integer_Text_IO;

procedure Main3 is
   I : Integer := 0;
begin
   while I < 5 loop
      I := I + 1;
      Put(I);
      Put_Line();
   end loop;
end Main3;
