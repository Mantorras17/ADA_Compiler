with Ada.Text_IO; use Ada.Text_IO;
with Ada.Integer_Text_IO; use Ada.Integer_Text_IO;

procedure Main6 is
   I : Integer := 1;
   R : Integer := 1;
   N : Integer;
begin
   Get(N);
   while I <= N loop
      R := R * I;
      I := I + 1;
   end loop;
   Put(R);
end Main6;
