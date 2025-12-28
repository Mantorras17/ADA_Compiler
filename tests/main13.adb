with Ada.Text_IO; use Ada.Text_IO;
with Ada.Integer_Text_IO; use Ada.Integer_Text_IO;

procedure Main13 is
    N : Integer;
begin
    Get(N);
    if N > 1000 then
	Put_Line("More than a thousand!");
    end if;
    if N >= 0 then
	Put_Line("Not Negative");
    else 
	Put_Line("Negative");
    end if;
end Main13;
