with Ada.Text_IO; use Ada.Text_IO;
with Ada.Integer_Text_IO; use Ada.Integer_Text_IO;

procedure Main9 is
   N : Integer;
begin
   Get(N);
   if N > 0 then
      Put_Line("Positive");
   elsif N < 0 then
      Put_Line("Negative");
   else 
      Put_Line("Zero");
   end if;
end Main9;
