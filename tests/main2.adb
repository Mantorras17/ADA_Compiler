with Ada.Text_IO; use Ada.Text_IO;
with Ada.Integer_Text_IO; use Ada.Integer_Text_IO;

procedure Main2 is
   Age : Integer;
begin
   Get(Age);
   if Age = 19 then
      Put_Line("Hello, Ada!");
   else
      Put_Line("Hello, stranger!");
   end if;
end Main2;
