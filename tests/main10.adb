with Ada.Text_IO; use Ada.Text_IO;
with Ada.Integer_Text_IO; use Ada.Integer_Text_IO;

procedure Main10 is
   N : Integer;
   X : Integer := 0;
   Y : Integer := 1;
   Z : Integer;
   I : Integer;
begin
   Get(N);
   if N = 0 or N = 1 then
	Put(N);
   else
	I := 2;
	while (I <= N) loop
		I := I + 1;
		Z := X + Y;
		X := Y;
		Y := Z;
	end loop;
	Put(Z);
   end if;
end Main10;

