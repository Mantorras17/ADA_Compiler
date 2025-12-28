with Ada.Text_IO; use Ada.Text_IO;
with Ada.Integer_Text_IO; use Ada.Integer_Text_IO;

procedure Main11 is
    I : Integer := 0;
begin
    while I < 3 loop
        if I = 0 then
            Put_Line("Faster");
        elsif I = 1 then
            Put_Line("Ok");
        elsif I = 2 then
            Put_Line("Slower");
        end if;

        I := I + 1;
    end loop;
end Main11;
