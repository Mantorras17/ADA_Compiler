with Ada.Text_IO; use Ada.Text_IO;
with Ada.Integer_Text_IO; use Ada.Integer_Text_IO;

procedure Main5 is
   A : Integer;
   B : Integer;
begin
   Get(A);
   Get(B);
   if A < B then
      if B < 100 then
         Put_Line("B is less than 100");
      else
         Put_Line("B is large");
      end if;
   else
      Put_Line("A is not less than B");
   end if;
end Main5;
